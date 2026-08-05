
// ===============================================================================
//
// Внимание!!! Не забудьте настроить работу библиотеки
// в файле samsung_ir_decoder_configuration.h !!!
//
// -------------------------------------------------------------------------------
//
// Attention!!! Don't forget to configure the library
// in the samsung_ir_decoder_configuration.h file!!!
//
// ===============================================================================


#include "samsung_ir_decoder.h"


// макроопределение адреса ИК пульта
//
// ------------------------------------------------------------------------------
// macro detection of the IR remote control address
//
#define REMOTE_CONTROL_ADDRESS 0xE0


// макроопределения кодов команд с ИК пульта
//
// ------------------------------------------------------------------------------
// macro definitions of command codes from the IR remote control
//
#define COMMAND_1 0x20
#define COMMAND_2 0xA0
#define COMMAND_3 0x60
#define COMMAND_4 0x10
#define COMMAND_5 0x90
#define COMMAND_6 0x50
#define COMMAND_7 0x30
#define COMMAND_8 0xB0


// функции команд
//
// ------------------------------------------------------------------------------
// command functions
//
inline void Command_1()
{
	PORTB ^= (1 << 0);
}

inline void Command_2()
{
	PORTB ^= (1 << 1);
}

inline void Command_3()
{
	PORTB ^= (1 << 2);
}

inline void Command_4()
{
	PORTB ^= (1 << 3);
}

inline void Command_5()
{
	PORTB ^= (1 << 4);
}

inline void Command_6()
{
	PORTB ^= (1 << 5);
}

inline void Command_7()
{
	PORTB ^= (1 << 6);
}

inline void Command_8()
{
	PORTB ^= (1 << 7);
}



// инициализация GPIO
//
// ------------------------------------------------------------------------------
// GPIO initialize
//
inline void GPIO_Initialize()
{
	DDRB  = 0xFF;
	PORTB = 0xFF;
}



// функция-колбэк, срабатывающая при принятия пакета данных
//
// -------------------------------------------------------------------------------
// callback function that is triggered when a data packet is received
//
void Samsung_IR_Decoder_Callback()
{
	// получение значения данных принятого пакета
	//
	// -------------------------------------------------------------------------------
	// getting the data value of the received packet
	//
	Samsung_IR_Protocol_Data_t samsung_ir = Samsung_IR_Decoder_Get_Data();
	
	
	if ((Samsung_IR_Check_Package_Integrity_For_Standart_Protocol(&samsung_ir)) && (samsung_ir.addr_1 == REMOTE_CONTROL_ADDRESS))
	{
		switch (samsung_ir.commmand_1)
		{
			case COMMAND_1:
			
			if (Samsung_IR_Decoder_Received_Package_Is_Repeated() == false)
			{
				Command_1();
			}
			
			break;
			
			
			case COMMAND_2:
			
			if (Samsung_IR_Decoder_Received_Package_Is_Repeated() == false)
			{
				Command_2();
			}
			
			break;
			
			
			case COMMAND_3:
			
			if (Samsung_IR_Decoder_Received_Package_Is_Repeated() == false)
			{
				Command_3();
			}
			
			break;
			
			
			case COMMAND_4:
			
			if (Samsung_IR_Decoder_Received_Package_Is_Repeated() == false)
			{
				Command_4();
			}
			
			break;
			
			
			case COMMAND_5:
			
			if (Samsung_IR_Decoder_Received_Package_Is_Repeated() == false)
			{
				Command_5();
			}
			
			break;
			
			
			case COMMAND_6:
			
			if (Samsung_IR_Decoder_Received_Package_Is_Repeated() == false)
			{
				Command_6();
			}
			
			break;
			
			
			case COMMAND_7:
			
			if (Samsung_IR_Decoder_Received_Package_Is_Repeated() == false)
			{
				Command_7();
			}
			
			break;
			
			
			case COMMAND_8:
			
			if (Samsung_IR_Decoder_Received_Package_Is_Repeated() == false)
			{
				Command_8();
			}
			
			break;
			
			
			default: break;
		}
	}
}


int main(void)
{
	// инициализация декодера
	//
	// -------------------------------------------------------------------------------
	// decoder initializing
	//
	Samsung_IR_Decoder_Initialize(Samsung_IR_Decoder_Callback);
	

	// инициализация GPIO
	//
	// ------------------------------------------------------------------------------
	// GPIO initialize
	//
	GPIO_Initialize();
	
	
	// не забудьте включить глобальные прерывания
	//
	// -------------------------------------------------------------------------------
	// don't forget to enable global interrupts
	//
	sei();
	
	
	while (1)
	{
	}
}






// ===============================================================================
//
// Внимание!!! Не забудьте настроить работу библиотеки
// в файле nec_ir_decoder_configuration.h !!!
//
// -------------------------------------------------------------------------------
//
// Attention!!! Don't forget to configure the library
// in the nec_ir_decoder_configuration.h file!!!
//
// ===============================================================================


#include "nec_ir_decoder.h"


// макроопределение адреса ИК пульта
//
// ------------------------------------------------------------------------------
// macro detection of the IR remote control address
//
#define REMOTE_CONTROL_ADDRESS 0x04


// макроопределения кодов команд с ИК пульта
//
// ------------------------------------------------------------------------------
// macro definitions of command codes from the IR remote control
//
#define COMMAND_1 0x11
#define COMMAND_2 0x12
#define COMMAND_3 0x13
#define COMMAND_4 0x14
#define COMMAND_5 0x15
#define COMMAND_6 0x16
#define COMMAND_7 0x17
#define COMMAND_8 0x18


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
void NEC_IR_Decoder_Callback()
{
	// получение значения данных принятого пакета
	//
	// -------------------------------------------------------------------------------
	// getting the data value of the received packet
	//
	NEC_IR_Protocol_Data_t nec_ir = NEC_IR_Decoder_Get_Data();
	
	
	if ((NEC_IR_Check_Package_Integrity_For_Standart_Protocol(&nec_ir)) && (nec_ir.addr_1 == REMOTE_CONTROL_ADDRESS))
	{
		switch (nec_ir.command_1)
		{
			case COMMAND_1:
			
			Command_1(); break;
			
			
			case COMMAND_2:
			
			Command_2(); break;
			
			
			case COMMAND_3:
			
			Command_3(); break;
			
			
			case COMMAND_4:
			
			Command_4(); break;
			
			
			case COMMAND_5:
			
			Command_5(); break;
			
			
			case COMMAND_6:
			
			Command_6(); break;
			
			
			case COMMAND_7:
			
			Command_7(); break;
			
			
			case COMMAND_8:
			
			Command_8(); break;
			
			
			default: break;
		}
	}
}


int main(void)
{
	// инициализация декодера
	//
	// Первая передаваемая функция срабатывает при первом принятии
	// пакета NEC протокола; вторая - при повторных принятиях пакета
	//
	// -------------------------------------------------------------------------------
	// decoder initializing
	//
	// first transmitted function is triggered when the NEC protocol
	// packet is received for the first time; the second is triggered
	// when the packet is received again
	//
	NEC_IR_Decoder_Initialize(NEC_IR_Decoder_Callback, NULL);
	

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





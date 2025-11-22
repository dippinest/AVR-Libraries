
// ===============================================================================
//
// Внимание!!! Не забудьте настроить работу библиотеки
// в файле nec_ir_encoder_configuration.h !!!
//
// -------------------------------------------------------------------------------
//
// Attention!!! Don't forget to configure the library
// in the nec_ir_encoder_configuration.h file!!!
//
// ===============================================================================


#include <avr/io.h>

#include "nec_ir_encoder.h"



int main(void)
{
	// инициализация кодера
	//
	// -------------------------------------------------------------------------------
	// encoder initializing
	//
	NEC_IR_Encoder_Initialize();
	
	
	// не забудьте включить глобальные прерывания
	//
	// -------------------------------------------------------------------------------
	// don't forget to enable global interrupts
	//
	sei();
	
	
	// флаг для обработки единоразового нажатия кнопки
	//
	// (для реального проекта я рекомендую использовать
	// библиотеки button.h или virtualbutton.h)
	//
	// -------------------------------------------------------------------------------
	// flag for processing a single button click
	//
	// (for a real project, I recommend using
	// the button.h or virtualbutton.h libraries)
	//
	bool button_flag = true;
	
    while (1) 
    {
		// к выводу PC0 подключена кнопка, подтянутая к GND.
		//
		// Если кнопка нажата (на вывод PC0 поступает логическая единица),
		// передаём пакет данных (адрес - 0x12, команда - 0x34) с повторами.
		// Если кнопка отпущена, прекращаем слать пакеты данных
		//
		// -------------------------------------------------------------------------------
		// a button is connected to the PC0 pin, pulled up to GND.
		//
		// If the button is pressed (a logical unit is sent to the PC0 pin),
		// we transmit a data packet (address - 0x12, command - 0x34) with repeats.
		// If the button is released, we stop sending data packets.
		//
		if ( !(PINC & (1 << 0)) )
		{
			if (button_flag == true)
			{
				NEC_IR_Encoder_Transmit_Standart_Packet(0x12, 0x34, true);
				
				button_flag = false;
			}
		}
		else
		{
			NEC_IR_Encoder_Wait_Complete_And_Stop_Transmittion();
			
			button_flag = true;
		}
    }
}






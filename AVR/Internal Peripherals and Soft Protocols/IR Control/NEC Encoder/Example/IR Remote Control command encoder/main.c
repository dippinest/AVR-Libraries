
// ===============================================================================
//
// Внимание!!! Не забудьте настроить работу библиотеки
// в файле nec_encoder_configuration.h !!!
//
// -------------------------------------------------------------------------------
//
// Attention!!! Don't forget to configure the library
// in the nec_encoder_configuration.h file!!!
//
// ===============================================================================



#include <avr/interrupt.h>

#include <util/delay.h>

#include "nec_encoder.h"


int main(void)
{
	NEC_Encoder_Initialize();
	

	// не забудьте включить глобальные прерывания
	// -------------------------------------------------------------------------------
	// don't forget to enable global interrupts
	sei();
	
	uint8_t ir_nec_command = 0;
	
	while (1)
	{
		// шлём пакет каждые 500 мс
		// -------------------------------------------------------------------------------
		// send a packet every 500 ms
		NEC_Encoder_Transmit_Packet(0x01, ir_nec_command, false); _delay_ms(500);
		
		++ir_nec_command;
	}
}






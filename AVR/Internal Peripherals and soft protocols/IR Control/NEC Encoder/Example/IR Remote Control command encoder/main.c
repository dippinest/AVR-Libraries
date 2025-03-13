

#include <avr/interrupt.h>

#include <util/delay.h>

#include "nec_encoder.h"


int main(void)
{
	NEC_Encoder_Initialize();
	
	NEC_Encoder_FSM_Timer_Interrupt_Initialize();
	
	NEC_Encoder_Carrier_Frequency_Generator_Timer_Initialize();

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





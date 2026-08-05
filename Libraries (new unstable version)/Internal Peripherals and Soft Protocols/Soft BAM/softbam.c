
#include "softbam.h"


void SOFTBAM_Channel_Initialize_Object(SOFTBAM_Channel_t *softbam_channel, uint8_t *port, uint8_t pin, uint8_t duty_cycle)
{
	(*softbam_channel).softbam_channel_port = port;
	(*softbam_channel).softbam_channel_pin  = pin;
	
	(*softbam_channel).softbam_channel_duty_cycle     = duty_cycle;
	(*softbam_channel).softbam_channel_duty_cycle_buf = duty_cycle;
	
	
	*(port) &= ~(1 << pin);
}



void SOFTBAM_Initialize_Object(SOFTBAM_t *softbam, SOFTBAM_Channel_t *channels, const uint8_t num_of_channels, void (*callback_function)(uint8_t prescaler))
{
	(*softbam).channels           = channels;
	(*softbam).num_of_channels    = num_of_channels;
	
	(*softbam).prescaler_callback = callback_function;
}



// ===============================================================================



void SOFTBAM_Processing(SOFTBAM_t *softbam)
{
	uint8_t prescaler = (0b11111111 >> softbam->bits_counter);
	
	softbam->prescaler_callback(prescaler);
	
	
	for (uint8_t i = 0; i < softbam->num_of_channels; ++i)
	{
		if (softbam->bits_counter == 0)
		{
			(softbam->channels[i]).softbam_channel_duty_cycle_buf = (softbam->channels[i]).softbam_channel_duty_cycle;
		}
		
		if ((softbam->channels[i]).softbam_channel_duty_cycle_buf & (1 << (7 - (softbam->bits_counter))))
		{
			*((softbam->channels[i]).softbam_channel_port) |=  (1 << (softbam->channels[i]).softbam_channel_pin);
			
		}
		else
		{
			*((softbam->channels[i]).softbam_channel_port) &= ~(1 << (softbam->channels[i]).softbam_channel_pin);
		}
	}
	
	
	++(softbam->bits_counter);
	
	if (softbam->bits_counter > 7)
	{
		softbam->bits_counter = 0;
	}
}








#include "softbam.h"


SOFTBAM_Channel_t SOFTBAM_Channel_Create_Object(uint8_t *port, uint8_t pin, uint8_t duty_cycle)
{
	SOFTBAM_Channel_t channel;
	
	channel.softbam_channel_port = port;
	channel.softbam_channel_pin  = pin;
	
	channel.softbam_channel_duty_cycle     = duty_cycle;
	channel.softbam_channel_duty_cycle_buf = duty_cycle;
	
	
	*(port) &= ~(1 << pin);
	
	return channel;
}



SOFTBAM_t SOFTBAM_Create_Object(SOFTBAM_Channel_t *channels, const uint8_t num_of_channels, void (*callback_function)(uint8_t prescaler))
{
	SOFTBAM_t bam;
	
	bam.channels           = channels;
	bam.num_of_channels    = num_of_channels;
	bam.prescaler_callback = callback_function;
	
	return bam;
}


// ===============================================================================


void SOFTBAM_Processing(SOFTBAM_t *bam)
{
	register uint8_t prescaler = (0b11111111 >> bam->bits_counter);
	
	bam->prescaler_callback(prescaler);
	
	
	for (register uint8_t i = 0; i < bam->num_of_channels; ++i)
	{
		if (bam->bits_counter == 0)
		{
			bam->channels[i].softbam_channel_duty_cycle_buf = bam->channels[i].softbam_channel_duty_cycle;
		}
		
		if (bam->channels[i].softbam_channel_duty_cycle_buf & (1 << (7 - (bam->bits_counter))))
		{
			*(bam->channels[i].softbam_channel_port) |=  (1 << bam->channels[i].softbam_channel_pin);
			
		}
		else
		{
			*(bam->channels[i].softbam_channel_port) &= ~(1 << bam->channels[i].softbam_channel_pin);
		}
	}
	
	
	++(bam->bits_counter);
	
	if (bam->bits_counter > 7)
	{
		bam->bits_counter = 0;
	}
}




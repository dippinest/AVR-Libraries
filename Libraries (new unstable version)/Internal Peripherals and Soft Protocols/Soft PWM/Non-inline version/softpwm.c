
#include "softpwm.h"


void SOFTPWM_Initialize_Object(SOFTPWM_t *softpwm, uint8_t *port, uint8_t pin, uint8_t max_depth, uint8_t duty_cycle)
{
	(*softpwm).softpwm_channel_port           = port;
	(*softpwm).softpwm_channel_pin            = pin;
	
	(*softpwm).softpwm_channel_max_depth      = max_depth;
	(*softpwm).softpwm_channel_duty_cycle     = duty_cycle;
	(*softpwm).softpwm_channel_duty_cycle_buf = duty_cycle;
	
	(*softpwm).softpwm_channel_counter        = 0;
}


// ===============================================================================


void SOFTPWM_Channel_Processing(SOFTPWM_t *softpwm)
{
	if (softpwm->softpwm_channel_counter == softpwm->softpwm_channel_max_depth)
	{
		*(softpwm->softpwm_channel_port) |=  (1 << softpwm->softpwm_channel_pin);
		
		softpwm->softpwm_channel_duty_cycle_buf = softpwm->softpwm_channel_duty_cycle;
		
		softpwm->softpwm_channel_counter = 0;
	}
	
	if (softpwm->softpwm_channel_counter >= softpwm->softpwm_channel_duty_cycle_buf)
	{
		*(softpwm->softpwm_channel_port) &= ~(1 << softpwm->softpwm_channel_pin);
	}
	
	++(softpwm->softpwm_channel_counter);
}

void SOFTPWM_All_Channels_Processing(SOFTPWM_t *softpwm_channels, const uint8_t num_of_channels)
{
	for (uint8_t i = 0; i < num_of_channels; ++i)
	{
		SOFTPWM_Channel_Processing(&(softpwm_channels[i]));
	}
}




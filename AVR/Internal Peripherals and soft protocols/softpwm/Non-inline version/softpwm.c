
#include "softpwm.h"


SOFTPWM_t SOFTPWM_Get_Channel_Object(uint8_t *port, uint8_t pin, uint8_t max_depth, uint8_t duty_cycle)
{
	SOFTPWM_t pwm;
	
	pwm.softpwm_channel_port           = port;
	pwm.softpwm_channel_pin            = pin;
	
	pwm.softpwm_channel_max_depth      = max_depth;
	pwm.softpwm_channel_duty_cycle     = duty_cycle;
	pwm.softpwm_channel_duty_cycle_buf = duty_cycle;
	
	pwm.softpwm_channel_counter        = 0;
	
	return pwm;
}


// ===============================================================================


void SOFTPWM_Channel_Processing(SOFTPWM_t *channel)
{
	if (channel->softpwm_channel_counter == channel->softpwm_channel_max_depth)
	{
		*(channel->softpwm_channel_port) |=  (1 << channel->softpwm_channel_pin);
		
		channel->softpwm_channel_duty_cycle_buf = channel->softpwm_channel_duty_cycle;
		
		channel->softpwm_channel_counter = 0;
	}
	
	if (channel->softpwm_channel_counter >= channel->softpwm_channel_duty_cycle_buf)
	{
		*(channel->softpwm_channel_port) &= ~(1 << channel->softpwm_channel_pin);
	}
	
	++(channel->softpwm_channel_counter);
}

void SOFTPWM_All_Channels_Processing(SOFTPWM_t *channels, uint8_t num_of_channels)
{
	for (uint8_t i = 0; i < num_of_channels; ++i)
	{
		SOFTPWM_Channel_Processing(&(channels[i]));
	}
}


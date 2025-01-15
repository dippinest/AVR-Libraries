
#include "softpwm.h"


SOFTPWM_t SOFTPWM_Get_Object(uint8_t *port, uint8_t pin, uint8_t max_depth, uint8_t duty_cycle)
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


void SOFTPWM_Channel_Processing(SOFTPWM_t *pwm)
{
	if (pwm->softpwm_channel_counter == pwm->softpwm_channel_max_depth)
	{
		*(pwm->softpwm_channel_port) |=  (1 << pwm->softpwm_channel_pin);
		
		pwm->softpwm_channel_duty_cycle_buf = pwm->softpwm_channel_duty_cycle;
		
		pwm->softpwm_channel_counter = 0;
	}
	
	if (pwm->softpwm_channel_counter >= pwm->softpwm_channel_duty_cycle_buf)
	{
		*(pwm->softpwm_channel_port) &= ~(1 << pwm->softpwm_channel_pin);
	}
	
	++(pwm->softpwm_channel_counter);
}

void SOFTPWM_All_Channels_Processing(SOFTPWM_t *channels, uint8_t num_of_channels)
{
	for (uint8_t i = 0; i < num_of_channels; ++i)
	{
		SOFTPWM_Channel_Processing(&(channels[i]));
	}
}


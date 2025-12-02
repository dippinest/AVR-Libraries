
// ===============================================================================
//
// Библиотека для реализации программной ШИМ.
//
// В данной реализации библиотеки отсутствует файл реализации функций
// (файл с расширением *.c). Все функции являются встраиваемыми (inline)
// с целью повышения быстродействия, поскольку программная ШИМ является
// достаточно тяжёлой для процессора, так как занимает много процессорного времени.
// 
// Эту реализацию библиотеки я предлагаю использовать для относительно
// высокочастотной ШИМ с ограниченным числом каналов. в противном случае
// я рекомендую использовать версию библиотеки с невстраиваемыми
// (non-inline) функциями softpwm.h
//
// -------------------------------------------------------------------------------
//
// Library for implementing software PWM.
//
// This library implementation does not have a function implementation file
// (a file with the extension *.c). All functions are inline in order to increase
// performance, since the software PWM is quite heavy for the processor,
// since it takes a lot of processor time.
//
// I suggest using this library implementation for a relatively
// high-frequency PWM with a limited number of channels. otherwise,
// I recommend using the library version with non-embedded
// (non-inline) softpwm.h functions.
//
// ===============================================================================


#ifndef SOFTPWM_INLINE_H_
#define SOFTPWM_INLINE_H_


#include <avr/io.h>

#include <stdint.h>


// ===============================================================================


#ifndef T
#define T(P) ((uint8_t*)&P)
#endif


typedef struct
{
	volatile uint8_t *softpwm_channel_port;

	uint8_t  softpwm_channel_pin;
	uint8_t  softpwm_channel_max_depth;

	volatile uint8_t  softpwm_channel_duty_cycle;
	volatile uint8_t  softpwm_channel_duty_cycle_buf;
	
	volatile uint8_t  softpwm_channel_counter;

} SOFTPWM_Inline_t;


// ===============================================================================


inline SOFTPWM_Inline_t SOFTPWM_Inline_Create_Object(uint8_t *port, uint8_t pin, uint8_t max_depth, uint8_t duty_cycle)
{
	SOFTPWM_Inline_t pwm;
	
	pwm.softpwm_channel_port           = port;
	pwm.softpwm_channel_pin            = pin;
	
	pwm.softpwm_channel_max_depth      = max_depth;
	pwm.softpwm_channel_duty_cycle     = duty_cycle;
	pwm.softpwm_channel_duty_cycle_buf = duty_cycle;
	
	pwm.softpwm_channel_counter        = 0;
	
	return pwm;
}


// ===============================================================================


#define SOFTPWM_INLINE_DUTY_CYCLE(SOFTPWMCHANNEL) (SOFTPWMCHANNEL.softpwm_channel_duty_cycle)


// ===============================================================================


inline void SOFTPWM_Inline_Channel_Processing(SOFTPWM_Inline_t *channel)
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

inline void SOFTPWM_Inline_All_Channels_Processing(SOFTPWM_Inline_t *channels, uint8_t num_of_channels)
{
	for (uint8_t i = 0; i < num_of_channels; ++i)
	{
		SOFTPWM_Inline_Channel_Processing(&(channels[i]));
	}
}


#endif





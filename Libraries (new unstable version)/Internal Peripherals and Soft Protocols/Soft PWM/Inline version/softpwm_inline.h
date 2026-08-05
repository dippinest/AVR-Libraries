
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
	uint8_t  softpwm_channel_duty_cycle;
	uint8_t  softpwm_channel_duty_cycle_buf;
	
	uint8_t  softpwm_channel_counter;

} SOFTPWM_Inline_t;


// ===============================================================================


inline void SOFTPWM_Inline_Initialize_Object(SOFTPWM_Inline_t *softpwm, uint8_t *port, uint8_t pin, uint8_t max_depth, uint8_t duty_cycle)
{
	(*softpwm).softpwm_channel_port           = port;
	(*softpwm).softpwm_channel_pin            = pin;
	
	(*softpwm).softpwm_channel_max_depth      = max_depth;
	(*softpwm).softpwm_channel_duty_cycle     = duty_cycle;
	(*softpwm).softpwm_channel_duty_cycle_buf = duty_cycle;
	
	(*softpwm).softpwm_channel_counter        = 0;
}


// ===============================================================================


#define SOFTPWM_INLINE_DUTY_CYCLE(SOFTPWMCHANNEL) (SOFTPWMCHANNEL.softpwm_channel_duty_cycle)


// ===============================================================================


inline void SOFTPWM_Inline_Channel_Processing(SOFTPWM_Inline_t *softpwm_channel)
{
	if (softpwm_channel->softpwm_channel_counter == softpwm_channel->softpwm_channel_max_depth)
	{
		*(softpwm_channel->softpwm_channel_port) |=  (1 << softpwm_channel->softpwm_channel_pin);
		
		softpwm_channel->softpwm_channel_duty_cycle_buf = softpwm_channel->softpwm_channel_duty_cycle;
		
		softpwm_channel->softpwm_channel_counter = 0;
	}
	
	if (softpwm_channel->softpwm_channel_counter >= softpwm_channel->softpwm_channel_duty_cycle_buf)
	{
		*(softpwm_channel->softpwm_channel_port) &= ~(1 << softpwm_channel->softpwm_channel_pin);
	}
	
	++(softpwm_channel->softpwm_channel_counter);
}

inline void SOFTPWM_Inline_All_Channels_Processing(SOFTPWM_Inline_t *softpwm_channels, const uint8_t num_of_channels)
{
	for (uint8_t i = 0; i < num_of_channels; ++i)
	{
		SOFTPWM_Inline_Channel_Processing(&(softpwm_channels[i]));
	}
}


#endif






// ===============================================================================
//
// Библиотека для реализации программной ШИМ.
//
// Эту реализацию библиотеки я предлагаю использовать для относительно
// низкочастотной ШИМ с большим числом каналов. Для работы с ограниченным
// числом каналов ВЫСОКОЧАСТОТНОЙ программной ШИМ в я рекомендую использовать
// версию библиотеки с встраиваемыми (inline) функциями softpwm_inline.h
//
// -------------------------------------------------------------------------------
//
// Library for implementing software PWM.
//
// I suggest using this library implementation for a relatively
// low-frequency PWM with a large number of channels. To work with
// a limited number of channels of HIGH-FREQUENCY software PWM,
// I recommend using the version of the library with embedded
// (inline) functions softpwm_inline.h
//
// ===============================================================================


#ifndef SOFTPWM_H_
#define SOFTPWM_H_


#include <avr/io.h>

#include <stdlib.h>


// ===============================================================================


#ifndef T
#define T(P) ((uint8_t*)&P)
#endif


typedef struct
{
	uint8_t *softpwm_channel_port;
	uint8_t  softpwm_channel_pin;
	
	uint8_t  softpwm_channel_max_depth;
	uint8_t  softpwm_channel_duty_cycle;
	uint8_t  softpwm_channel_duty_cycle_buf;
	
	uint8_t  softpwm_channel_counter;

} SOFTPWM_t;


// ===============================================================================


SOFTPWM_t SOFTPWM_Get_Channel_Object(uint8_t *port, uint8_t pin, uint8_t max_depth, uint8_t duty_cycle);


// ===============================================================================


#define SOFTPWM_DUTY_CYCLE(T) (T.softpwm_channel_duty_cycle)


// ===============================================================================


void SOFTPWM_Channel_Processing(SOFTPWM_t *channel);

void SOFTPWM_All_Channels_Processing(SOFTPWM_t *channels, uint8_t num_of_channels);


#endif




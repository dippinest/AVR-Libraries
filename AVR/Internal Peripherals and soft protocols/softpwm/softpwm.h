
// ===============================================================================
//
// Это не библиотека в привычном понимании, а лишь файл с реализацией
// программного ШИМ. Поскольку реализация программного ШИМ занимает довольно
// много процессорного времени, все функции являются встраиваемыми (inline).
// Соответственно, здесь отсутствуют какие-либо колбэк-функции и прочее.
//
// Настройка программного ШИМ выполняется исключительно редактированием
// этого файла. Для работы необходимо периодически вызывать функции
// опроса ШИМ (к примеру, в обработчике прерывания таймера).
//
// -------------------------------------------------------------------------------
//
// This is not a library in the usual sense, but only a file with the
// implementation of a software PWM. Since the implementation of software
// PWM takes quite a lot of CPU time, all functions are inline.
// Accordingly, there are no callback functions and so on.
// The configuration of the software PWM is performed
// exclusively by editing this file.
//
// To work, it is necessary to periodically call the PWM polling functions
// (for example, in the timer interrupt handler).
//
// ===============================================================================


#ifndef SOFTPWM_H_
#define SOFTPWM_H_

#include <avr/io.h>

#include <stdint.h>


// ===============================================================================


// дефайны с определениями регистров GPIO
//
// -------------------------------------------------------------------------------
// defines with GPIO register definitions
//
#define SOFTWARE_PWM_CH1_PORT PORTB
#define SOFTWARE_PWM_CH1_DDRX DDRB

#define SOFTWARE_PWM_CH2_PORT PORTB
#define SOFTWARE_PWM_CH2_DDRX DDRB

#define SOFTWARE_PWM_CH3_PORT PORTB
#define SOFTWARE_PWM_CH3_DDRX DDRB

#define SOFTWARE_PWM_CH1  1
#define SOFTWARE_PWM_CH2  2
#define SOFTWARE_PWM_CH3  3


// ===============================================================================


// инициализация GPIO портов, выделенные под каждый канал программного ШИМ
//
// -------------------------------------------------------------------------------
// initialization of GPIO ports allocated for each channel of the software PWM
//
inline void SOFTPWM_Initialize()
{
	SOFTWARE_PWM_CH1_DDRX |= (1 << SOFTWARE_PWM_CH1);
	SOFTWARE_PWM_CH2_DDRX |= (1 << SOFTWARE_PWM_CH2);
	SOFTWARE_PWM_CH3_DDRX |= (1 << SOFTWARE_PWM_CH3);
	
	SOFTWARE_PWM_CH1_PORT |= (1 << SOFTWARE_PWM_CH1);
	SOFTWARE_PWM_CH2_PORT |= (1 << SOFTWARE_PWM_CH2);
	SOFTWARE_PWM_CH3_PORT |= (1 << SOFTWARE_PWM_CH3);
}


// ===============================================================================


// переменные, хранящие коэффициент заполнения каждого для канала программного ШИМ
//
// -------------------------------------------------------------------------------
// variables storing the duty cycle for each channel of the software PWM
//
volatile uint8_t SOFTPWM_Channel_1_Value, SOFTPWM_Channel_2_Value, SOFTPWM_Channel_3_Value;


// ===============================================================================


// функции опроса отдельных каналов программного ШИМ
//
// -------------------------------------------------------------------------------
// polling functions of individual channels of the software PWM
//
inline static void SOFTPWM_Channel_1_Polling()
{
	static uint8_t _pwm_counter = 0;
	
	if (_pwm_counter == 0)
	{
		SOFTWARE_PWM_CH1_PORT |= (1 << SOFTWARE_PWM_CH1);
	}
	
	
	if (_pwm_counter == SOFTPWM_Channel_1_Value)
	{
		SOFTWARE_PWM_CH1_PORT &= ~(1 << SOFTWARE_PWM_CH1);
	}
	
	++_pwm_counter;
}

inline static void SOFTPWM_Channel_2_Polling()
{
	static uint8_t _pwm_counter = 0;
	
	if (_pwm_counter == 0)
	{
		SOFTWARE_PWM_CH2_PORT |= (1 << SOFTWARE_PWM_CH2);
	}
	
	
	if (_pwm_counter == SOFTPWM_Channel_2_Value)
	{
		SOFTWARE_PWM_CH2_PORT &= ~(1 << SOFTWARE_PWM_CH2);
	}
	
	++_pwm_counter;
}

inline static void SOFTPWM_Channel_3_Polling()
{
	static uint8_t _pwm_counter = 0;
	
	if (_pwm_counter == 0)
	{
		SOFTWARE_PWM_CH3_PORT |= (1 << SOFTWARE_PWM_CH3);
	}
	
	
	if (_pwm_counter == SOFTPWM_Channel_3_Value)
	{
		SOFTWARE_PWM_CH3_PORT &= ~(1 << SOFTWARE_PWM_CH3);
	}
	
	++_pwm_counter;
}


// ===============================================================================


// функции опроса всех каналов программного ШИМ
//
// -------------------------------------------------------------------------------
// polling functions for all channels of the software PWM
//
inline static void SOFTPWM_All_Channels_Polling()
{
	static uint8_t _pwm_counter = 0;
	
	if (_pwm_counter == 0)
	{
		SOFTWARE_PWM_CH1_PORT |= (1 << SOFTWARE_PWM_CH1);
		SOFTWARE_PWM_CH2_PORT |= (1 << SOFTWARE_PWM_CH2);
		SOFTWARE_PWM_CH3_PORT |= (1 << SOFTWARE_PWM_CH3);
	}
	
	if (_pwm_counter == SOFTPWM_Channel_1_Value)
	{
		SOFTWARE_PWM_CH1_PORT &= ~(1 << SOFTWARE_PWM_CH1);
	}
	
	if (_pwm_counter == SOFTPWM_Channel_2_Value)
	{
		SOFTWARE_PWM_CH2_PORT &= ~(1 << SOFTWARE_PWM_CH2);
	}
	
	if (_pwm_counter == SOFTPWM_Channel_3_Value)
	{
		SOFTWARE_PWM_CH3_PORT &= ~(1 << SOFTWARE_PWM_CH3);
	}
	
	++_pwm_counter;
}


#endif


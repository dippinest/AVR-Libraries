

// ===============================================================================
//
// Библиотека для работы с внутренним модулем аналогового компаратора.
// Большинство функций данной библиотеки являются блокирующими, однако
// есть возможность использовать неблокирующий режим работы, используя
// чистые прерывания или же коллбэк-функции (это можно настроить в файле
// конфигурации anacomp_configuration.h)
//
// -------------------------------------------------------------------------------
//
// Library for working with the internal module of the analog comparator.
// Most of the functions of this library are blocking, but it is possible
// to use a non-blocking mode of operation using pure interrupts or callback
// functions (this can be configured in the configuration file anacomp_configuration.h)
//
// ===============================================================================


#ifndef ANACOMP_H_
#define ANACOMP_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


#if defined\
(__AVR_ATmega64__)   ||\
(__AVR_ATmega64A__)  ||\
(__AVR_ATmega128__)  ||\
(__AVR_ATmega128A__)

#define ANA_COMP_vect ANALOG_COMP_vect

#endif


#include "anacomp_configuration.h"


#define ANACOMP_DIRECT_INPUT_IS_CONNECTED_TO_INTERNAL_VOLTAGE_SOURCE  true
#define ANACOMP_DIRECT_INPUT_IS_NOT_CONNECTED                         false

#define ANACOMP_INTERRUPT_TYPE_ANY_CHANGE              0b00
#define ANACOMP_INTERRUPT_TYPE_TRANSITION_FROM_1_TO_0  0b10
#define ANACOMP_INTERRUPT_TYPE_TRANSITION_FROM_0_TO_1  0b11

#define ANACOMP_STATE_IS_HIGH  true
#define ANACOMP_STATE_IS_LOW   false


// ===============================================================================


inline void ANACOMP_Set_Enable(bool is_enable)
{
	if (is_enable)
	{
		ACSR &= ~(1 << ACD);
	}
	else
	{
		ACSR |=  (1 << ACD);
	}
}

inline void ANACOMP_Direct_Input_Set_Connect(bool direct_input_is_connect)
{
	if (direct_input_is_connect)	{
		ACSR |=  (1 << ACBG);
	}
	else
	{
		ACSR &= ~(1 << ACBG);
	}
}

inline void ANACOMP_Set_Interrupt_Enable(bool is_enable)
{
	if (is_enable)
	{
		ACSR |=  (1 << ACIE);
	}
	else
	{
		ACSR &= ~(1 << ACIE);
	}
}

inline void ANACOMP_Set_Interrupt_Type(uint8_t interrupt_type)
{
	switch (interrupt_type)
	{
		case ANACOMP_INTERRUPT_TYPE_TRANSITION_FROM_1_TO_0:
		ACSR |=  (1 << ACIS1);
		ACSR &= ~(1 << ACIS0);
		break;
		
		case ANACOMP_INTERRUPT_TYPE_TRANSITION_FROM_0_TO_1:
		ACSR |=  (1 << ACIS1);
		ACSR |=  (1 << ACIS0);
		break;
		
		case ANACOMP_INTERRUPT_TYPE_ANY_CHANGE:
		default:
		ACSR &= ~(1 << ACIS1);
		ACSR &= ~(1 << ACIS0);
	}
}

inline bool ANACOMP_Is_Enable()
{
	if (!(ACSR & (1 << ACD)))
	{
		return true;
	}
	
	return false;
}

inline bool ANACOMP_Direct_Input_Is_Connect()
{
	if (ACSR & (1 << ACBG))
	{
		return true;
	}
	
	return false;
}

inline bool ANACOMP_Interrupt_Is_Enable()
{
	if (ACSR & (1 << ACIE))
	{
		return true;
	}
	
	return false;
}

inline uint8_t ANACOMP_Get_Interrupt_Type()
{
	uint8_t interrupt_type = 0;
	
	interrupt_type |= (ACSR & (1 << ACIS1));
	interrupt_type |= (ACSR & (1 << ACIS0));
	
	if (interrupt_type == 0b01)
	{
		interrupt_type = ANACOMP_INTERRUPT_TYPE_ANY_CHANGE;
	}
	
	return interrupt_type;
}

inline bool ANACOMP_Get_State()
{
	if (ACSR & (1 << ACO))
	{
		return ANACOMP_STATE_IS_HIGH;
	}
	
	return ANACOMP_STATE_IS_LOW;
}


// ===============================================================================


#ifdef ANACOMP_USE_CALLBACK

void ANACOMP_Set_CallBack_Function(void (*callback_function)());

void *ANACOMP_Get_CallBack_Function();

#endif


#endif



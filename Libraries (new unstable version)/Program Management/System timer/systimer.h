

// ===============================================================================
//
// Библиотека с реализацией системного таймера и работы с ним. Поскольку
// системный таймер можно реализовать с помощью любого аппаратного таймера
// микроконтроллера, то его реализация вынесена в отдельный файл
// конфигурации systimer_configuration.h
//
// Вы можете установить длительность такта системного таймера
// в соответствии со своими потребностями (1 мс, 20 мс, 1 с и т. д.).
//
// Его можно использовать в различных приложениях - например, для
// организации операционной системы, измерения времени работы кода,
// организации точных задержек и т.д.
//
// -------------------------------------------------------------------------------
//
// Library with the implementation of the system timer and working with it.
// Since the system timer can be implemented using any MCU
// hardware timer, its implementation is placed in a separate
// configuration file, systimer_configuration.h
//
// You can set the system timer tick to any duration
// based on your needs (1 ms, 20 ms, 1 sec, etc.).
//
// It can be used in various applications - for example,
// to organize the operating system, measure the running time
// of the code, organize accurate delays, etc.
//
// ===============================================================================


#ifndef SYSTIMER_H_
#define SYSTIMER_H_


#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>
#include <stddef.h>


#include "systimer_configuration.h"




#ifdef SYSTIMER_WIDE_32BIT

typedef uint32_t SYSTIMER_t;

#else

typedef uint16_t SYSTIMER_t;

#endif





// ===============================================================================



SYSTIMER_t SYSTIMER_Get_Value();

void SYSTIMER_Delay(SYSTIMER_t ticks);



// ===============================================================================



typedef struct
{
	volatile SYSTIMER_t timer;
	volatile SYSTIMER_t interval;
	
} SYSTIMER_Task_Params_t;



void SYSTIMER_Initialize_Task_Params(SYSTIMER_Task_Params_t *task_params, SYSTIMER_t interval);


void SYSTIMER_Run_Task(SYSTIMER_Task_Params_t *task_params, void (*task)());




#endif









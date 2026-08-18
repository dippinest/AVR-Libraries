

// Пример использования системного таймера с внешним тактированием.
//
// В качестве внешнего источника тактирования можгу выступать
// генераторы частоты, RTC и т.д. В данном примере в качестве такового
// используется RTC DS1307, которые выдаёт тактовые сигналы с частотой 4096 Гц
// на внешнее прерывание INT0. В обработчике прерывания INT0
// происходит инкремент системного таймера.
//
// -------------------------------------------------------------------------------
// Example of using a system timer with external clocking.
//
// The external clocking source can be a frequency generator, RTC, etc.
// In this example, the RTC DS1307 is used as such; it outputs clock signals
// with a frequency of 4096 Hz to the external interrupt INT0.
// In the INT0 interrupt handler, the system timer is incremented.


#include <avr/interrupt.h>
#include <avr/sleep.h>


#include <util/delay.h>


#include "softi2c.h"

#include "ds1307.h"

#include "systimer.h"



// объекты SYSTIMER_Task_Params
//
// ===============================================================================
// SYSTIMER_Task_Params objects
//
SYSTIMER_Task_Params_t tparams0;
SYSTIMER_Task_Params_t tparams1;
SYSTIMER_Task_Params_t tparams2;
SYSTIMER_Task_Params_t tparams3;





// отдельные задачи для управления пинами GPIO
//
// -------------------------------------------------------------------------------
// separate tasks for managing GPIO pins
//
void Task0()
{
	PORTB ^= (1 << 0);
}

void Task1()
{
	PORTB ^= (1 << 1);
}

void Task2()
{
	PORTB ^= (1 << 2);
}

void Task3()
{
	PORTB ^= (1 << 3);
}






// обработчик внешнего прерывания INT0
//
// ===============================================================================
// the external interrupt handler INT0
//
ISR(INT0_vect)
{
	// программный счётчик для коррекции частоты.
	// Он инкрементируется каждое прерывние INT0.
	// Когда значение программного счётчика достигнет значения коэффициента N,
	// произойдёт инкремент системного таймера. Учитывая опорную тактовую частоту
	// (частоту срабатывания прерывания INT0) и коэффициент N,
	// можно получить различные значения частоты системного таймера.
	// В данном случае, чтобы получить частоту системного таймера 128 Гц
	// и зная частоту опорного генератора (4096 Гц), необходимо расчитать
	// значение коэффициента N по следущей формуле:
	//
	// N = F_ref / F_systimer (4096 Гц / 128 Гц = 32)
	//
	// ===============================================================================
	// A software counter for frequency correction.
	// It is incremented with each INT0 interrupt.
	// When the value of the software counter reaches the value of the N coefficient,
	// the system timer will be incremented.
	// Taking into account the reference clock frequency
	// (the frequency at which the INT0 interrupt is triggered)
	// and the N coefficient, various values of the system timer frequency
	// can be obtained.
	// In this case, to obtain a system timer frequency of 128 Hz,
	// and knowing the frequency of the reference oscillator (4096 Hz),
	// it is necessary to calculate the value of the N coefficient using
	// the following formula:
	//
	// N = F_ref / F_systimer (4096 Hz / 128 Hz = 32)
	//
	static volatile uint16_t counter = 1;
	
	#define N 32
	
	
	
	if (counter >= N)
	{
		counter = 0;
		
		// инкремент системного таймера
		//
		// ===============================================================================
		// system timer increment
		//
		SYSTIMER_Increment_Timer();
	}
	
	++counter;
	
	
	#undef N
}



int main(void)
{
	// настройка внешнего прерывания INT0 на срабатывание по восходящему фронту
	//
	// ===============================================================================
	// configuring the external interrupt INT0 to be triggered by the rising edge
	//
	GICR  |= (1 << INT0);
	MCUCR |= (1 << ISC01) | (1 << ISC00);
	
	
	
	// инициализация GPIO
	//
	// -------------------------------------------------------------------------------
	// GPIO initialize
	//
	DDRB  = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
	PORTB = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
	
	
	
	
	SOFTI2C_Initialize();
	
	
	
	// настройка и активация генератора частоты в DS1307
	//
	// ===============================================================================
	// setting up and activating the frequency generator in DS1307
	//
	DS1307_Set_SQW_Frequency(DS1307_SQWE_FREQUENCY_4096_HZ);
	
	DS1307_Set_SQW_Enable(true);
	
	
	
	// если микросхема отключена (если на неё только подняли питание),
	// её обязательно надо включить
	//
	// ===============================================================================
	// If the microchip is turned off (if power has just been applied to it),
	// it must be turned on
	//
	DS1307_Set_Enable(true);
	
	
	
	// переменные для хранения параметров выполнения каждой задачи
	//
	// -------------------------------------------------------------------------------
	// variables for storing the execution params of each task
	//
	SYSTIMER_Initialize_Task_Params(&tparams0,  16);  // (128 Hz /  16) = 0.125 sec (8 Hz)
	SYSTIMER_Initialize_Task_Params(&tparams1,  32);  // (128 Hz /  32) = 0.25  sec (4 Hz)
	SYSTIMER_Initialize_Task_Params(&tparams2,  64);  // (128 Hz /  64) = 0.5   sec (2 Hz)
	SYSTIMER_Initialize_Task_Params(&tparams3, 128);  // (128 Hz / 128) =   1   sec (1 Hz)
	
	
	
	
	// обязательно включите глобальные прерывания
	// -------------------------------------------------------------------------------
	// be sure to enable global interrupts
	//
	sei();
	
	
	while (1)
	{
		// псевдопараллельная обработка задач системным таймером
		//
		// ===============================================================================
		// pseudo‑parallel task processing by the system timer
		//
		SYSTIMER_Run_Task(&tparams0, Task0);  // run every 100  ticks
		SYSTIMER_Run_Task(&tparams1, Task1);  // run every 200  ticks
		SYSTIMER_Run_Task(&tparams2, Task2);  // run every 500  ticks
		SYSTIMER_Run_Task(&tparams3, Task3);  // run every 1000 ticks
		
		
		
		// при желании после отработки всех задач вы можете
		// усыпить процессор с целью экономии энергии
		//
		// -------------------------------------------------------------------------------
		// if desired, after working out all the tasks,
		// you can put the processor to sleep in order to save energy
		//
		sleep_enable();
		sleep_cpu();
	}
}





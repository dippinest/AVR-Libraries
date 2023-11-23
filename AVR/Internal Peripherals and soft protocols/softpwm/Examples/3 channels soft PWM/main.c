
// ===============================================================================
//
// Пример использования программного ШИМ.
//
// Основная настройка производится путём редактирования
// заголовочного файла softpwm.h (см. описание).
// В данном случае задействовано 3 канала, к которым подключены светодиоды.
//
// -------------------------------------------------------------------------------
//
// An example of using a software PWM.
// 
// The basic setup is done by editing the softpwm.h header file
// (see description). In this case, 3 channels are involved,
// to which LEDs are connected.
//
// ===============================================================================


#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include "softpwm.h"


// инициализируем Timer2
//
// -------------------------------------------------------------------------------
// Timer2 initialize
//
inline void TIMER2_Initialize()
{
	TCCR2 = (1 << CS20);  // not div F_CPU
	TIMSK = (1 << TOIE2); // set overflow interrupt
	
	sei();
}


// опрашиваем программный ШИМ в обработчике прерывания по переполнению Timer2
//
// -------------------------------------------------------------------------------
// polling the program PWM in the interrupt handler for Timer2 overflow
//
ISR(TIMER2_OVF_vect)
{
	// опрашиваем все каналы программного ШИМ
	//
	// -------------------------------------------------------------------------------
	// polling all channels of the software PWM
	//
	SOFTPWM_All_Channels_Polling();
}


int main(void)
{
	TIMER2_Initialize();
	
	SOFTPWM_Initialize();
	
	
	// начальные значения коэффициентов заполнения каждого канала ШИМ
	//
	// -------------------------------------------------------------------------------
	// initial values of the duty cycle of each PWM channel
	//
	SOFTPWM_Channel_1_Value = 255;
	SOFTPWM_Channel_2_Value = 255;
	SOFTPWM_Channel_3_Value = 255;
	
	while (1)
	{
		#define DELAY_MS 10
		
		
		// плавно увеличиваем и уменьшаем коэффициент заполнения каждого канала ШИМ
		//
		// -------------------------------------------------------------------------------
		// smoothly increase and decrease the duty cycle of each PWM channel
		//
		while(SOFTPWM_Channel_1_Value != 0)
		{
			SOFTPWM_Channel_1_Value--;
			_delay_ms(DELAY_MS);
		}
		while(SOFTPWM_Channel_1_Value != 255)
		{
			SOFTPWM_Channel_1_Value++;
			_delay_ms(DELAY_MS);
		}
		
		while(SOFTPWM_Channel_2_Value != 0)
		{
			SOFTPWM_Channel_2_Value--;
			_delay_ms(DELAY_MS);
		}
		while(SOFTPWM_Channel_2_Value != 255)
		{
			SOFTPWM_Channel_2_Value++;
			_delay_ms(DELAY_MS);
		}
		
		while(SOFTPWM_Channel_3_Value != 0)
		{
			SOFTPWM_Channel_3_Value--;
			_delay_ms(DELAY_MS);
		}
		while(SOFTPWM_Channel_3_Value != 255)
		{
			SOFTPWM_Channel_3_Value++;
			_delay_ms(DELAY_MS);
		}
	}
}



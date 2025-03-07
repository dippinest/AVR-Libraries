

// ===============================================================================
//
// Пример использования программного ШИМ.
//
// В данном примере используются 1 канал программного ШИМ разрядностью
// 4 бита (16 градаций) для управления яркостью светодиода
//
// -------------------------------------------------------------------------------
//
// An example of using a software PWM.
//
// In this example, 1 channel of 4 bits (16 gradations) software PWM is used to
// control the brightness of the LED
//
// ===============================================================================


#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include "softpwm_inline.h"


// макросы с определением разрядности программного ШИМ (32 градации)
//
// -------------------------------------------------------------------------------
// macros with the definition of the bit depth of the software PWM (32 gradations)
//
#define MAX_PWM_WIDTH 0x20


// переменная структуры канала программного ШИМ
//
// -------------------------------------------------------------------------------
// variable of the structure of the software PWM channel
//
SOFTPWM_Inline_t softpwm;


// инициализируем таймера 2 (Timer2)
//
// -------------------------------------------------------------------------------
// Timer2 initialize
//
inline void TIMER2_Initialize()
{
	TCCR2 = (1 << CS21);  // div F_CPU / 8 (16 MHz / (8 * MAX_PWM_WIDTH) = 125 kHz)
	TIMSK = (1 << TOIE2); // set overflow interrupt
}


// обработка канала ШИМ в прерывании по переполнению таймера 2 (Timer2)
//
// -------------------------------------------------------------------------------
// processing of PWM channel in the overflow interrupt Timer2
//
ISR(TIMER2_OVF_vect)
{
	SOFTPWM_Inline_Channel_Processing(&softpwm);
}


int main(void)
{
	TIMER2_Initialize();
	
	// инициализация порта GPIO и программного ШИМ
	//
	// -------------------------------------------------------------------------------
	// initialization of GPIO port and software PWM
	//
	DDRB |= (1 << 1);

	softpwm = SOFTPWM_Inline_Create_Object(T(PORTB), 1, MAX_PWM_WIDTH, MAX_PWM_WIDTH);
	
	sei();
	
	while (1)
	{
		#define DELAY_MS 50
		
		// плавно увеличиваем и уменьшаем коэффициент заполнения канала ШИМ
		//
		// -------------------------------------------------------------------------------
		// smoothly increase and decrease the duty cycle of PWM channel
		//
		while(SOFTPWM_INLINE_DUTY_CYCLE(softpwm) != 0)
		{
			SOFTPWM_INLINE_DUTY_CYCLE(softpwm)--;
			_delay_ms(DELAY_MS);
		}
		while(SOFTPWM_INLINE_DUTY_CYCLE(softpwm) != MAX_PWM_WIDTH)
		{
			SOFTPWM_INLINE_DUTY_CYCLE(softpwm)++;
			_delay_ms(DELAY_MS);
		}
	}
}



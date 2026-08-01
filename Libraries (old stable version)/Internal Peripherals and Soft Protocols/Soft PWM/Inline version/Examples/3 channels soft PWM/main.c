

// ===============================================================================
//
// Пример использования программного ШИМ.
//
// В данном примере используются 3 канала программного ШИМ разрядностью 4 бита
// (16 градаций) для управления трёхцветного светодиода с общим анодом
//
// -------------------------------------------------------------------------------
//
// An example of using a software PWM.
//
// In this example, 3 channels of software PWM with a bit depth of 4 bits
// (16 gradations) are used to control a three-color LED with a common anode
//
// ===============================================================================


#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include "softpwm_inline.h"


// макросы с определениями разрядности программного ШИМ (16 градаций) и количества каналов
//
// -------------------------------------------------------------------------------
// macros with definitions of the bit depth of the software PWM (16 gradations) and the
// number of channels
//
#define MAX_PWM_WIDTH 0xF
#define SOFTPWM_NUM_OF_CHANNELS 3


// массив каналов программного ШИМ
//
// -------------------------------------------------------------------------------
// array of software PWM channels
//
SOFTPWM_Inline_t softpwm[SOFTPWM_NUM_OF_CHANNELS];


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


// обработка всех каналов ШИМ в прерывании по переполнению таймера 2 (Timer2)
//
// -------------------------------------------------------------------------------
// processing of all PWM channels in the overflow interrupt Timer2
//
ISR(TIMER2_OVF_vect)
{
	SOFTPWM_Inline_All_Channels_Processing(softpwm, SOFTPWM_NUM_OF_CHANNELS);
}


int main(void)
{
	TIMER2_Initialize();
	
	// инициализация портов GPIO и каналов программного ШИМ
	//
	// -------------------------------------------------------------------------------
	// initialization of GPIO ports and software PWM channels
	//
	DDRB |= (1 << 1) | (1 << 2) | (1 << 3);

	softpwm[0] = SOFTPWM_Inline_Create_Object(T(PORTB), 1, MAX_PWM_WIDTH, MAX_PWM_WIDTH);
	softpwm[1] = SOFTPWM_Inline_Create_Object(T(PORTB), 2, MAX_PWM_WIDTH, MAX_PWM_WIDTH);
	softpwm[2] = SOFTPWM_Inline_Create_Object(T(PORTB), 3, MAX_PWM_WIDTH, MAX_PWM_WIDTH);


	// не забудьте включить глобальные прерывания
	//
	// -------------------------------------------------------------------------------
	// don't forget to enable global interrupts
	//
	sei();
	
	while (1)
	{
		#define DELAY_MS 50
		
		// плавно увеличиваем и уменьшаем коэффициент заполнения каждого канала ШИМ
		//
		// -------------------------------------------------------------------------------
		// smoothly increase and decrease the duty cycle of each PWM channel
		//
		while(SOFTPWM_INLINE_DUTY_CYCLE(softpwm[0]) != 0)
		{
			SOFTPWM_INLINE_DUTY_CYCLE(softpwm[0])--;
			_delay_ms(DELAY_MS);
		}
		while(SOFTPWM_INLINE_DUTY_CYCLE(softpwm[0]) != MAX_PWM_WIDTH)
		{
			SOFTPWM_INLINE_DUTY_CYCLE(softpwm[0])++;
			_delay_ms(DELAY_MS);
		}
		
		while(SOFTPWM_INLINE_DUTY_CYCLE(softpwm[1]) != 0)
		{
			SOFTPWM_INLINE_DUTY_CYCLE(softpwm[1])--;
			_delay_ms(DELAY_MS);
		}
		while(SOFTPWM_INLINE_DUTY_CYCLE(softpwm[1]) != MAX_PWM_WIDTH)
		{
			SOFTPWM_INLINE_DUTY_CYCLE(softpwm[1])++;
			_delay_ms(DELAY_MS);
		}
		
		while(SOFTPWM_INLINE_DUTY_CYCLE(softpwm[2]) != 0)
		{
			SOFTPWM_INLINE_DUTY_CYCLE(softpwm[2])--;
			_delay_ms(DELAY_MS);
		}
		while(SOFTPWM_INLINE_DUTY_CYCLE(softpwm[2]) != MAX_PWM_WIDTH)
		{
			SOFTPWM_INLINE_DUTY_CYCLE(softpwm[2])++;
			_delay_ms(DELAY_MS);
		}
	}
}




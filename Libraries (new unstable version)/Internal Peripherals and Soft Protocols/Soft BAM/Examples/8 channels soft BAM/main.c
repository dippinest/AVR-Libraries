

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include "softbam.h"



// число каналов BAM
//
// -------------------------------------------------------------------------------
// num of BAM channels
//
#define SOFTBAM_NUM_OF_CHANNELS 8


// объявление объекта BAM и массива его каналов
//
// -------------------------------------------------------------------------------
// declaring a BAM object and an array of its channels
//
SOFTBAM_t softbam;

SOFTBAM_Channel_t softbam_channels[SOFTBAM_NUM_OF_CHANNELS];



// инициализируем таймера 2 (Timer2)
//
// -------------------------------------------------------------------------------
// Timer2 initialize
//
inline void TIMER2_Initialize()
{
	TCCR2 = (1 << CS22) | (1 << CS21)   | (1 << WGM21);  // div F_CPU / 256 (16 MHz / 256 = 62500 Hz)
	TIMSK = (1 << OCIE2); // set overflow interrupt
}



// колбэк для изменения периода прерывания таймера по совпадению
//
// -------------------------------------------------------------------------------
// callback for changing the timer interrupt period by coincidence
//
void Timer2_Set_COMP_Prescaler_Callback(uint8_t prescaler)
{
	OCR2 = prescaler;
}


// обработка всех каналов BAM в прерывании по переполнению таймера 2 (Timer2)
//
// -------------------------------------------------------------------------------
// processing of all BAM channels in the overflow interrupt Timer2
//
ISR(TIMER2_COMP_vect)
{
	SOFTBAM_Processing(&softbam);
}




int main(void)
{
	TIMER2_Initialize();
	
	// инициализация портов GPIO и каналов и программного BAM
	//
	// -------------------------------------------------------------------------------
	// initialization of GPIO ports and software PWM channels
	//
	DDRB = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
	

	// инициализируем каналы BAM и её объект
	//
	// первый параметр - указатель на порт GPIO
	// второй параметр - номер канала
	// третий параметр - начальное значение заполнения
	//
	// -------------------------------------------------------------------------------
	//
	// initialize BAM channels and its object
	//
	// first parameter  - a pointer to the GPIO port
	// second parameter - the channel number
	// third parameter  - the initial fill value
	//
	SOFTBAM_Channel_Initialize_Object(&(softbam_channels[0]), T(PORTB), 0, 255);
	SOFTBAM_Channel_Initialize_Object(&(softbam_channels[1]), T(PORTB), 1, 255);
	SOFTBAM_Channel_Initialize_Object(&(softbam_channels[2]), T(PORTB), 2, 255);
	SOFTBAM_Channel_Initialize_Object(&(softbam_channels[3]), T(PORTB), 3, 255);
	SOFTBAM_Channel_Initialize_Object(&(softbam_channels[4]), T(PORTB), 4, 255);
	SOFTBAM_Channel_Initialize_Object(&(softbam_channels[5]), T(PORTB), 5, 255);
	SOFTBAM_Channel_Initialize_Object(&(softbam_channels[6]), T(PORTB), 6, 255);
	SOFTBAM_Channel_Initialize_Object(&(softbam_channels[7]), T(PORTB), 7, 255);
	
	
	SOFTBAM_Initialize_Object(&softbam, softbam_channels, SOFTBAM_NUM_OF_CHANNELS, Timer2_Set_COMP_Prescaler_Callback);
	
	
	
	
	// не забудьте включить глобальные прерывания
	//
	// -------------------------------------------------------------------------------
	// don't forget to enable global interrupts
	//
	sei();
	
	
	while (1)
	{
		#define DELAY_MS 2
		
		for (uint8_t i = 0; i < SOFTBAM_NUM_OF_CHANNELS; ++i)
		{
			// плавно увеличиваем и уменьшаем коэффициент заполнения
			// в цикле для каждого канала BAM
			//
			// -------------------------------------------------------------------------------
			// smoothly increasing and decreasing the duty factor
			// in the cycle for each BAM channel
			//
			while(SOFTBAM_DUTY_CYCLE(softbam_channels[i]) != 0)
			{
				SOFTBAM_DUTY_CYCLE(softbam_channels[i])--;
				_delay_ms(DELAY_MS);
			}
			while(SOFTBAM_DUTY_CYCLE(softbam_channels[i]) != 255)
			{
				SOFTBAM_DUTY_CYCLE(softbam_channels[i])++;
				_delay_ms(DELAY_MS);
			}
		}
	}
}







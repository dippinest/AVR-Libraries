
// ===============================================================================
//
// Библиотека для реализации программной BAM.
//
// BAM (Binary Angle Modulation) - один из методов модуляции аналогового сигнала,
// используя всего один вывод GPIO. В отличии от ШИМ (широтно-импульсной модуляции),
// BAM оперирует не скважностью сигнала, а периодом удержания высокого или низкого
// логического уровня в зависимости от входных данных.
//
// Программная реализация BAM работает быстрее программной реализации ШИМ
// и хорошо подходит в качестве альтернативы последнему для управления светодиодами,
// нашревательными элементами и пр., однако он не рекомендуется для использования
// в индуктивных нагрузках (например, для управления электродвигателями).
// Кроме того, BAM может вносить большое число высокочастотных помех,
// что также может иметь негативное влияние в некоторых случаях.
//
// Некоторые идеи по реализации BAM были взяты из этих статей
// (там же Вы увидите подробное описание BAM):
//
// https://easyelectronics.ru/upravlenie-bolshim-kolichestvom-svetodiodov-cherez-binary-angle-modulation.html
// https://www.drive2.ru/c/2575446/
//
// -------------------------------------------------------------------------------
//
// Library for implementing software BAM.
//
// BAM (Binary Angle Modulation) is one of the methods of modulating
// an analog signal using only one GPIO pin. Unlike PWM (pulse width modulation),
// BAM does not operate with the frequency of the signal, but with the retention
// period of a high or low logic level, depending on the input data.
//
// The software implementation of BAM is faster than the software implementation
// of PWM and is well suited as an alternative to the latter for controlling LEDs,
// heating elements, etc., however, it is not recommended for use in inductive loads
// (for example, for controlling electric motors). In addition, BAM can introduce
// a large number of high-frequency interference, which can also have a negative
// impact in some cases.
//
// Some ideas for implementing BAM were taken from these articles in Russian
// (you will also see a detailed description of BAM there):
//
// https://easyelectronics.ru/upravlenie-bolshim-kolichestvom-svetodiodov-cherez-binary-angle-modulation.html
// https://www.drive2.ru/c/2575446/
//
// ===============================================================================


#ifndef SOFTBAM_H_
#define SOFTBAM_H_


#include <avr/io.h>

#include <stdint.h>


// ===============================================================================


#ifndef T
#define T(P) ((uint8_t*)&P)
#endif


typedef struct
{
	uint8_t *softbam_channel_port;
	uint8_t  softbam_channel_pin;
	
	uint8_t  softbam_channel_duty_cycle;
	uint8_t  softbam_channel_duty_cycle_buf;

} SOFTBAM_Channel_t;


typedef struct
{
	SOFTBAM_Channel_t *channels;
	
	uint8_t num_of_channels;
	
	uint8_t bits_counter;
	
	
	void (*prescaler_callback)(uint8_t prescaler);

} SOFTBAM_t;


// ===============================================================================


SOFTBAM_t SOFTBAM_Create_Object(SOFTBAM_Channel_t *channels, const uint8_t num_of_channels, void (*callback_function)(uint8_t prescaler));

SOFTBAM_Channel_t SOFTBAM_Channel_Create_Object(uint8_t *port, uint8_t pin, uint8_t duty_cycle);


// ===============================================================================


#define SOFTBAM_DUTY_CYCLE(SOFTBAMCHANNEL) (SOFTBAMCHANNEL.softbam_channel_duty_cycle)


// ===============================================================================


void SOFTBAM_Processing(SOFTBAM_t *bam);


#endif




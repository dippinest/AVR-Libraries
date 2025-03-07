

// ===============================================================================
//
// Библиотека для работы с внутренним модулем АЦП. Большинство функций данной
// библиотеки являются блокирующими, однако есть возможность использовать неблокирующий
// режим работы модуля АЦП, используя чистые прерывания или же коллбэк-функции
// (это можно настроить в файле конфигурации adc_configuration.h)
//
// -------------------------------------------------------------------------------
//
// Library for working with the internal ADC module. Most of the functions of this
// library are blocking, but it is possible to use a non-blocking mode of operation
// of the ADC module using pure interrupts or callback functions
// (this can be configured in the configuration file adc_configuration.h)
//
// ===============================================================================


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


#ifndef ADCSRA
#define ADCSRA ADCSR
#endif


#include "adc_configuration.h"


#define ADC_VREF_SOURCE_EXTERNAL_AREF 0b00
#define ADC_VREF_SOURCE_EXTERNAL_AVCC 0b01
#define ADC_VREF_SOURCE_INTERNAL      0b11

#define ADC_PRESCALER_2    0b001
#define ADC_PRESCALER_4    0b010
#define ADC_PRESCALER_8    0b011
#define ADC_PRESCALER_16   0b100
#define ADC_PRESCALER_32   0b101
#define ADC_PRESCALER_64   0b110
#define ADC_PRESCALER_128  0b111



// ===============================================================================


#define ADC_GET_FLOAT_VOLTAGE(ADC_VAL, ADC_BITRATE, MAX_REF_VOLTAGE) \
							(((float)MAX_REF_VOLTAGE / ((1ULL << ADC_BITRATE) - 1)) * ADC_VAL)
							
#define ADC_GET_DATA_SIZE_FOR_OVERSAMPLING(BITRATE) (1ULL << (2 * (BITRATE - 10)))


// ===============================================================================



inline void ADC_Set_Enable(bool is_enable)
{
	if (is_enable)
	{
		ADCSRA |=  (1 << ADEN);
	}
	else
	{
		ADCSRA &= ~(1 << ADEN);
	}
}

inline void ADC_Set_Interrupt_Enable(bool is_enable)
{
	if (is_enable)
	{
		ADCSRA |=  (1 << ADIE);
	}
	else
	{
		ADCSRA &= ~(1 << ADIE);
	}
}

inline void ADC_Set_Channel(uint8_t channel)
{
	ADMUX &= 0b11110000;
	ADMUX |= channel;
}

inline void ADC_Set_Prescaler(uint8_t prescaler)
{
	ADCSRA &= 0b11111000;
	ADCSRA |= prescaler;
}

inline void ADC_Set_VREF_Source(const uint8_t vref)
{
	ADMUX &= 0b00111111;
	ADMUX |= (vref << 6);
}

inline void ADC_Start_Conversion()
{
	ADCSRA |= (1 << ADSC);
}

inline bool ADC_Is_Enable()
{
	if (ADCSRA & (1 << ADEN))
	{
		return true;
	}
	
	return false;
}

inline bool ADC_Is_Interrupt_Enable()
{
	if (ADCSRA & (1 << ADIE))
	{
		return true;
	}
	
	return false;
}

inline uint8_t ADC_Get_Channel()
{
	return ADMUX;
}

inline uint8_t ADC_Get_Prescaler()
{
	uint8_t prescaler = ADCSRA & 0b111;
	
	if (prescaler == 0 || prescaler == 1)
	{
		return ADC_PRESCALER_2;
	}
	
	return prescaler;
}

inline uint8_t ADC_Get_VREF_Source()
{
	return ADMUX >> 6;
}

inline void ADC_Initialize(uint8_t channel, uint8_t prescaler, uint8_t vref_source, bool is_enable)
{
	ADC_Set_Channel(channel);
	ADC_Set_Prescaler(prescaler);
	ADC_Set_VREF_Source(vref_source);
	ADC_Set_Enable(is_enable);
}


// ===============================================================================


void ADC_Set_Max_Reference_Voltage_Value(float voltage);

float ADC_Get_Max_Reference_Voltage_Value();

uint16_t ADC_Get_Value_10bit();

float ADC_Get_Voltage_Value();

float ADC_Get_Voltage_Value_From_Measured_Value(uint16_t adc_value);


// ===============================================================================


uint32_t ADC_Get_Oversampling_Value(uint8_t required_bitrate);

uint32_t ADC_Get_Oversampling_Value_From_Set_Of_Dimensions
(
	uint8_t   required_bitrate,
	uint16_t *set_of_dimensions,
	uint8_t   set_of_dimensions_size
);


// ===============================================================================



//
// функции для получения значения шума на неподключённых каналах АЦП
// (для генерации случайных чисел)
//
//
// Внимание! Я не рекомендую использовать эти функции для серьёзных применений
// (например, для криптографии), поскольку числа на самом деле не являются случайными
// (смотрите статистический тест случайности на Python в примерах кода).
//
// Я рекомендую использовать эти функции для начальной инициализации функции srand()
//
// -------------------------------------------------------------------------------
//
// functions for obtaining the noise value on unconnected ADC channels
// (for generating random numbers)
//
// ATN! I do not recommend using this function for serious applications (for example,
// for cryptography), since the numbers are not truly random
// (see the statistical test in Python in the code examples).
//
// I recommend use it for the initial initialization of the srand() function
//


uint8_t ADC_Get_Random_Entropy_Value_8bit(uint8_t channel);

uint16_t ADC_Get_Random_Entropy_Value_16bit(uint8_t channel);

uint32_t ADC_Get_Random_Entropy_Value_32bit(uint8_t channel);


// ===============================================================================


#ifdef ADC_USE_CALLBACK

void ADC_Set_Reception_Buffer_Ptr(const void *buffer);

void ADC_Set_Reception_Buffer_Size(const uint16_t buffer_size);

void ADC_Set_Reception_CallBack_Function(void (*callback_function)());

bool ADC_Is_Reception_Buffer_Filled();

void *ADC_Get_Reception_Buffer_Ptr();

uint16_t ADC_Get_Reception_Buffer_Size();

void *ADC_Get_Reception_CallBack_Function();

uint16_t ADC_Get_Current_Reception_Buffer_Fullness();


#endif

#endif



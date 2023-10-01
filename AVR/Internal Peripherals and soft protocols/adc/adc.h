
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



// макроопределения для разных микроконтроллеров
// -------------------------------------------------------------------------------
// macro definitions for different microcontrollers
#ifndef ADCSRA
#define ADCSRA ADCSR
#endif



#include "adc_configuration.h"



// макросы для определения источника опорного напряжения
// -------------------------------------------------------------------------------
// macros for determining the reference voltage source
#define ADC_VREF_SOURCE_EXTERNAL_AREF 0b00
#define ADC_VREF_SOURCE_EXTERNAL_AVCC 0b01
#define ADC_VREF_SOURCE_INTERNAL      0b11



// макросы для определения предделителя АЦП
// -------------------------------------------------------------------------------
// macros for determining the ADC prescaler
#define ADC_PRESCALER_2    0b001
#define ADC_PRESCALER_4    0b010
#define ADC_PRESCALER_8    0b011
#define ADC_PRESCALER_16   0b100
#define ADC_PRESCALER_32   0b101
#define ADC_PRESCALER_64   0b110
#define ADC_PRESCALER_128  0b111


// ===============================================================================


// функция для активации (деактивации) модуля АЦП
// -------------------------------------------------------------------------------
// function for activating (deactivating) the ADC module
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


// функция для активации (деактивации) прерываний модуля АЦП
// -------------------------------------------------------------------------------
// function for activating (deactivating) interrupts of the ADC module
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


// функция для выбора канала АЦП
// -------------------------------------------------------------------------------
// function for selecting the ADC channel
inline void ADC_Set_Channel(uint8_t channel)
{
	ADMUX &= 0b11110000;
	ADMUX |= channel;
}


// функция для установки предделителя АЦП
// -------------------------------------------------------------------------------
// function for setting the ADC prescaler
inline void ADC_Set_Prescaler(uint8_t prescaler)
{
	ADCSRA &= 0b11111000;
	ADCSRA |= prescaler;
}


// функция для установки источника опорного напряжения АЦП
// -------------------------------------------------------------------------------
// function for setting the ADC reference voltage source
inline void ADC_Set_VREF_Source(const uint8_t vref)
{
	ADMUX &= 0b00111111;
	ADMUX |= (vref << 6);
}


// функция для запуска процедуры преобразования
// -------------------------------------------------------------------------------
// function to start the conversion procedure
inline void ADC_Start_Conversion()
{
	ADCSRA |= (1 << ADSC);
}


// функция, возвращающая true если модуль АЦП включен (иначе - вернёт false)
// -------------------------------------------------------------------------------
// function that returns true if the ADC module is enabled
// (otherwise it will return false)
inline bool ADC_Is_Enable()
{
	if (ADCSRA & (1 << ADEN))
	{
		return true;
	}
	
	return false;
}


// функция, возвращающая true если прерывания модуля АЦП разрешены
// (иначе - вернёт false)
// -------------------------------------------------------------------------------
// function that returns true if interrupts of the ADC module are allowed
// (otherwise it will return false)
inline bool ADC_Is_Interrupt_Enable()
{
	if (ADCSRA & (1 << ADIE))
	{
		return true;
	}
	
	return false;
}


// функция, возвращающая номер текущего канала АЦП
// -------------------------------------------------------------------------------
// function that returns the number of the current ADC channel
inline uint8_t ADC_Get_Channel()
{
	return ADMUX;
}


// функция, возвращающая предделитель АЦП
// -------------------------------------------------------------------------------
// function that returns the ADC predelector
inline uint8_t ADC_Get_Prescaler()
{
	uint8_t prescaler = ADCSRA & 0b111;
	
	if (prescaler == 0 || prescaler == 1)
	{
		return ADC_PRESCALER_2;
	}
	
	return prescaler;
}


// функция, возвращающая источник опорного напряжения АЦП
// -------------------------------------------------------------------------------
// function that returns the ADC reference voltage source
inline uint8_t ADC_Get_VREF_Source()
{
	return ADMUX >> 6;
}


// функция для начальной инициализации модуля АЦП
// -------------------------------------------------------------------------------
// function for initial initialization of the ADC module
inline void ADC_Initialize(uint8_t channel, uint8_t prescaler, uint8_t vref_source, bool is_enable)
{
	ADC_Set_Channel(channel);
	ADC_Set_Prescaler(prescaler);
	ADC_Set_VREF_Source(vref_source);
	ADC_Set_Enable(is_enable);
}


// ===============================================================================


// функция для установки максимального значения измеряемого напряжения
// -------------------------------------------------------------------------------
// function for setting the maximum value of the measured voltage
void ADC_Set_Max_Reference_Voltage_Value(float voltage);


// функция для получения максимального значения измеряемого напряжения
// -------------------------------------------------------------------------------
// function for obtaining the maximum value of the measured voltage
float ADC_Get_Max_Reference_Voltage_Value();


// функция для измерения и получения значения напряжения
// (в виде 10-ти битного значения)
// -------------------------------------------------------------------------------
// function for measuring and obtaining the voltage value
// (in the form of a 10-bit value)
uint16_t ADC_Get_Value_10bit();


// функция для измерения и получения значения напряжения (в вольтах)
// -------------------------------------------------------------------------------
// function for measuring and obtaining voltage values (in volts)
float ADC_Get_Voltage_Value();


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



// ===============================================================================
// эти функции доступны, если определён макрос ADC_USE_CALLBACK для
// асинхронного приёма значений из АЦП в буфер приёма
// (в файле adc_configuration.h)
// -------------------------------------------------------------------------------
// these functions are available if the ADC_USE_CALLBACK macro is defined to
// asynchronously receive values from the ADC to the receive buffer
// (in the adc_configuration.h file)
// ===============================================================================
#ifdef ADC_USE_CALLBACK


// функция для установки указателя на приёмный буфер
// -------------------------------------------------------------------------------
// function for setting the pointer to the receiving buffer
void ADC_Set_Reception_Buffer_Ptr(const void *buffer);


// функция для установки размера приёмного буфера
// -------------------------------------------------------------------------------
// function for setting the size of the receiving buffer
void ADC_Set_Reception_Buffer_Size(const uint16_t buffer_size);


// функция для установки указателя на колбэк-функцию
// -------------------------------------------------------------------------------
// function for setting the pointer to the callback function
void ADC_Set_Reception_CallBack_Function(void (*callback_function)());


// функция, возвращающая true если приёмный буфер АЦП
// полностью заполнен (иначе - вернёт false)
// -------------------------------------------------------------------------------
// function that returns true if the ADC receiving buffer is
// completely full (otherwise it will return false)
bool ADC_Is_Reception_Buffer_Filled();


// функция, возвращающая указатель на приёмный буфер АЦП
// -------------------------------------------------------------------------------
// function that returns a pointer to the receiving buffer of the ADC
void *ADC_Get_Reception_Buffer_Ptr();


// функция, возвращающая размер приёмного буфера АЦП
// -------------------------------------------------------------------------------
// function that returns the size of the ADC receiving buffer
uint16_t ADC_Get_Reception_Buffer_Size();


// функция, возвращающая указатель на функцию-колбэк
// -------------------------------------------------------------------------------
// function that returns a pointer to a callback function
void *ADC_Get_Reception_CallBack_Function();


// функция, возвращающая количество уже полученных значений
// АЦП в приёмном буфере
// -------------------------------------------------------------------------------
// function that returns the number of ADC values already
// received in the receiving buffer
uint16_t ADC_Get_Current_Reception_Buffer_Fullness();

#endif

#endif

#endif

#endif



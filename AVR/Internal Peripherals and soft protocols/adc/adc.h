
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
#define ADC_VREF_SOURCE_INTERNAL      0b11 // internal VREF 2.56 Volts

#define ADC_PRESCALER_2    0b001
#define ADC_PRESCALER_4    0b010
#define ADC_PRESCALER_8    0b011
#define ADC_PRESCALER_16   0b100
#define ADC_PRESCALER_32   0b101
#define ADC_PRESCALER_64   0b110
#define ADC_PRESCALER_128  0b111

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

inline void ADC_Set_Interrupt_Is_Enable(bool is_enable)
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

inline void ADC_Connect_To_Ground()
{
	ADC_Set_Channel(0b1111);
}

inline void ADC_Connect_To_Vbg()
{
	ADC_Set_Channel(0b1110);
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

inline bool ADC_Interrupt_Is_Enable()
{
	if (ADCSRA & (1 << ADIE))
	{
		return true;
	}
	
	return false;
}

inline uint8_t ADC_Get_Channel()
{
	return ADMUX & 0b1111;
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

// ===============================================================================

// ATN! I do not recommend using this function for serious applications,
// since the numbers are not truly random (see the statistical test in Python).
//
// I recommend use it for the initial initialization of the srand() function

uint8_t ADC_Get_Random_Entropy_Value_8bit(uint8_t channel);

uint16_t ADC_Get_Random_Entropy_Value_16bit(uint8_t channel);

uint32_t ADC_Get_Random_Entropy_Value_32bit(uint8_t channel);

// ===============================================================================

#ifdef ADC_USE_CALLBACK

void ADC_Set_Reception_Buffer_Ptr(const void *buffer);

void ADC_Set_Reception_Buffer_Size(const uint16_t buffer_size);

void ADC_Set_Reception_CallBack_Function(void (*callback_function)());

bool ADC_Get_Reception_Status();

bool ADC_Reception_Buffer_Is_Filled();

void *ADC_Get_Reception_Buffer_Ptr();

uint16_t ADC_Get_Reception_Buffer_Size();

void *ADC_Get_Reception_CallBack_Function();

uint16_t ADC_Get_Current_Reception_Buffer_Fullness();

#endif

#endif

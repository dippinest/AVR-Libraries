#include "adc.h"

static float _max_ref_voltage = 5.0f; // default value

void ADC_Set_Max_Reference_Voltage_Value(float voltage)
{
	_max_ref_voltage = voltage;
}

uint16_t ADC_Get_Value_10bit()
{
	ADC_Start_Conversion();
	while (ADCSRA & (1 << ADSC));
	return ADC;
}

float ADC_Get_Voltage_Value()
{
	return (_max_ref_voltage / 1023) * ADC_Get_Value_10bit();
}

// ===============================================================================

uint8_t ADC_Get_Random_Entropy_Value_8bit(uint8_t channel)
{
	uint8_t random_entropy = 0;
	
	uint8_t tmp_ADMUX  = ADMUX;
	uint8_t tmp_ADCSRA = ADCSRA;
	
	ADC_Set_Channel(channel);
	ADC_Set_Prescaler(ADC_PRESCALER_128);
	
	for (uint8_t i = 0; i < 8; ++i)
	{
		random_entropy |= (ADC_Get_Value_10bit() & 0b1) << i;
	}
	
	ADCSRA = tmp_ADCSRA;
	ADMUX  = tmp_ADMUX;
	
	return random_entropy;
}

uint16_t ADC_Get_Random_Entropy_Value_16bit(uint8_t channel)
{
	uint16_t random_entropy = 0;
	
	uint8_t tmp_ADMUX  = ADMUX;
	uint8_t tmp_ADCSRA = ADCSRA;
	
	ADC_Set_Channel(channel);
	ADC_Set_Prescaler(ADC_PRESCALER_128);
	
	for (uint8_t i = 0; i < 16; ++i)
	{
		random_entropy |= (ADC_Get_Value_10bit() & 0b1) << i;
	}
	
	ADCSRA = tmp_ADCSRA;
	ADMUX  = tmp_ADMUX;
	
	return random_entropy;
}

uint32_t ADC_Get_Random_Entropy_Value_32bit(uint8_t channel)
{
	uint32_t random_entropy = 0;
	
	uint8_t tmp_ADMUX  = ADMUX;
	uint8_t tmp_ADCSRA = ADCSRA;
	
	ADC_Set_Channel(channel);
	ADC_Set_Prescaler(ADC_PRESCALER_128);
	
	for (uint8_t i = 0; i < 32; ++i)
	{
		random_entropy |= (ADC_Get_Value_10bit() & 0b1) << i;
	}
	
	ADCSRA = tmp_ADCSRA;
	ADMUX  = tmp_ADMUX;
	
	return random_entropy;
}
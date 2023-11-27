
#include "adc.h"

static float _max_ref_voltage = 5.0f; // default value

void ADC_Set_Max_Reference_Voltage_Value(float voltage)
{
	_max_ref_voltage = voltage;
}

float ADC_Get_Max_Reference_Voltage_Value()
{
	return _max_ref_voltage;
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

float ADC_Get_Voltage_Value_From_Value(uint16_t adc_value)
{
	return (_max_ref_voltage / 1023) * adc_value;
}


// ===============================================================================


uint32_t ADC_Get_Oversampling_Value(uint8_t bitrate)
{
	uint32_t oversampling_value = 0;
	
	uint32_t count = ADC_GET_DATA_SIZE_FOR_OVERSAMPLING(bitrate);
	
	for (uint32_t i = 0; i < count; ++i)
	{
		oversampling_value += ADC_Get_Value_10bit();
	}
	
	return (uint32_t)(oversampling_value >> (bitrate - 10));
}

uint32_t ADC_Get_Oversampling_Value_From_Set_Of_Dimensions
(
	uint8_t   bitrate,
	uint16_t *set_of_dimensions,
	uint8_t   set_of_dimensions_size
)
{
	uint32_t oversampling_value = 0;
	
	uint32_t count = ADC_GET_DATA_SIZE_FOR_OVERSAMPLING(bitrate);
	
	for (uint32_t i = 0; i < count; ++i)
	{
		if (i < set_of_dimensions_size)
		{
			oversampling_value += set_of_dimensions[i];
		}
	}
	
	return (uint32_t)(oversampling_value >> (bitrate - 10));
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

// ===============================================================================

#ifdef ADC_USE_CALLBACK

static uint16_t*  _reception_buffer = NULL;
static volatile uint16_t  _reception_buffer_size;
static volatile uint16_t  _reception_counter            = 0;
static volatile bool      _reception_buffer_is_filled   = false;

static void (*_reception_callback)() = NULL;

void ADC_Set_Reception_Buffer_Ptr(const void *buffer)
{
	_reception_buffer = (uint16_t*)buffer;
}

void ADC_Set_Reception_Buffer_Size(const uint16_t buffer_size)
{
	_reception_buffer_size = buffer_size;
}

void ADC_Set_Reception_CallBack_Function(void (*callback_function)())
{
	_reception_callback = callback_function;
}

bool ADC_Is_Reception_Buffer_Filled()
{
	return _reception_buffer_is_filled;
}

void *ADC_Get_Reception_Buffer_Ptr()
{
	return _reception_buffer;
}

uint16_t ADC_Get_Reception_Buffer_Size()
{
	return _reception_buffer_size;
}

void *ADC_Get_Reception_CallBack_Function()
{
	return _reception_callback;
}

uint16_t ADC_Get_Current_Reception_Buffer_Fullness()
{
	return _reception_counter;
}


// ===============================================================================



ISR(ADC_vect)
{
	if (_reception_buffer != NULL)
	{
		_reception_buffer[_reception_counter] = ADC;
		
		++_reception_counter;
		
		if (_reception_counter >= _reception_buffer_size)
		{
			_reception_buffer_is_filled = true;
			
			_reception_callback();
			
			_reception_counter = 0;
			_reception_buffer_is_filled = false;
		}
		else
		{
			ADC_Start_Conversion();
		}
	}
}

#endif



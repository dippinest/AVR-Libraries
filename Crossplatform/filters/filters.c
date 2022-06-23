
#include "filters.h"

int16_t Filters_Get_Rand_Noise_Int16(int16_t amp)
{
	int16_t noise = rand() % amp;
	
	if (rand() & 1)
	{
		noise = -noise;
	}
	
	return noise;
}

int16_t Filters_Get_Splash_Int16(int16_t amp, uint16_t frequency)
{
	uint16_t rand_val1 = rand(), rand_val2 = 0;
	
	if (rand_val1 <= frequency)
	{
		rand_val2 = rand() % amp;
		
		if (rand_val1 & 1)
		{
			rand_val2 = -rand_val2;
		}
	}
	
	return rand_val2;
}

float Filters_Get_Rand_Noise_Float(float amp)
{
	float noise = (float)rand() / (float)(RAND_MAX / amp);
	
	if (rand() & 1)
	{
		noise = -noise;
	}
	
	return noise;
}

float Filters_Get_Splash_Float(float amp, uint16_t frequency)
{
	uint16_t rand_val1 = rand();
	float    rand_val2 = 0;
	
	if (rand_val1 <= frequency)
	{
		rand_val2 = (float)rand() / (float)(RAND_MAX / amp);
		
		if (rand_val1 & 1)
		{
			rand_val2 = -rand_val2;
		}
	}
	
	return rand_val2;
}

// ===============================================================================

float Filters_Get_Gaussian_Noise(float amp)
{
	#define PI 3.1415926536

	float temp1, temp2, result;
	int p = 1;

	while (p > 0)
	{
		temp2 = (rand() / ((float)RAND_MAX));

		if (temp2 == 0)
		{
			p = 1;
		}
		else
		{
			p = -1;
		}

	}

	temp1 = cos((2.0 * (float)PI) * rand() / ((float)RAND_MAX));
	result = sqrt(-2.0 * log(temp2)) * temp1;

	return result * amp;

}

// ===============================================================================

int8_t Filters_SMA_Int8(int8_t *buffer, uint16_t buffer_size, uint16_t *index, int8_t value)
{
	if (*index >= buffer_size)
	{
		*index = 0;
	}
	
	buffer[*index] = value;
	++(*index);
	
	int16_t sum = 0;
	
	for (uint16_t i = 0; i < buffer_size; ++i)
	{
		sum += buffer[i];
	}
	
	return sum / buffer_size;
}

int16_t Filters_SMA_Int16(int16_t *buffer, uint16_t buffer_size, uint16_t *index, int16_t value)
{
	if (*index >= buffer_size)
	{
		*index = 0;
	}
	
	buffer[*index] = value;
	++(*index);
	
	int32_t sum = 0;
	
	for (uint16_t i = 0; i < buffer_size; ++i)
	{
		sum += buffer[i];
	}
	
	return sum / buffer_size;
}

int32_t Filters_SMA_Int32(int32_t *buffer, uint16_t buffer_size, uint16_t *index, int32_t value)
{
	if (*index >= buffer_size)
	{
		*index = 0;
	}
	
	buffer[*index] = value;
	++(*index);
	
	int64_t sum = 0;
	
	for (uint16_t i = 0; i < buffer_size; ++i)
	{
		sum += buffer[i];
	}
	
	return sum / buffer_size;
}

float Filters_SMA_Float(float *buffer, uint16_t buffer_size, uint16_t *index, float value)
{
	if (*index >= buffer_size)
	{
		*index = 0;
	}
	
	buffer[*index] = value;
	++(*index);
	
	float sum = 0;
	
	for (uint16_t i = 0; i < buffer_size; ++i)
	{
		sum += buffer[i];
	}
	
	return sum / buffer_size;
}

// ===============================================================================

int8_t Filters_SMM_Int8(int8_t *buffer, uint16_t buffer_size, uint16_t *index, int8_t value)
{
	if (*index >= buffer_size)
	{
		*index = 0;
	}
	
	buffer[*index] = value;
	++(*index);
	
	int8_t tmp;
	
	// for sorting the array used the Shell's algorithm
	for (int32_t s = buffer_size >> 1; s > 0; s >>= 1)
	{
		for (int32_t i = s; i < buffer_size; ++i)
		{
			for (int32_t j = i - s; j >= 0 && buffer[j] > buffer[j + s]; j -= s)
			{
				tmp = buffer[j];
				buffer[j] = buffer[j + s];
				buffer[j + s] = tmp;
			}
		}
	}
	
	return buffer[buffer_size >> 1];
}

int16_t Filters_SMM_Int16(int16_t *buffer, uint16_t buffer_size, uint16_t *index, int16_t value)
{
	if (*index >= buffer_size)
	{
		*index = 0;
	}
	
	buffer[*index] = value;
	++(*index);
	
	int16_t tmp;
	
	// for sorting the array used the Shell's algorithm
	for (int32_t s = buffer_size >> 1; s > 0; s >>= 1)
	{
		for (int32_t i = s; i < buffer_size; ++i)
		{
			for (int32_t j = i - s; j >= 0 && buffer[j] > buffer[j + s]; j -= s)
			{
				tmp = buffer[j];
				buffer[j] = buffer[j + s];
				buffer[j + s] = tmp;
			}
		}
	}
	
	return buffer[buffer_size >> 1];
}

int32_t Filters_SMM_Int32(int32_t *buffer, uint16_t buffer_size, uint16_t *index, int32_t value)
{
	if (*index >= buffer_size)
	{
		*index = 0;
	}
	
	buffer[*index] = value;
	++(*index);
	
	int32_t tmp;
	
	// for sorting the array used the Shell's algorithm
	for (int32_t s = buffer_size >> 1; s > 0; s >>= 1)
	{
		for (int32_t i = s; i < buffer_size; ++i)
		{
			for (int32_t j = i - s; j >= 0 && buffer[j] > buffer[j + s]; j -= s)
			{
				tmp = buffer[j];
				buffer[j] = buffer[j + s];
				buffer[j + s] = tmp;
			}
		}
	}
	
	return buffer[buffer_size >> 1];
}

float Filters_SMM_Float(float *buffer, uint16_t buffer_size, uint16_t *index, float value)
{
	if (*index >= buffer_size)
	{
		*index = 0;
	}
	
	buffer[*index] = value;
	++(*index);
	
	float tmp;
	
	// for sorting the array used the Shell's algorithm
	for (int32_t s = buffer_size >> 1; s > 0; s >>= 1)
	{
		for (int32_t i = s; i < buffer_size; ++i)
		{
			for (int32_t j = i - s; j >= 0 && buffer[j] > buffer[j + s]; j -= s)
			{
				tmp = buffer[j];
				buffer[j] = buffer[j + s];
				buffer[j + s] = tmp;
			}
		}
	}
	
	return buffer[buffer_size >> 1];
}

// ===============================================================================

int8_t Filters_LWMA_Int8(int8_t *buffer, uint16_t buffer_size, uint16_t *index, int16_t value)
{
	if (*index >= buffer_size)
	{
		*index = 0;
	}
	
	buffer[*index] = value;
	++(*index);
	
	int16_t sum = 0;
	
	for (uint16_t i = 0; i < buffer_size; ++i)
	{
		sum += buffer[i] * (buffer_size - i);
	}
	
	return sum * (2.0 / (buffer_size * (buffer_size + 1)));
}

int16_t Filters_LWMA_Int16(int16_t *buffer, uint16_t buffer_size, uint16_t *index, int16_t value)
{
	if (*index >= buffer_size)
	{
		*index = 0;
	}
	
	buffer[*index] = value;
	++(*index);
	
	int32_t sum = 0;
	
	for (uint16_t i = 0; i < buffer_size; ++i)
	{
		sum += buffer[i] * (buffer_size - i);
	}
	
	return sum * (2.0 / (buffer_size * (buffer_size + 1)));
}

int32_t Filters_LWMA_Int32(int32_t *buffer, uint16_t buffer_size, uint16_t *index, int32_t value)
{
	if (*index >= buffer_size)
	{
		*index = 0;
	}
	
	buffer[*index] = value;
	++(*index);
	
	int64_t sum = 0;
	
	for (uint16_t i = 0; i < buffer_size; ++i)
	{
		sum += buffer[i] * (buffer_size - i);
	}
	
	return sum * (2.0 / (buffer_size * (buffer_size + 1)));
}

float Filters_LWMA_Float(float *buffer, uint16_t buffer_size, uint16_t *index, float value)
{
	if (*index >= buffer_size)
	{
		*index = 0;
	}
	
	buffer[*index] = value;
	++(*index);
	
	float sum = 0;
	
	for (uint16_t i = 0; i < buffer_size; ++i)
	{
		sum += buffer[i] * (buffer_size - i);
	}
	
	return sum * (2.0 / (buffer_size * (buffer_size + 1)));
}

// ===============================================================================

int8_t Filters_EMA_Int8(int8_t *accumulator, float coef, int8_t value)
{
	*accumulator = (value * coef) + (*accumulator * (1.0 - coef));
	
	return *accumulator;
}

int16_t Filters_EMA_Int16(int16_t *accumulator, float coef, int16_t value)
{
	*accumulator = (value * coef) + (*accumulator * (1.0 - coef));
	
	return *accumulator;
}

int32_t Filters_EMA_Int32(int32_t *accumulator, float coef, int32_t value)
{
	*accumulator = (value * coef) + (*accumulator * (1.0 - coef));
	
	return *accumulator;
}

float Filters_EMA_Float(float *accumulator, float coef, float value)
{
	*accumulator = (value * coef) + (*accumulator * (1.0 - coef));
	
	return *accumulator;
}

// ===============================================================================

int8_t Filters_CMA_Int8(int16_t *accumulator, int8_t *old_value, uint16_t filter_order, int8_t value)
{
	*accumulator += value - *old_value;
	
	*old_value = *accumulator / filter_order;
	
	return *old_value;
}

int16_t Filters_CMA_Int16(int32_t *accumulator, int16_t *old_value, uint16_t filter_order, int16_t value)
{
	*accumulator += value - *old_value;
	
	*old_value = *accumulator / filter_order;
	
	return *old_value;
}

int32_t Filters_CMA_Int32(int64_t *accumulator, int32_t *old_value, uint16_t filter_order, int32_t value)
{
	*accumulator += value - *old_value;
	
	*old_value = *accumulator / filter_order;
	
	return *old_value;
}

float Filters_CMA_Float(float *accumulator, float *old_value, uint16_t filter_order, float value)
{
	*accumulator += value - *old_value;
	
	*old_value = *accumulator / filter_order;
	
	return *old_value;
}

// ===============================================================================

int8_t Filters_RMA_Int8(int8_t *accumulator, const uint16_t filter_order, int8_t value)
{
	*accumulator =  value + (*accumulator * (filter_order - 1));
	*accumulator /= filter_order;
	
	return *accumulator;
}

int16_t Filters_RMA_Int16(int16_t *accumulator, const uint16_t filter_order, int16_t value)
{
	*accumulator =  value + (*accumulator * (filter_order - 1));
	*accumulator /= filter_order;
	
	return *accumulator;
}

int32_t Filters_RMA_Int32(int32_t *accumulator, const uint16_t filter_order, int32_t value)
{
	*accumulator =  value + (*accumulator * (filter_order - 1));
	*accumulator /= filter_order;
	
	return *accumulator;
}

float Filters_RMA_Float(float *accumulator, const uint16_t filter_order, float value)
{
	*accumulator =  value + (*accumulator * (filter_order - 1));
	*accumulator /= filter_order;
	
	return *accumulator;
}

// ===============================================================================

int8_t Filters_Adaptive_EMA_Int8(int8_t *accumulator, int8_t min_value, int8_t max_value, uint8_t noise_max_amp, float coef, int8_t value)
{
	uint8_t delta = abs(value - *accumulator);
	
	if (delta >= noise_max_amp)
	{
		coef += delta / (float)abs(max_value - min_value);
	}
	
	if (coef > 1.0)
	{
		coef = 1.0;
	}
	
	*accumulator = (value * coef) + (*accumulator * (1.0 - coef));
	
	return *accumulator;
}

int16_t Filters_Adaptive_EMA_Int16(int16_t *accumulator, int16_t min_value, int16_t max_value, uint16_t noise_max_amp, float coef, int16_t value)
{
	uint16_t delta = abs(value - *accumulator);
	
	if (delta >= noise_max_amp)
	{
		coef += delta / (float)abs(max_value - min_value);
	}
	
	if (coef > 1.0)
	{
		coef = 1.0;
	}
	
	*accumulator = (value * coef) + (*accumulator * (1.0 - coef));
	
	return *accumulator;
}

int32_t Filters_Adaptive_EMA_Int32(int32_t *accumulator, int32_t min_value, int32_t max_value, uint32_t noise_max_amp, float coef, int32_t value)
{
	uint32_t delta = abs(value - *accumulator);
	
	if (delta >= noise_max_amp)
	{
		coef += delta / (float)abs(max_value - min_value);
	}
	
	if (coef > 1.0)
	{
		coef = 1.0;
	}
	
	*accumulator = (value * coef) + (*accumulator * (1.0 - coef));
	
	return *accumulator;
}

float Filters_Adaptive_EMA_Float(float *accumulator, float min_value, float max_value, float noise_max_amp, float coef, float value)
{
	float delta = fabs(value - *accumulator);
	
	if (delta >= noise_max_amp)
	{
		coef += delta / (float)fabs(max_value - min_value);
	}
	
	if (coef > 1.0)
	{
		coef = 1.0;
	}
	
	*accumulator = (value * coef) + (*accumulator * (1.0 - coef));
	
	return *accumulator;
}

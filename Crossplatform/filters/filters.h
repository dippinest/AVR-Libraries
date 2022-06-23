
#ifndef FILTERS_H_
#define FILTERS_H_

#include <stdint.h>
#include <stdlib.h>
#include <math.h>

// ===============================================================================

// functions for artificial signal noise (can be used in simulation)


int16_t Filters_Get_Rand_Noise_Int16(int16_t amp);

int16_t Filters_Get_Splash_Int16(int16_t amp, uint16_t frequency);

float Filters_Get_Rand_Noise_Float(float amp);

float Filters_Get_Splash_Float(float amp, uint16_t frequency);

float Filters_Get_Gaussian_Noise(float amp);

// ===============================================================================

// simple moving average (FIR filter)


int8_t Filters_SMA_Int8(int8_t *buffer, uint16_t buffer_size, uint16_t *index, int8_t value);

int16_t Filters_SMA_Int16(int16_t *buffer, uint16_t buffer_size, uint16_t *index, int16_t value);

int32_t Filters_SMA_Int32(int32_t *buffer, uint16_t buffer_size, uint16_t *index, int32_t value);

float Filters_SMA_Float(float *buffer, uint16_t buffer_size, uint16_t *index, float value);

// ===============================================================================

// simple moving median (FIR filter)


int8_t Filters_SMM_Int8(int8_t *buffer, uint16_t buffer_size, uint16_t *index, int8_t value);

int16_t Filters_SMM_Int16(int16_t *buffer, uint16_t buffer_size, uint16_t *index, int16_t value);

int32_t Filters_SMM_Int32(int32_t *buffer, uint16_t buffer_size, uint16_t *index, int32_t value);

float Filters_SMM_Float(float *buffer, uint16_t buffer_size, uint16_t *index, float value);

// ===============================================================================

// linearly weighted moving average (IIR filter)


int8_t Filters_LWMA_Int8(int8_t *buffer, uint16_t buffer_size, uint16_t *index, int16_t value);

int16_t Filters_LWMA_Int16(int16_t *buffer, uint16_t buffer_size, uint16_t *index, int16_t value);

int32_t Filters_LWMA_Int32(int32_t *buffer, uint16_t buffer_size, uint16_t *index, int32_t value);

float Filters_LWMA_Float(float *buffer, uint16_t buffer_size, uint16_t *index, float value);

// ===============================================================================

// exponentially weighted moving average (IIR filter)


int8_t Filters_EMA_Int8(int8_t *accumulator, float coef, int8_t value);

int16_t Filters_EMA_Int16(int16_t *accumulator, float coef, int16_t value);

int32_t Filters_EMA_Int32(int32_t *accumulator, float coef, int32_t value);

float Filters_EMA_Float(float *accumulator, float coef, float value);

// ===============================================================================

// cumulative moving average - simplest IIR filter (digital analog RC filter)


int8_t Filters_CMA_Int8(int16_t *accumulator, int8_t *old_value, uint16_t filter_order, int8_t value);

int16_t Filters_CMA_Int16(int32_t *accumulator, int16_t *old_value, uint16_t filter_order, int16_t value);

int32_t Filters_CMA_Int32(int64_t *accumulator, int32_t *old_value, uint16_t filter_order, int32_t value);

float Filters_CMA_Float(float *accumulator, float *old_value, uint16_t filter_order, float value);

// ===============================================================================

// running moving average (IIR filter)


int8_t Filters_RMA_Int8(int8_t *accumulator, const uint16_t filter_order, int8_t value);

int16_t Filters_RMA_Int16(int16_t *accumulator, const uint16_t filter_order, int16_t value);

int32_t Filters_RMA_Int32(int32_t *accumulator, const uint16_t filter_order, int32_t value);

float Filters_RMA_Float(float *accumulator, const uint16_t filter_order, float value);

// ===============================================================================

// adaptive exponentially weighted moving average (IIR filter) - here the coefficient adapts to the difference between the current and the previous value

int8_t Filters_Adaptive_EMA_Int8(int8_t *accumulator, int8_t min_value, int8_t max_value, uint8_t noise_max_amp, float coef, int8_t value);

int16_t Filters_Adaptive_EMA_Int16(int16_t *accumulator, int16_t min_value, int16_t max_value, uint16_t noise_max_amp, float coef, int16_t value);

int32_t Filters_Adaptive_EMA_Int32(int32_t *accumulator, int32_t min_value, int32_t max_value, uint32_t noise_max_amp, float coef, int32_t value);

float Filters_Adaptive_EMA_Float(float *accumulator, float min_value, float max_value, float noise_max_amp, float coef, float value);

#endif

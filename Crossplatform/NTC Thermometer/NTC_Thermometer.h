
#ifndef NTC_THERMOMETER_H_
#define NTC_THERMOMETER_H_

#include "NTC_Thermometer_configuration.h"

//  Function for calculating the temperature using an NTC thermistor.
//
//  The temperature is calculated using the teinhart-Hart equation:
//
//  T = 1 / (A + B*ln(R) + C*[ln(R)]^3), where:
//
//  T       - temperature in Kelvin;
//  R       - measured resistance at the ADC point in ohms
//  A, B, C - coefficients of the Steinhart-Hart equation
//  U can can calculate the coefficients A, B and C using the system of
//  linear equations solution (https://en.wikipedia.org/wiki/Steinhart-Hart_equation)
//  or using a special calculator
//
//
//	Please use a resistor and a thermistor with minimal parameter error.
//
//	Switching scheme:
//
//	+Vcc o----[NTC thermistor]---(ADC point)---[serial resistor]----o GND
//
//	At the ADC point, there is a measurement, the result of which is passed to the function.
//
//	The value of the obtained temperature has an error of +-0.5K.


float NTC_Thermometer_Get_Temperature_To_Kelvin(uint16_t adc_value);

inline float NTC_Thermometer_Convert_Temperature_Kelvin_To_Celsius(float temp_to_kelvin)
{
  return temp_to_kelvin - 273.15f;
}

inline float NTC_Thermometer_Convert_Temperature_Kelvin_To_Fahrenheit(float temp_to_kelvin)
{
  return (1.8f * (temp_to_kelvin - 273.15f)) + 32.0f;
}

#endif

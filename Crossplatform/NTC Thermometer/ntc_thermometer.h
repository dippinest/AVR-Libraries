// ======================================================================================================
//  Header              : ntc_thermometer.h                                                             -
//  Created             : 18.03.2022                                                                    -
//  Author              : Denis Chicherov (dippinest)                                                   -
//  Description         : Declaration and definition of the calculation function                        -
//                        Steinhart-Hart equation for temperature measurement using an NTC thermistor   -
// ======================================================================================================

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

#ifndef NTC_THERMOMETER_H_
#define NTC_THERMOMETER_H_

#include <math.h>
#include <stdint.h>

// coefficient A
#ifndef A_COEF
#error("ntc_thermometer.h error! Please define the macro "A_COEF" in the main project file before including the header file")
#endif

// coefficient B
#ifndef B_COEF
#error("ntc_thermometer.h error! Please define the macro "B_COEF" in the main project file before including the header file")
#endif

// coefficient C
#ifndef C_COEF
#error("ntc_thermometer.h error! Please define the macro "C_COEF" in the main project file before including the header file")
#endif

// serial resistor resistance in ohms
#ifndef SERIAL_R
#error("ntc_thermometer.h error! Please define the macro "SERIAL_R" in the main project file before including the header file")
#endif

// +Vcc voltage
#ifndef U_GEN
#error("ntc_thermometer.h error! Please define the macro "U_GEN" in the main project file before including the header file")
#endif

// ADC reference voltage
#ifndef U_REF
#error("ntc_thermometer.h error! Please define the macro "U_REF" in the main project file before including the header file")
#endif

// ADC max value
#ifndef ADC_MAX_VAL
#error("ntc_thermometer.h error! Please define the macro "ADC_MAX_VAL" in the main project file before including the header file")
#endif

float NTC_Thermometer_Get_Temperature_To_Kelvin(float adc_value)
{
	float U2 = (adc_value / ADC_MAX_VAL) * U_REF;
	float U1 = U_GEN - U2;
	float I  = U2 / SERIAL_R;
	float R  = U1 / I;
	
	float lnR = log(R);
	
	return 1.0 / (A_COEF + (B_COEF * lnR) + (C_COEF * (lnR * lnR * lnR)));
}

float NTC_Thermometer_Get_Temperature_To_Celsius(float adc_value)
{
	float U2 = (adc_value / ADC_MAX_VAL) * U_REF;
	float U1 = U_GEN - U2;
	float I  = U2 / SERIAL_R;
	float R  = U1 / I;
	
	float lnR = log(R);
	
	float t_K = 1.0 / (A_COEF + (B_COEF * lnR) + (C_COEF * (lnR * lnR * lnR)));
	
	return t_K - 273.15f;
}

float NTC_Thermometer_Get_Temperature_To_Fahrenheit(float adc_value)
{
	float U2 = (adc_value / ADC_MAX_VAL) * U_REF;
	float U1 = U_GEN - U2;
	float I  = U2 / SERIAL_R;
	float R  = U1 / I;
	
	float lnR = log(R);
	
	float t_K = 1.0 / (A_COEF + (B_COEF * lnR) + (C_COEF * (lnR * lnR * lnR)));
	
	return (1.8f * (t_K - 273.15f)) + 32.0f;
}


#endif

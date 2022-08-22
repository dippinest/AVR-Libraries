
#include "NTC_Thermometer.h"

float NTC_Thermometer_Get_Temperature_To_Kelvin(uint16_t adc_value)
{
	float U  = ((float)adc_value / ADC_MAX_VAL) * U_REF;
	float R  = SERIAL_R * (U / (U_GEN - U));
	
	float lnR = log(R);
	
	return 1.0 / (A_COEF + (B_COEF * lnR) + (C_COEF * (lnR * lnR * lnR)));
}

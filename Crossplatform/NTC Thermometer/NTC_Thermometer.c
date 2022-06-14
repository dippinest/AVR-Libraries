
#include "NTC_Thermometer.h"

float NTC_Thermometer_Get_Temperature_To_Kelvin(uint16_t adc_value)
{
	float U2 = ((float)adc_value / ADC_MAX_VAL) * U_REF;
	float U1 = U_GEN - U2;
	float I  = U2 / SERIAL_R;
	float R  = U1 / I;
	
	float lnR = log(R);
	
	return 1.0 / (A_COEF + (B_COEF * lnR) + (C_COEF * (lnR * lnR * lnR)));
}

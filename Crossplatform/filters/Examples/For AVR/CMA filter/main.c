
#define F_CPU 16000000UL
#include <util/delay.h>

#include "uart.h"
#include "adc.h"
#include "filters.h"

static float filter_acc = 0, old_value = 0;

#define NOISE_AMPLITUDE   0.25
#define SPLASH_AMPLITUDE  0.8

int main(void)
{
	UART_Initialize(56000, true, false);
	ADC_Initialize(5, ADC_PRESCALER_128, ADC_VREF_SOURCE_EXTERNAL_AVCC, true);
	
	ADC_Set_Max_Reference_Voltage_Value(4.8);
	
	srand(ADC_Get_Random_Entropy_Value_16bit(2));
	
	
	while (1)
	{
		// reading data from ADC with artificial signal noise (I randomly change the voltage on the ADC using a potentiometer)
		float adc_val = ADC_Get_Voltage_Value() + Filters_Get_Gaussian_Noise(NOISE_AMPLITUDE) + Filters_Get_Splash_Float(SPLASH_AMPLITUDE, 1000);
		
		float filtered_adc_val = Filters_CMA_Float(&filter_acc, &old_value, 128, adc_val);
		
		UART_Data_Transmit(&adc_val,          sizeof(float));
		UART_Data_Transmit(&filtered_adc_val, sizeof(float));
		
		_delay_ms(5);
	}
}


#define F_CPU 16000000UL
#include <util/delay.h>

#include "uart.h"
#include "adc.h"
#include "filters.h"

#define  BUFFER_SIZE 32

static int16_t  filter_acc = 0;

static int16_t  filter_buffer[BUFFER_SIZE] = { 0 };
static uint16_t filter_index = 0;

#define NOISE_AMPLITUDE    50
#define SPLASH_AMPLITUDE  200

int main(void)
{
	UART_Initialize(56000, true, false);
	ADC_Initialize(5, ADC_PRESCALER_128, ADC_VREF_SOURCE_EXTERNAL_AVCC, true);
	
	srand(ADC_Get_Random_Entropy_Value_16bit(2));
	
	
	while (1)
	{
		// reading data from ADC with artificial signal noise (I randomly change the voltage on the ADC using a potentiometer)
		int16_t adc_val = ADC_Get_Value_10bit() + Filters_Get_Rand_Noise_Int16(NOISE_AMPLITUDE) + Filters_Get_Splash_Int16(SPLASH_AMPLITUDE, 10000);
		
		// using combination of two filters: SMM filter suppresses sharp splashing and Adaptive_EMA suppresses high-frequency noise
		int16_t filtered_adc_val =
			Filters_Adaptive_EMA_Int16(&filter_acc, 0, 1023, NOISE_AMPLITUDE, 0.02,
				Filters_SMM_Int16(filter_buffer, BUFFER_SIZE, &filter_index, adc_val));
		
		UART_Data_Transmit(&adc_val,          sizeof(int16_t));
		UART_Data_Transmit(&filtered_adc_val, sizeof(int16_t));
		
		_delay_ms(5);
	}
}

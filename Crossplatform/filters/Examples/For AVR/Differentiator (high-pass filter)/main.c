
#define F_CPU 16000000UL
#include <util/delay.h>

#include "uart.h"
#include "adc.h"
#include "filters.h"

#define  BUFFER_SIZE 32

static float filter_buffer[BUFFER_SIZE] = { 0 };
static uint16_t filter_index = 0;

int main(void)
{
	UART_Initialize(56000, true, false);
	ADC_Initialize(5, ADC_PRESCALER_128, ADC_VREF_SOURCE_EXTERNAL_AVCC, true);
	
	while (1)
	{
		// ===============================================================================
		
		// simulation of an ideal square wave signal
		
		static uint8_t i = 0;
		
		float val = 5;
		
		if(i++ < 128)
		{
			val = 0;
		}
		
		// ===============================================================================
		
		
		
		// high frequency signal = val - low frequency signal
		float diff_val = val - Filters_SMA_Float(filter_buffer, BUFFER_SIZE, &filter_index, val);
		
		UART_Data_Transmit(&val,     sizeof(float));
		UART_Data_Transmit(&diff_val, sizeof(float));
		
		_delay_ms(5);
	}
}


#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "adc.h"

#define ADC_BUF_SIZE 8
static uint16_t adc_buffer[ADC_BUF_SIZE];

// ATN! when working directly with the "ADC_vect"
// interrupt, comment out #define ADC_USE_CALLBACK
// in the adc_callback_configuration.h file!

ISR(ADC_vect)
{
	static uint8_t i = 0;
	
	adc_buffer[i] = ADC;
	
	++i;
	
	if (i >= ADC_BUF_SIZE)
	{
		i = 0;
	}
	
	ADC_Start_Conversion();
}

int main(void)
{
	UART_Initialize(9600, true, false);
	
	sei();
	
	ADC_Initialize(0, ADC_PRESCALER_128, ADC_VREF_SOURCE_EXTERNAL_AVCC, true);
	ADC_Set_Interrupt_Enable();
	
	ADC_Start_Conversion();
	
	// now data buffering in the interrupt will occur constantly with minimal CPU usage
	
	while (1)
	{
		UART_String_Transmit("Refresh data buffer: ");
		
		for (uint8_t i = 0; i < ADC_BUF_SIZE; ++i)
		{
			UART_StringFmt_Transmit("%d ", adc_buffer[i]);
		}
		
		UART_NEW_LINE;
		
		_delay_ms(1000);
	}
}

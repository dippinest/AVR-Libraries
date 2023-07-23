
#define F_CPU 16000000UL

#include <util/delay.h>

#include "uart.h"
#include "adc.h"

#define ADC_BUF_SIZE 16
static uint16_t adc_buffer[ADC_BUF_SIZE];

void send_buffer()
{
	ADC_Set_Interrupt_Disable();
	UART_String_Transmit("ADC DATA: ");
	
	uint32_t adc_mean = 0;
	
	for (uint16_t i = 0; i < ADC_BUF_SIZE; ++i)
	{
		adc_mean += adc_buffer[i];
		UART_StringFmt_Transmit("%d ", adc_buffer[i]);
	}
	
	UART_StringFmt_Transmit("\r\n\r\nADC MEAN = %d\r\n", adc_mean / ADC_BUF_SIZE);
	
	_delay_ms(500);
	
	ADC_Set_Interrupt_Enable();
}

int main(void)
{
	UART_Initialize(9600, true, false);
	
	sei();
	
	ADC_Initialize(0, ADC_PRESCALER_2, ADC_VREF_SOURCE_EXTERNAL_AVCC, true);
	
	ADC_Set_Reception_Buffer_Ptr(adc_buffer);
	ADC_Set_Reception_Buffer_Size(ADC_BUF_SIZE);
	
	ADC_Set_Reception_CallBack_Function(send_buffer);
	
	
	ADC_Set_Interrupt_Enable();
	
	ADC_Start_Conversion();
	
	while (1)
	{
	}
}

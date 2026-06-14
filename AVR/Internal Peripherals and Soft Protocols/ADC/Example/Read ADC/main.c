
#include <util/delay.h>

#include "adc.h"
#include "uart.h"

int main(void)
{
	ADC_Initialize(0, ADC_PRESCALER_128, ADC_VREF_SOURCE_EXTERNAL_AVCC, true);
	UART_Initialize(9600, true, false);
	
	while (1)
	{
		UART_StringFmt_Transmit("ADC0 value = %d\r\n", ADC_Get_Value_10bit());
		
		_delay_ms(500);
	}
}

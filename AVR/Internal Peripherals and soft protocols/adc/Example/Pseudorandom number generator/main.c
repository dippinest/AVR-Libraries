
#define F_CPU 16000000UL
#include <util/delay.h>

#include "uart.h"
#include "adc.h"

int main(void)
{
	UART_Initialize(9600, true, false);
	ADC_Initialize(2, ADC_PRESCALER_128, ADC_VREF_SOURCE_EXTERNAL_AVCC, true);
	
	while (1)
	{
		// ATN! I do not recommend using this function for serious applications,
		// since the numbers are not truly random (see the statistical test in Python).
		//
		// I recommend use it for the initial initialization of the srand() function
		UART_StringFmt_Transmit("Random 8-bit value = %d\r\n", ADC_Get_Random_Entropy_Value_8bit(2));
		
		_delay_ms(500);
	}
}

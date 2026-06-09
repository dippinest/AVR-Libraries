

#include "adc.h"
#include "uart.h"

#include <util/delay.h>



int main(void)
{
	ADC_Initialize(0, ADC_PRESCALER_128, ADC_VREF_SOURCE_EXTERNAL_AVCC, true);
	
	UART_Initialize(9600, true, false);
	
	
	
	while (1)
	{
		float fvalue = ADC_Get_Voltage_Value_From_Measured_Value(ADC_Get_Oversampling_Value(12), 12);
		
		UART_StringFmt_Transmit("Voltage = %f\r\n", fvalue);
		
		
		_delay_ms(100);
	}
}



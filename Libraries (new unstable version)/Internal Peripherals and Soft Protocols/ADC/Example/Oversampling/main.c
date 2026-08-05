
#include <util/delay.h>

#include "uart.h"
#include "adc.h"

int main(void)
{
	UART_Initialize(9600, true, false);
	ADC_Initialize(0, ADC_PRESCALER_128, ADC_VREF_SOURCE_EXTERNAL_AVCC, true);
	
	while (1)
	{
		uint16_t adc_val      = ADC_Get_Value_10bit();
		uint16_t adc_val_ovs  = ADC_Get_Oversampling_Value(12); // 12 bit oversampling oversampling
		
		float adc_voltage     = ADC_GET_FLOAT_VOLTAGE(adc_val,     10, 5.0);
		float adc_voltage_ovs = ADC_GET_FLOAT_VOLTAGE(adc_val_ovs, 12, 5.0);
		
		UART_StringFmt_Transmit("ADC     val = %d;  Voltage = %f\r\n", adc_val,     adc_voltage);
		UART_StringFmt_Transmit("ADC OVS val = %d; Voltage = %f\r\n",  adc_val_ovs, adc_voltage_ovs);
		
		UART_NEW_LINE;
		
		_delay_ms(250);
	}
}



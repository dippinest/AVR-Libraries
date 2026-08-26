

#include <util/delay.h>

#include "adc.h"
#include "uart.h"


// желаемая разрядность значения после оверсемплинга (12 бит)
//
// -------------------------------------------------------------------------------
// desired bit depth of the value after oversampling (12 bits)
//
#define ADC_OVS_BITRATE 12


// максимальное значение опорного напряжения
//
// -------------------------------------------------------------------------------
// maximum value of the reference voltage
//
#define ADC_MAX_REF_VOLTAGE 5.0f



int main(void)
{
	ADC_Initialize(0, ADC_PRESCALER_128, ADC_VREF_SOURCE_EXTERNAL_AVCC, true);
	
	UART_Initialize(9600, true, false);
	
	
	
	while (1)
	{
		uint16_t adc_ovs_value = ADC_Get_Oversampling_Value(ADC_OVS_BITRATE);
		
		float voltage = ADC_Get_Voltage_Value_From_Measured_Value(adc_ovs_value, ADC_OVS_BITRATE, ADC_MAX_REF_VOLTAGE);
		
		
		UART_StringFmt_Transmit("Voltage = %f\r\n", voltage);
		
		
		_delay_ms(100);
	}
}




/*


// пример вольтметра с оверсемплингом, используя Fixed Decimal Point (FDP)
//
// -------------------------------------------------------------------------------
// example of a voltmeter with oversampling using Fixed Decimal Point (FDP)
//



#include <util/delay.h>

#include "adc.h"
#include "uart.h"

#include "fdpn.h"


// желаемая разрядность значения после оверсемплинга (12 бит)
//
// -------------------------------------------------------------------------------
// desired bit depth of the value after oversampling (12 bits)
//
#define ADC_OVS_BITRATE 12


// максимальное значение опорного напряжения, умноженное на 10 (5.0 * 10 = 50)
//
//
//
// -------------------------------------------------------------------------------
// maximum value of the reference voltage multiplied by 10 (5.0 * 10 = 50)
//
#define ADC_MAX_REF_VOLTAGE 50



char string_buffer[16];


int main(void)
{
	ADC_Initialize(0, ADC_PRESCALER_128, ADC_VREF_SOURCE_EXTERNAL_AVCC, true);
	
	UART_Initialize(9600, true, false);
	
	
	
	while (1)
	{
		uint16_t adc_ovs_val = ADC_Get_Oversampling_Value(12);
		
		uint32_t fdpn_int32base_voltage =
		ADC_Get_Voltage_FDPN_Int32Base_1_Fract_Digit_Value_From_Measured_Value(adc_ovs_val, 12, ADC_MAX_REF_VOLTAGE);
		
		
		// преобразование FDPN с 1 знаком
		// после десятичного разделителя значения в ASCII строку
		//
		// -------------------------------------------------------------------------------
		// converting FDPN with 1 digit after the decimal point into an ASCII string
		//
		FDPN_Int32Base_Convert_Number_To_String(string_buffer, fdpn_int32base_voltage, 2, 1, '.');
		
		
		UART_StringFmt_Transmit("Voltage = %s\r\n", string_buffer);
		
		
		_delay_ms(100);
	}
}



*/








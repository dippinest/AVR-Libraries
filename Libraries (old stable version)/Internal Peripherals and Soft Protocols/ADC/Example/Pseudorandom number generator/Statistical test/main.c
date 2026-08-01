
#include "uart.h"
#include "adc.h"

int main(void)
{
	UART_Initialize(9600, true, false);
	
	ADC_Initialize(2, ADC_PRESCALER_128, ADC_VREF_SOURCE_EXTERNAL_AVCC, true);
	
	
	#define NUM_OF_VAL 10000
	
	// генерирация 10.000 чисел в диапазоне от 0 до 256
	// -------------------------------------------------------------------------------
	// generating 10,000 numbers in the range from 0 to 256
	for (uint16_t i = 0; i < NUM_OF_VAL; ++i)
	{
		// получение случайного значения со 2-го канала АЦП
		// -------------------------------------------------------------------------------
		// getting a random value from the 2nd ADC channel
		uint8_t val = ADC_Get_Random_Entropy_Value_8bit(2);
		
		UART_StringFmt_Transmit("%i, ", val);
	}
	
	while (1)
	{
	}
}



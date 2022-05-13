
// This file compares the amount of memory occupied by the microcontroller
// with different representations of real numbers (as an example, the task of
// deducing the voltage value on the ADC in volts is taken).
//
// The greatest gain is observed for numbers with a pseudo-fixed point.
// Code examples with other solutions are commented out, you can see them below.
//
// All tests were carried out during optimization with the -Os flag (avr-gcc compiler)
//
// ======================================================================================
//
// an example of implementing a program with a pseudo-fixed point number
// conversion using the PFIXPoint_Int32FP_To_String function
//
// the program in the memory of the ATmega8 microcontroller occupies 1778 bytes

#define F_CPU 16000000UL
#include <util/delay.h>

#include "i2c.h"
#include "hd44780_i2c.h"
#include "adc.h"

#include "PFIXPoint.h"

static char str_buf[16];

int main(void)
{
	ADC_Initialize(0, ADC_PRESCALER_128, ADC_VREF_SOURCE_EXTERNAL_AVCC, true);
	
	// maximum value of the ADC voltage multiplied by 100 (to shift the decimal point to the end to the right)
	const int32_t PFIXPOINT_MAX_VOLTAGE = 481; // (4.81 * 100) * 10000
	
	I2C_Initialize(100000);
	
	PFIXPoint_Set_Number_Of_Decimal_Places(2); // fixing a point at position 2
	PFIXPoint_Set_String_Buffer(str_buf);
	
	HD44780_I2C_t display = HD44780_I2C_Get_Display_Object(HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1T_A0T, true);
	HD44780_I2C_Set_Target_Display_Object(&display);
	
	HD44780_I2C_Set_Cursor_Pos(0, 0); HD44780_I2C_Print_String("Voltage in ADC0:");
	HD44780_I2C_Set_Cursor_Pos(2, 0); HD44780_I2C_Print_String("Voltage =");
	
	while (1)
	{
		// working with fixed-type numbers
		int32_t PFIXPOINT_voltage = (((PFIXPOINT_MAX_VOLTAGE * 10000) / 1023) * ADC_Get_Value_10bit()) / 10000;
		
		HD44780_I2C_Clear_String_By_Pos(2, 10, 19); HD44780_I2C_Set_Cursor_Pos(2, 10);
		HD44780_I2C_Print_String(PFIXPoint_Int32PFP_To_String(PFIXPOINT_voltage, 1, 2));
		
		_delay_ms(200);
	}
}

/*

// an example of implementing a program with the conversion of
// a float type number using the ITOA_Float_To_String function
//
// the program in the memory of the ATmega8 microcontroller occupies 3038 bytes

#define F_CPU 16000000UL
#include <util/delay.h>

#include "i2c.h"
#include "hd44780_i2c.h"
#include "adc.h"

#include "itoa.h"

static char str_buf[16];

int main(void)
{
	ADC_Initialize(0, ADC_PRESCALER_128, ADC_VREF_SOURCE_EXTERNAL_AVCC, true);
	ADC_Set_Max_Reference_Voltage_Value(4.81); // real value of the reference voltage
	
	I2C_Initialize(100000);
	
	ITOA_Set_String_Buffer(str_buf);
	
	HD44780_I2C_t display = HD44780_I2C_Get_Display_Object(HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1T_A0T, true);
	HD44780_I2C_Set_Target_Display_Object(&display);
	
	HD44780_I2C_Set_Cursor_Pos(0, 0); HD44780_I2C_Print_String("Voltage in ADC0:");
	HD44780_I2C_Set_Cursor_Pos(2, 0); HD44780_I2C_Print_String("Voltage =");
	
	while (1)
	{
		ITOA_Float_To_String(ADC_Get_Voltage_Value(), 1, 2);
		
		HD44780_I2C_Clear_String_By_Pos(2, 10, 19); HD44780_I2C_Set_Cursor_Pos(2, 10); HD44780_I2C_Print_String(str_buf);
		
		_delay_ms(200);
	}
}
*/


/*

// an example of implementing a program with a float number
// conversion using the standard sprintf function (library
// functions of the HD44780_I2C_Print_String type are not
// used intentionally, because it consumes even more memory).
//
// the program in the memory of the ATmega8 microcontroller occupies 4980 bytes

#define F_CPU 16000000UL
#include <util/delay.h>

#include "i2c.h"
#include "hd44780_i2c.h"
#include "adc.h"

#include <stdio.h>

static char str_buf[16];

int main(void)
{
	ADC_Initialize(0, ADC_PRESCALER_128, ADC_VREF_SOURCE_EXTERNAL_AVCC, true);
	ADC_Set_Max_Reference_Voltage_Value(4.81); // real value of the reference voltage
	
	I2C_Initialize(100000);
	
	HD44780_I2C_t display = HD44780_I2C_Get_Display_Object(HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1T_A0T, true);
	HD44780_I2C_Set_Target_Display_Object(&display);
	
	HD44780_I2C_Set_Cursor_Pos(0, 0); HD44780_I2C_Print_String("Voltage in ADC0:");
	HD44780_I2C_Set_Cursor_Pos(2, 0); HD44780_I2C_Print_String("Voltage =");
	
	while (1)
	{
		sprintf(str_buf, "%.2f", ADC_Get_Voltage_Value());
		
		HD44780_I2C_Clear_String_By_Pos(2, 10, 19); HD44780_I2C_Set_Cursor_Pos(2, 10); HD44780_I2C_Print_String(str_buf);
		
		_delay_ms(200);
	}
}
*/

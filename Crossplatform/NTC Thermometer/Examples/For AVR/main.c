
#define F_CPU 16000000UL
#include <util/delay.h>

#include "i2c.h"
#include "hd44780_i2c.h"
#include "NTC_Thermometer.h"
#include "NTC_Thermometer_configuration.h"
#include "adc.h"

int main(void)
{
	ADC_Initialize(0, ADC_PRESCALER_128, ADC_VREF_SOURCE_EXTERNAL_AVCC, true);
	
	I2C_Initialize(100000);
	
	HD44780_I2C_t display = HD44780_I2C_Get_Display_Object(HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1T_A0T, true);
	HD44780_I2C_Set_Target_Display_Object(&display);
	
	HD44780_I2C_Set_Cursor_Pos(0, 0); HD44780_I2C_Print_String("NTC Thermometer:");
	
	HD44780_I2C_Set_Cursor_Pos(1, 0); HD44780_I2C_Print_String("Kelvin:     ");
	HD44780_I2C_Set_Cursor_Pos(2, 0); HD44780_I2C_Print_String("Celsius:    ");
	HD44780_I2C_Set_Cursor_Pos(3, 0); HD44780_I2C_Print_String("Fahrenheit: ");
	
	while (1)
	{
		float temp_to_kelvin = NTC_Thermometer_Get_Temperature_To_Kelvin(ADC_Get_Value_10bit());
		
		HD44780_I2C_Clear_String_By_Pos(1, 12, 19); HD44780_I2C_Set_Cursor_Pos(1, 12);
		HD44780_I2C_Print_StringFmt("%.1f *K", temp_to_kelvin);
		
		HD44780_I2C_Clear_String_By_Pos(2, 12, 19); HD44780_I2C_Set_Cursor_Pos(2, 12);
		HD44780_I2C_Print_StringFmt("%.1f  *C", NTC_Thermometer_Convert_Temperature_Kelvin_To_Celsius(temp_to_kelvin));
		
		HD44780_I2C_Clear_String_By_Pos(3, 12, 19); HD44780_I2C_Set_Cursor_Pos(3, 12);
		HD44780_I2C_Print_StringFmt("%.1f  *F", NTC_Thermometer_Convert_Temperature_Kelvin_To_Fahrenheit(temp_to_kelvin));
		
		_delay_ms(200);
	}
}

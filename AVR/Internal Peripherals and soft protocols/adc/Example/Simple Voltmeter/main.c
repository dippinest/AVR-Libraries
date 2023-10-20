
#include <util/delay.h>

#include "i2c.h"
#include "hd44780_i2c.h"
#include "adc.h"

int main(void)
{
	ADC_Initialize(0, ADC_PRESCALER_128, ADC_VREF_SOURCE_EXTERNAL_AVCC, true);
	ADC_Set_Max_Reference_Voltage_Value(4.81); // real value of the reference voltage
	
	I2C_Initialize(100000);
	
	HD44780_I2C_t display = HD44780_I2C_Get_Display_Object(HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1T_A0T, true);
	HD44780_I2C_Set_Target_Display_Object(&display);
	
	HD44780_I2C_Set_Cursor_Pos(0, 0); HD44780_I2C_Print_String("Voltage in ADC0:");
	HD44780_I2C_Set_Cursor_Pos(2, 0); HD44780_I2C_Print_String("Voltage = ");
	
	while (1)
	{
		HD44780_I2C_Clear_String_By_Pos(2, 10, 19); HD44780_I2C_Set_Cursor_Pos(2, 10);
		HD44780_I2C_Print_StringFmt("%.2f V", ADC_Get_Voltage_Value());
		
		_delay_ms(200);
	}
}

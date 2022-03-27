#define F_CPU 16000000UL

#include "i2c.h"
#include "hd44780_i2c.h"
#include "lm75.h"

int main(void)
{
	I2C_Initialize(100000);
	
	HD44780_I2C_t display = HD44780_I2C_Get_Display_Object(HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1T_A0T, true);
	HD44780_I2C_Set_Target_Display_Object(&display);
	
	LM75_t thermometer = LM75_Get_Thermometer_Object(LM75_I2C_DEV_ADDR_A2T_A1F_A0F, true);
	LM75_Set_Target_Thermometer_Object(&thermometer);
	
	HD44780_I2C_Set_Cursor_Pos(0, 0); HD44780_I2C_Print_String("LM75 THERMOMETER");
	
	while (1)
	{
		HD44780_I2C_Clear_String_By_Pos(2, 0, 19);
		HD44780_I2C_Set_Cursor_Pos(2, 0);
		HD44780_I2C_Print_StringFmt("Temp = %.1f *C", LM75_Get_Float_Temperature());
		
		_delay_ms(500);
	}
}
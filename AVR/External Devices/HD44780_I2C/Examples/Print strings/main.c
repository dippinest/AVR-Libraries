
#define F_CPU 16000000UL

#include "i2c.h"
#include "hd44780_i2c.h"

int main(void)
{
	I2C_Initialize(100000);
	
	HD44780_I2C_t display = HD44780_I2C_Get_Display_Object(HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1T_A0T, true);
	
	HD44780_I2C_Set_Target_Display_Object(&display);
	
	HD44780_I2C_Set_Cursor_Pos(0, 0); HD44780_I2C_Print_String("String 1");
	HD44780_I2C_Set_Cursor_Pos(1, 0); HD44780_I2C_Print_String("String 2");
	HD44780_I2C_Set_Cursor_Pos(2, 0); HD44780_I2C_Print_String("String 3");
	HD44780_I2C_Set_Cursor_Pos(3, 0); HD44780_I2C_Print_String("String 4");
	
	while (1)
	{
	}
}

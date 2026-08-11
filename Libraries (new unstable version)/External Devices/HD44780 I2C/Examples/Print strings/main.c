

#include "softi2c.h"
#include "hd44780_i2c.h"



// объект LCD дисплея HD44780 в связке c I2C расширителем портов PCF8574
//
// ===============================================================================
// HD44780 LCD display object in conjunction with the I2C port expander PCF8574
//
HD44780_I2C_t hd44780_i2c;


int main(void)
{
	SOFTI2C_Initialize();
	
	
	HD44780_I2C_Initialize_Object(&hd44780_i2c, HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1T_A0T, true);
	
	HD44780_I2C_Set_Target_Object(&hd44780_i2c);
	
	
	HD44780_I2C_Set_Cursor_Pos(0, 0); HD44780_I2C_Print_String("String 1");
	HD44780_I2C_Set_Cursor_Pos(1, 0); HD44780_I2C_Print_String("String 2");
	HD44780_I2C_Set_Cursor_Pos(2, 0); HD44780_I2C_Print_String("String 3");
	HD44780_I2C_Set_Cursor_Pos(3, 0); HD44780_I2C_Print_String("String 4");
	
	while (1)
	{
	}
}





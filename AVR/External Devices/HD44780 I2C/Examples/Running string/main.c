
#include "softi2c.h"
#include "hd44780_i2c.h"

int main(void)
{
	SOFTI2C_Initialize();
	
	HD44780_I2C_t display = HD44780_I2C_Get_Object(HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1T_A0T, true);
	
	HD44780_I2C_Set_Target_Object(&display);
	
	HD44780_I2C_Set_Cursor_Pos(0, 0); HD44780_I2C_Print_String("This is a very loooong running string...");
	
	while (1)
	{
		HD44780_I2C_Display_Shift(HD44780_I2C_SHIFT_TO_LEFT);
		_delay_ms(500);
	}
}


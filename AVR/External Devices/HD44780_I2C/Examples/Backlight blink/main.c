
#include <util/delay.h>

#include "i2c.h"
#include "hd44780_i2c.h"

int main(void)
{
	I2C_Initialize(100000);
	
	
	// по умолчанию подсветка дисплея всегда включена - её не надо включать вручную
	// -------------------------------------------------------------------------------
	// by default, the display backlight is always on - it doesn't need to be turned on manually
	
	HD44780_I2C_t display = HD44780_I2C_Get_Display_Object(HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1T_A0T, true);
	
	HD44780_I2C_Set_Target_Display_Object(&display);
	
	HD44780_I2C_Set_Cursor_Pos(0, 0); HD44780_I2C_Print_String("String 1");
	HD44780_I2C_Set_Cursor_Pos(1, 0); HD44780_I2C_Print_String("String 2");
	HD44780_I2C_Set_Cursor_Pos(2, 0); HD44780_I2C_Print_String("String 3");
	HD44780_I2C_Set_Cursor_Pos(3, 0); HD44780_I2C_Print_String("String 4");
	
	
	while (1)
	{
		// переключение подсветки каждые 500 мс.
		// Этот эффект можно применить для индикации какого-либо события.
		// Кроме того, подсветку можно выключать с целью экономии энергии
		// -------------------------------------------------------------------------------
		// switching the backlight every 500 ms.
		// This effect can be applied to indicate an event.
		// In addition, the backlight can be turned off in order to save energy
		
		HD44780_I2C_Set_Display_Backlight_Enable(false);
		_delay_ms(500);
		HD44780_I2C_Set_Display_Backlight_Enable(true);
		_delay_ms(500);
	}
}


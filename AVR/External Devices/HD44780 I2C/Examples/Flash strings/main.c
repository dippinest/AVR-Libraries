
#include <avr/pgmspace.h>

#include "softi2c.h"
#include "hd44780_i2c.h"
#include "deftypes.h"

const char FLASH_STRING_1[] PROGMEM = "String FLASH 1";
const char FLASH_STRING_2[] PROGMEM = "String FLASH 2";
const char FLASH_FMT_STRING[] PROGMEM = "Euler's num E = %.2f";

int main(void)
{
	SOFTI2C_Initialize();
	
	HD44780_I2C_t display = HD44780_I2C_Get_Device_Object(HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1T_A0T, true);
	
	HD44780_I2C_Set_Target_Device_Object(&display);
	
	
	HD44780_I2C_Set_Cursor_Pos(0, 0);  HD44780_I2C_Print_Flash_String(FLASH_STRING_1);
	
	HD44780_I2C_Set_Cursor_Pos(1, 0);  HD44780_I2C_Safe_Print_Flash_String(FLASH_STRING_2, 14);
	
	HD44780_I2C_Set_Cursor_Pos(2, 10); HD44780_I2C_Print_Flash_String_To_Char_Terminator(FLASH_STRING_2, 'g');
	
	HD44780_I2C_Set_Cursor_Pos(3, 0);  HD44780_I2C_Print_Flash_StringFmt(FLASH_FMT_STRING, MATH_E); // not supported '%s' from flash!
	
	while (1)
	{
	}
}

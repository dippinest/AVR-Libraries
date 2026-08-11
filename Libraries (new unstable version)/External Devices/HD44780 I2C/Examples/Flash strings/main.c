

#include "softi2c.h"
#include "hd44780_i2c.h"


AVR_FLASH_DATA(FLASH_STRING_1,    char, "String FLASH 1");
AVR_FLASH_DATA(FLASH_STRING_2,    char, "String FLASH 2");
AVR_FLASH_DATA(FLASH_FMT_STRING,  char, "Euler's num E = %.2f");



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
	
	
	
	HD44780_I2C_Set_Cursor_Pos(0, 0);  HD44780_I2C_Print_Flash_String(FLASH_STRING_1);
	
	HD44780_I2C_Set_Cursor_Pos(1, 0);  HD44780_I2C_Safe_Print_Flash_String(FLASH_STRING_2, 14);
	
	HD44780_I2C_Set_Cursor_Pos(2, 10); HD44780_I2C_Print_Flash_String_To_Char_Terminator(FLASH_STRING_2, 'g');
	
	
	float Euler_number = 2.718281f;
	
	HD44780_I2C_Set_Cursor_Pos(3, 0);  HD44780_I2C_Print_Flash_StringFmt(FLASH_FMT_STRING, Euler_number); // not supported '%s' from flash!
	
	while (1)
	{
	}
}







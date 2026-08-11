

#include "hd44780.h"


AVR_FLASH_DATA(FLASH_STRING_1,    char, "String FLASH 1");
AVR_FLASH_DATA(FLASH_STRING_2,    char, "String FLASH 2");
AVR_FLASH_DATA(FLASH_FMT_STRING,  char, "Euler's num E = %.2f");



int main(void)
{
	HD44780_Initialize(true);
	
	
	
	HD44780_Set_Cursor_Pos(0, 0);  HD44780_Print_Flash_String(FLASH_STRING_1);
	
	HD44780_Set_Cursor_Pos(1, 0);  HD44780_Safe_Print_Flash_String(FLASH_STRING_2, 14);
	
	HD44780_Set_Cursor_Pos(2, 10); HD44780_Print_Flash_String_To_Char_Terminator(FLASH_STRING_2, 'g');
	
	
	float Euler_number = 2.718281f;
	
	HD44780_Set_Cursor_Pos(3, 0);  HD44780_Print_Flash_StringFmt(FLASH_FMT_STRING, Euler_number); // not supported '%s' from flash!
	
	while (1)
	{
	}
}






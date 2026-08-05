
#include "hd44780.h"
#include "ftoa.h"



char string_buffer[16];

const float MATH_PI = 3.141592f;


AVR_FLASH_DATA(FLASH_STRING, char, "String FLASH");


int main(void)
{	
	HD44780_Initialize(true);
	
	HD44780_Set_Cursor_Pos(0, 0);  HD44780_Print_Flash_String(FLASH_STRING); // write flash string
	
	HD44780_Set_Cursor_Pos(1, 0);  HD44780_Print_String("PI ="); HD44780_Print_String(FTOA_Float32_To_String(string_buffer, MATH_PI, 2, 5, '.'));
	
	while (1)
	{
	}
}




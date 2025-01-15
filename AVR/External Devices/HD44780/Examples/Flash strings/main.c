
#include "hd44780.h"
#include "deftypes.h"
#include "itoa.h"

AVR_FLASH_DATA(FLASH_STRING, char, "String FLASH");

int main(void)
{
	ITOA_Set_String_Buffer_To_Dynamic_Memory(16);
	
	HD44780_Initialize(true);
	
	HD44780_Set_Cursor_Pos(0, 0);  HD44780_Print_Flash_String(FLASH_STRING); // write flash string
	
	HD44780_Set_Cursor_Pos(1, 0);  HD44780_Print_String("PI ="); HD44780_Print_String(ITOA_Float_To_String(MATH_PI, 2, 5));
	
	while (1)
	{
	}
}




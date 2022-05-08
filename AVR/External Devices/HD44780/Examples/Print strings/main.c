
#define F_CPU 16000000UL
#include "hd44780.h"

int main(void)
{
	HD44780_Initialize(true);
	
	HD44780_Set_Cursor_Pos(0, 0); HD44780_Print_String("String 1");
	HD44780_Set_Cursor_Pos(1, 0); HD44780_Print_String("String 2");
	
	while (1)
	{
	}
}

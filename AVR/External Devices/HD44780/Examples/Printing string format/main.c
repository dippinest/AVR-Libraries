#define F_CPU 16000000UL

#include "hd44780.h"

int main(void)
{
	DDRD = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);
	
	HD44780_Initialize(true);
	
	HD44780_Set_Cursor_Pos(0, 0); HD44780_Print_String("Hello, world!");
	HD44780_Set_Cursor_Pos(1, 0); HD44780_Print_String("Counter Fmt: ");
	
	uint8_t i = 0;
	
	while (1)
	{
		HD44780_Set_Cursor_Pos(1, 13); HD44780_Print_StringFmt("%d", i++);
		_delay_ms(500);
	}
}

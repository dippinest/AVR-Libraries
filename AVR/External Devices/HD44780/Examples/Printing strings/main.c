#define HD44780_RS_PORT   PORTD
#define HD44780_RS_PIN    0

#define HD44780_E_PORT    PORTD
#define HD44780_E_PIN     1

#define HD44780_D4_PORT   PORTD
#define HD44780_D4_PIN    2

#define HD44780_D5_PORT   PORTD
#define HD44780_D5_PIN    3

#define HD44780_D6_PORT   PORTD
#define HD44780_D6_PIN    4

#define HD44780_D7_PORT   PORTD
#define HD44780_D7_PIN    5

#define F_CPU 16000000UL

#include "hd44780.h"

int main(void)
{
	DDRD = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);
	
	HD44780_Initialize(true);
	
	HD44780_Set_Cursor_Pos(0, 0); HD44780_Print_String("String 1");
	HD44780_Set_Cursor_Pos(1, 0); HD44780_Print_String("String 2");
	
	while (1)
	{
	}
}
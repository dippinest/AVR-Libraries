
#define F_CPU 16000000UL
#include "hd44780.h"

int main(void)
{
	const uint8_t customChar_CyrillicP[8] =
	{
		0b11111,
		0b10001,
		0b10001,
		0b10001,
		0b10001,
		0b10001,
		0b10001,
		0b00000
	};

	const uint8_t customChar_CyrillicI[8] =
	{
		0b10001,
		0b10001,
		0b10011,
		0b10101,
		0b11001,
		0b10001,
		0b10001,
		0b00000
	};
	
	HD44780_Initialize(true);
	
	HD44780_Set_User_Symbol_To_CGRAM(customChar_CyrillicP, 0x01);
	HD44780_Set_User_Symbol_To_CGRAM(customChar_CyrillicI, 0x02);
	
	char helloWorld_Russian[] = { 0x01, 'P', 0x02, 'B', 'E', 'T', ',', ' ', 'M', 0x02, 'P', '!', '\0' };
	HD44780_Set_Cursor_Pos(0, 0); HD44780_Print_String(helloWorld_Russian);
	
	char helloWorld_Ukrainian[] = { 0x01, 'P', 0x02, 'B', 'I', 'T', ',', ' ', 'C', 'B', 'I', 'T', 'E', '!', '\0' };
	HD44780_Set_Cursor_Pos(1, 0); HD44780_Print_String(helloWorld_Ukrainian);
	
	while (1)
	{
	}
}


/*
// this code is an example of writing user characters to the CGRAM
// of the display from the flash memory (program memory) of the MCU

#define F_CPU 16000000UL

#include <avr/pgmspace.h>
#include "i2c.h"
#include "hd44780.h"

const PROGMEM uint8_t customChar_CyrillicP[8] =
{
	0b11111,
	0b10001,
	0b10001,
	0b10001,
	0b10001,
	0b10001,
	0b10001,
	0b00000
};
const PROGMEM uint8_t customChar_CyrillicI[8] =
{
	0b10001,
	0b10001,
	0b10011,
	0b10101,
	0b11001,
	0b10001,
	0b10001,
	0b00000
};

int main(void)
{
	HD44780_Initialize(true);
	
	HD44780_Set_Flash_User_Symbol_To_CGRAM(customChar_CyrillicP, 0x01);
	HD44780_Set_Flash_User_Symbol_To_CGRAM(customChar_CyrillicI, 0x02);
	
	char helloWorld_Russian[] = { 0x01, 'P', 0x02, 'B', 'E', 'T', ',', ' ', 'M', 0x02, 'P', '!', '\0' };
	HD44780_Set_Cursor_Pos(0, 0); HD44780_Print_String(helloWorld_Russian);
	
	char helloWorld_Ukrainian[] = { 0x01, 'P', 0x02, 'B', 'I', 'T', ',', ' ', 'C', 'B', 'I', 'T', 'E', '!', '\0' };
	HD44780_Set_Cursor_Pos(1, 0); HD44780_Print_String(helloWorld_Ukrainian);
	
	while (1)
	{
	}
}
*/

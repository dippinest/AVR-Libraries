
// ATN! to run the example, be sure to uncomment out the
// MAX7219_USE_SPI_CS_CALLBACKS macro in the hd44780_configuration.h file!

#include "spi.h"
#include "max7219.h"
#include "max7219_symbols.h"

void CS_ON()
{
	PORTD &= ~(1 << 7);
}

void CS_OFF()
{
	PORTD |= (1 << 7);
}

int main(void)
{
	DDRD |= (1 << 7);
	
	SPI_Initialize(true, SPI_DEV_IS_MASTER, SPI_MODE_0, SPI_SPEED_FCPU_DIV_2);
	SPI_Set_CS_CallBack_Functions(CS_ON, CS_OFF);
	
	MAX7219_Initialize(true, MAX7219_DECODE_MODE_NO_DECODE, MAX7219_8_DIGIT, MAX7219_BRIGHTNESS_COEFFICIENT_4);
	
	MAX7219_Set_Digit(7, MAX7219_CHAR_L_BIG);    // "L"
	MAX7219_Set_Digit(6, MAX7219_CHAR_E_BIG);    // "E"
	MAX7219_Set_Digit(5, MAX7219_CHAR_D_SMALL);  // "d"
	
	MAX7219_Set_Digit(4, MAX7219_CHAR_SPACE);    // " "
	
	MAX7219_Set_Digit(3, MAX7219_CHAR_T_SMALL);  // "t"
	MAX7219_Set_Digit(2, MAX7219_CHAR_E_BIG);    // "E"
	MAX7219_Set_Digit(1, MAX7219_CHAR_S_BIG);    // "S"
	MAX7219_Set_Digit(0, MAX7219_CHAR_T_SMALL);  // "t"
	
	while (1)
	{
	}
}

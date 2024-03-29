
// ATN! to run the example, be sure to uncomment out the
// MAX7219_USE_SPI_CS_CALLBACKS macro in the max7219_configuration.h file!

#include <util/delay.h>

#include "spi.h"
#include "itoa.h"
#include "max7219.h"

void CS_ON()
{
	PORTD &= ~(1 << 7);
}

void CS_OFF()
{
	PORTD |= (1 << 7);
}

static char str_buf[16];

int main(void)
{
	ITOA_Set_String_Buffer(str_buf);
	
	DDRD |= (1 << 7);
	
	SPI_Initialize(true, SPI_DEV_IS_MASTER, SPI_MODE_0, SPI_SPEED_FCPU_DIV_2);
	SPI_Set_CS_CallBack_Functions(CS_ON, CS_OFF);
	
	MAX7219_Initialize(true, MAX7219_DECODE_MODE_DECODE_ALL_DIGITS, MAX7219_8_DIGIT, MAX7219_BRIGHTNESS_COEFFICIENT_4);
	
	uint16_t number = 0;
	
	while (1)
	{
		MAX7219_Set_Char_Digits(ITOA_UInt16_To_String(number++, 8), 8, 8); _delay_ms(50);
	}
}

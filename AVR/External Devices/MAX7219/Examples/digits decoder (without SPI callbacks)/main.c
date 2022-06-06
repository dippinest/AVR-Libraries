
// ATN! to run the example, be sure to comment out the
// MAX7219_USE_SPI_CS_CALLBACKS macro in the hd44780_configuration.h file!

#define F_CPU 16000000UL
#include <util/delay.h>

#include "spi.h"
#include "itoa.h"
#include "max7219.h"

// macro for setting and resetting the
// Chip Select (CS) line when transmitting data over SPI
#define CS_ONOFF_MAX7219(SPI_FUNCTION)  \
PORTD &= ~(1 << 7);                 \
SPI_FUNCTION;                       \
PORTD |=  (1 << 7);

static char str_buf[16];

int main(void)
{
	ITOA_Set_String_Buffer(str_buf);
	
	DDRD |= (1 << 7);
	
	SPI_Initialize(true, SPI_DEV_IS_MASTER, SPI_MODE_0, SPI_SPEED_FCPU_DIV_2);

	CS_ONOFF_MAX7219(MAX7219_Set_Decode_Mode(MAX7219_DECODE_MODE_DECODE_ALL_DIGITS));
	CS_ONOFF_MAX7219(MAX7219_Set_Num_Of_Involved_Digits(MAX7219_8_DIGIT));
	CS_ONOFF_MAX7219(MAX7219_Set_Brightness(MAX7219_BRIGHTNESS_COEFFICIENT_4));
	CS_ONOFF_MAX7219(MAX7219_Set_Enable(true));
	
	CS_ONOFF_MAX7219(MAX7219_Decode_Mode_Clear_All(MAX7219_8_DIGIT));
	
	uint16_t number = 0;
	
	while (1)
	{
		ITOA_UInt16_To_String(number++, 8);
		
		for (uint8_t i = 0; i < 8; i++)
		{
			if (str_buf[i] == ' ')
			{
				CS_ONOFF_MAX7219(MAX7219_Set_Digit(7 - i, 15));
			}
			else
			{
				CS_ONOFF_MAX7219(MAX7219_Set_Digit(7 - i, str_buf[i] - 48));
			}
		}
		
		_delay_ms(50);
	}
}

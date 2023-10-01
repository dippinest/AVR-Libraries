

#include "softspi.h"
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
	
	SOFTSPI_Initialize();
	SOFTSPI_Set_CS_CallBack_Functions(CS_ON, CS_OFF);
	
	MAX7219_Initialize(true, MAX7219_DECODE_MODE_NO_DECODE, MAX7219_8_DIGIT, MAX7219_BRIGHTNESS_COEFFICIENT_4);
	
	
	// data output by character
	
	//MAX7219_Set_Digit(7, MAX7219_L);      // "L"
	//MAX7219_Set_Digit(6, MAX7219_E);      // "E"
	//MAX7219_Set_Digit(5, MAX7219_d);      // "d"
	//MAX7219_Set_Digit(4, MAX7219_SPACE);  // " "
	//MAX7219_Set_Digit(3, MAX7219_t);      // "t"
	//MAX7219_Set_Digit(2, MAX7219_E);      // "E"
	//MAX7219_Set_Digit(1, MAX7219_S);      // "S"
	//MAX7219_Set_Digit(0, MAX7219_t);      // "t"
	
	uint8_t max7219_data[] =
	{
		MAX7219_L, MAX7219_E, MAX7219_d,
		
		MAX7219_SPACE,
		
		MAX7219_t, MAX7219_E, MAX7219_S, MAX7219_t
	};
	
	MAX7219_Set_Data(max7219_data, 8, true);
	
	while (1)
	{
	}
}





#include <util/delay.h>

#include "softspi.h"
#include "itohexa.h"

#include "max7219.h"


// функции переключения вывода CS (Chip Select Pin)
//
// ===============================================================================
// CS output switching functions (Chip Select Pin)
//
void CS_Set_Active()
{
	PORTA &= ~(1 << 4);
}

void CS_Set_Inactive()
{
	PORTA |=  (1 << 4);
}



char string_buf[16];


int main(void)
{
	DDRA |= (1 << 4);
	
	
	
	SOFTSPI_Initialize();
	SOFTSPI_Set_CS_Callback_Functions(CS_Set_Active, CS_Set_Inactive);
	
	
	MAX7219_Initialize(true, MAX7219_DECODE_MODE_NO_DECODE, MAX7219_8_DIGIT, MAX7219_BRIGHTNESS_COEFFICIENT_4);
	
	
	uint32_t val = 0x00000000;
	
	
	
	while (1)
	{
		MAX7219_Put_Num_String_With_Using_Program_Decoder(ITOHEXA_32bitNum_To_HexString(string_buf, val, true), 8);
		
		
		++val;
		
		_delay_ms(50);
	}
}





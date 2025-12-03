
#include <util/delay.h>

#include "softspi.h"
#include "itoa.h"

#include "max7219.h"


// функции переключения вывода CS (Chip Select Pin)
//
// ===============================================================================
// CS output switching functions (Chip Select Pin)
//
void CS_Set_Active()
{
	PORTA &= ~(1 << 3);
}

void CS_Set_Inactive()
{
	PORTA |=  (1 << 3);
}



char string_buf[16];


int main(void)
{
	DDRA |= (1 << 3);
	
	
	
	ITOA_Set_String_Buffer(string_buf);
	
	
	SOFTSPI_Initialize();
	SOFTSPI_Set_CS_Callback_Functions(CS_Set_Active, CS_Set_Inactive);
	
	
	MAX7219_Initialize(true, MAX7219_DECODE_MODE_NO_DECODE, MAX7219_8_DIGIT, MAX7219_BRIGHTNESS_COEFFICIENT_4);
	
	
	int32_t val = -150;
	
	while (1)
	{
		MAX7219_Put_Num_String_With_Using_Program_Decoder(ITOA_Int32_To_String(val, 8), 8);
		
		
		++val;
		
		_delay_ms(50);
	}
}





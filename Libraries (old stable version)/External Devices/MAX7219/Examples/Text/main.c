

#include "softspi.h"
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


int main(void)
{
	DDRA |= (1 << 3);
	
	
	SOFTSPI_Initialize();
	SOFTSPI_Set_CS_Callback_Functions(CS_Set_Active, CS_Set_Inactive);
	
	
	MAX7219_Initialize(true, MAX7219_DECODE_MODE_NO_DECODE, MAX7219_8_DIGIT, MAX7219_BRIGHTNESS_COEFFICIENT_4);
	
	
	
	const uint8_t max7219_data[] =
	{
		MAX7219_L, MAX7219_E, MAX7219_D,
		
		MAX7219_SPACE,
		
		MAX7219_T, MAX7219_E, MAX7219_S, MAX7219_T
	};
	
	MAX7219_Put_Symbols(max7219_data, 8, true);
	
	
	while (1)
	{
	}
}







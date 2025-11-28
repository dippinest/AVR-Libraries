

#include <util/delay.h>

#include "hc595sevsegind.h"
#include "softspi.h"
#include "itohexa.h"


// функция для работы "защёлки" регистра
//
// ===============================================================================
// function for register "latch" operation
//
void HC595_Latches()
{
	PORTA |=  (1 << 2);
	
	asm("NOP");
	
	PORTA &= ~(1 << 2);
}




char string_buf[16];


int main(void)
{
	DDRA |= (1 << 2);
	
	
	ITOHEXA_Set_String_Buffer(string_buf);
	
	
	SOFTSPI_Initialize();
	
	
	HC595SevSegInd_t indicator = HC595SevSegInd_Create_Object(4, HC595_Latches);
	
	HC595SevSegInd_Set_Target_Object(&indicator);
	
	HC595SevSegInd_Clear_Display();
	
	
	
	uint16_t val = 0x0000;
	
	
	while (1)
	{
		// регистр букв в hex строке не имеет значения
		//
		// ===============================================================================
		// the case of the letters in the hex string does not matter
		//
		HC595SevSegInd_Put_Num_String(ITOHEXA_16bitNum_To_HexString(val, true), 4);
		
		++val;
		
		_delay_ms(200);
	}
}





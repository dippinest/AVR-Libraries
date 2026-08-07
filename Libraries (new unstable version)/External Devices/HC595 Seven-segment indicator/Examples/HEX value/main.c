

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
	PORTA |=  (1 << 4);
	
	asm("NOP");
	
	PORTA &= ~(1 << 4);
}




char string_buf[8];


int main(void)
{
	DDRA |= (1 << 4);
	
	
	SOFTSPI_Initialize();
	
	
	HC595SevSegInd_Clear_Display(4, HC595_Latches);
	
	
	
	uint16_t val = 0x0000;
	
	
	while (1)
	{
		// регистр букв в hex строке не имеет значения
		//
		// ===============================================================================
		// the case of the letters in the hex string does not matter
		//
		HC595SevSegInd_Put_Num_String(ITOHEXA_16bitNum_To_HexString(string_buf, val, true), 4, HC595_Latches);
		
		++val;
		
		
		_delay_ms(200);
	}
}






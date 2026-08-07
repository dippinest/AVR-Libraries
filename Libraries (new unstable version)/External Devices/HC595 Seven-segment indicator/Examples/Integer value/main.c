

#include <util/delay.h>

#include "hc595sevsegind.h"
#include "softspi.h"
#include "itoa.h"


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
	
	
	
	int16_t val = -200;
	
	
	while (1)
	{
		HC595SevSegInd_Put_Num_String(ITOA_Int16_To_String(string_buf, val, 4), 4, HC595_Latches);
		
		++val;
		
		
		_delay_ms(200);
	}
}






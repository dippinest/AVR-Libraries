

#include <util/delay.h>

#include "hc595sevsegind.h"
#include "softspi.h"
#include "ftoa.h"


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




char string_buffer[8];


int main(void)
{
	DDRA |= (1 << 4);
	
	
	SOFTSPI_Initialize();
	
	HC595SevSegInd_Clear_Display(4, HC595_Latches);
	
	
	
	float val = -10.0;
	
	
	while (1)
	{
		// так как в строке символов присутствует разделительная точка,
		// длина строки будет больше на 1 (5 символов в данном случае)
		//
		// ===============================================================================
		// since there is a dividing point in the string of characters,
		// the length of the string will be longer by 1 (5 characters in this case)
		//
		HC595SevSegInd_Put_Num_String(FTOA_Float32_To_String(string_buffer, val, 3, 1, '.'), 5, HC595_Latches);
		
		
		val += 0.1;
		
		
		
		_delay_ms(200);
	}
}







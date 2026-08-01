

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
	PORTA |=  (1 << 3);
	
	asm("NOP");
	
	PORTA &= ~(1 << 3);
}




char string_buf[16];


int main(void)
{
	DDRA |= (1 << 3);
	
	
	FTOA_Set_String_Buffer(string_buf);
	
	
	SOFTSPI_Initialize();
	
	
	HC595SevSegInd_t indicator = HC595SevSegInd_Create_Object(4, HC595_Latches);
	
	HC595SevSegInd_Set_Target_Object(&indicator);
	
	HC595SevSegInd_Clear_Display();
	
	
	
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
		HC595SevSegInd_Put_Num_String(FTOA_Float32_To_String(val, 3, 1), 5);
		
		val += 0.1;
		
		_delay_ms(200);
	}
}







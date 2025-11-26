

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
	PORTA |=  (1 << 2);
	
	asm("NOP");
	
	PORTA &= ~(1 << 2);
}




char string_buf[16];


int main(void)
{
	DDRA |= (1 << 2);
	
	
	ITOA_Set_String_Buffer(string_buf);
	
	
	SOFTSPI_Initialize();
	
	
	HC595SevSegInd_t indicator = HC595SevSegInd_Create_Object(4, HC595_Latches);
	
	HC595SevSegInd_Set_Target_Object(&indicator);
	
	HC595SevSegInd_Clear_Display();
	
	
	
	int16_t val = -200;
	
	
	while (1)
	{
		HC595SevSegInd_Put_Num_String(ITOA_Int16_To_String(val, 4), 4);
		
		++val;
		
		_delay_ms(200);
	}
}





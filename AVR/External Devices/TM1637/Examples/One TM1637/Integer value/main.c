

#include <util/delay.h>

#include "tm1637.h"
#include "itoa.h"


char string_buffer[16];


int main(void)
{
	TM1637_Initialize(true, TM1637_BRIGHTNESS_COEFFICIENT_2);
	
	
	ITOA_Set_String_Buffer(string_buffer);
	
	
	int16_t val = -50;
	
	while (1)
	{
		++val;
		
		TM1637_Put_Num_String(ITOA_Int16_To_String(val, 4), 4);
		
		_delay_ms(100);
	}
}




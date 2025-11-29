

#include <util/delay.h>

#include "tm1637.h"
#include "ftoa.h"


char string_buf[16];


int main(void)
{
	TM1637_Initialize(true, TM1637_BRIGHTNESS_COEFFICIENT_2);
	
	
	FTOA_Set_String_Buffer(string_buf);
	
	
	float val = -20;
	
	while (1)
	{
		val += 0.1;
		
		TM1637_Put_Num_String(FTOA_Float32_To_String(val, 3, 1), 5);
		
		_delay_ms(100);
	}
}




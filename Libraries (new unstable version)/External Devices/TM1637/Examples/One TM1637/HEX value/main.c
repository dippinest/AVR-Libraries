

#include <util/delay.h>

#include "tm1637.h"
#include "itohexa.h"


char string_buffer[8];


int main(void)
{
	TM1637_Initialize(true, TM1637_BRIGHTNESS_COEFFICIENT_2);
	
	
	uint16_t val = 0x0000;
	
	while (1)
	{
		++val;
		
		TM1637_Put_Num_String(ITOHEXA_16bitNum_To_HexString(string_buffer, val, true), 4);
		
		_delay_ms(100);
	}
}




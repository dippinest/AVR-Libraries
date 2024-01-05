

#include "tm1637.h"
#include "itoa.h"


static int16_t data = -50;

static char buf[4];


int main(void)
{
	TM1637_Initialize(true, TM1637_BRIGHTNESS_COEFFICIENT_2);
	
	
	ITOA_Set_String_Buffer(buf);
	
	while (1)
	{
		++data;
		TM1637_Put_Num_String(ITOA_Int16_To_String(data, 4), 4);
		
		_delay_ms(100);
	}
}




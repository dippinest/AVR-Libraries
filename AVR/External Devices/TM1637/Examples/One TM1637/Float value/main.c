

#include "tm1637.h"
#include "itoa.h"


static float data = -7.00;

static char buf[4];


int main(void)
{
	TM1637_Initialize(true, TM1637_BRIGHTNESS_COEFFICIENT_2);
	
	
	ITOA_Set_String_Buffer(buf);
	
	while (1)
	{
		data += 0.1;
		
		TM1637_Convert_Num_String_To_Symbols_Array(ITOA_Float_To_String(data, 3, 1), 4);
		TM1637_Put_Symbols((uint8_t*)ITOA_Get_String_Buffer_Ptr(), 4);
		
		_delay_ms(100);
	}
}







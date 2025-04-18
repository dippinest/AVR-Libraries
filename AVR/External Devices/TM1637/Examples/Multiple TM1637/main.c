

#include "tm1637.h"
#include "itoa.h"
#include "ftoa.h"


static int16_t data1 = -50;
static float   data2 = -50.0;

static char buf_1[4];
static char buf_2[4];


int main(void)
{
	TM1637_t tm1637_1 =
	TM1637_Create_Object(T(DDRC), T(PORTC), 0, T(DDRC), T(PINC), T(PORTC), 1, true, TM1637_BRIGHTNESS_COEFFICIENT_2);
	
	TM1637_t tm1637_2 =
	TM1637_Create_Object(T(DDRA), T(PORTA), 0, T(DDRA), T(PINA), T(PORTA), 1, true, TM1637_BRIGHTNESS_COEFFICIENT_8);
	

	ITOA_Set_String_Buffer(buf_1);
	FTOA_Set_String_Buffer(buf_2);
	
	
	
	while (1)
	{
		TM1637_Set_Target_Object(&tm1637_1);
		
		
		++data1;
		
		TM1637_Put_Num_String(ITOA_Int16_To_String(data1, 4), 4);
		
		
		
		TM1637_Set_Target_Object(&tm1637_2);
		
		
		data2 += 0.1;
		
		TM1637_Convert_Num_String_To_Symbols_Array(FTOA_Float32_To_String(data2, 3, 1), 4);
		TM1637_Put_Symbols((uint8_t*)FTOA_Get_String_Buffer_Ptr(), 4);
		
		
		_delay_ms(100);
	}
}






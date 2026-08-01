

#include <util/delay.h>

#include "tm1637.h"

#include "itoa.h"
#include "ftoa.h"



char string_buf_1[16];
char string_buf_2[16];


int main(void)
{
	TM1637_t tm1637_1 =
	TM1637_Create_Object(T(DDRB), T(PORTB), 0, T(DDRB), T(PINB), T(PORTB), 1, true, TM1637_BRIGHTNESS_COEFFICIENT_2);
	
	TM1637_t tm1637_2 =
	TM1637_Create_Object(T(DDRA), T(PORTA), 0, T(DDRA), T(PINA), T(PORTA), 1, true, TM1637_BRIGHTNESS_COEFFICIENT_8);
	

	ITOA_Set_String_Buffer(string_buf_1);
	FTOA_Set_String_Buffer(string_buf_2);
	
	
	int16_t val_1 = -50;
	float   val_2 = -50.0;
	
	
	
	while (1)
	{
		TM1637_Set_Target_Object(&tm1637_1);
		
		TM1637_Put_Num_String(ITOA_Int16_To_String(val_1, 4), 4);
		
		++val_1;
		
		
		
		TM1637_Set_Target_Object(&tm1637_2);
		
		TM1637_Put_Num_String(FTOA_Float32_To_String(val_2, 3, 1), 5);
		
		val_2 += 0.1;
		
		
		
		_delay_ms(100);
	}
}






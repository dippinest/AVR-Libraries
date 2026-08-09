

#include <util/delay.h>

#include "softi2c.h"
#include "lm75.h"
#include "uart.h"
#include "fixpoint.h"



// объект индикатора LM75
//
// ===============================================================================
// LM75 indicator object
//
LM75_t lm75;



char string_buffer[8];


int main(void)
{
	SOFTI2C_Initialize();
	
	UART_Initialize(9600, true, false);
	
	
	LM75_Initialize_Object(&lm75, LM75_I2C_DEV_ADDR_A2F_A1T_A0T, true);
	
	
	while (1)
	{
		UART_StringFmt_Transmit
		(
			"Temp = %s *C\r\n",
			
			FIXPoint_Int32FP_To_String
			(
				string_buffer, 2, LM75_Get_FIXPoint_2_Fractional_Digits_Temperature(&lm75), 3, 2, ' ', '.'
			)
		);
		
		
		_delay_ms(1000);
	}
}






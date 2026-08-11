

#include <util/delay.h>

#include "softi2c.h"
#include "lm75.h"
#include "uart.h"



// объект датчика температуры LM75
//
// ===============================================================================
// LM75 temperature sensor object
//
LM75_t lm75;



int main(void)
{
	SOFTI2C_Initialize();
	
	UART_Initialize(9600, true, false);
	
	
	LM75_Initialize_Object(&lm75, LM75_I2C_DEV_ADDR_A2F_A1T_A0T, true);
	
	
	while (1)
	{
		UART_StringFmt_Transmit("Temp = %d *C\r\n", LM75_Get_Integer_Temperature(&lm75));
		
		_delay_ms(1000);
	}
}





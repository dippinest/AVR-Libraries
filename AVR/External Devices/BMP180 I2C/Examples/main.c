
#include <util/delay.h>

#include "i2c.h"
#include "uart.h"

#include "bmp180_i2c.h"


BMP180_I2C_t bmp180;


int main(void)
{
	I2C_Initialize(100000);
	UART_Initialize(9600, true, false);
	
	bmp180 = BMP180_I2C_Get_Object();
	BMP180_I2C_Set_Target_Object(&bmp180);
	
	int16_t t;
	int32_t p;
	int16_t mmHg;
	
	while (1)
	{
		BMP180_I2C_Get_Temperature_And_Pressure(&t, &p, BMP180_I2C_PRESSURE_OSS_ACCURACY_MODE3);
		
		mmHg = BMP180_I2C_Convert_Pa_To_mmHg(p);
		
		
		UART_StringFmt_Transmit("T = %d *C; P = %li Pa (%d mm Hg)\r\n", t, p, mmHg);
		
		_delay_ms(1000);
	}
}




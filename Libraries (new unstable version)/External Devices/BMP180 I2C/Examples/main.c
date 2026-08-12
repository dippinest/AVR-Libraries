

#include <util/delay.h>

#include "bmp180_i2c.h"
#include "softi2c.h"
#include "uart.h"



// объект датчика BMP180_I2C
//
// ===============================================================================
// BMP180_I2C sensor object
//
BMP180_I2C_t bmp180;


int main(void)
{
	SOFTI2C_Initialize();
	
	
	UART_Initialize(9600, true, false);
	
	
	
	BMP180_I2C_Initialize_Object(&bmp180);
	
	
	
	// переменные для хранения значений температуры и давления
	//
	// ===============================================================================
	// variables for storing temperature and pressure values
	//
	int16_t t;
	int32_t p;
	int16_t mmHg;
	
	while (1)
	{
		BMP180_I2C_Get_Temperature_And_Pressure(&bmp180, &t, &p, BMP180_I2C_PRESSURE_OSS_ACCURACY_MODE3);
		
		mmHg = BMP180_I2C_Convert_Pa_To_mmHg(p);
		
		
		UART_StringFmt_Transmit("T = %d *C; P = %li Pa (%d mm Hg)\r\n", t, p, mmHg);
		
		_delay_ms(1000);
	}
}






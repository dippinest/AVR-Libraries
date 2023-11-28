
// ATN! to run the example, be sure to uncomment out the
// MAX6675_USE_SPI_CS_CALLBACKS macro in the max6675_configuration.h file!

#include <util/delay.h>

#include "i2c.h"
#include "hd44780_i2c.h"
#include "spi.h"
#include "max6675.h"

void CS_ON()
{
	PORTD &= ~(1 << 7);
}

void CS_OFF()
{
	PORTD |= (1 << 7);
}

int main(void)
{
	I2C_Initialize(100000);
	
	HD44780_I2C_t display = HD44780_I2C_Get_Device_Object(HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1T_A0T, true);
	
	HD44780_I2C_Set_Target_Device_Object(&display);
	
	
	DDRD |= (1 << 7);
	
	SPI_Initialize(true, SPI_DEV_IS_MASTER, SPI_MODE_0, SPI_SPEED_FCPU_DIV_2);
	SPI_Set_CS_CallBack_Functions(CS_ON, CS_OFF);
	
	while (1)
	{
		HD44780_I2C_Set_Cursor_Pos(0, 0);
		HD44780_I2C_Print_StringFmt("TEMP = %f *C", MAX6675_Get_Temperature_In_Celsius_Float());
		_delay_ms(500);
	}
}


#include "i2c.h"
#include "hd44780_i2c.h"
#include "lm75.h"
#include "itoa.h"

static char str[16];

int main(void)
{
	I2C_Initialize(100000);
	
	HD44780_I2C_t display = HD44780_I2C_Get_Object(HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1T_A0T, true);
	HD44780_I2C_Set_Target_Object(&display);
	
	LM75_t thermometer = LM75_Get_Object(LM75_I2C_DEV_ADDR_A2F_A1T_A0T, true);
	LM75_Set_Target_Object(&thermometer);
	
	HD44780_I2C_Set_Cursor_Pos(0, 0); HD44780_I2C_Print_String("LM75 THERMOMETER");
	
	ITOA_Set_String_Buffer(str);
	
	while (1)
	{
		HD44780_I2C_Clear_String_By_Pos(2, 0, 19);
		HD44780_I2C_Set_Cursor_Pos(2, 0);
		HD44780_I2C_Print_String("Temp = *C");
		HD44780_I2C_Print_String(ITOA_Float_To_String(LM75_Get_Float_Temperature(), 3, 1));
		
		_delay_ms(500);
	}
}



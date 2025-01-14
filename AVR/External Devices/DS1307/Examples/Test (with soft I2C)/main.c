
#include "softi2c.h"
#include "hd44780_i2c.h"
#include "ds1307.h"

int main(void)
{
	SOFTI2C_Initialize();
	
	HD44780_I2C_t display = HD44780_I2C_Get_Object(HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1T_A0T, true);
	
	HD44780_I2C_Set_Target_Object(&display);
	
	// This commented-out code is an example of recording time data
	//
	//	DS1307_Data_t data;
	//
	//	data.seconds      = 12;
	//	data.minutes      = 48;
	//	data.hours        = 11;
	//	data.weekday      = SUNDAY;
	//	data.day_of_month = 16;
	//	data.month        = JULY;
	//	data.year         = 23;
	//
	//	DS1307_Set_Data_From_Struct(&data);

	
	while (1)
	{
		HD44780_I2C_Clear_String_By_Pos(0, 0, 19); HD44780_I2C_Set_Cursor_Pos(0, 0);
		
		HD44780_I2C_Print_StringFmt("%02d/%02d/%04d", DS1307_Get_Day_Of_Month(), DS1307_Get_Month(), (2000 + DS1307_Get_Year()));
		
		HD44780_I2C_Clear_String_By_Pos(1, 0, 19); HD44780_I2C_Set_Cursor_Pos(1, 0);
		
		HD44780_I2C_Print_StringFmt("%02d:%02d:%02d", DS1307_Get_Hours(), DS1307_Get_Minutes(), DS1307_Get_Seconds());
		
		_delay_ms(800);
	}
}

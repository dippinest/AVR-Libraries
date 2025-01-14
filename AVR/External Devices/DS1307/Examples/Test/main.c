
#include "i2c.h"
#include "hd44780_i2c.h"
#include "ds1307.h"

int main(void)
{
	I2C_Initialize(100000);
	
	HD44780_I2C_t display = HD44780_I2C_Get_Object(HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1T_A0T, true);
	
	HD44780_I2C_Set_Target_Object(&display);
	
	HD44780_I2C_Set_Cursor_Pos(0, 0); HD44780_I2C_Print_String("DS1307 RTC Example");
	
	// This commented-out code is an example of recording time data
	//
	//	DS1307_Data_t data;
	//
	//	data.seconds      = 32;
	//	data.minutes      = 00;
	//	data.hours        = 20;
	//	data.weekday      = SATURDAY;
	//	data.day_of_month = 7;
	//	data.month        = MAY;
	//	data.year         = 22;
	//
	//	DS1307_Set_Data_From_Struct(&data);
	
	while (1)
	{
		HD44780_I2C_Clear_String_By_Pos(2, 0, 19); HD44780_I2C_Set_Cursor_Pos(2, 0);
		
		HD44780_I2C_Print_StringFmt("%02d/%02d/%04d  %02d:%02d:%02d",
			DS1307_Get_Day_Of_Month(), DS1307_Get_Month(), (2000 + DS1307_Get_Year()), DS1307_Get_Hours(), DS1307_Get_Minutes(), DS1307_Get_Seconds());
			
		_delay_ms(800);
	}
}

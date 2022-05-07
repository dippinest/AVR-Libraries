
#define F_CPU 16000000UL

#include "i2c.h"
#include "hd44780_i2c.h"

int main(void)
{
	const uint8_t customChar_CyrillicP[8] =
	{
		0b11111,
		0b10001,
		0b10001,
		0b10001,
		0b10001,
		0b10001,
		0b10001,
		0b00000
	};

	const uint8_t customChar_CyrillicI[8] =
	{
		0b10001,
		0b10001,
		0b10011,
		0b10101,
		0b11001,
		0b10001,
		0b10001,
		0b00000
	};

	const uint8_t customChar_SignoDeExclamacion[8] =
	{
		0b00100,
		0b00000,
		0b00000,
		0b00100,
		0b00100,
		0b00100,
		0b00100,
		0b00000
	};
	
	I2C_Initialize(100000);
	
	HD44780_I2C display = HD44780_I2C_Get_Display_Object(HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1T_A0T, true);
	
	HD44780_I2C_Set_Target_Display_Object(&display);
	
	HD44780_I2C_Set_User_Symbol_To_CGRAM(customChar_CyrillicP, 0x01);
	HD44780_I2C_Set_User_Symbol_To_CGRAM(customChar_CyrillicI, 0x02);
	HD44780_I2C_Set_User_Symbol_To_CGRAM(customChar_SignoDeExclamacion, 0x03);
	
	HD44780_I2C_Set_Cursor_Pos(0, 0); HD44780_I2C_Print_String(" HELLO, WORLD!  EN");
	
	char helloWorld_Spanish[] = { 0x03, 'H', 'O', 'L', 'A', ' ', 'M', 'U', 'N', 'D', 'O', '!', ' ', ' ', ' ', ' ', 'E', 'S', '\0' };
	HD44780_I2C_Set_Cursor_Pos(1, 0); HD44780_I2C_Print_String(helloWorld_Spanish);
	
	char helloWorld_Russian[] = { ' ', 0x01, 'P', 0x02, 'B', 'E', 'T', ',', ' ', 'M', 0x02, 'P', '!', ' ', ' ', ' ', 'R', 'U', '\0' };
	HD44780_I2C_Set_Cursor_Pos(2, 0); HD44780_I2C_Print_String(helloWorld_Russian);
	
	char helloWorld_Ukrainian[] = { ' ', 0x01, 'P', 0x02, 'B', 'I', 'T', ',', ' ', 'C', 'B', 'I', 'T', 'E', '!', ' ', 'U', 'A', '\0' };
	HD44780_I2C_Set_Cursor_Pos(3, 0); HD44780_I2C_Print_String(helloWorld_Ukrainian);
	
	while (1)
	{
	}
}
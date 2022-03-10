#define F_CPU 16000000UL

#include "i2c.h"
#include "uart.h"


//  For the I2C bus test, 2 devices were connected: pcf8574 chip (address: 0x27) and
//  SSD1306 (OLED 126*64 display controller) chip (address: 0x3D)

int main(void)
{
	I2C_Initialize(100000);
	
	UART_Initialize(9600, true, true, false, false, false, UART_NUM_OF_DATA_BITS_8, UART_NUM_OF_STOP_BITS_1, UART_PARITY_BIT_NONE);
	
	uint8_t device_counter = 0;
	
	UART_StringLn_Transmit("I2C Scanner...");; UART_NEW_LINE;
	
	for (uint8_t i = 8; i < 127; ++i)
	{
		if (I2C_Check_Device_By_Address(i))
		{
			UART_StringFmt_Transmit("Device was found on the bus! Address (hex): 0x%X\r\n", i);
			device_counter++;
		}
	}
	
	if (device_counter == 0)
	{
		UART_StringLn_Transmit("Unfortunately, no devices could be found...");
	}
	
	UART_NEW_LINE; UART_StringLn_Transmit("Done.");
	
	while (1)
	{
	}
}
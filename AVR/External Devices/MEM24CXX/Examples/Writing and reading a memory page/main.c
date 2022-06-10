
#include <util/delay.h>
#define F_CPU 16000000UL

#include <string.h>

#include "uart.h"
#include "i2c.h"
#include "mem24cxx.h"

static char buffer[32];

int main(void)
{
	UART_Initialize(9600, true, false);
	I2C_Initialize(100000);
	
	// use the recording timeout to work with standard 24Cxx chips.
	// If you use memory with support for "NoDelay" technology (for example,
	// FM24Cxx FRAM memory), you can not use the timeout
	MEM24CXX_t memory_chip = MEM24CXX_Get_Memory_Chip_Object(MEM24C32, MEM24CXX_DEV_ADDR_A2F_A1F_A0F, true);
	MEM24CXX_Set_Target_Memory_Chip_Object(&memory_chip);
	
	// data recording
	//
	//char string[] = "Hello from 24C32 EEPROM chip!";
	//MEM24CXX_Write_Page(0x0000, string, strlen(string));
	
	uint16_t reading_data_size = MEM24CXX_Read_Page(0x0000, buffer, 29);
	UART_Data_Transmit(buffer, reading_data_size);
	
	while (1)
	{
	}
}

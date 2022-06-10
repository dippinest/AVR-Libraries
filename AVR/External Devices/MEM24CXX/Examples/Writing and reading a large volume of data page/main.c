
#include <util/delay.h>
#define F_CPU 16000000UL

#include <string.h>

#include "uart.h"
#include "i2c.h"
#include "mem24cxx.h"

static char buffer[128];

int main(void)
{
	UART_Initialize(9600, true, false);
	I2C_Initialize(100000);
	
	char str[] = "Remember! Reality is an illusion, the Universe is an hologram, buy gold, bye! ©Bill Cipher";
	
	// use the recording timeout to work with standard 24Cxx chips.
	// If you use memory with support for "NoDelay" technology (for example,
	// FM24Cxx FRAM memory), you can not use the timeout
	MEM24CXX_t memory_chip = MEM24CXX_Get_Memory_Chip_Object(MEM24C32, MEM24CXX_DEV_ADDR_A2F_A1F_A0F, true);
	MEM24CXX_Set_Target_Memory_Chip_Object(&memory_chip);
	
	uint16_t n = MEM24CXX_Write_Data(0x0000, str, strlen(str));
	
	uint16_t reading_data_size = MEM24CXX_Read_Data(0x0000, buffer, n);
	UART_Data_Transmit(buffer, reading_data_size);
	
	while (1)
	{
	}
}

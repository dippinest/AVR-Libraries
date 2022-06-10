
#include <util/delay.h>
#define F_CPU 16000000UL

#include "uart.h"
#include "i2c.h"
#include "mem24cxx.h"

int main(void)
{
	UART_Initialize(9600, true, false);
	I2C_Initialize(100000);
	
	// use the recording timeout to work with standard 24Cxx chips.
	// If you use memory with support for "NoDelay" technology (for example,
	// FM24Cxx FRAM memory), you can not use the timeout
	MEM24CXX_t memory_chip = MEM24CXX_Get_Memory_Chip_Object(MEM24C32, MEM24CXX_DEV_ADDR_A2F_A1F_A0F, true);
	MEM24CXX_Set_Target_Memory_Chip_Object(&memory_chip);
	
	uint8_t buffer[memory_chip.page_size];
	
	for (uint32_t i = 0; i < memory_chip.byte_memory_size; i += memory_chip.page_size)
	{
		MEM24CXX_Read_Page(i, buffer, memory_chip.page_size);
		UART_Data_Transmit(buffer, memory_chip.page_size);
	}
	
	while (1)
	{
	}
}

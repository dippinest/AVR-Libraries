
#include <util/delay.h>
#define F_CPU 16000000UL

#include "uart.h"
#include "i2c.h"
#include "mem24cxx.h"

typedef struct
{
	uint16_t u16_data_1;
	uint16_t u16_data_2;
	float    float_data;
	
} SomeoneData;

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
	//SomeoneData data1 = { 0x1337, 0xFA11, 2.71828 };
	//MEM24CXX_Write_Data(0x0000, &data1, sizeof(SomeoneData));
	
	
	SomeoneData data2;
	
	MEM24CXX_Read_Data(0x0000, &data2, sizeof(SomeoneData));
	
	UART_StringFmt_Transmit("u16_data_1 = 0x%X, u32_data_2 = 0x%X, float_data = %f", data2.u16_data_1, data2.u16_data_2, data2.float_data);
	
	while (1)
	{
	}
}


#include "frami2c.h"

static FRAMI2C_t *target_memory_chip = NULL;


// ===============================================================================


FRAMI2C_t FRAMI2C_Get_Object(uint8_t dev_addr, uint16_t max_mem_addr)
{
	FRAMI2C_t mem;
	
	mem.dev_addr     = dev_addr;
	mem.max_mem_addr = max_mem_addr;
	
	return mem;
}

void FRAMI2C_Set_Target_Object(FRAMI2C_t *memory_chip)
{
	target_memory_chip = memory_chip;
}

FRAMI2C_t *FRAMI2C_Get_Target_Object()
{
	return target_memory_chip;
}


// ===============================================================================


#ifdef FRAMI2C_USE_SOFTI2C

#include "softi2c.h"


void FRAMI2C_Write_Byte(uint16_t memory_addr, uint8_t byte)
{
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(target_memory_chip->dev_addr << 1);
	SOFTI2C_Send_Byte(memory_addr >> 8);
	
	SOFTI2C_Send_Byte((uint8_t)memory_addr);
	
	SOFTI2C_Send_Byte(byte);
	
	SOFTI2C_Stop();
}

uint8_t FRAMI2C_Read_Byte(uint16_t memory_addr)
{
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(target_memory_chip->dev_addr << 1);
	SOFTI2C_Send_Byte(memory_addr >> 8);
	
	SOFTI2C_Send_Byte((uint8_t)memory_addr);
	
	SOFTI2C_Restart();
	
	SOFTI2C_Send_Byte((target_memory_chip->dev_addr << 1) | 1);
	
	uint8_t byte;
	
	SOFTI2C_Read_Byte(&byte, NACK);
	
	SOFTI2C_Stop();
	
	return byte;
}

uint16_t FRAMI2C_Write_Data(uint16_t memory_addr, void *data, uint16_t data_size)
{
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(target_memory_chip->dev_addr << 1);
	SOFTI2C_Send_Byte(memory_addr >> 8);
	
	SOFTI2C_Send_Byte((uint8_t)memory_addr);
	
	uint16_t i = 0;
	
	while(i < data_size)
	{
		SOFTI2C_Send_Byte(((uint8_t*)data)[i]);
		++i;
	}
	
	SOFTI2C_Stop();
	
	return i;
}

uint16_t FRAMI2C_Read_Data(uint16_t memory_addr, void *data, uint16_t data_size)
{
	if (data_size == 0)
	{
		return 0;
	}
	
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(target_memory_chip->dev_addr << 1);
	SOFTI2C_Send_Byte(memory_addr >> 8);
	
	SOFTI2C_Send_Byte((uint8_t)memory_addr);
	
	SOFTI2C_Restart();
	
	SOFTI2C_Send_Byte((target_memory_chip->dev_addr << 1) | 1);
	
	uint16_t i = 0;
	
	while (i < (data_size - 1))
	{
		SOFTI2C_Read_Byte(&((uint8_t*)data)[i], ACK);
		++i;
	}
	
	SOFTI2C_Read_Byte(&((uint8_t*)data)[i], NACK);
	++i;
	
	SOFTI2C_Stop();
	
	return i;
}

uint32_t FRAMI2C_Fill(uint16_t memory_addr, uint8_t val, uint32_t num)
{
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(target_memory_chip->dev_addr << 1);
	SOFTI2C_Send_Byte(memory_addr >> 8);
	
	SOFTI2C_Send_Byte((uint8_t)memory_addr);
	
	uint32_t i = 0;
	
	while(i < num)
	{
		SOFTI2C_Send_Byte(val);
		++i;
	}
	
	SOFTI2C_Stop();
	
	return i;
}


#else

#include "i2c.h"


void FRAMI2C_Write_Byte(uint16_t memory_addr, uint8_t byte)
{
	I2C_Start();
	
	I2C_Send_Byte(target_memory_chip->dev_addr << 1);
	I2C_Send_Byte(memory_addr >> 8);
	
	I2C_Send_Byte((uint8_t)memory_addr);
	
	I2C_Send_Byte(byte);
	
	I2C_Stop();
}

uint8_t FRAMI2C_Read_Byte(uint16_t memory_addr)
{
	I2C_Start();
	
	I2C_Send_Byte(target_memory_chip->dev_addr << 1);
	I2C_Send_Byte(memory_addr >> 8);
	
	I2C_Send_Byte((uint8_t)memory_addr);
	
	I2C_Restart();
	
	I2C_Send_Byte((target_memory_chip->dev_addr << 1) | 1);
	
	uint8_t byte;
	
	I2C_Read_Byte(&byte, NACK);
	
	I2C_Stop();
	
	return byte;
}

uint16_t FRAMI2C_Write_Data(uint16_t memory_addr, void *data, uint16_t data_size)
{
	I2C_Start();
	
	I2C_Send_Byte(target_memory_chip->dev_addr << 1);
	I2C_Send_Byte(memory_addr >> 8);
	
	I2C_Send_Byte((uint8_t)memory_addr);
	
	uint16_t i = 0;
	
	while(i < data_size)
	{
		I2C_Send_Byte(((uint8_t*)data)[i]);
		++i;
	}
	
	I2C_Stop();
	
	return i;
}

uint16_t FRAMI2C_Read_Data(uint16_t memory_addr, void *data, uint16_t data_size)
{
	if (data_size == 0)
	{
		return 0;
	}
	
	I2C_Start();
	
	I2C_Send_Byte(target_memory_chip->dev_addr << 1);
	I2C_Send_Byte(memory_addr >> 8);
	
	I2C_Send_Byte((uint8_t)memory_addr);
	
	I2C_Restart();
	
	I2C_Send_Byte((target_memory_chip->dev_addr << 1) | 1);
	
	uint16_t i = 0;
	
	while (i < (data_size - 1))
	{
		I2C_Read_Byte(&((uint8_t*)data)[i], ACK);
		++i;
	}
	
	I2C_Read_Byte(&((uint8_t*)data)[i], NACK);
	++i;
	
	I2C_Stop();
	
	return i;
}

uint32_t EEPROMI2C_Fill_All_Memory(uint16_t memory_addr, uint8_t val, uint32_t num)
{
	I2C_Start();
	
	I2C_Send_Byte(target_memory_chip->dev_addr << 1);
	I2C_Send_Byte(memory_addr >> 8);
	
	I2C_Send_Byte((uint8_t)memory_addr);
	
	uint32_t i = 0;
	
	while(i < num)
	{
		I2C_Send_Byte(val);
		++i;
	}
	
	I2C_Stop();
	
	return i;
}

#endif




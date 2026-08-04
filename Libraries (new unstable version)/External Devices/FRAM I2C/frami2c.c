

#include "frami2c.h"



// ===============================================================================



void FRAMI2C_Initialize_Object(FRAMI2C_t *frami2c, uint8_t dev_addr, uint16_t max_mem_addr)
{
	frami2c->dev_addr     = dev_addr;
	frami2c->max_mem_addr = max_mem_addr;
}



// ===============================================================================



#ifdef FRAMI2C_USE_SOFTI2C

#include "softi2c.h"



void FRAMI2C_Write_Byte(FRAMI2C_t *frami2c, uint16_t memory_addr, const uint8_t byte)
{
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(frami2c->dev_addr << 1);
	
	SOFTI2C_Send_Byte(memory_addr >> 8);
	
	SOFTI2C_Send_Byte((uint8_t)memory_addr);
	
	SOFTI2C_Send_Byte(byte);
	
	SOFTI2C_Stop();
}


uint8_t FRAMI2C_Read_Byte(FRAMI2C_t *frami2c, uint16_t memory_addr)
{
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(frami2c->dev_addr << 1);
	
	SOFTI2C_Send_Byte(memory_addr >> 8);
	
	SOFTI2C_Send_Byte((uint8_t)memory_addr);
	
	SOFTI2C_Restart();
	
	SOFTI2C_Send_Byte((frami2c->dev_addr << 1) | 1);
	
	
	uint8_t byte;
	
	
	SOFTI2C_Read_Byte(&byte, NACK);
	
	SOFTI2C_Stop();
	
	
	return byte;
}


uint16_t FRAMI2C_Write_Data(FRAMI2C_t *frami2c, uint16_t memory_addr, const void *data, uint16_t data_size)
{
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(frami2c->dev_addr << 1);
	
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


uint16_t FRAMI2C_Read_Data(FRAMI2C_t *frami2c, uint16_t memory_addr, void *data, uint16_t data_size)
{
	if (data_size == 0)
	{
		return 0;
	}
	
	
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(frami2c->dev_addr << 1);
	
	SOFTI2C_Send_Byte(memory_addr >> 8);
	
	SOFTI2C_Send_Byte((uint8_t)memory_addr);
	
	SOFTI2C_Restart();
	
	SOFTI2C_Send_Byte((frami2c->dev_addr << 1) | 1);
	
	
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


uint32_t FRAMI2C_Fill_Memory(FRAMI2C_t *frami2c, uint16_t memory_addr, const uint8_t val, uint32_t num)
{
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(frami2c->dev_addr << 1);
	
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


void FRAMI2C_Write_Byte(FRAMI2C_t *frami2c, uint16_t memory_addr, const uint8_t byte)
{
	I2C_Start();
	
	I2C_Send_Byte(frami2c->dev_addr << 1);
	
	I2C_Send_Byte(memory_addr >> 8);
	
	I2C_Send_Byte((uint8_t)memory_addr);
	
	I2C_Send_Byte(byte);
	
	I2C_Stop();
}


uint8_t FRAMI2C_Read_Byte(FRAMI2C_t *frami2c, uint16_t memory_addr)
{
	I2C_Start();
	
	I2C_Send_Byte(frami2c->dev_addr << 1);
	
	I2C_Send_Byte(memory_addr >> 8);
	
	I2C_Send_Byte((uint8_t)memory_addr);
	
	I2C_Restart();
	
	I2C_Send_Byte((frami2c->dev_addr << 1) | 1);
	
	
	uint8_t byte;
	
	
	I2C_Read_Byte(&byte, NACK);
	
	I2C_Stop();
	
	
	return byte;
}


uint16_t FRAMI2C_Write_Data(FRAMI2C_t *frami2c, uint16_t memory_addr, const void *data, uint16_t data_size)
{
	I2C_Start();
	
	I2C_Send_Byte(frami2c->dev_addr << 1);
	
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


uint16_t FRAMI2C_Read_Data(FRAMI2C_t *frami2c, uint16_t memory_addr, void *data, uint16_t data_size)
{
	if (data_size == 0)
	{
		return 0;
	}
	
	
	I2C_Start();
	
	I2C_Send_Byte(frami2c->dev_addr << 1);
	
	I2C_Send_Byte(memory_addr >> 8);
	
	I2C_Send_Byte((uint8_t)memory_addr);
	
	I2C_Restart();
	
	I2C_Send_Byte((frami2c->dev_addr << 1) | 1);
	
	
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


uint32_t FRAMI2C_Fill_Memory(FRAMI2C_t *frami2c, uint16_t memory_addr, const uint8_t val, uint32_t num)
{
	I2C_Start();
	
	I2C_Send_Byte(frami2c->dev_addr << 1);
	
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










#include "frami2c.h"



// ===============================================================================

#ifdef FRAMI2C_USE_SOFTI2C


#include "softi2c.h"

#define _I2C_Start       SOFTI2C_Start
#define _I2C_Send_Byte   SOFTI2C_Send_Byte
#define _I2C_Restart     SOFTI2C_Restart
#define _I2C_Read_Byte   SOFTI2C_Read_Byte
#define _I2C_Stop        SOFTI2C_Stop


#else


#include "i2c.h"

#define _I2C_Start       I2C_Start
#define _I2C_Send_Byte   I2C_Send_Byte
#define _I2C_Restart     I2C_Restart
#define _I2C_Read_Byte   I2C_Read_Byte
#define _I2C_Stop        I2C_Stop

#endif

// ===============================================================================



void FRAMI2C_Initialize_Object(FRAMI2C_t *frami2c, uint8_t dev_addr, uint16_t max_mem_addr)
{
	frami2c->dev_addr     = dev_addr;
	frami2c->max_mem_addr = max_mem_addr;
}



// ===============================================================================



void FRAMI2C_Write_Byte(FRAMI2C_t *frami2c, uint16_t memory_addr, const uint8_t byte)
{
	_I2C_Start();
	
	_I2C_Send_Byte(frami2c->dev_addr << 1);
	
	_I2C_Send_Byte(memory_addr >> 8);
	
	_I2C_Send_Byte((uint8_t)memory_addr);
	
	_I2C_Send_Byte(byte);
	
	_I2C_Stop();
}


uint8_t FRAMI2C_Read_Byte(FRAMI2C_t *frami2c, uint16_t memory_addr)
{
	_I2C_Start();
	
	_I2C_Send_Byte(frami2c->dev_addr << 1);
	
	_I2C_Send_Byte(memory_addr >> 8);
	
	_I2C_Send_Byte((uint8_t)memory_addr);
	
	_I2C_Restart();
	
	_I2C_Send_Byte((frami2c->dev_addr << 1) | 1);
	
	
	uint8_t byte;
	
	
	_I2C_Read_Byte(&byte, NACK);
	
	_I2C_Stop();
	
	
	return byte;
}


uint16_t FRAMI2C_Write_Data(FRAMI2C_t *frami2c, uint16_t memory_addr, const void *data, uint16_t data_size)
{
	_I2C_Start();
	
	_I2C_Send_Byte(frami2c->dev_addr << 1);
	
	_I2C_Send_Byte(memory_addr >> 8);
	
	_I2C_Send_Byte((uint8_t)memory_addr);
	
	
	uint16_t i = 0;
	
	
	while(i < data_size)
	{
		_I2C_Send_Byte(((uint8_t*)data)[i]);
		
		++i;
	}
	
	
	_I2C_Stop();
	
	
	return i;
}


uint16_t FRAMI2C_Read_Data(FRAMI2C_t *frami2c, uint16_t memory_addr, void *data, uint16_t data_size)
{
	if (data_size == 0)
	{
		return 0;
	}
	
	
	_I2C_Start();
	
	_I2C_Send_Byte(frami2c->dev_addr << 1);
	
	_I2C_Send_Byte(memory_addr >> 8);
	
	_I2C_Send_Byte((uint8_t)memory_addr);
	
	_I2C_Restart();
	
	_I2C_Send_Byte((frami2c->dev_addr << 1) | 1);
	
	
	uint16_t i = 0;
	
	
	while (i < (data_size - 1))
	{
		_I2C_Read_Byte(&((uint8_t*)data)[i], ACK);
		
		++i;
	}
	
	
	_I2C_Read_Byte(&((uint8_t*)data)[i], NACK);
	
	++i;
	
	
	_I2C_Stop();
	
	
	return i;
}


uint32_t FRAMI2C_Fill_Memory(FRAMI2C_t *frami2c, uint16_t memory_addr, const uint8_t val, uint32_t num)
{
	_I2C_Start();
	
	_I2C_Send_Byte(frami2c->dev_addr << 1);
	
	_I2C_Send_Byte(memory_addr >> 8);
	
	_I2C_Send_Byte((uint8_t)memory_addr);
	
	
	uint32_t i = 0;
	
	
	while(i < num)
	{
		_I2C_Send_Byte(val);
		
		++i;
	}
	
	
	_I2C_Stop();
	
	
	return i;
}








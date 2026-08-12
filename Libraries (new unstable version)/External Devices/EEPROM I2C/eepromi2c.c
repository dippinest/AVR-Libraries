

#include "eepromi2c.h"



// ===============================================================================


#ifdef EEPROMI2C_USE_SOFTI2C


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



void EEPROMI2C_Initialize_Object(EEPROMI2C_t *eepromi2c, uint8_t dev_addr, uint16_t max_mem_addr, uint8_t page_size)
{
	(*eepromi2c).dev_addr      = dev_addr;
	(*eepromi2c).max_mem_addr  = max_mem_addr;
	(*eepromi2c).page_size     = page_size;
}


void EEPROMI2C_Operation_Delay_Ms(uint8_t ms)
{
	while (ms)
	{
		_delay_ms(1);
		--ms;
	}
}




// ===============================================================================


void EEPROMI2C_Write_Byte(EEPROMI2C_t *eepromi2c, uint16_t memory_addr, const uint8_t byte)
{
	_I2C_Start();
	
	_I2C_Send_Byte(eepromi2c->dev_addr << 1);
	
	if (eepromi2c->max_mem_addr > EEPROMI2C_24C16_MAX_MEM_ADDR)
	{
		_I2C_Send_Byte(memory_addr >> 8);
	}
	
	_I2C_Send_Byte((uint8_t)memory_addr);
	
	_I2C_Send_Byte(byte);
	
	_I2C_Stop();
}


uint8_t EEPROMI2C_Read_Byte(EEPROMI2C_t *eepromi2c, uint16_t memory_addr)
{
	_I2C_Start();
	
	_I2C_Send_Byte(eepromi2c->dev_addr << 1);
	
	if (eepromi2c->max_mem_addr > EEPROMI2C_24C16_MAX_MEM_ADDR)
	{
		_I2C_Send_Byte(memory_addr >> 8);
	}
	
	_I2C_Send_Byte((uint8_t)memory_addr);
	
	_I2C_Restart();
	
	_I2C_Send_Byte((eepromi2c->dev_addr << 1) | 1);
	
	uint8_t byte;
	
	_I2C_Read_Byte(&byte, NACK);
	
	_I2C_Stop();
	
	return byte;
}


uint16_t EEPROMI2C_Write_Page(EEPROMI2C_t *eepromi2c, uint16_t memory_addr, const void *page, uint16_t page_size)
{
	_I2C_Start();
	
	_I2C_Send_Byte(eepromi2c->dev_addr << 1);
	
	if (eepromi2c->max_mem_addr > EEPROMI2C_24C16_MAX_MEM_ADDR)
	{
		_I2C_Send_Byte(memory_addr >> 8);
	}
	
	_I2C_Send_Byte((uint8_t)memory_addr);
	
	uint16_t i = 0;
	uint16_t j = memory_addr % eepromi2c->page_size;
	
	while(i < page_size && j < eepromi2c->page_size)
	{
		_I2C_Send_Byte(((uint8_t*)page)[i]);
		++i;
		++j;
	}
	
	_I2C_Stop();
	
	return i;
}


uint16_t EEPROMI2C_Fill_Page(EEPROMI2C_t *eepromi2c, uint16_t memory_addr, const uint8_t val, uint16_t num)
{
	_I2C_Start();
	
	_I2C_Send_Byte(eepromi2c->dev_addr << 1);
	
	if (eepromi2c->max_mem_addr > EEPROMI2C_24C16_MAX_MEM_ADDR)
	{
		_I2C_Send_Byte(memory_addr >> 8);
	}
	
	_I2C_Send_Byte((uint8_t)memory_addr);
	
	uint16_t i = 0;
	uint16_t j = memory_addr % eepromi2c->page_size;
	
	while(i < num && j < eepromi2c->page_size)
	{
		_I2C_Send_Byte(val);
		++i;
		++j;
	}
	
	_I2C_Stop();
	
	return i;
}


uint16_t EEPROMI2C_Read_Page(EEPROMI2C_t *eepromi2c, uint16_t memory_addr, void *page, uint16_t page_size)
{
	if (page_size == 0)
	{
		return 0;
	}
	
	_I2C_Start();
	
	_I2C_Send_Byte(eepromi2c->dev_addr << 1);
	
	if (eepromi2c->max_mem_addr > EEPROMI2C_24C16_MAX_MEM_ADDR)
	{
		_I2C_Send_Byte(memory_addr >> 8);
	}
	
	_I2C_Send_Byte((uint8_t)memory_addr);
	
	_I2C_Restart();
	
	_I2C_Send_Byte((eepromi2c->dev_addr << 1) | 1);
	
	uint16_t i = 0;
	uint16_t j = memory_addr % eepromi2c->page_size;
	
	while(j < (eepromi2c->page_size - 1) && i < (page_size - 1))
	{
		_I2C_Read_Byte(&((uint8_t*)page)[i], ACK);
		++i;
		++j;
	}
	
	_I2C_Read_Byte(&((uint8_t*)page)[i], NACK);
	++i;
	
	_I2C_Stop();
	
	return i;
}




// ===============================================================================



uint16_t EEPROMI2C_Write_Data(EEPROMI2C_t *eepromi2c, uint16_t memory_addr, const void *data, uint16_t data_size, uint8_t operation_delay_ms)
{
	uint16_t i = 0, n = 0;
	
	do
	{
		n = EEPROMI2C_Write_Page(eepromi2c, memory_addr + i, (void*)(data + i), data_size);
		
		EEPROMI2C_Operation_Delay_Ms(operation_delay_ms);
		
		i += n;
		data_size -= n;
		
	} while (n);
	
	return i;
}


uint16_t EEPROMI2C_Read_Data(EEPROMI2C_t *eepromi2c, uint16_t memory_addr, void *data, uint16_t data_size, uint8_t operation_delay_ms)
{
	uint16_t i = 0, n = 0;
	
	do
	{
		n = EEPROMI2C_Read_Page(eepromi2c, memory_addr + i, (void*)(data + i), data_size);
		
		EEPROMI2C_Operation_Delay_Ms(operation_delay_ms);
		
		i += n;
		data_size -= n;
		
	} while (n);
	
	return i;
}


uint32_t EEPROMI2C_Fill_Memory(EEPROMI2C_t *eepromi2c, uint16_t memory_addr, const uint8_t val, uint32_t num, uint8_t operation_delay_ms)
{
	uint16_t i = 0, n = 0;
	
	do
	{
		n = EEPROMI2C_Fill_Page(eepromi2c, memory_addr + i, val, num);
		
		EEPROMI2C_Operation_Delay_Ms(operation_delay_ms);
		
		i += n;
		num -= n;
		
	} while (num);
	
	return i;
}











#include "eepromi2c.h"

static EEPROMI2C_t *target_memory_chip = NULL;


// ===============================================================================


EEPROMI2C_t EEPROMI2C_Create_Object(uint8_t dev_addr, uint16_t max_mem_addr, uint8_t page_size)
{
	EEPROMI2C_t mem;
	
	mem.dev_addr           = dev_addr;
	mem.max_mem_addr       = max_mem_addr;
	mem.page_size          = page_size;
	
	return mem;
}

void EEPROMI2C_Set_Target_Object(EEPROMI2C_t *memory_chip)
{
	target_memory_chip = memory_chip;
}

EEPROMI2C_t *EEPROMI2C_Get_Target_Object()
{
	return target_memory_chip;
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


#ifdef EEPROMI2C_USE_SOFTI2C

#include "softi2c.h"


void EEPROMI2C_Write_Byte(uint16_t memory_addr, uint8_t byte)
{
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(target_memory_chip->dev_addr << 1);
	
	if (target_memory_chip->max_mem_addr > EEPROMI2C_24C16_MAX_MEM_ADDR)
	{
		SOFTI2C_Send_Byte(memory_addr >> 8);
	}
	
	SOFTI2C_Send_Byte((uint8_t)memory_addr);
	
	SOFTI2C_Send_Byte(byte);
	
	SOFTI2C_Stop();
}

uint8_t EEPROMI2C_Read_Byte(uint16_t memory_addr)
{
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(target_memory_chip->dev_addr << 1);
	
	if (target_memory_chip->max_mem_addr > EEPROMI2C_24C16_MAX_MEM_ADDR)
	{
		SOFTI2C_Send_Byte(memory_addr >> 8);
	}
	
	SOFTI2C_Send_Byte((uint8_t)memory_addr);
	
	SOFTI2C_Restart();
	
	SOFTI2C_Send_Byte((target_memory_chip->dev_addr << 1) | 1);
	
	uint8_t byte;
	
	SOFTI2C_Read_Byte(&byte, NACK);
	
	SOFTI2C_Stop();
	
	return byte;
}

uint16_t EEPROMI2C_Write_Page(uint16_t memory_addr, const void *page, uint16_t data_size)
{
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(target_memory_chip->dev_addr << 1);
	
	if (target_memory_chip->max_mem_addr > EEPROMI2C_24C16_MAX_MEM_ADDR)
	{
		SOFTI2C_Send_Byte(memory_addr >> 8);
	}
	
	SOFTI2C_Send_Byte((uint8_t)memory_addr);
	
	uint16_t i = 0;
	uint16_t j = memory_addr % target_memory_chip->page_size;
	
	while(i < data_size && j < target_memory_chip->page_size)
	{
		SOFTI2C_Send_Byte(((uint8_t*)page)[i]);
		++i;
		++j;
	}
	
	SOFTI2C_Stop();
	
	return i;
}

uint16_t EEPROMI2C_Fill_Page(uint16_t memory_addr, uint8_t val, uint16_t num)
{
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(target_memory_chip->dev_addr << 1);
	
	if (target_memory_chip->max_mem_addr >= EEPROMI2C_24C32_MAX_MEM_ADDR)
	{
		SOFTI2C_Send_Byte(memory_addr >> 8);
	}
	
	SOFTI2C_Send_Byte((uint8_t)memory_addr);
	
	uint16_t i = 0;
	uint8_t  j = memory_addr % target_memory_chip->page_size;
	
	while(i < num && j < target_memory_chip->page_size)
	{
		SOFTI2C_Send_Byte(val);
		++i;
		++j;
	}
	
	SOFTI2C_Stop();
	
	return i;
}

uint16_t EEPROMI2C_Read_Page(uint16_t memory_addr, void *page, uint16_t data_size)
{
	if (data_size == 0)
	{
		return 0;
	}
	
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(target_memory_chip->dev_addr << 1);
	
	if (target_memory_chip->max_mem_addr > EEPROMI2C_24C16_MAX_MEM_ADDR)
	{
		SOFTI2C_Send_Byte(memory_addr >> 8);
	}
	
	SOFTI2C_Send_Byte((uint8_t)memory_addr);
	
	SOFTI2C_Restart();
	
	SOFTI2C_Send_Byte((target_memory_chip->dev_addr << 1) | 1);
	
	uint16_t i = 0;
	uint16_t j = memory_addr % target_memory_chip->page_size;
	
	while(j < (target_memory_chip->page_size - 1) && i < (data_size - 1))
	{
		SOFTI2C_Read_Byte(&((uint8_t*)page)[i], ACK);
		++i;
		++j;
	}
	
	SOFTI2C_Read_Byte(&((uint8_t*)page)[i], NACK);
	++i;
	
	SOFTI2C_Stop();
	
	return i;
}



#else


#include "i2c.h"


void EEPROMI2C_Write_Byte(uint16_t memory_addr, const uint8_t byte)
{
	I2C_Start();
	
	I2C_Send_Byte(target_memory_chip->dev_addr << 1);
	
	if (target_memory_chip->max_mem_addr > EEPROMI2C_24C16_MAX_MEM_ADDR)
	{
		I2C_Send_Byte(memory_addr >> 8);
	}
	
	I2C_Send_Byte((uint8_t)memory_addr);
	
	I2C_Send_Byte(byte);
	
	I2C_Stop();
}

uint8_t EEPROMI2C_Read_Byte(uint16_t memory_addr)
{
	I2C_Start();
	
	I2C_Send_Byte(target_memory_chip->dev_addr << 1);
	
	if (target_memory_chip->max_mem_addr > EEPROMI2C_24C16_MAX_MEM_ADDR)
	{
		I2C_Send_Byte(memory_addr >> 8);
	}
	
	I2C_Send_Byte((uint8_t)memory_addr);
	
	I2C_Restart();
	
	I2C_Send_Byte((target_memory_chip->dev_addr << 1) | 1);
	
	uint8_t byte;
	
	I2C_Read_Byte(&byte, NACK);
	
	I2C_Stop();
	
	return byte;
}

uint16_t EEPROMI2C_Write_Page(uint16_t memory_addr, const void *page, uint16_t page_size)
{
	I2C_Start();
	
	I2C_Send_Byte(target_memory_chip->dev_addr << 1);
	
	if (target_memory_chip->max_mem_addr > EEPROMI2C_24C16_MAX_MEM_ADDR)
	{
		I2C_Send_Byte(memory_addr >> 8);
	}
	
	I2C_Send_Byte((uint8_t)memory_addr);
	
	uint16_t i = 0;
	uint16_t j = memory_addr % target_memory_chip->page_size;
	
	while(i < page_size && j < target_memory_chip->page_size)
	{
		I2C_Send_Byte(((uint8_t*)page)[i]);
		++i;
		++j;
	}
	
	I2C_Stop();
	
	return i;
}

uint16_t EEPROMI2C_Fill_Page(uint16_t memory_addr, const uint8_t val, uint16_t num)
{
	I2C_Start();
	
	I2C_Send_Byte(target_memory_chip->dev_addr << 1);
	
	if (target_memory_chip->max_mem_addr > EEPROMI2C_24C16_MAX_MEM_ADDR)
	{
		I2C_Send_Byte(memory_addr >> 8);
	}
	
	I2C_Send_Byte((uint8_t)memory_addr);
	
	uint16_t i = 0;
	uint16_t j = memory_addr % target_memory_chip->page_size;
	
	while(i < num && j < target_memory_chip->page_size)
	{
		I2C_Send_Byte(val);
		++i;
		++j;
	}
	
	I2C_Stop();
	
	return i;
}

uint16_t EEPROMI2C_Read_Page(uint16_t memory_addr, void *page, uint16_t page_size)
{
	if (page_size == 0)
	{
		return 0;
	}
	
	I2C_Start();
	
	I2C_Send_Byte(target_memory_chip->dev_addr << 1);
	
	if (target_memory_chip->max_mem_addr > EEPROMI2C_24C16_MAX_MEM_ADDR)
	{
		I2C_Send_Byte(memory_addr >> 8);
	}
	
	I2C_Send_Byte((uint8_t)memory_addr);
	
	I2C_Restart();
	
	I2C_Send_Byte((target_memory_chip->dev_addr << 1) | 1);
	
	uint16_t i = 0;
	uint16_t j = memory_addr % target_memory_chip->page_size;
	
	while(j < (target_memory_chip->page_size - 1) && i < (page_size - 1))
	{
		I2C_Read_Byte(&((uint8_t*)page)[i], ACK);
		++i;
		++j;
	}
	
	I2C_Read_Byte(&((uint8_t*)page)[i], NACK);
	++i;
	
	I2C_Stop();
	
	return i;
}


#endif // ===============================================================================



uint16_t EEPROMI2C_Write_Data(uint16_t memory_addr, const void *data, uint16_t data_size, uint8_t operation_delay_ms)
{
	uint16_t i = 0, n = 0;
	
	do
	{
		n = EEPROMI2C_Write_Page(memory_addr + i, (void*)(data + i), data_size);
		
		EEPROMI2C_Operation_Delay_Ms(operation_delay_ms);
		
		i += n;
		data_size -= n;
		
	} while (n);
	
	return i;
}

uint16_t EEPROMI2C_Read_Data(uint16_t memory_addr, void *data, uint16_t data_size, uint8_t operation_delay_ms)
{
	uint16_t i = 0, n = 0;
	
	do
	{
		n = EEPROMI2C_Read_Page(memory_addr + i, (void*)(data + i), data_size);
		
		EEPROMI2C_Operation_Delay_Ms(operation_delay_ms);
		
		i += n;
		data_size -= n;
		
	} while (n);
	
	return i;
}

uint32_t EEPROMI2C_Fill_Memory(uint16_t memory_addr, const uint8_t val, uint32_t num, uint8_t operation_delay_ms)
{
	uint16_t i = 0, n = 0;
	
	do
	{
		n = EEPROMI2C_Fill_Page(memory_addr + i, val, num);
		
		EEPROMI2C_Operation_Delay_Ms(operation_delay_ms);
		
		i += n;
		num -= n;
		
	} while (num);
	
	return i;
}



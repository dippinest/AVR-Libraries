
#include "mem24cxx.h"

static MEM24CXX_t *target_memory_chip = NULL;
static int16_t _eeprom_24cxx_waiting_timeout_ms = 10;

// ===============================================================================

static void _MEM24CXX_Waiting_Timeout_Ms(int16_t ms)
{
	while (ms)
	{
		_delay_ms(1);
		--ms;
	}
}

// ===============================================================================

MEM24CXX_t MEM24CXX_Get_Memory_Chip_Object(uint8_t memory_chip_type, uint8_t dev_addr, bool use_writing_delay)
{
	MEM24CXX_t mem;
	
	switch(memory_chip_type)
	{
		case MEM24C01:
			mem.byte_memory_size = MEM24C01_BYTE_SIZE;
			mem.page_size        = MEM24C01_PAGE_SIZE;
		break;
		case MEM24C02:
			mem.byte_memory_size = MEM24C02_BYTE_SIZE;
			mem.page_size        = MEM24C02_PAGE_SIZE;
		break;
		case MEM24C04:
			mem.byte_memory_size = MEM24C04_BYTE_SIZE;
			mem.page_size        = MEM24C04_PAGE_SIZE;
		break;
		case MEM24C08:
			mem.byte_memory_size = MEM24C08_BYTE_SIZE;
			mem.page_size        = MEM24C08_PAGE_SIZE;
		break;
		case MEM24C16:
			mem.byte_memory_size = MEM24C16_BYTE_SIZE;
			mem.page_size        = MEM24C16_PAGE_SIZE;
		break;
		case MEM24C32:
			mem.byte_memory_size = MEM24C32_BYTE_SIZE;
			mem.page_size        = MEM24C32_PAGE_SIZE;
		break;
		case MEM24C64:
			mem.byte_memory_size = MEM24C64_BYTE_SIZE;
			mem.page_size        = MEM24C64_PAGE_SIZE;
		break;
		case MEM24C128:
			mem.byte_memory_size = MEM24C128_BYTE_SIZE;
			mem.page_size        = MEM24C128_PAGE_SIZE;
		break;
		case MEM24C256:
			mem.byte_memory_size = MEM24C256_BYTE_SIZE;
			mem.page_size        = MEM24C256_PAGE_SIZE;
		break;
		case MEM24C512:
			mem.byte_memory_size = MEM24C512_BYTE_SIZE;
			mem.page_size        = MEM24C512_PAGE_SIZE;
		break;
		default:
			mem.byte_memory_size = 0;
			mem.page_size        = 0;
	}
	
	mem.dev_addr = dev_addr;
	mem.use_writing_delay = use_writing_delay;
	
	return mem;
}

void MEM24CXX_Set_Target_Memory_Chip_Object(MEM24CXX_t *memory_chip)
{
	target_memory_chip = memory_chip;
}

void MEM24CXX_Set_Target_Waiting_Timeout_Ms(const int16_t waiting_timeout_ms)
{
	_eeprom_24cxx_waiting_timeout_ms = waiting_timeout_ms;
}

int16_t MEM24CXX_Get_Target_Waiting_Timeout_Ms()
{
	return _eeprom_24cxx_waiting_timeout_ms;
}

// ===============================================================================

void MEM24CXX_Write_Byte(uint32_t memory_addr, uint8_t byte)
{
	I2C_Start();
	
	I2C_Send_Byte(target_memory_chip->dev_addr << 1);
	
	if (target_memory_chip->byte_memory_size > MEM24C16_BYTE_SIZE)
	{
		I2C_Send_Byte(memory_addr >> 8);
	}
	
	I2C_Send_Byte((uint8_t)memory_addr);
	
	I2C_Send_Byte(byte);
	
	I2C_Stop();
	
	if (target_memory_chip->use_writing_delay)
	{
		_MEM24CXX_Waiting_Timeout_Ms(_eeprom_24cxx_waiting_timeout_ms);
	}
}

uint8_t MEM24CXX_Read_Byte(uint32_t memory_addr)
{
	I2C_Start();
	
	I2C_Send_Byte(target_memory_chip->dev_addr << 1);
	
	if (target_memory_chip->byte_memory_size > MEM24C16_BYTE_SIZE)
	{
		I2C_Send_Byte(memory_addr >> 8);
	}
	
	I2C_Send_Byte((uint8_t)memory_addr);
	
	I2C_Restart();
	
	I2C_Send_Byte((target_memory_chip->dev_addr << 1) | 1);
	
	uint8_t byte;
	
	I2C_Read_Byte_Without_Confirmation(&byte);
	
	I2C_Stop();
	
	return byte;
}

uint16_t MEM24CXX_Write_Page(uint32_t memory_addr, void *page, uint8_t page_size)
{
	I2C_Start();
	
	I2C_Send_Byte(target_memory_chip->dev_addr << 1);
	
	if (target_memory_chip->byte_memory_size > MEM24C16_BYTE_SIZE)
	{
		I2C_Send_Byte(memory_addr >> 8);
	}
	
	I2C_Send_Byte((uint8_t)memory_addr);
	
	uint16_t i = 0;
	
	while(i < page_size && i < target_memory_chip->page_size)
	{
		I2C_Send_Byte(((uint8_t*)page)[i]);
		++i;
	}
	
	I2C_Stop();
	
	if (target_memory_chip->use_writing_delay)
	{
		_MEM24CXX_Waiting_Timeout_Ms(_eeprom_24cxx_waiting_timeout_ms);
	}
	
	return i;
}

uint16_t MEM24CXX_Fill_Page(uint32_t memory_addr, uint8_t val, uint16_t num)
{
	I2C_Start();
	
	I2C_Send_Byte(target_memory_chip->dev_addr << 1);
	
	if (target_memory_chip->byte_memory_size > MEM24C16_BYTE_SIZE)
	{
		I2C_Send_Byte(memory_addr >> 8);
	}
	
	I2C_Send_Byte((uint8_t)memory_addr);
	
	uint16_t i = 0;
	
	while(i < num && i < target_memory_chip->page_size)
	{
		I2C_Send_Byte(val);
		++i;
	}
	
	I2C_Stop();
	
	if (target_memory_chip->use_writing_delay)
	{
		_MEM24CXX_Waiting_Timeout_Ms(_eeprom_24cxx_waiting_timeout_ms);
	}
	
	return i;
}

uint16_t MEM24CXX_Read_Page(uint32_t memory_addr, void *page, uint8_t page_size)
{
	if (page_size == 0)
	{
		return 0;
	}
	
	I2C_Start();
	
	I2C_Send_Byte(target_memory_chip->dev_addr << 1);
	
	if (target_memory_chip->byte_memory_size > MEM24C16_BYTE_SIZE)
	{
		I2C_Send_Byte(memory_addr >> 8);
	}
	
	I2C_Send_Byte((uint8_t)memory_addr);
	
	I2C_Restart();
	
	I2C_Send_Byte((target_memory_chip->dev_addr << 1) | 1);
	
	uint16_t i = 0;
	
	while(i < (page_size - 1) && i < (target_memory_chip->page_size - 1))
	{
		I2C_Read_Byte_With_Confirmation(&((uint8_t*)page)[i]);
		++i;
	}
	
	if (i < target_memory_chip->page_size)
	{
		I2C_Read_Byte_Without_Confirmation(&((uint8_t*)page)[page_size - 1]);
		++i;
	}
	
	I2C_Stop();
	
	return i;
}

uint16_t MEM24CXX_Write_Data(uint32_t memory_addr, void *data, uint16_t data_size)
{
	uint16_t i = 0, n = 0;
	
	do
	{
		n = MEM24CXX_Write_Page(memory_addr + i, (void*)(data + i), data_size);
		
		i += n;
		data_size -= n;
		
	} while (n);
	
	return i;
}

uint16_t MEM24CXX_Read_Data(uint32_t memory_addr, void *data, uint16_t data_size)
{
	uint16_t i = 0, n = 0;
	
	do
	{
		n = MEM24CXX_Read_Page(memory_addr + i, (void*)(data + i), data_size);
		
		if (n == target_memory_chip->page_size)
		{
			--n;
		}
		
		i += n;
		data_size -= n;
		
	} while (n);
	
	return i;
}

uint16_t MEM24CXX_Memory_Set(uint32_t memory_addr, uint8_t val, uint16_t num)
{
	uint16_t i = 0, n = 0;
	
	do
	{
		n = MEM24CXX_Fill_Page(memory_addr + i, val, num);
		
		i += n;
		num -= n;
		
	} while (n);
	
	return i;
}

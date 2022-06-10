
#ifndef MEM24CXX_H_
#define MEM24CXX_H_

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "i2c.h"

#define MEM24CXX_DEV_ADDR_A2F_A1F_A0F 0x50 // A2F- A1F- A0F-
#define MEM24CXX_DEV_ADDR_A2F_A1F_A0T 0x51 // A2F- A1F- A0T+
#define MEM24CXX_DEV_ADDR_A2F_A1T_A0F 0x52 // A2F- A1T+ A0F-
#define MEM24CXX_DEV_ADDR_A2F_A1T_A0T 0x53 // A2F- A1T+ A0T+
#define MEM24CXX_DEV_ADDR_A2T_A1F_A0F 0x54 // A2T+ A1F- A0F-
#define MEM24CXX_DEV_ADDR_A2T_A1F_A0T 0x55 // A2T+ A1F- A0T+
#define MEM24CXX_DEV_ADDR_A2T_A1T_A0F 0x56 // A2T+ A1T+ A0F-
#define MEM24CXX_DEV_ADDR_A2T_A1T_A0T 0x57 // A2T+ A1T+ A0T+

#define MEM24C01    0
#define MEM24C02    1
#define MEM24C04    2
#define MEM24C08    3
#define MEM24C16    4
#define MEM24C32    5
#define MEM24C64    6
#define MEM24C128   7
#define MEM24C256   8
#define MEM24C512   9

#define MEM24C01_BYTE_SIZE    128
#define MEM24C02_BYTE_SIZE    256
#define MEM24C04_BYTE_SIZE    512
#define MEM24C08_BYTE_SIZE    1024
#define MEM24C16_BYTE_SIZE    2048
#define MEM24C32_BYTE_SIZE    4096
#define MEM24C64_BYTE_SIZE    8192
#define MEM24C128_BYTE_SIZE   16384
#define MEM24C256_BYTE_SIZE   32768
#define MEM24C512_BYTE_SIZE   65536

#define MEM24C01_PAGE_SIZE    8
#define MEM24C02_PAGE_SIZE    8
#define MEM24C04_PAGE_SIZE    16
#define MEM24C08_PAGE_SIZE    16
#define MEM24C16_PAGE_SIZE    16
#define MEM24C32_PAGE_SIZE    32
#define MEM24C64_PAGE_SIZE    32
#define MEM24C128_PAGE_SIZE   64
#define MEM24C256_PAGE_SIZE   64
#define MEM24C512_PAGE_SIZE   128

typedef struct
{
	uint8_t  dev_addr;
	uint32_t byte_memory_size;
	uint8_t  page_size;
	bool     use_writing_delay;
	
} MEM24CXX_t;

// ===============================================================================

MEM24CXX_t MEM24CXX_Get_Memory_Chip_Object(uint8_t memory_chip_type, uint8_t dev_addr, bool use_writing_delay);

void MEM24CXX_Set_Target_Memory_Chip_Object(MEM24CXX_t *memory_chip);

void MEM24CXX_Set_Target_Waiting_Timeout_Ms(const int16_t waiting_timeout_ms);

int16_t MEM24CXX_Get_Target_Waiting_Timeout_Ms();

// ===============================================================================

void MEM24CXX_Write_Byte(uint32_t memory_addr, uint8_t byte);

uint8_t MEM24CXX_Read_Byte(uint32_t memory_addr);

uint16_t MEM24CXX_Write_Page(uint32_t memory_addr, void *page, uint8_t page_size);

uint16_t MEM24CXX_Fill_Page(uint32_t memory_addr, uint8_t val, uint16_t num);

uint16_t MEM24CXX_Read_Page(uint32_t memory_addr, void *page, uint8_t page_size);

uint16_t MEM24CXX_Write_Data(uint32_t memory_addr, void *data, uint16_t data_size);

uint16_t MEM24CXX_Read_Data(uint32_t memory_addr, void *data, uint16_t data_size);

uint16_t MEM24CXX_Memory_Set(uint32_t memory_addr, uint8_t val, uint16_t num);

#endif

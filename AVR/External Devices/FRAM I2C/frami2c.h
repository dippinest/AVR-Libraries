

// ===============================================================================
//
// Библиотека для работы с FRAM памятью FM24CXX по шине I2C.
// Поддерживаются  чипы с размером памяти от 64 МБит (8 КБ).
// Библиотека позволяет записывать и читать данные из памяти по произвольным
// адресам, а также заполнять память конкретным значением.
//
// I2C можно использовать как аппаратный, так и программный -
// это можно настроить в файле конфигурации frami2c_configuration.h
//
// -------------------------------------------------------------------------------
//
// Library for working with FM24CXX FRAM memory over the I2C bus.
// Chips with a memory size of 64 MBit (8 KB) are supported.
// The library allows you to write and read data from memory
// at arbitrary addresses, as well as fill memory with a specific value.
//
// I2C can be used both hardware and software - this can be
// configured in the frami2c_configuration.h configuration file
//
// ===============================================================================


#ifndef FRAMI2C_H_
#define FRAMI2C_H_

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>

#include "frami2c_configuration.h"

// macros different I2C addresses for FM24Cxx
#define FRAMI2C_DEV_ADDR_A2F_A1F_A0F 0x50 // A2F- A1F- A0F-
#define FRAMI2C_DEV_ADDR_A2F_A1F_A0T 0x51 // A2F- A1F- A0T+
#define FRAMI2C_DEV_ADDR_A2F_A1T_A0F 0x52 // A2F- A1T+ A0F-
#define FRAMI2C_DEV_ADDR_A2F_A1T_A0T 0x53 // A2F- A1T+ A0T+
#define FRAMI2C_DEV_ADDR_A2T_A1F_A0F 0x54 // A2T+ A1F- A0F-
#define FRAMI2C_DEV_ADDR_A2T_A1F_A0T 0x55 // A2T+ A1F- A0T+
#define FRAMI2C_DEV_ADDR_A2T_A1T_A0F 0x56 // A2T+ A1T+ A0F-
#define FRAMI2C_DEV_ADDR_A2T_A1T_A0T 0x57 // A2T+ A1T+ A0T+

// --------------------------------------------
#define FM24C64_MAX_MEM_ADDR         8191UL
#define FM24C128_MAX_MEM_ADDR        16383UL
#define FM24C256_MAX_MEM_ADDR        32767UL
#define FM24C512_MAX_MEM_ADDR        65535UL


typedef struct
{
	uint8_t  dev_addr;
	uint16_t max_mem_addr;
	
} FRAMI2C_t;


// ===============================================================================

FRAMI2C_t FRAMI2C_Create_Object(uint8_t dev_addr, uint16_t max_mem_addr);

void FRAMI2C_Set_Target_Object(FRAMI2C_t *memory_chip);

FRAMI2C_t *FRAMI2C_Get_Target_Object();

// ===============================================================================

void FRAMI2C_Write_Byte(uint16_t memory_addr, uint8_t byte);

uint8_t FRAMI2C_Read_Byte(uint16_t memory_addr);

uint16_t FRAMI2C_Write_Data(uint16_t memory_addr, void *data, uint16_t data_size);

uint16_t FRAMI2C_Read_Data(uint16_t memory_addr, void *data, uint16_t data_size);

uint32_t FRAMI2C_Fill_Memory(uint16_t memory_addr, uint8_t val, uint32_t num);


#endif




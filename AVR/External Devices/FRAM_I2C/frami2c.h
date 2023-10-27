

// ===============================================================================
//
// Библиотека для работы с LCD дисплеем на контроллере HD44780 посредством I2C
// расширителя портов ввода-вывода PCF8574 (переходник). Библиотека позволяет
// работать с дисплеем как с I2C устройством. I2C можно использовать как
// аппаратный, так и программный - это можно настроить в
// файле конфигурации hd44780_configuration.h
//
// -------------------------------------------------------------------------------
//
// Library for working with the LCD display on the HD44780 controller via
// the I2C I/O port extender PCF8574 (adapter). The library allows you to
// work with the display as an I2C device. I2C can be used both hardware
// and software - this can be configured in the configuration
// file hd44780_configuration.h
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
#define FM24C01_MAX_MEM_ADDR         127UL
#define FM24C02_MAX_MEM_ADDR         255UL
#define FM24C04_MAX_MEM_ADDR         511UL
#define FM24C08_MAX_MEM_ADDR         1023UL
#define FM24C16_MAX_MEM_ADDR         2047UL
#define FM24C32_MAX_MEM_ADDR         4095UL
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

FRAMI2C_t FRAMI2C_Get_Memory_Chip_Object(uint8_t dev_addr, uint16_t max_mem_addr);

void FRAMI2C_Set_Target_Memory_Chip_Object(FRAMI2C_t *memory_chip);

FRAMI2C_t *FRAMI2C_Get_Target_Memory_Chip_Object();

// ===============================================================================

void FRAMI2C_Write_Byte(uint16_t memory_addr, uint8_t byte);

uint8_t FRAMI2C_Read_Byte(uint16_t memory_addr);

uint16_t FRAMI2C_Write_Data(uint16_t memory_addr, void *data, uint16_t data_size);

uint16_t FRAMI2C_Read_Data(uint16_t memory_addr, void *data, uint16_t data_size);

uint32_t FRAMI2C_Fill(uint16_t memory_addr, uint8_t val, uint32_t num);


#endif


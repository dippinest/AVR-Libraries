

// ===============================================================================
//
// Библиотека для работы с EEPROM памятью 24CXX по шине I2C.
// Библиотека позволяет записывать и читать данные из памяти по произвольным
// адресам, а также заполнять память конкретным значением.
//
// Следует отметить, что для операций записи и чтения память EEPROM
// требует некоторого временного интервала, поэтому между транзакциями
// следует делать паузу (к примеру, использовать временной промежуток для
// полезной работы или просто ждать, используя функцию EEPROMI2C_Operation_Delay_Ms).
// Обычно время между транзакциями занимает ~5 мс.
//
// В функциях EEPROMI2C_Write_Data, EEPROMI2C_Read_Data и EEPROMI2C_Fill_All_Memory
// таймаут между транзакциями задаётся непосредственно с помощью передаваемого
// параметра operation_delay_ms. Эти функции надолго блокируют систему, поэтому
// используйте их с осторожностью! Если для Вас важно быстродействие и/или
// энергоэффективность, я не рекомендую использовать эти функции напрямую,
// а весь необходимый функционал реализовывать с помощью конечных автоматов
// через отдельные транзакции (чтение/запись отдельных байтов, страниц).
//
// I2C можно использовать как аппаратный, так и программный -
// это можно настроить в файле конфигурации eepromi2c_configuration.h
//
// -------------------------------------------------------------------------------
//
// Library for working with 24CXX EEPROM memory over the I2C bus.
// The library allows you to write and read data from memory
// at arbitrary addresses, as well as fill memory with a specific value.
//
// It should be noted that for write and read operations, EEPROM memory
// requires a certain time interval, so you should pause between transactions
// (for example, use a time interval for useful work or just wait using the
// EEPROMI2C_Operation_Delay_Ms function). Usually the time between
// transactions takes ~5 ms.
//
// In the functions EEPROMI2C_Write_Data, EEPROMI2C_Read_Data and
// EEPROMI2C_Fill_All_Memory, the timeout between transactions is set
// directly using the passed parameter operation_delay_ms. These functions
// block the system for a long time, so use them with caution! If speed and/or
// energy efficiency are important to you, I do not recommend using these
// functions directly, but implementing all the necessary functionality
// using finite state machines through separate transactions
// (reading/writing individual bytes, pages).
//
// I2C can be used both hardware and software - this can be
// configured in the eepromi2c_configuration.h configuration file
//
// ===============================================================================


#ifndef EEPROMI2C_H_
#define EEPROMI2C_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>

#include "eepromi2c_configuration.h"

// macros different I2C addresses for 24Cxx
#define EEPROMI2C_DEV_ADDR_A2F_A1F_A0F 0x50 // A2F- A1F- A0F-
#define EEPROMI2C_DEV_ADDR_A2F_A1F_A0T 0x51 // A2F- A1F- A0T+
#define EEPROMI2C_DEV_ADDR_A2F_A1T_A0F 0x52 // A2F- A1T+ A0F-
#define EEPROMI2C_DEV_ADDR_A2F_A1T_A0T 0x53 // A2F- A1T+ A0T+
#define EEPROMI2C_DEV_ADDR_A2T_A1F_A0F 0x54 // A2T+ A1F- A0F-
#define EEPROMI2C_DEV_ADDR_A2T_A1F_A0T 0x55 // A2T+ A1F- A0T+
#define EEPROMI2C_DEV_ADDR_A2T_A1T_A0F 0x56 // A2T+ A1T+ A0F-
#define EEPROMI2C_DEV_ADDR_A2T_A1T_A0T 0x57 // A2T+ A1T+ A0T+

// --------------------------------------------
#define EEPROMI2C_24C01_MAX_MEM_ADDR   127UL
#define EEPROMI2C_24C02_MAX_MEM_ADDR   255UL
#define EEPROMI2C_24C04_MAX_MEM_ADDR   511UL
#define EEPROMI2C_24C08_MAX_MEM_ADDR   1023UL
#define EEPROMI2C_24C16_MAX_MEM_ADDR   2047UL
#define EEPROMI2C_24C32_MAX_MEM_ADDR   4095UL
#define EEPROMI2C_24C64_MAX_MEM_ADDR   8191UL
#define EEPROMI2C_24C128_MAX_MEM_ADDR  16383UL
#define EEPROMI2C_24C256_MAX_MEM_ADDR  32767UL
#define EEPROMI2C_24C512_MAX_MEM_ADDR  65535UL

// --------------------------------------------
#define EEPROMI2C_24C01_PAGE_SIZE        8
#define EEPROMI2C_24C02_PAGE_SIZE        8
#define EEPROMI2C_24C04_PAGE_SIZE       16
#define EEPROMI2C_24C08_PAGE_SIZE       16
#define EEPROMI2C_24C16_PAGE_SIZE       16
#define EEPROMI2C_24C32_PAGE_SIZE       32
#define EEPROMI2C_24C64_PAGE_SIZE       32
#define EEPROMI2C_24C128_PAGE_SIZE      64
#define EEPROMI2C_24C256_PAGE_SIZE      64
#define EEPROMI2C_24C512_PAGE_SIZE     128


typedef struct
{
	uint8_t  dev_addr;
	uint16_t max_mem_addr;
	uint8_t  page_size;
	
} EEPROMI2C_t;


// ===============================================================================

EEPROMI2C_t EEPROMI2C_Get_Memory_Chip_Object(uint8_t dev_addr, uint16_t max_mem_addr, uint8_t page_size);

void EEPROMI2C_Set_Target_Memory_Chip_Object(EEPROMI2C_t *memory_chip);

EEPROMI2C_t *EEPROMI2C_Get_Target_Memory_Chip_Object();

void EEPROMI2C_Operation_Delay_Ms(uint8_t ms);

// ===============================================================================

void EEPROMI2C_Write_Byte(uint16_t memory_addr, uint8_t byte);

uint8_t EEPROMI2C_Read_Byte(uint16_t memory_addr);

uint16_t EEPROMI2C_Write_Page(uint16_t memory_addr, void *page, uint16_t data_size);

uint16_t EEPROMI2C_Fill_Page(uint16_t memory_addr, uint8_t val, uint16_t num);

uint16_t EEPROMI2C_Read_Page(uint16_t memory_addr, void *page, uint16_t data_size);

uint16_t EEPROMI2C_Write_Data(uint16_t memory_addr, void *data, uint16_t data_size, uint8_t operation_delay_ms);

uint16_t EEPROMI2C_Read_Data(uint16_t memory_addr, void *data, uint16_t data_size, uint8_t operation_delay_ms);

uint32_t EEPROMI2C_Fill_All_Memory(uint16_t memory_addr, uint8_t val, uint32_t num, uint8_t operation_delay_ms);


#endif


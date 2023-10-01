

// ===============================================================================
//
// Библиотека для работы с датчиками температуры DS18B20 по программной шине 1-Wire.
// Вы можете работать как с одним датчиком, так и с несколькими - это можно
// настроить в файле конфигурации ds18b20_configuration.h
//
// -------------------------------------------------------------------------------
//
// Library for working with DS18B20 temperature sensors over the 1-Wire
// software bus. You can work with either one sensor or several - this can be
// configured in the ds18b20_configuration.h configuration file
//
// ===============================================================================


#ifndef DS18B20_H_
#define DS18B20_H_

#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "onewire.h"
#include "ds18b20_configuration.h"


// ===============================================================================


#define DS18B20_12BIT_RESOLUTION_CONVERT_TIMEOUT_MS  750
#define DS18B20_11BIT_RESOLUTION_CONVERT_TIMEOUT_MS  375
#define DS18B20_10BIT_RESOLUTION_CONVERT_TIMEOUT_MS  188
#define DS18B20_9BIT_RESOLUTION_CONVERT_TIMEOUT_MS   94

#define DS18B20_12BIT_RESOLUTION  0x7F
#define DS18B20_11BIT_RESOLUTION  0x5F
#define DS18B20_10BIT_RESOLUTION  0x3F
#define DS18B20_9BIT_RESOLUTION   0x1F

#define DS18B20_IS_USING_EXTERNAL_POWER_SUPPLY_MODE true
#define DS18B20_IS_USING_PARASITE_POWER_SUPPLY_MODE false


// ===============================================================================


inline uint8_t DS18B20_Test()
{
	if (ONEWIRE_Reset() == ONEWIRE_DEVICES_WAS_FOUND)
	{
		return 0;
	}
	
	return 1;
}


#ifdef DS18B20_USE_MULTIPLE_SENSORS


void DS18B20_Set_Target_DS18B20_Address(uint8_t *ds18b20_address);

uint8_t *DS18B20_Get_Target_DS18B20_Address();


// ===============================================================================


void DS18B20_Set_Resolution(uint8_t resolution);

void DS18B20_Set_Resolution_With_Skip_ROM(uint8_t resolution);

uint8_t *DS18B20_Get_Scratchpad(uint8_t *scrathpad_buffer);

void DS18B20_Start_Convert();

void DS18B20_Start_Convert_With_Skip_ROM();

int8_t DS18B20_Get_Integer_Temperature();

float DS18B20_Get_Float_Temperature();

float DS18B20_Get_Float_Temperature_With_Increased_Accuracy();

bool DS18B20_Get_Power_Supply();


#else // ===============================================================================


void DS18B20_Set_Resolution(uint8_t resolution);

uint8_t *DS18B20_Get_Scratchpad(uint8_t *scrathpad_buffer);

void DS18B20_Start_Convert();

int8_t DS18B20_Get_Integer_Temperature();

float DS18B20_Get_Float_Temperature();

bool DS18B20_Get_Power_Supply();


#endif


#endif



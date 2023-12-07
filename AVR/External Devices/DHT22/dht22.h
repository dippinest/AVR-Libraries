

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


#ifndef DHT22_H_
#define DHT22_H_


#include <avr/interrupt.h>

#include <stdint.h>

#include "onewire.h"



typedef struct
{
	uint8_t dht22_40bit_data_buffer[5];

} DHT22_Data_t;


// ===============================================================================

void DHT22_Convert_Prepare();

uint8_t DHT22_Start_Convert(DHT22_Data_t *dht22);

// ===============================================================================

int8_t DHT22_Get_Integer_Temperature(DHT22_Data_t *dht22);

int8_t DHT22_Get_Integer_Humidity(DHT22_Data_t *dht22);

float DHT22_Get_Float_Temperature(DHT22_Data_t *dht22);

float DHT22_Get_Float_Humidity(DHT22_Data_t *dht22);

// the return value is a signed int16_t number with a pseudo-fixed point
// with 1 decimal place
int16_t DHT22_Get_FIXPoint_1_Fractional_Digit_Temperature(DHT22_Data_t *dht22);

// the return value is a signed int16_t number with a pseudo-fixed point
// with 1 decimal place
int16_t DHT22_Get_FIXPoint_1_Fractional_Digit_Humidity(DHT22_Data_t *dht22);


#endif





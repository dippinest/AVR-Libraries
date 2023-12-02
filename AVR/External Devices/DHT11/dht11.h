

// ===============================================================================
//
// Библиотека дл работы с датчиком температуры и влажности DHT11
// по программной шине 1-Wire.
//
// -------------------------------------------------------------------------------
//
// A library for working with the DHT11 temperature and humidity sensor
// via the 1-Wire software bus.
//
// ===============================================================================


#ifndef DHT11_H_
#define DHT11_H_


#include <avr/interrupt.h>

#include <stdint.h>

#include "onewire.h"



typedef struct
{
	uint8_t dht11_40bit_data_buffer[5];

} DHT11_Data_t;


// ===============================================================================

void DHT11_Convert_Prepare();

uint8_t DHT11_Start_Convert(DHT11_Data_t *dht11);

int8_t DHT11_Get_Temperature(DHT11_Data_t *dht11);

int8_t DHT11_Get_Humidity(DHT11_Data_t *dht11);


#endif



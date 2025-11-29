

// ===============================================================================
//
// Библиотека для работы с преобразователем сигнала термопары K-типа MAX6675
// по интерфейсу SPI. SPI можно использовать как аппаратный, так и
// программный - это можно настроить в файле конфигурации max6675_configuration.h
//
// -------------------------------------------------------------------------------
//
// Library for working with the MAX6675 K-type thermocouple signal converter via
// the SPI interface. SPI can be used both hardware and software - this can be
// configured in the configuration file max6675_configuration.h
//
// ===============================================================================


#ifndef MAX6675_H_
#define MAX6675_H_

#include <stdint.h>

#include "max6675_configuration.h"


#ifdef MAX6675_USE_SOFTSPI

#include "softspi.h"

#else

#include "spi.h"

#endif


// ===============================================================================


float MAX6675_Get_Temperature_In_Celsius_Float();

uint16_t MAX6675_Get_Temperature_In_Celsius_Integer();

uint16_t MAX6675_Get_Temperature_In_Celsius_Fixpoint_2Bit();

#endif



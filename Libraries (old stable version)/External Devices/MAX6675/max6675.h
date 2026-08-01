

// ===============================================================================
//
// Библиотека для работы с преобразователем сигнала термопары K-типа MAX6675
// по интерфейсу SPI. SPI можно использовать как аппаратный, так и
// программный - это можно настроить в файле конфигурации max6675_configuration.h
//
// Помимо вывода температуры в различных типах чисел
// (целые, дробные и с значения фиксированной точкой), функции библиотеки
// автоматически отслеживают факт подключения и исправности термопары
// (если термопара исправна и подключена, функции возвращают значение true)
//
// -------------------------------------------------------------------------------
//
// Library for working with the MAX6675 K-type thermocouple signal converter via
// the SPI interface. SPI can be used both hardware and software - this can be
// configured in the configuration file max6675_configuration.h
//
// In addition to displaying the temperature in various types of numbers
// (integers, fractions, and fixed-point values), the library functions
// automatically monitor whether the thermocouple is connected and
// in good condition
// (if the thermocouple is in good condition and connected, the functions return true)
//
// ===============================================================================


#ifndef MAX6675_H_
#define MAX6675_H_

#include <stdint.h>
#include <stdbool.h>

#include "max6675_configuration.h"


// ===============================================================================


bool MAX6675_Get_Temperature_In_Celsius_Float(float *temperature);

bool MAX6675_Get_Temperature_In_Celsius_Integer(uint16_t *temperature);

bool MAX6675_Get_Temperature_In_Celsius_Fixpoint_2Bit(uint16_t *temperature);

#endif





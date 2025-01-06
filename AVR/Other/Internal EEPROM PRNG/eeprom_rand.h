
// ===============================================================================
//
// Библиотека генератора псевдослучайных чисел на основе внутренней EEPROM.
//
// Функции библиотеки позволяют получать псевдослучайные числа в диапазоне
// 8, 16 и 32 бита (а также числа в установленном диапазоне), используя
// EEPROM ячейки с адресами от 0x00 до max_eeprom_addr,
// который задаётся в параметрах функции. Основная ячейка памяти также
// задаётся в параметрах функции.
//
// Поскольку ячейки EEPROM имеют ограниченный ресурс на операцию записи,
// а скорость работы данной библиотеки из-за особенностей I/O операций EEPROM
// памяти невысока, рекомендуется применять данную библиотеку для генерации
// начального сида (семени) для для других типов ГПСЧ генераторов
// (например, стандартной функции rand()).
//
// -------------------------------------------------------------------------------
//
// Library of a pseudo-random number generator based on an internal EEPROM.
//
// The library functions allow you to get pseudorandom numbers in the range
// of 8, 16, and 32 bits (as well as numbers in the specified range)
// using the cell EEPROM with addresses from 0x00 to max_eeprom_addr,
// which is set in the function parameters.
// The main memory location is also set in the function parameters.
//
// Since EEPROM cells have a limited resource for a write operation,
// and the speed of this library is low due to the peculiarities of I/O
// operations of EEPROM memory, it is recommended to use this library
// to generate the initial seed for other types of PRNG generators
// (for example, the standard rand() function).
//
// ===============================================================================


#ifndef EEPROM_RAND_H_
#define EEPROM_RAND_H_

#include <stdint.h>
#include <stdbool.h>

#include "eeprom.h"


// ===============================================================================


void EEPROM_RAND_Initialize(uint16_t init_eeprom_addr, uint16_t max_eeprom_addr);

uint8_t EEPROM_RAND_Get_8Bit_Value();

uint16_t EEPROM_RAND_Get_16Bit_Value();

uint32_t EEPROM_RAND_Get_32Bit_Value();


// ===============================================================================


bool EEPROM_RAND_Get_Bool_Value();

uint8_t EEPROM_RAND_Get_UInt8_Value(uint8_t min, uint8_t max);

int8_t EEPROM_RAND_Get_Int8_Value(int8_t min, int8_t max);

uint16_t EEPROM_RAND_Get_UInt16_Value(uint16_t min, uint16_t max);

int16_t EEPROM_RAND_Get_Int16_Value(int16_t min, int16_t max);

uint32_t EEPROM_RAND_Get_UInt32_Value(uint32_t min, uint32_t max);

int32_t EEPROM_RAND_Get_Int32_Value(int32_t min, int32_t max);

float EEPROM_RAND_Get_Float_Value();


#endif



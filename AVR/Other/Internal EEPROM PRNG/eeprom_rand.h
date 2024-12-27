
// ===============================================================================
//
// Ѕиблиотека генератора псевдослучайных чисел на основе внутренней EEPROM.
//
// ‘ункции библиотеки позвол€ют получать псевдослучайные числа в диапазоне
// 8, 16 и 32 бита, использу€ EEPROM €чейки с адресами от 0x00 до max_eeprom_addr,
// который задаЄтс€ в параметрах функции. ќсновна€ €чейка пам€ти также
// задаЄтс€ в параметрах функции.
//
// ѕоскольку €чейки EEPROM имеют ограниченный ресурс на операцию записи,
// а скорость работы данной библиотеки из-за особенностей I/O операций EEPROM
// пам€ти невысока, рекомендуетс€ примен€ть данную библиотеку дл€ генерации
// начального сида (семени) дл€ дл€ других типов √ѕ—„ генераторов
// (например, стандартной функции rand()).
//
// -------------------------------------------------------------------------------
//
// Library of a pseudo-random number generator based on an internal EEPROM.
//
// The library functions allow you to get pseudo-random numbers in
// the range of 8, 16, and 32 bits using the cell EEPROM with addresses
// from 0x00 to max_eeprom_addr, which is set in the function parameters.
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


#include <avr/eeprom.h>

#include <stdint.h>


// ===============================================================================


uint8_t EEPROM_RAND_Get_8Bit_Value(uint8_t init_eeprom_addr, uint8_t max_eeprom_addr);

uint16_t EEPROM_RAND_Get_16Bit_Value(uint8_t init_eeprom_addr, uint8_t max_eeprom_addr);

uint32_t EEPROM_RAND_Get_32Bit_Value(uint8_t init_eeprom_addr, uint8_t max_eeprom_addr);


#endif



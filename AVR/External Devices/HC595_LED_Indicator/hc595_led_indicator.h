

// ===============================================================================
//
// Библиотека для работы с модулем семисегментного индикатора на основе двух
// микросхем сдвиговых регистров 74hc595, работающих по интерфейсу SPI.
// SPI можно использовать как аппаратный, так и программный - это можно настроить
// в файле конфигурации hc595_led_indicator_configuration.h
//
// -------------------------------------------------------------------------------
//
// Library for working with a seven-segment indicator module based on two
// 74hc595 shift register chips operating via the SPI interface. SPI can be
// used both hardware and software - this can be configured in the
// hc595_led_indicator_configuration.h configuration file
//
// ===============================================================================


#ifndef HC595_LED_INDICATOR_H_
#define HC595_LED_INDICATOR_H_

#include <stdint.h>

#include "hc595_led_indicator_configuration.h"


// ===============================================================================


#define HC595_LED_INDICATOR_SET_POINT(SYMBOL)   (SYMBOL & ~(1 << 7))
#define HC595_LED_INDICATOR_RESET_POINT(SYMBOL) (SYMBOL |  (1 << 7))

#define HC595_LED_INDICATOR_0      0b11000000
#define HC595_LED_INDICATOR_1      0b11111001
#define HC595_LED_INDICATOR_2      0b10100100
#define HC595_LED_INDICATOR_3      0b10110000
#define HC595_LED_INDICATOR_4      0b10011001
#define HC595_LED_INDICATOR_5      0b10010010
#define HC595_LED_INDICATOR_6      0b10000010
#define HC595_LED_INDICATOR_7      0b11111000
#define HC595_LED_INDICATOR_8      0b10000000
#define HC595_LED_INDICATOR_9      0b10010000
#define HC595_LED_INDICATOR_EMPTY  0b11111111
#define HC595_LED_INDICATOR_MINUS  0b10111111

#define HC595_LED_INDICATOR_A      0b10001000
#define HC595_LED_INDICATOR_B      0b10000011
#define HC595_LED_INDICATOR_C      0b11000110
#define HC595_LED_INDICATOR_D      0b10100001
#define HC595_LED_INDICATOR_E      0b10000110
#define HC595_LED_INDICATOR_F      0b10001110
#define HC595_LED_INDICATOR_G      0b10010000
#define HC595_LED_INDICATOR_H      0b10001011
#define HC595_LED_INDICATOR_I      0b11111011
#define HC595_LED_INDICATOR_J      0b11100001
#define HC595_LED_INDICATOR_K      0b10001001
#define HC595_LED_INDICATOR_L      0b11000111
#define HC595_LED_INDICATOR_M      0b11101010
#define HC595_LED_INDICATOR_N      0b10101011
#define HC595_LED_INDICATOR_O      0b11000000
#define HC595_LED_INDICATOR_P      0b10001100
#define HC595_LED_INDICATOR_Q      0b10011000
#define HC595_LED_INDICATOR_R      0b10101111
#define HC595_LED_INDICATOR_S      0b10010010
#define HC595_LED_INDICATOR_T      0b10000111
#define HC595_LED_INDICATOR_U      0b11000001
#define HC595_LED_INDICATOR_V      0b11100011
#define HC595_LED_INDICATOR_W      0b11010101
#define HC595_LED_INDICATOR_X      0b10001001
#define HC595_LED_INDICATOR_Y      0b10010001
#define HC595_LED_INDICATOR_Z      0b10100100


// ===============================================================================


const uint8_t *HC595_LED_Indicator_Get_Digits_Table();


// ===============================================================================


void HC595_LED_Indicator_Clear();

void HC595_LED_Indicator_Put_Symbols(uint8_t *simbols_arr, uint8_t simbols_arr_size, uint8_t *digits_counter);

void HC595_LED_Indicator_Put_Symbols_Reverse(uint8_t *simbols_arr, uint8_t simbols_arr_size, uint8_t *digits_counter);

void HC595_LED_Indicator_Put_Num_String(char *num_string, uint8_t num_string_size, uint8_t *digits_counter);

void HC595_LED_Indicator_Put_Num_String_Reverse(char *num_string, uint8_t num_string_size, uint8_t *digits_counter);


// ===============================================================================


char *HC595_LED_Indicator_Convert_Num_String_To_Symbols_Array(char *num_string, uint8_t num_string_size);

#endif





// ===============================================================================
//
// Библиотека для работы с модулем семисегментного индикатора на основе двух
// микросхем сдвиговых регистров 74hc595, работающих по интерфейсу SPI.
// SPI можно использовать как аппаратный, так и программный - это можно настроить
// в файле конфигурации hc595_ledind_configuration.h
//
// -------------------------------------------------------------------------------
//
// Library for working with a seven-segment indicator module based on two
// 74hc595 shift register chips operating via the SPI interface. SPI can be
// used both hardware and software - this can be configured in the
// hc595_ledind_configuration.h configuration file
//
// ===============================================================================


#ifndef HC595_LEDIND_H_
#define HC595_LEDIND_H_


#include <stdint.h>
#include <stddef.h>

#include "hc595_ledind_configuration.h"



// ===============================================================================


#define HC595_LEDIND_SET_POINT(SYMBOL)   (SYMBOL & ~(1 << 7))
#define HC595_LEDIND_RESET_POINT(SYMBOL) (SYMBOL |  (1 << 7))


#define HC595_LEDIND_0      0b11000000  // '0'
#define HC595_LEDIND_1      0b11111001  // '1'
#define HC595_LEDIND_2      0b10100100  // '2'
#define HC595_LEDIND_3      0b10110000  // '3'
#define HC595_LEDIND_4      0b10011001  // '4'
#define HC595_LEDIND_5      0b10010010  // '5'
#define HC595_LEDIND_6      0b10000010  // '6'
#define HC595_LEDIND_7      0b11111000  // '7'
#define HC595_LEDIND_8      0b10000000  // '8'
#define HC595_LEDIND_9      0b10010000  // '9'
#define HC595_LEDIND_EMPTY  0b11111111  // ' '
#define HC595_LEDIND_MINUS  0b10111111  // '-'

#define HC595_LEDIND_A      0b10001000  // 'A'
#define HC595_LEDIND_B      0b10000011  // 'b'
#define HC595_LEDIND_C      0b11000110  // 'C'
#define HC595_LEDIND_D      0b10100001  // 'd'
#define HC595_LEDIND_E      0b10000110  // 'E'
#define HC595_LEDIND_F      0b10001110  // 'F'
#define HC595_LEDIND_G      0b10010000  // 'g -> like a 9'
#define HC595_LEDIND_H      0b10001011  // 'h'
#define HC595_LEDIND_I      0b11111011  // 'i'
#define HC595_LEDIND_J      0b11100001  // 'J'
#define HC595_LEDIND_K      0b10001001  // 'K -> like a H'
#define HC595_LEDIND_L      0b11000111  // 'L'
#define HC595_LEDIND_M      0b11101010  // 'M'
#define HC595_LEDIND_N      0b10101011  // 'n'
#define HC595_LEDIND_O      0b11000000  // 'O -> like a 0'
#define HC595_LEDIND_P      0b10001100  // 'P'
#define HC595_LEDIND_Q      0b10011000  // 'q'
#define HC595_LEDIND_R      0b10101111  // 'r'
#define HC595_LEDIND_S      0b10010010  // 'S -> like a 5'
#define HC595_LEDIND_T      0b10000111  // 't'
#define HC595_LEDIND_U      0b11000001  // 'U'
#define HC595_LEDIND_V      0b11100011  // 'v'
#define HC595_LEDIND_W      0b11010101  // 'W'
#define HC595_LEDIND_X      0b10001001  // 'X -> like a H'
#define HC595_LEDIND_Y      0b10010001  // 'Y'
#define HC595_LEDIND_Z      0b10100100  // 'Z -> like a 2'


// ===============================================================================


typedef struct
{
	uint8_t digits_counter;

} HC595_LEDInd_t;


// ===============================================================================


HC595_LEDInd_t HC595_LEDInd_Get_Object();

void HC595_LEDInd_Set_Target_Object(HC595_LEDInd_t *indicator);

HC595_LEDInd_t *HC595_LEDInd_Get_Target_Object();

const uint8_t *HC595_LEDInd_Get_Digits_Table();


// ===============================================================================


void HC595_LEDInd_Clear();

void HC595_LEDInd_Put_Symbols(uint8_t *simbols_arr, uint8_t simbols_arr_size);

void HC595_LEDInd_Put_Symbols_Reverse(uint8_t *simbols_arr, uint8_t simbols_arr_size);

void HC595_LEDInd_Put_Num_String(char *num_string, uint8_t num_string_size);

void HC595_LEDInd_Put_Num_String_Reverse(char *num_string, uint8_t num_string_size);


// ===============================================================================


char *HC595_LEDInd_Convert_Num_String_To_Symbols_Array(char *num_string, uint8_t num_string_size);



#endif



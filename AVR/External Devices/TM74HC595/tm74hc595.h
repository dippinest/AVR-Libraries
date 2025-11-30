

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


#ifndef TM74HC595_H_
#define TM74HC595_H_


#include <avr/pgmspace.h>

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "tm74hc595_configuration.h"



// ===============================================================================


#define TM74HC595_SET_POINT(SYMBOL)   (SYMBOL & ~(1 << 7))
#define TM74HC595_RESET_POINT(SYMBOL) (SYMBOL |  (1 << 7))


#define TM74HC595_0      0b11000000  // '0'
#define TM74HC595_1      0b11111001  // '1'
#define TM74HC595_2      0b10100100  // '2'
#define TM74HC595_3      0b10110000  // '3'
#define TM74HC595_4      0b10011001  // '4'
#define TM74HC595_5      0b10010010  // '5'
#define TM74HC595_6      0b10000010  // '6'
#define TM74HC595_7      0b11111000  // '7'
#define TM74HC595_8      0b10000000  // '8'
#define TM74HC595_9      0b10010000  // '9'
#define TM74HC595_EMPTY  0b11111111  // ' '
#define TM74HC595_MINUS  0b10111111  // '-'

#define TM74HC595_A      0b10001000  // 'A'
#define TM74HC595_B      0b10000011  // 'b'
#define TM74HC595_C      0b11000110  // 'C'
#define TM74HC595_D      0b10100001  // 'd'
#define TM74HC595_E      0b10000110  // 'E'
#define TM74HC595_F      0b10001110  // 'F'
#define TM74HC595_G      0b10010000  // 'g -> like a 9'
#define TM74HC595_H      0b10001011  // 'h'
#define TM74HC595_I      0b11111011  // 'i'
#define TM74HC595_J      0b11100001  // 'J'
#define TM74HC595_K      0b10001001  // 'K -> like a H'
#define TM74HC595_L      0b11000111  // 'L'
#define TM74HC595_M      0b11101010  // 'M'
#define TM74HC595_N      0b10101011  // 'n'
#define TM74HC595_O      0b11000000  // 'O -> like a 0'
#define TM74HC595_P      0b10001100  // 'P'
#define TM74HC595_Q      0b10011000  // 'q'
#define TM74HC595_R      0b10101111  // 'r'
#define TM74HC595_S      0b10010010  // 'S -> like a 5'
#define TM74HC595_T      0b10000111  // 't'
#define TM74HC595_U      0b11000001  // 'U'
#define TM74HC595_V      0b11100011  // 'v'
#define TM74HC595_W      0b11010101  // 'W'
#define TM74HC595_X      0b10001001  // 'X -> like a H'
#define TM74HC595_Y      0b10010001  // 'Y'
#define TM74HC595_Z      0b10100100  // 'Z -> like a 2'


// ===============================================================================


typedef struct
{
	uint8_t symbols_counter;
	
	uint8_t point_char_separator_counter;
	
	void (*latch_callback)();

} TM74HC595_t;


// ===============================================================================


TM74HC595_t TM74HC595_Create_Object(void (*latch_callback)());

void TM74HC595_Set_Target_Object(TM74HC595_t *indicator);

TM74HC595_t *TM74HC595_Get_Target_Object();


// ===============================================================================


void TM74HC595_Clear();

void TM74HC595_Put_Symbols(uint8_t *symbols_arr, uint8_t symbols_arr_size);

void TM74HC595_Put_Symbols_Reverse(uint8_t *symbols_arr, uint8_t symbols_arr_size);

void TM74HC595_Put_Num_String(char *num_string, uint8_t num_string_size);

void TM74HC595_Put_Num_String_Reverse(char *num_string, uint8_t num_string_size);


// ===============================================================================


char *TM74HC595_Convert_Num_String_To_Symbols_Array(char *num_string, uint8_t num_string_size);



#endif



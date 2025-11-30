

// ===============================================================================
//
// Библиотека для работы с модулем семисегментных индикаторов,
// управление которых осуществляется с помощью микросхем сдвиговых регистров
// 74HC595 (по одному регистру на каждый семисегментный индикатор),
// работающих по интерфейсу SPI.
//
// SPI можно использовать как аппаратный, так и программный - это можно настроить
// в файле конфигурации hc595_ledind_configuration.h
//
// -------------------------------------------------------------------------------
//
// Library for working with a module of seven-segment indicators,
// which are controlled using 74HC595 shift register chips
// (one register for each seven-segment indicator)
// operating via the SPI interface.
//
// SPI can be used both hardware and software - this can be configured
// in the hc595_ledind_configuration.h configuration file
//
// ===============================================================================


#ifndef HC595SEVSEGIND_H_
#define HC595SEVSEGIND_H_



#include <avr/pgmspace.h>

#include <stdio.h>

#include "hc595sevsegind_configuration.h"



// ===============================================================================



#define HC595SEVSEGIND_SET_POINT(SYMBOL)   (SYMBOL & ~(1 << 7))
#define HC595SEVSEGIND_RESET_POINT(SYMBOL) (SYMBOL |  (1 << 7))


#define HC595SEVSEGIND_0      0b11000000  // '0'
#define HC595SEVSEGIND_1      0b11111001  // '1'
#define HC595SEVSEGIND_2      0b10100100  // '2'
#define HC595SEVSEGIND_3      0b10110000  // '3'
#define HC595SEVSEGIND_4      0b10011001  // '4'
#define HC595SEVSEGIND_5      0b10010010  // '5'
#define HC595SEVSEGIND_6      0b10000010  // '6'
#define HC595SEVSEGIND_7      0b11111000  // '7'
#define HC595SEVSEGIND_8      0b10000000  // '8'
#define HC595SEVSEGIND_9      0b10010000  // '9'
#define HC595SEVSEGIND_EMPTY  0b11111111  // ' '
#define HC595SEVSEGIND_MINUS  0b10111111  // '-'
#define HC595SEVSEGIND_POINT  0b01111111  // '.'

#define HC595SEVSEGIND_A      0b10001000  // 'A'
#define HC595SEVSEGIND_B      0b10000011  // 'b'
#define HC595SEVSEGIND_C      0b11000110  // 'C'
#define HC595SEVSEGIND_D      0b10100001  // 'd'
#define HC595SEVSEGIND_E      0b10000110  // 'E'
#define HC595SEVSEGIND_F      0b10001110  // 'F'
#define HC595SEVSEGIND_G      0b10010000  // 'g -> like a 9'
#define HC595SEVSEGIND_H      0b10001011  // 'h'
#define HC595SEVSEGIND_I      0b11111011  // 'i'
#define HC595SEVSEGIND_J      0b11100001  // 'J'
#define HC595SEVSEGIND_K      0b10001001  // 'K -> like a H'
#define HC595SEVSEGIND_L      0b11000111  // 'L'
#define HC595SEVSEGIND_M      0b11101010  // 'M'
#define HC595SEVSEGIND_N      0b10101011  // 'n'
#define HC595SEVSEGIND_O      0b11000000  // 'O -> like a 0'
#define HC595SEVSEGIND_P      0b10001100  // 'P'
#define HC595SEVSEGIND_Q      0b10011000  // 'q'
#define HC595SEVSEGIND_R      0b10101111  // 'r'
#define HC595SEVSEGIND_S      0b10010010  // 'S -> like a 5'
#define HC595SEVSEGIND_T      0b10000111  // 't'
#define HC595SEVSEGIND_U      0b11000001  // 'U'
#define HC595SEVSEGIND_V      0b11100011  // 'v'
#define HC595SEVSEGIND_W      0b11010101  // 'W'
#define HC595SEVSEGIND_X      0b10001001  // 'X -> like a H'
#define HC595SEVSEGIND_Y      0b10010001  // 'Y'
#define HC595SEVSEGIND_Z      0b10100100  // 'Z -> like a 2'



// ===============================================================================



typedef struct
{
	int8_t num_of_segments;
	
	void (*latch_callback)();
	
} HC595SevSegInd_t;


// ===============================================================================


HC595SevSegInd_t HC595SevSegInd_Create_Object(const int8_t num_of_segments, void (*latch_callback)());

void HC595SevSegInd_Set_Target_Object(HC595SevSegInd_t *indicator);

HC595SevSegInd_t *HC595SevSegInd_Get_Target_Object();


// ===============================================================================


void HC595SevSegInd_Clear_Display();

void HC595SevSegInd_Put_Symbols(const uint8_t *symbols_arr, int8_t symbols_arr_size);

void HC595SevSegInd_Put_Symbols_Reverse(const uint8_t *symbols_arr, int8_t symbols_arr_size);

void HC595SevSegInd_Put_Num_String(const char *num_string, uint8_t num_string_size);

void HC595SevSegInd_Put_Num_String_Reverse(const char *num_string, uint8_t num_string_size);



#endif



char *HC595SevSegInd_Convert_Num_String_To_Symbols_Array(char *num_string, uint8_t num_string_size);



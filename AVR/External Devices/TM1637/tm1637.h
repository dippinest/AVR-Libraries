

// ===============================================================================
//
// Библиотека для работы с семисегментным дисплеем на TM1637. Библиотека позволяет работать
// как с одиночным индикатором TM1637, так и с их множеством (это настраивается
// в файле tm1637_configuration.h)
//
// -------------------------------------------------------------------------------
//
// Library for working with a seven-segment display on TM1637. The library
// allows you to work with both a single TM1637 indicator and with many of
// them (this is configured in the tm1637_configuration.h file)
//
// ===============================================================================


#ifndef _TM1637_H_
#define _TM1637_H_

#include <avr/io.h>
#include <util/delay.h>

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tm1637_configuration.h"


#ifndef ACK
#define ACK true
#endif

#ifndef NACK
#define NACK false
#endif


// ===============================================================================


// macros for the luminance values of segments
#define TM1637_BRIGHTNESS_COEFFICIENT_1   0x00
#define TM1637_BRIGHTNESS_COEFFICIENT_2   0x01
#define TM1637_BRIGHTNESS_COEFFICIENT_3   0x02
#define TM1637_BRIGHTNESS_COEFFICIENT_4   0x03
#define TM1637_BRIGHTNESS_COEFFICIENT_5   0x04
#define TM1637_BRIGHTNESS_COEFFICIENT_6   0x05
#define TM1637_BRIGHTNESS_COEFFICIENT_7   0x06
#define TM1637_BRIGHTNESS_COEFFICIENT_8   0x07


#define TM1637_LEDIND_SET_POINT(SYMBOL)   (SYMBOL |  (1 << 7))
#define TM1637_LEDIND_RESET_POINT(SYMBOL) (SYMBOL & ~(1 << 7))


#define TM1637_0      0b00111111  // '0'
#define TM1637_1      0b00000110  // '1'
#define TM1637_2      0b01011011  // '2'
#define TM1637_3      0b01001111  // '3'
#define TM1637_4      0b01100110  // '4'
#define TM1637_5      0b01101101  // '5'
#define TM1637_6      0b01111101  // '6'
#define TM1637_7      0b00000111  // '7'
#define TM1637_8      0b01111111  // '8'
#define TM1637_9      0b01101111  // '9'
#define TM1637_EMPTY  0b00000000  // ' '
#define TM1637_MINUS  0b01000000  // '-'


#define TM1637_A      0b01110111  // 'A'
#define TM1637_B      0b01111100  // 'A'
#define TM1637_C      0b00111001  // 'C'
#define TM1637_D      0b01011110  // 'd'
#define TM1637_E      0b01111001  // 'E'
#define TM1637_F      0b01110001  // 'F'
#define TM1637_G      0b01101111  // 'g -> like a 9'
#define TM1637_H      0b01110100  // 'h'
#define TM1637_I      0b00110000  // 'I'
#define TM1637_J      0b00011110  // 'J'
#define TM1637_K      0b01110110  // 'K -> like a H'
#define TM1637_L      0b00111000  // 'L'
#define TM1637_N      0b01010100  // 'n'
#define TM1637_O      0b01011100  // 'o'
#define TM1637_P      0b01110011  // 'P'
#define TM1637_Q      0b01100111  // 'q'
#define TM1637_R      0b01010000  // 'r'
#define TM1637_S      0b01101101  // 'S -> like a 5'
#define TM1637_T      0b01111000  // 't'
#define TM1637_U      0b00111110  // 'U'
#define TM1637_V      0b00011100  // 'v'
#define TM1637_X      0b01110110  // 'X -> like a H'
#define TM1637_Y      0b01101110  // 'Y'
#define TM1637_Z      0b01011011  // 'Z -> like a 2'


// ===============================================================================


#ifndef TM1637_USE_MULTIPLE_INTERFACE


void TM1637_Initialize(bool is_enable, uint8_t brightness_coef);

void TM1637_Set_Enable(bool is_enable);

void TM1637_Set_Brightness(uint8_t brightness_coef);


#else // ===============================================================================


#ifndef T
#define T(P) ((uint8_t*)&P)
#endif


typedef struct
{
	uint8_t *clk_ddr;
	uint8_t *clk_port;
	uint8_t  clk_pin;
	
	uint8_t *dio_ddr;
	uint8_t *dio_pinx;
	uint8_t *dio_port;
	uint8_t  dio_pin;
	
	uint8_t  configuration_register_buffer;
	
} TM1637_t;

// ===============================================================================


TM1637_t TM1637_Create_Object(

	uint8_t *clk_ddr,
	uint8_t *clk_port,
	uint8_t  clk_pin,

	uint8_t *dio_ddr,
	uint8_t *dio_pinx,
	uint8_t *dio_port,
	uint8_t  dio_pin,

	bool is_enable,
	uint8_t brightness_coef
);

void TM1637_Set_Target_Object(TM1637_t *device);

TM1637_t *TM1637_Get_Target_Object();

void TM1637_Set_Enable(bool is_enable);

void TM1637_Set_Brightness(uint8_t brightness_coef);


#endif



void TM1637_Put_Symbols(uint8_t *simbols_arr, uint8_t simbols_arr_size);

void TM1637_Put_Symbols_Reverse(uint8_t *simbols_arr, uint8_t simbols_arr_size);

void TM1637_Put_Num_String(char *num_string, uint8_t num_string_size);

void TM1637_Put_Num_String_Reverse(char *num_string, uint8_t num_string_size);

void TM1637_Clear();

char *TM1637_Convert_Num_String_To_Symbols_Array(char *num_string, uint8_t num_string_size);



#endif





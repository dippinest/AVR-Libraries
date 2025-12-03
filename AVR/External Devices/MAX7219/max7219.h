

// ===============================================================================
//
// Библиотека для работы с драйвером семисегментных светодиодных индикаторов
// MAX7219 по интерфейсу SPI. SPI можно использовать как аппаратный, так и
// программный - это можно настроить в файле конфигурации max7219_configuration.h
//
// -------------------------------------------------------------------------------
//
// Library for working with the driver of seven-segment LED indicators MAX7219
// via the SPI interface. SPI can be used both hardware and software - this can
// be configured in the configuration file max7219_configuration.h
//
// ===============================================================================


#ifndef MAX7219_H_
#define MAX7219_H_


#include <avr/pgmspace.h>

#include <stdint.h>
#include <stdbool.h>

#include "max7219_configuration.h"



// ===============================================================================



// macros for the luminance values of segments
#define MAX7219_BRIGHTNESS_COEFFICIENT_1   0x00
#define MAX7219_BRIGHTNESS_COEFFICIENT_2   0x01
#define MAX7219_BRIGHTNESS_COEFFICIENT_3   0x02
#define MAX7219_BRIGHTNESS_COEFFICIENT_4   0x03
#define MAX7219_BRIGHTNESS_COEFFICIENT_5   0x04
#define MAX7219_BRIGHTNESS_COEFFICIENT_6   0x05
#define MAX7219_BRIGHTNESS_COEFFICIENT_7   0x06
#define MAX7219_BRIGHTNESS_COEFFICIENT_8   0x07
#define MAX7219_BRIGHTNESS_COEFFICIENT_9   0x08
#define MAX7219_BRIGHTNESS_COEFFICIENT_10  0x09
#define MAX7219_BRIGHTNESS_COEFFICIENT_11  0x0A
#define MAX7219_BRIGHTNESS_COEFFICIENT_12  0x0B
#define MAX7219_BRIGHTNESS_COEFFICIENT_13  0x0C
#define MAX7219_BRIGHTNESS_COEFFICIENT_14  0x0D
#define MAX7219_BRIGHTNESS_COEFFICIENT_15  0x0E
#define MAX7219_BRIGHTNESS_COEFFICIENT_16  0x0F


// macros for segment addresses
#define MAX7219_1_DIGIT                           0x00
#define MAX7219_2_DIGIT                           0x01
#define MAX7219_3_DIGIT                           0x02
#define MAX7219_4_DIGIT                           0x03
#define MAX7219_5_DIGIT                           0x04
#define MAX7219_6_DIGIT                           0x05
#define MAX7219_7_DIGIT                           0x06
#define MAX7219_8_DIGIT                           0x07


// macros of decoding modes
#define MAX7219_DECODE_MODE_NO_DECODE             0x00
#define MAX7219_DECODE_MODE_0_DIGIT_DECODE_ONLY   0x01
#define MAX7219_DECODE_MODE_3_0_DIGITS_DECODE     0x0F
#define MAX7219_DECODE_MODE_DECODE_ALL_DIGITS     0xFF


// macros for determining the direction of data output
#define MAX7219_DATA_DIRECTION_NORMAL   true
#define MAX7219_DATA_DIRECTION_REVERSE  false



// ===============================================================================



#define MAX7219_SET_POINT(SYMBOL)   (SYMBOL | 0b10000000)
#define MAX7219_RESET_POINT(SYMBOL) (SYMBOL & 0b01111111)


// macros of special character codes
#define MAX7219_EMPTY        0b00000000
#define MAX7219_SPACE        0b00000000
#define MAX7219_POINT        0b10000000
#define MAX7219_MINUS        0b00000001
#define MAX7219_DASH         0b00000001
#define MAX7219_DEGREE       0b01100011
#define MAX7219_OVERLINE     0b01000000
#define MAX7219_UNDERSCORE   0b00001000

// macros of digit codes
#define MAX7219_0            0b01111110
#define MAX7219_1            0b00110000
#define MAX7219_2            0b01101101
#define MAX7219_3            0b01111001
#define MAX7219_4            0b00110011
#define MAX7219_5            0b01011011
#define MAX7219_6            0b01011111
#define MAX7219_7            0b01110000
#define MAX7219_8            0b01111111
#define MAX7219_9            0b01111011

// macros of codes of some Latin letters
#define MAX7219_A            0b01110111
#define MAX7219_B            0b00011111
#define MAX7219_C            0b01001110
#define MAX7219_D            0b00111101
#define MAX7219_E            0b01001111
#define MAX7219_F            0b01000111
#define MAX7219_G            0b01111011
#define MAX7219_H            0b00110111
#define MAX7219_I            0b00110000
#define MAX7219_J            0b00111000
#define MAX7219_L            0b00001110
#define MAX7219_N            0b00010101
#define MAX7219_O            0b01111110
#define MAX7219_P            0b01100111
#define MAX7219_Q            0b01110011
#define MAX7219_R            0b00000101
#define MAX7219_S            0b01011011
#define MAX7219_T            0b00001111
#define MAX7219_U            0b00111110
#define MAX7219_V            0b00011100
#define MAX7219_Y            0b00111011
#define MAX7219_Z            0b01001001



// ===============================================================================



void MAX7219_Set_Enable(bool is_enable);

void MAX7219_Set_Decode_Mode(uint8_t decode_mode);

void MAX7219_Set_Num_Of_Involved_Digits(uint8_t num_of_involved_digits);

void MAX7219_Set_Brightness(uint8_t brightness_coef);



// ===============================================================================



void MAX7219_Set_Digit(uint8_t single_digit_pos, uint8_t digit_value);

void MAX7219_Clear_Single_Digit(uint8_t single_digit_pos);

void MAX7219_Clear_All(uint8_t num_of_involved_digits);

void MAX7219_Decode_Mode_Clear_Single_Digit(uint8_t single_digit_pos);

void MAX7219_Decode_Mode_Clear_All(uint8_t num_of_involved_digits);

void MAX7219_Display_Test();



// ===============================================================================



#ifdef MAX7219_USE_CS_CALLBACKS

void MAX7219_Initialize(bool is_enable, uint8_t decode_mode, uint8_t num_of_involved_digits, uint8_t brightness_coef);



void MAX7219_Put_Symbols(const uint8_t *symbols_arr, uint8_t symbols_arr_size, bool output_direction);

// use this function only with data decoding mode!
void MAX7219_Put_Num_String_With_Using_Decode_Mode(const char *data, uint8_t data_size, const uint8_t max_num_digits);


// use this function only without data decoding mode (MAX7219_DECODE_MODE_NO_DECODE)!
void MAX7219_Put_Num_String_With_Using_Program_Decoder(const char *data, uint8_t data_size);

void MAX7219_Put_Num_String_Reverse_With_Using_Program_Decoder(const char *data, uint8_t data_size);



#endif


char *MAX7219_Convert_Num_String_To_Symbols_Array(char *num_string, uint8_t num_string_size);



#endif






#ifndef MAX7219_H_
#define MAX7219_H_

#include <stdint.h>
#include <stdbool.h>

#include "spi.h"
#include "max7219_configuration.h"

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

#ifdef MAX7219_USE_SPI_CS_CALLBACKS

inline void MAX7219_Initialize(bool is_enable, uint8_t decode_mode, uint8_t num_of_involved_digits, uint8_t brightness_coef)
{
	MAX7219_Set_Enable(is_enable);
	MAX7219_Set_Decode_Mode(decode_mode);
	MAX7219_Set_Num_Of_Involved_Digits(num_of_involved_digits);
	MAX7219_Set_Brightness(brightness_coef);
	
	MAX7219_Decode_Mode_Clear_All(num_of_involved_digits);
}

// use this function only with data decoding mode!
void MAX7219_Set_Char_Digits(char *data, uint8_t data_size, const uint8_t max_num_digits);

#endif

#endif

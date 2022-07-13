
#ifndef LED_7SEG_74HC595_INDICATOR_H_
#define LED_7SEG_74HC595_INDICATOR_H_

#include <stdint.h>

#include "led_7seg_74hc595_indicator_configuration.h"

#ifdef LED_7SEG_74HC595_INDICATOR_USE_SOFTSPI
#include "softspi.h"
#else
#include "spi.h"
#endif

// ===============================================================================

#define LED_7SEG_74HC595_INDICATOR_SET_POINT(SYMBOL)   (SYMBOL & ~(1 << 7))
#define LED_7SEG_74HC595_INDICATOR_RESET_POINT(SYMBOL) (SYMBOL |  (1 << 7))

#define LED_7SEG_74HC595_INDICATOR_DIGIT_0     0b11000000
#define LED_7SEG_74HC595_INDICATOR_DIGIT_1     0b11111001
#define LED_7SEG_74HC595_INDICATOR_DIGIT_2     0b10100100
#define LED_7SEG_74HC595_INDICATOR_DIGIT_3     0b10110000
#define LED_7SEG_74HC595_INDICATOR_DIGIT_4     0b10011001
#define LED_7SEG_74HC595_INDICATOR_DIGIT_5     0b10010010
#define LED_7SEG_74HC595_INDICATOR_DIGIT_6     0b10000010
#define LED_7SEG_74HC595_INDICATOR_DIGIT_7     0b11111000
#define LED_7SEG_74HC595_INDICATOR_DIGIT_8     0b10000000
#define LED_7SEG_74HC595_INDICATOR_DIGIT_9     0b10010000
#define LED_7SEG_74HC595_INDICATOR_CHAR_EMPTY  0b11111111
#define LED_7SEG_74HC595_INDICATOR_CHAR_MINUS  0b10111111

#define LED_7SEG_74HC595_INDICATOR_CHAR_A      0b10001000
#define LED_7SEG_74HC595_INDICATOR_CHAR_B      0b10000011
#define LED_7SEG_74HC595_INDICATOR_CHAR_C      0b11000110
#define LED_7SEG_74HC595_INDICATOR_CHAR_D      0b10100001
#define LED_7SEG_74HC595_INDICATOR_CHAR_E      0b10000110
#define LED_7SEG_74HC595_INDICATOR_CHAR_F      0b10001110
#define LED_7SEG_74HC595_INDICATOR_CHAR_G      0b10010000
#define LED_7SEG_74HC595_INDICATOR_CHAR_H      0b10001011
#define LED_7SEG_74HC595_INDICATOR_CHAR_I      0b11111011
#define LED_7SEG_74HC595_INDICATOR_CHAR_J      0b11100001
#define LED_7SEG_74HC595_INDICATOR_CHAR_K      0b10001001
#define LED_7SEG_74HC595_INDICATOR_CHAR_L      0b11000111
#define LED_7SEG_74HC595_INDICATOR_CHAR_M      0b11101010
#define LED_7SEG_74HC595_INDICATOR_CHAR_N      0b10101011
#define LED_7SEG_74HC595_INDICATOR_CHAR_O      0b11000000
#define LED_7SEG_74HC595_INDICATOR_CHAR_P      0b10001100
#define LED_7SEG_74HC595_INDICATOR_CHAR_Q      0b10011000
#define LED_7SEG_74HC595_INDICATOR_CHAR_R      0b10101111
#define LED_7SEG_74HC595_INDICATOR_CHAR_S      0b10010010
#define LED_7SEG_74HC595_INDICATOR_CHAR_T      0b10000111
#define LED_7SEG_74HC595_INDICATOR_CHAR_U      0b11000001
#define LED_7SEG_74HC595_INDICATOR_CHAR_V      0b11100011
#define LED_7SEG_74HC595_INDICATOR_CHAR_W      0b11010101
#define LED_7SEG_74HC595_INDICATOR_CHAR_X      0b10001001
#define LED_7SEG_74HC595_INDICATOR_CHAR_Y      0b10010001
#define LED_7SEG_74HC595_INDICATOR_CHAR_Z      0b10100100

// ===============================================================================

const uint8_t *LED_7Seg_74HC595_Indicator_Get_Digits_Table();

// ===============================================================================

void LED_7Seg_74HC595_Indicator_Put_Symbols(uint8_t *simbols_arr, uint8_t simbols_arr_size, uint8_t *digits_counter);

void LED_7Seg_74HC595_Indicator_Put_Symbols_Reverse(uint8_t *simbols_arr, uint8_t simbols_arr_size, uint8_t *digits_counter);

void LED_7Seg_74HC595_Indicator_Put_Num_String(char *num_string, uint8_t num_string_size, uint8_t *digits_counter);

void LED_7Seg_74HC595_Indicator_Put_Num_String_Reverse(char *num_string, uint8_t num_string_size, uint8_t *digits_counter);

// ===============================================================================

char *LED_7Seg_74HC595_Indicator_Num_String_To_Symbols_Array(char *num_string, uint8_t num_string_size);

#endif

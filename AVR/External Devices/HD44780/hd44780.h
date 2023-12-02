

// ===============================================================================
//
// Библиотека для работы с LCD дисплеем на контроллере HD44780. Библиотека
// позволяет работать с дисплеем в 4-х битном режиме. Выводы микроконтроллера,
// через которые подключается дисплей можно настроить в файле
// конфигурации hd44780_configuration.h
//
// -------------------------------------------------------------------------------
//
// Library for working with the LCD display on the HD44780 controller.
// The library allows you to work with the display in 4-bit mode.
// The microcontroller pins through which the display is connected can
// be configured in the configuration file hd44780_configuration.h
//
// ===============================================================================


#ifndef HD44780_H_
#define HD44780_H_

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "hd44780_configuration.h"


#ifndef FLASH
#define FLASH(VAL, TYPE, DATA) const TYPE VAL[] PROGMEM = DATA
#endif



#define _HD44780_SET_E_HIGH  (HD44780_E_PORT |=  (1 << HD44780_E_PIN))
#define _HD44780_SET_E_LOW   (HD44780_E_PORT &= ~(1 << HD44780_E_PIN))

#define _HD44780_SET_RS_HIGH (HD44780_RS_PORT |=  (1 << HD44780_RS_PIN))
#define _HD44780_SET_RS_LOW  (HD44780_RS_PORT &= ~(1 << HD44780_RS_PIN))

#define _HD44780_ENTRY_MODE_DISPLAY_S_DISPLAY_SHIFT_BIT              0
#define _HD44780_ENTRY_MODE_DISPLAY_ID_INCDEC_CURSOR_POSITION_BIT    1

#define _HD44780_CONTROL_MODE_DISPLAY_B_CURSOR_BLINK_BIT             0
#define _HD44780_CONTROL_MODE_DISPLAY_C_CURSOR_ONOFF_BIT             1
#define _HD44780_CONTROL_MODE_DISPLAY_D_DISPLAY_ONOFF_BIT            2

#define _HD44780_CURSOR_DISPLAY_SHIFT_MODE_RL_SHIFT_CURSOR_BIT       2
#define _HD44780_CURSOR_DISPLAY_SHIFT_MODE_SC_SHIFT_DISPLAY_BIT      3

#define _HD44780_FUNCTION_SET_MODE_DISPLAY_F_FONT_BIT                2
#define _HD44780_FUNCTION_SET_MODE_DISPLAY_N_NUM_LINES_BIT           3
#define _HD44780_FUNCTION_SET_MODE_DISPLAY_DL_BITMODE_INTERFACE_BIT  4

#define _HD44780_DISPLAY_SEND_COMMAND_MODE                           0
#define _HD44780_DISPLAY_SEND_DATA_MODE                              1

#define HD44780_SHIFT_TO_RIGHT  true
#define HD44780_SHIFT_TO_LEFT   false


void HD44780_Initialize(bool display_is_enable);

void HD44780_Set_Display_Enable(bool display_is_enable);

void HD44780_Set_Cursor_Enable(bool cursor_is_enable);

void HD44780_Set_Cursor_Blink(bool cursor_is_blink);

void HD44780_Set_Cursor_Pos(uint8_t string_pos, uint8_t first_char_pos);

void HD44780_Set_User_Symbol_To_CGRAM(const uint8_t *_8byte_simbol_bitmap_array, uint8_t simbol_number);

void HD44780_Set_Flash_User_Symbol_To_CGRAM(const uint8_t *_8byte_flash_simbol_bitmap_array, uint8_t flash_simbol_number);


// ===============================================================================


void HD44780_Print_Char(char c);

void HD44780_Print_Data(const void *data, uint8_t data_size);

void HD44780_Print_String(const char *string_array);

void HD44780_Safe_Print_String(const char *string_array, uint16_t max_string_len);

void HD44780_Print_StringFmt(const char *string_fmt, ...);

void HD44780_Set_Print_To_Char_Terminator(const char* string_array, const char terminator);

void HD44780_Fill_Char_Pattern(const char char_pattern, uint8_t num_pattern_chars);


// ===============================================================================


void HD44780_Print_Flash_Char(const char *flash_c);

void HD44780_Print_Flash_Data(const void *flash_data, uint8_t flash_data_size);

void HD44780_Print_Flash_String(const char *flash_string);

void HD44780_Safe_Print_Flash_String(const char *flash_string, uint16_t max_flash_string_len);

void HD44780_Print_Flash_StringFmt(const char *flash_string_fmt, ...);

void HD44780_Print_Flash_String_To_Char_Terminator(const char* flash_string, const char terminator);


// ===============================================================================


void HD44780_Display_Shift(bool display_shift_is_right);

void HD44780_Set_Cursor_Home();

void HD44780_Clear_String_By_Pos(uint8_t string_pos, uint8_t first_char_pos, uint8_t end_char_pos);

void HD44780_Clear();


#endif



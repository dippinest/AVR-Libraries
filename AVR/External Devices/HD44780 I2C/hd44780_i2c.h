

// ===============================================================================
//
// Библиотека для работы с LCD дисплеем на контроллере HD44780 посредством I2C
// расширителя портов ввода-вывода PCF8574 (переходник). Библиотека позволяет
// работать с дисплеем как с I2C устройством. I2C можно использовать как
// аппаратный, так и программный - это можно настроить в
// файле конфигурации hd44780_i2c_configuration.h
//
// -------------------------------------------------------------------------------
//
// Library for working with the LCD display on the HD44780 controller via
// the I2C I/O port extender PCF8574 (adapter). The library allows you to
// work with the display as an I2C device. I2C can be used both hardware
// and software - this can be configured in the configuration
// file hd44780_i2c_configuration.h
//
// ===============================================================================


#ifndef HD44780_I2C_H_
#define HD44780_I2C_H_

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "hd44780_i2c_configuration.h"


#ifndef AVR_FLASH_DATA
#define AVR_FLASH_DATA(VAL, TYPE, DATA) const TYPE VAL[] PROGMEM = DATA
#endif

// macros different I2C addresses for PCF8574 and PCF8574A
#define HD44780_I2C_PCF8574_DEV_ADDR_A2F_A1F_A0F   0x20
#define HD44780_I2C_PCF8574_DEV_ADDR_A2F_A1F_A0T   0x21
#define HD44780_I2C_PCF8574_DEV_ADDR_A2F_A1T_A0F   0x22
#define HD44780_I2C_PCF8574_DEV_ADDR_A2F_A1T_A0T   0x23
#define HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1F_A0F   0x24
#define HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1F_A0T   0x25
#define HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1T_A0F   0x26
#define HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1T_A0T   0x27

#define HD44780_I2C_PCF8574A_DEV_ADDR_A2F_A1F_A0F  0x38
#define HD44780_I2C_PCF8574A_DEV_ADDR_A2F_A1F_A0T  0x39
#define HD44780_I2C_PCF8574A_DEV_ADDR_A2F_A1T_A0F  0x3A
#define HD44780_I2C_PCF8574A_DEV_ADDR_A2F_A1T_A0T  0x3B
#define HD44780_I2C_PCF8574A_DEV_ADDR_A2T_A1F_A0F  0x3C
#define HD44780_I2C_PCF8574A_DEV_ADDR_A2T_A1F_A0T  0x3D
#define HD44780_I2C_PCF8574A_DEV_ADDR_A2T_A1T_A0F  0x3E
#define HD44780_I2C_PCF8574A_DEV_ADDR_A2T_A1T_A0T  0x3F

#define HD44780_I2C_SHIFT_TO_RIGHT  true
#define HD44780_I2C_SHIFT_TO_LEFT   false

#define _HD44780_I2C_ENTRY_MODE_DISPLAY_S_DISPLAY_SHIFT_BIT              0
#define _HD44780_I2C_ENTRY_MODE_DISPLAY_ID_INCDEC_CURSOR_POSITION_BIT    1

#define _HD44780_I2C_CONTROL_MODE_DISPLAY_B_CURSOR_BLINK_BIT             0
#define _HD44780_I2C_CONTROL_MODE_DISPLAY_C_CURSOR_ONOFF_BIT             1
#define _HD44780_I2C_CONTROL_MODE_DISPLAY_D_DISPLAY_ONOFF_BIT            2

#define _HD44780_I2C_CURSOR_DISPLAY_SHIFT_MODE_RL_SHIFT_CURSOR_BIT       2
#define _HD44780_I2C_CURSOR_DISPLAY_SHIFT_MODE_SC_SHIFT_DISPLAY_BIT      3

#define _HD44780_I2C_FUNCTION_SET_MODE_DISPLAY_F_FONT_BIT                2
#define _HD44780_I2C_FUNCTION_SET_MODE_DISPLAY_N_NUM_LINES_BIT           3
#define _HD44780_I2C_FUNCTION_SET_MODE_DISPLAY_DL_BITMODE_INTERFACE_BIT  4

#define _HD44780_I2C_DISPLAY_SEND_COMMAND_MODE  0
#define _HD44780_I2C_DISPLAY_SEND_DATA_MODE     1

#define _HD44780_I2C_RS  (1 << 0)
#define _HD44780_I2C_E   (1 << 2)

#define _HD44780_I2C_INITIAL_ENTRY_MODE_DISPLAY         0b00000100
#define _HD44780_I2C_INITIAL_CONTROL_MODE_DISPLAY       0b00001000
#define _HD44780_I2C_INITIAL_CURSOR_DISPLAY_SHIFT_MODE  0b00010000
#define _HD44780_I2C_INITIAL_FUNCTION_SET_MODE_DISPLAY  0b00101000


// ===============================================================================


typedef struct
{
	uint8_t dev_addr;
	uint8_t entry_mode_display;
	uint8_t control_mode_display;
	uint8_t cursor_display_shift_mode;
	uint8_t function_set_mode_display;
	
} HD44780_I2C_t;


HD44780_I2C_t HD44780_I2C_Create_Object(uint8_t dev_addr, bool display_is_enable);

void HD44780_I2C_Set_Target_Object(HD44780_I2C_t *display);

HD44780_I2C_t *HD44780_I2C_Get_Target_Object();


// ===============================================================================


void HD44780_I2C_Set_Display_Enable(bool display_is_enable);

void HD44780_I2C_Set_Cursor_Enable(bool cursor_is_enable);

void HD44780_I2C_Set_Cursor_Blink(bool cursor_is_blink);

void HD44780_I2C_Set_Cursor_Pos(uint8_t string_pos, uint8_t first_char_pos);

void HD44780_I2C_Set_User_Symbol_To_CGRAM(const uint8_t *_8byte_simbol_bitmap_array, uint8_t simbol_number);

void HD44780_I2C_Set_Flash_User_Symbol_To_CGRAM(const uint8_t *_8byte_flash_simbol_bitmap_array, uint8_t flash_simbol_number);


// ===============================================================================

void HD44780_I2C_Set_PCF8574_Alternative_Function_Pin_Enable(uint8_t pin, bool is_enable);

// ===============================================================================


void HD44780_I2C_Print_Char(char c);

void HD44780_I2C_Print_Data(const void *data, uint8_t data_size);

void HD44780_I2C_Print_String(const char *string);

void HD44780_I2C_Safe_Print_String(const char *string, uint16_t max_string_len);

void HD44780_I2C_Print_StringFmt(const char *string_fmt, ...);

void HD44780_I2C_Print_String_To_Char_Terminator(const char* string, const char terminator);

void HD44780_I2C_Fill_Char_Pattern(const char char_pattern, uint8_t num_pattern_chars);


// ===============================================================================


void HD44780_I2C_Print_Flash_Char(const char *flash_c);

void HD44780_I2C_Print_Flash_Data(const void *flash_data, uint8_t flash_data_size);

void HD44780_I2C_Print_Flash_String(const char *flash_string);

void HD44780_I2C_Safe_Print_Flash_String(const char *flash_string, uint16_t max_flash_string_len);

void HD44780_I2C_Print_Flash_StringFmt(const char *flash_string_fmt, ...);

void HD44780_I2C_Print_Flash_String_To_Char_Terminator(const char* flash_string, const char terminator);


// ===============================================================================


void HD44780_I2C_Display_Shift(bool display_shift_is_right);

void HD44780_I2C_Set_Cursor_Home();

void HD44780_I2C_Clear_String_By_Pos(uint8_t string_pos, uint8_t first_char_pos, uint8_t end_char_pos);

void HD44780_I2C_Clear();

#endif


// ======================================================================================================
//  Header              : hd44780.h                                                                     -
//  Created             : 18.03.2022                                                                    -
//  Author              : Denis Chicherov (dippinest)                                                   -
//  Description         : Declarations of functions and macros for working with the LED display         -
//                        on the Hitachi HD44780 controller in 4-bit mode                               -
// ======================================================================================================

#ifndef HD44780_H_
#define HD44780_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifndef HD44780_RS_PORT
#error("hd44780.h error! Please define the macro "HD44780_RS_PORT" in the main project file before including the header file")
#endif

#ifndef HD44780_RS_PIN
#error("hd44780.h error! Please define the macro "HD44780_RS_PIN" in the main project file before including the header file")
#endif

#ifndef HD44780_E_PORT
#error("hd44780.h error! Please define the macro "HD44780_E_PORT" in the main project file before including the header file")
#endif

#ifndef HD44780_E_PIN
#error("hd44780.h error! Please define the macro "HD44780_E_PIN" in the main project file before including the header file")
#endif

#ifndef HD44780_D4_PORT
#error("hd44780.h error! Please define the macro "HD44780_D4_PORT" in the main project file before including the header file")
#endif

#ifndef HD44780_D5_PORT
#error("hd44780.h error! Please define the macro "HD44780_D5_PORT" in the main project file before including the header file")
#endif

#ifndef HD44780_D6_PORT
#error("hd44780.h error! Please define the macro "HD44780_D6_PORT" in the main project file before including the header file")
#endif

#ifndef HD44780_D7_PORT
#error("hd44780.h error! Please define the macro "HD44780_D7_PORT" in the main project file before including the header file")
#endif

#ifndef HD44780_D4_PIN
#error("hd44780.h error! Please define the macro "HD44780_D4_PIN" in the main project file before including the header file")
#endif

#ifndef HD44780_D5_PIN
#error("hd44780.h error! Please define the macro "HD44780_D5_PIN" in the main project file before including the header file")
#endif

#ifndef HD44780_D6_PIN
#error("hd44780.h error! Please define the macro "HD44780_D6_PIN" in the main project file before including the header file")
#endif

#ifndef HD44780_D7_PIN
#error("hd44780.h error! Please define the macro "HD44780_D7_PIN" in the main project file before including the header file")
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

static volatile uint8_t _entry_mode_display        = 0b00000100;
static volatile uint8_t _control_mode_display      = 0b00001000;
static volatile uint8_t _cursor_display_shift_mode = 0b00010000;
static volatile uint8_t _function_set_mode_display = 0b00101000;

static void _HD44780_Send_Half_Byte_4Bit_Mode(uint8_t data)
{
	_HD44780_SET_E_HIGH;
	
	HD44780_D4_PORT &= ~(1 << HD44780_D4_PIN);
	HD44780_D5_PORT &= ~(1 << HD44780_D5_PIN);
	HD44780_D6_PORT &= ~(1 << HD44780_D6_PIN);
	HD44780_D7_PORT &= ~(1 << HD44780_D7_PIN);
	
	_delay_us(40);
	
	HD44780_D4_PORT |= ( (data & 0x01)       << HD44780_D4_PIN);
	HD44780_D5_PORT |= (((data & 0x02) >> 1) << HD44780_D5_PIN);
	HD44780_D6_PORT |= (((data & 0x04) >> 2) << HD44780_D6_PIN);
	HD44780_D7_PORT |= (((data & 0x08) >> 3) << HD44780_D7_PIN);
	
	_HD44780_SET_E_LOW;
}

static void _HD44780_Send_Byte(uint8_t c, uint8_t mode)
{
	if (!mode)
	{
		_HD44780_SET_RS_LOW;
	}
	else
	{
		_HD44780_SET_RS_HIGH;
	}
	
	_HD44780_Send_Half_Byte_4Bit_Mode(c >> 4);
	_HD44780_Send_Half_Byte_4Bit_Mode(c);
}

static int _HD44780_Send_Char(char c, FILE *stream)
{
	_HD44780_Send_Byte(c, _HD44780_DISPLAY_SEND_DATA_MODE);
	return 0;
}

void HD44780_Set_Display_Enable(bool display_is_enable)
{
	
	if (display_is_enable)
	{
		_control_mode_display |=  (1 << _HD44780_CONTROL_MODE_DISPLAY_D_DISPLAY_ONOFF_BIT);
	}
	else
	{
		_control_mode_display &= ~(1 << _HD44780_CONTROL_MODE_DISPLAY_D_DISPLAY_ONOFF_BIT);
	}
	
	_HD44780_Send_Byte(_control_mode_display, _HD44780_DISPLAY_SEND_COMMAND_MODE);
	_delay_us(40);

}

void HD44780_Set_Cursor_Enable(bool cursor_is_enable)
{
	
	if (cursor_is_enable)
	{
		_control_mode_display |=  (1 << _HD44780_CONTROL_MODE_DISPLAY_C_CURSOR_ONOFF_BIT);
	}
	else
	{
		_control_mode_display &= ~(1 << _HD44780_CONTROL_MODE_DISPLAY_C_CURSOR_ONOFF_BIT);
	}
	
	_HD44780_Send_Byte(_control_mode_display, _HD44780_DISPLAY_SEND_COMMAND_MODE);
	
	_delay_us(40);

}

void HD44780_Set_Cursor_Blink(bool cursor_is_blink)
{
	
	if (cursor_is_blink)
	{
		_control_mode_display |=  (1 << _HD44780_CONTROL_MODE_DISPLAY_B_CURSOR_BLINK_BIT);
	}
	else
	{
		_control_mode_display &= ~(1 << _HD44780_CONTROL_MODE_DISPLAY_B_CURSOR_BLINK_BIT);
	}
	
	_HD44780_Send_Byte(_control_mode_display, _HD44780_DISPLAY_SEND_COMMAND_MODE);
	
	_delay_us(40);

}

void HD44780_Set_Cursor_Pos(uint8_t string_pos, uint8_t first_char_pos)
{
	if (string_pos == 2)
	{
		string_pos = 0;
		first_char_pos += 20;
	}
	if (string_pos == 3)
	{
		string_pos = 1;
		first_char_pos += 20;
	}
	
	uint8_t addr = ((0x40 * string_pos) + first_char_pos) | 0b10000000;
	_HD44780_Send_Byte(addr, _HD44780_DISPLAY_SEND_COMMAND_MODE);
}

void HD44780_Set_User_Symbol_To_CGRAM(const uint8_t *_8byte_simbol_bitmap_array, uint8_t simbol_number)
{
	
	_HD44780_Send_Byte((0b01000000 | (simbol_number * 8)), _HD44780_DISPLAY_SEND_COMMAND_MODE);
	_delay_us(40);
	
	for (uint8_t i = 0; i < 8; i++)
	{
		_HD44780_Send_Byte(_8byte_simbol_bitmap_array[i], _HD44780_DISPLAY_SEND_DATA_MODE);
		_delay_us(40);
	}
	
	_HD44780_Send_Byte(0b10000000, _HD44780_DISPLAY_SEND_COMMAND_MODE);
	_delay_us(40);
}

void HD44780_Print_Char(char c)
{
	_HD44780_Send_Byte(c, _HD44780_DISPLAY_SEND_DATA_MODE);
}

void HD44780_Print_Print_Data(const void *data, uint8_t data_size)
{
	for (uint8_t i = 0; i < data_size; i++)
	{
		HD44780_Print_Char(((char*)data)[i]);
	}
}

void HD44780_Print_String(const char *string_array)
{
	for (uint8_t i = 0; string_array[i] != '\0'; i++)
	{
		HD44780_Print_Char(string_array[i]);
	}
}

void HD44780_Safe_Print_String(const char *string_array, uint16_t max_string_len)
{
	for (uint8_t i = 0; string_array[i] != '\0' && i < max_string_len; ++i)
	{
		HD44780_Print_Char(string_array[i]);
	}
}

void HD44780_Print_StringFmt(const char *string_fmt, ...)
{
	va_list argptr;
	va_start(argptr, string_fmt);
	static FILE hd44780_stdout = FDEV_SETUP_STREAM(_HD44780_Send_Char, NULL, _FDEV_SETUP_WRITE);
	stdout = &hd44780_stdout;
	vfprintf(stdout, string_fmt, argptr);
	va_end(argptr);
}

void HD44780_Set_Print_To_Char_Terminator(const char* string_array, const char terminator)
{
	for (uint8_t i = 0; string_array[i] != terminator; i++)
	{
		HD44780_Print_Char(string_array[i]);
	}
}

void HD44780_Fill_Char_Pattern(const char char_pattern, uint8_t num_pattern_chars)
{
	for (uint8_t i = 0; i < num_pattern_chars; i++)
	{
		HD44780_Print_Char(char_pattern);
	}
}

void HD44780_Display_Shift(bool display_shift_is_right)
{
	if (display_shift_is_right)
	{
		_cursor_display_shift_mode |= (1 << _HD44780_CURSOR_DISPLAY_SHIFT_MODE_SC_SHIFT_DISPLAY_BIT);
		_cursor_display_shift_mode &= ~(1 << _HD44780_CURSOR_DISPLAY_SHIFT_MODE_RL_SHIFT_CURSOR_BIT);
	}
	else
	{
		_cursor_display_shift_mode |= (1 << _HD44780_CURSOR_DISPLAY_SHIFT_MODE_SC_SHIFT_DISPLAY_BIT);
		_cursor_display_shift_mode |= (1 << _HD44780_CURSOR_DISPLAY_SHIFT_MODE_RL_SHIFT_CURSOR_BIT);
	}
	_HD44780_Send_Byte(_cursor_display_shift_mode, _HD44780_DISPLAY_SEND_COMMAND_MODE);
	_delay_us(40);
}

void HD44780_Set_Cursor_Home()
{
	_HD44780_Send_Byte(0b00000010, 0);
	_delay_us(1650);
}

void HD44780_Clear_String_By_Pos(uint8_t string_pos, uint8_t first_char_pos, uint8_t end_char_pos)
{
	HD44780_Set_Cursor_Pos(string_pos, first_char_pos);
	HD44780_Fill_Char_Pattern(' ', (end_char_pos - first_char_pos + 1));
}

void HD44780_Clear()
{
	_HD44780_Send_Byte(0b00000001, 0);
	_delay_us(1650);
}

void HD44780_Initialize(bool display_is_enable)
{
	_HD44780_Send_Half_Byte_4Bit_Mode(0b00000011); _delay_ms(5);
	
	_HD44780_Send_Half_Byte_4Bit_Mode(0b00000011); _delay_us(120);
	
	_HD44780_Send_Half_Byte_4Bit_Mode(0b00000011); _delay_us(120);

	_HD44780_Send_Half_Byte_4Bit_Mode(0b00000010); _delay_us(120);
	
	_HD44780_Send_Byte(_control_mode_display, _HD44780_DISPLAY_SEND_COMMAND_MODE); _delay_us(40);
	
	HD44780_Set_Cursor_Home();
	HD44780_Set_Cursor_Enable(false);
	HD44780_Clear();
	HD44780_Set_Display_Enable(display_is_enable);
	
	HD44780_Clear();
}

#endif

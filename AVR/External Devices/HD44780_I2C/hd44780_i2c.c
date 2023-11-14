
#include "hd44780_i2c.h"

static HD44780_I2C_t *target_display = NULL;

#ifdef HD44780_I2C_USE_SOFTI2C

#include "softi2c.h"

static void _HD44780_I2C_Write(uint8_t data)
{
	SOFTI2C_Start();
	SOFTI2C_Send_Byte(target_display->dev_addr << 1);
	SOFTI2C_Send_Byte(data);
	SOFTI2C_Stop();
}

#else

#include "i2c.h"

static void _HD44780_I2C_Write(uint8_t data)
{
	I2C_Start();
	I2C_Send_Byte(target_display->dev_addr << 1);
	I2C_Send_Byte(data);
	I2C_Stop();
}

#endif

static void _HD44780_I2C_Send_Byte(uint8_t b, uint8_t mode)
{
	uint8_t lcd_control_mask = 0x00; // spetial f mask (for display backlighting)
	
	if (target_display->display_backlight_is_enable)
	{
		lcd_control_mask |= _HD44780_I2C_SPECIAL_F_BACKLIGHT;
	}
	
	uint8_t lcd_buffer = b & 0xF0;
	
	if (!mode)
	{
		lcd_buffer &= ~_HD44780_I2C_RS;
	}
	else
	{
		lcd_buffer |= _HD44780_I2C_RS;
	}
	
	if (target_display->display_backlight_is_enable)
	{
		lcd_buffer |= (1 << 3);
	}
	
	lcd_buffer |= _HD44780_I2C_E;  lcd_buffer |= lcd_control_mask; _HD44780_I2C_Write(lcd_buffer); _delay_us(40);
	
	lcd_buffer &= ~_HD44780_I2C_E; lcd_buffer |= lcd_control_mask; _HD44780_I2C_Write(lcd_buffer); _delay_us(100);
	
	lcd_buffer = (b & 0x0F) << 4;
	
	if (!mode)
	{
		lcd_buffer &= ~_HD44780_I2C_RS;
	}
	else
	{
		lcd_buffer |= _HD44780_I2C_RS;
	}
	
	lcd_buffer |= _HD44780_I2C_E;  lcd_buffer |= lcd_control_mask; _HD44780_I2C_Write(lcd_buffer); _delay_us(40);

	lcd_buffer &= ~_HD44780_I2C_E; lcd_buffer |= lcd_control_mask; _HD44780_I2C_Write(lcd_buffer);
}

static int _HD44780_I2C_Send_Char(char c, FILE *stream)
{
	_HD44780_I2C_Send_Byte(c, _HD44780_I2C_DISPLAY_SEND_DATA_MODE);
	return 0;
}

HD44780_I2C_t HD44780_I2C_Get_Display_Object(uint8_t dev_addr, bool display_is_enable)
{
	HD44780_I2C_t display;
	
	display.dev_addr = dev_addr;
	display.entry_mode_display          = _HD44780_I2C_INITIAL_ENTRY_MODE_DISPLAY;
	display.control_mode_display        = _HD44780_I2C_INITIAL_CONTROL_MODE_DISPLAY;
	display.cursor_display_shift_mode   = _HD44780_I2C_INITIAL_CURSOR_DISPLAY_SHIFT_MODE;
	display.function_set_mode_display   = _HD44780_I2C_INITIAL_FUNCTION_SET_MODE_DISPLAY;
	display.display_backlight_is_enable =  true;
	
	target_display = &display;
	
	uint8_t data_buffer = 0b00000011 | _HD44780_I2C_E; _HD44780_I2C_Write(data_buffer); _delay_us(5);
	data_buffer &= ~_HD44780_I2C_E; _HD44780_I2C_Write(data_buffer); _delay_ms(5);
	
	data_buffer = 0b00000011 | _HD44780_I2C_E; _HD44780_I2C_Write(data_buffer); _delay_us(5);
	data_buffer &= ~_HD44780_I2C_E; _HD44780_I2C_Write(data_buffer); _delay_us(120);
	
	data_buffer = 0b00000011 | _HD44780_I2C_E; _HD44780_I2C_Write(data_buffer); _delay_us(5);
	data_buffer &= ~_HD44780_I2C_E; _HD44780_I2C_Write(data_buffer); _delay_us(120);

	data_buffer = 0b00000010 | _HD44780_I2C_E; _HD44780_I2C_Write(data_buffer); _delay_us(5);
	data_buffer &= ~_HD44780_I2C_E; _HD44780_I2C_Write(data_buffer); _delay_us(120);

	HD44780_I2C_Set_Cursor_Home();
	HD44780_I2C_Set_Cursor_Enable(false);
	HD44780_I2C_Clear();
	HD44780_I2C_Set_Display_Enable(display_is_enable);
	
	return display;
}

void HD44780_I2C_Set_Target_Display_Object(HD44780_I2C_t *display)
{
	target_display = display;
}

void HD44780_I2C_Set_Display_Enable(bool display_is_enable)
{
	if (display_is_enable)
	{
		target_display->control_mode_display |=  (1 << _HD44780_I2C_CONTROL_MODE_DISPLAY_D_DISPLAY_ONOFF_BIT);
	}
	else
	{
		target_display->control_mode_display &= ~(1 << _HD44780_I2C_CONTROL_MODE_DISPLAY_D_DISPLAY_ONOFF_BIT);
	}
	
	_HD44780_I2C_Send_Byte(target_display->control_mode_display, _HD44780_I2C_DISPLAY_SEND_COMMAND_MODE); _delay_us(40);
}

void HD44780_I2C_Set_Cursor_Enable(bool cursor_is_enable)
{
	if (cursor_is_enable)
	{
		target_display->control_mode_display |=  (1 << _HD44780_I2C_CONTROL_MODE_DISPLAY_C_CURSOR_ONOFF_BIT);
	}
	else
	{
		target_display->control_mode_display &= ~(1 << _HD44780_I2C_CONTROL_MODE_DISPLAY_C_CURSOR_ONOFF_BIT);
	}
	
	_HD44780_I2C_Send_Byte(target_display->control_mode_display, _HD44780_I2C_DISPLAY_SEND_COMMAND_MODE); _delay_us(40);
}

void HD44780_I2C_Set_Cursor_Blink(bool cursor_is_blink)
{
	if (cursor_is_blink)
	{
		target_display->control_mode_display |=  (1 << _HD44780_I2C_CONTROL_MODE_DISPLAY_B_CURSOR_BLINK_BIT);
	}
	else
	{
		target_display->control_mode_display &= ~(1 << _HD44780_I2C_CONTROL_MODE_DISPLAY_B_CURSOR_BLINK_BIT);
	}
	
	_HD44780_I2C_Send_Byte(target_display->control_mode_display, _HD44780_I2C_DISPLAY_SEND_COMMAND_MODE); _delay_us(40);
}

void HD44780_I2C_Set_Display_Backlight_Enable(bool display_backlight_is_enable)
{
	uint8_t data = 0x00;
	
	target_display->display_backlight_is_enable = display_backlight_is_enable;
	
	if (display_backlight_is_enable)
	{
		data |= _HD44780_I2C_SPECIAL_F_BACKLIGHT;
	}
	
	_HD44780_I2C_Write(data);
}

void HD44780_I2C_Set_Cursor_Pos(uint8_t string_pos, uint8_t first_char_pos)
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
	_HD44780_I2C_Send_Byte(addr, _HD44780_I2C_DISPLAY_SEND_COMMAND_MODE);
}

void HD44780_I2C_Set_User_Symbol_To_CGRAM(const uint8_t *_8byte_simbol_bitmap_array, uint8_t simbol_number)
{
	_HD44780_I2C_Send_Byte((0b01000000 | (simbol_number * 8)), _HD44780_I2C_DISPLAY_SEND_COMMAND_MODE); _delay_us(40);
	
	for (uint8_t i = 0; i < 8; ++i)
	{
		_HD44780_I2C_Send_Byte(_8byte_simbol_bitmap_array[i], _HD44780_I2C_DISPLAY_SEND_DATA_MODE); _delay_us(40);
	}
	
	_HD44780_I2C_Send_Byte(0b10000000, _HD44780_I2C_DISPLAY_SEND_COMMAND_MODE); _delay_us(40);
}

void HD44780_I2C_Set_Flash_User_Symbol_To_CGRAM(const uint8_t *_8byte_flash_simbol_bitmap_array, uint8_t flash_simbol_number)
{
	_HD44780_I2C_Send_Byte((0b01000000 | (flash_simbol_number * 8)), _HD44780_I2C_DISPLAY_SEND_COMMAND_MODE); _delay_us(40);
	
	uint8_t c;
	
	for (uint8_t i = 0; i < 8; ++i)
	{
		c = pgm_read_byte(&_8byte_flash_simbol_bitmap_array[i]);
		_HD44780_I2C_Send_Byte(c, _HD44780_I2C_DISPLAY_SEND_DATA_MODE); _delay_us(40);
	}
	
	_HD44780_I2C_Send_Byte(0b10000000, _HD44780_I2C_DISPLAY_SEND_COMMAND_MODE); _delay_us(40);
}

// ===============================================================================

void HD44780_I2C_Print_Char(char c)
{
	_HD44780_I2C_Send_Byte(c, _HD44780_I2C_DISPLAY_SEND_DATA_MODE);
}

void HD44780_I2C_Print_Data(const void *data, uint8_t data_size)
{
	for (uint8_t i = 0; i < data_size; ++i)
	{
		HD44780_I2C_Print_Char(((char*)data)[i]);
	}
}

void HD44780_I2C_Print_String(const char *string)
{
	for (uint8_t i = 0; string[i] != '\0'; ++i)
	{
		HD44780_I2C_Print_Char(string[i]);
	}
}

void HD44780_I2C_Safe_Print_String(const char *string, uint16_t max_string_len)
{
	for (uint8_t i = 0; string[i] != '\0' && i < max_string_len; ++i)
	{
		HD44780_I2C_Print_Char(string[i]);
	}
}

void HD44780_I2C_Print_StringFmt(const char *string_fmt, ...)
{
	va_list argptr;
	va_start(argptr, string_fmt);
	static FILE hd44780_stdout = FDEV_SETUP_STREAM(_HD44780_I2C_Send_Char, NULL, _FDEV_SETUP_WRITE);
	stdout = &hd44780_stdout;
	vfprintf(stdout, string_fmt, argptr);
	va_end(argptr);
}

void HD44780_I2C_Print_String_To_Char_Terminator(const char* string, const char terminator)
{
	for (uint8_t i = 0; string[i] != terminator; ++i)
	{
		HD44780_I2C_Print_Char(string[i]);
	}
}

void HD44780_I2C_Fill_Char_Pattern(const char char_pattern, uint8_t num_pattern_chars)
{
	for (uint8_t i = 0; i < num_pattern_chars; ++i)
	{
		HD44780_I2C_Print_Char(char_pattern);
	}
}

// ===============================================================================

void HD44780_I2C_Print_Flash_Char(const char *flash_c)
{
	HD44780_I2C_Print_Char(pgm_read_byte(flash_c));
}

void HD44780_I2C_Print_Flash_Data(const void *flash_data, uint8_t flash_data_size)
{
	for (uint16_t i = 0; i < flash_data_size; ++i)
	{
		HD44780_I2C_Print_Char(pgm_read_byte(&((uint8_t*)flash_data)[i]) );
	}
}

void HD44780_I2C_Print_Flash_String(const char *flash_string)
{
	char c = pgm_read_byte(&((uint8_t*)flash_string)[0]);
	uint16_t i = 0;
	
	while (c != '\0')
	{
		++i;
		HD44780_I2C_Print_Char(c);
		c = pgm_read_byte(&((uint8_t*)flash_string)[i]);
	}
}

void HD44780_I2C_Safe_Print_Flash_String(const char *flash_string, uint16_t max_flash_string_len)
{
	char c = pgm_read_byte(&((uint8_t*)flash_string)[0]);
	uint16_t i = 0;
	
	while (c != '\0' && i < max_flash_string_len)
	{
		++i;
		HD44780_I2C_Print_Char(c);
		c = pgm_read_byte(&((uint8_t*)flash_string)[i]);
	}
}

void HD44780_I2C_Print_Flash_StringFmt(const char *flash_string_fmt, ...)
{
	const uint16_t flash_string_size = strlen_P(flash_string_fmt);
	
	char string_buffer[flash_string_size];
	
	strcpy_P(string_buffer, flash_string_fmt);
	
	va_list argptr;
	va_start(argptr, flash_string_fmt);
	static FILE uartstdout = FDEV_SETUP_STREAM(_HD44780_I2C_Send_Char, NULL, _FDEV_SETUP_WRITE);
	stdout = &uartstdout;
	vfprintf(stdout, string_buffer, argptr);
	va_end(argptr);
}

void HD44780_I2C_Print_Flash_String_To_Char_Terminator(const char* flash_string, const char terminator)
{
	char c = pgm_read_byte(&((uint8_t*)flash_string)[0]);
	uint16_t i = 0;
	
	while (c != terminator)
	{
		++i;
		HD44780_I2C_Print_Char(c);
		c = pgm_read_byte(&((uint8_t*)flash_string)[i]);
	}
}

// ===============================================================================

void HD44780_I2C_Display_Shift(bool display_shift_is_right)
{
	target_display->cursor_display_shift_mode |=  (1 << _HD44780_I2C_CURSOR_DISPLAY_SHIFT_MODE_SC_SHIFT_DISPLAY_BIT);
	
	if (display_shift_is_right)
	{
		target_display->cursor_display_shift_mode |= (1 << _HD44780_I2C_CURSOR_DISPLAY_SHIFT_MODE_RL_SHIFT_CURSOR_BIT);
	}
	else
	{
		target_display->cursor_display_shift_mode &= ~(1 << _HD44780_I2C_CURSOR_DISPLAY_SHIFT_MODE_RL_SHIFT_CURSOR_BIT);
	}
	
	_HD44780_I2C_Send_Byte(target_display->cursor_display_shift_mode, _HD44780_I2C_DISPLAY_SEND_COMMAND_MODE); _delay_us(40);
}

void HD44780_I2C_Set_Cursor_Home()
{
	_HD44780_I2C_Send_Byte(0b00000010, _HD44780_I2C_DISPLAY_SEND_COMMAND_MODE); _delay_us(1650);
}

void HD44780_I2C_Clear_String_By_Pos(uint8_t string_pos, uint8_t first_char_pos, uint8_t end_char_pos)
{
	HD44780_I2C_Set_Cursor_Pos(string_pos, first_char_pos);
	HD44780_I2C_Fill_Char_Pattern(' ', (end_char_pos - first_char_pos + 1));
}

void HD44780_I2C_Clear()
{
	_HD44780_I2C_Send_Byte(0b00000001, _HD44780_I2C_DISPLAY_SEND_COMMAND_MODE); _delay_us(1650);
}

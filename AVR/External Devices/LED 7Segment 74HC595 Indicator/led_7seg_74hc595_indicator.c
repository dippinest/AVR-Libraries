
#include "led_7seg_74hc595_indicator.h"

const uint8_t _digits[] =
{
	0b11000000, // 0
	0b11111001, // 1
	0b10100100, // 2
	0b10110000, // 3
	0b10011001, // 4
	0b10010010, // 5
	0b10000010, // 6
	0b11111000, // 7
	0b10000000, // 8
	0b10010000, // 9
};

// ===============================================================================

const uint8_t *LED_7Seg_74HC595_Indicator_Get_Digits_Table()
{
	return _digits;
}

// ===============================================================================

#if defined (LED_7SEG_74HC595_INDICATOR_USE_SOFTSPI) && defined (LED_7SEG_74HC595_INDICATOR_USE_CS_CALLBACKS)

void LED_7Seg_74HC595_Indicator_Put_Symbols(uint8_t *simbols_arr, uint8_t simbols_arr_size, uint8_t *digits_counter)
{
	uint8_t digit = (1 << (simbols_arr_size - 1 - *digits_counter));
	uint8_t _char = simbols_arr[*digits_counter];
	
	SOFTSPI_Send_Byte(_char);
	SOFTSPI_Send_Byte(digit);
	SOFTSPI_Call_CS_OFF();
	SOFTSPI_Call_CS_ON();
	
	++(*digits_counter);
	
	if (*digits_counter == simbols_arr_size)
	{
		*digits_counter = 0;
	}
}

void LED_7Seg_74HC595_Indicator_Put_Symbols_Reverse(uint8_t *simbols_arr, uint8_t simbols_arr_size, uint8_t *digits_counter)
{
	uint8_t digit = (1 << (*digits_counter));
	uint8_t _char = simbols_arr[*digits_counter];
	
	SOFTSPI_Send_Byte(_char);
	SOFTSPI_Send_Byte(digit);
	SOFTSPI_Call_CS_OFF();
	SOFTSPI_Call_CS_ON();
	
	++(*digits_counter);
	
	if (*digits_counter == simbols_arr_size)
	{
		*digits_counter = 0;
	}
}

void LED_7Seg_74HC595_Indicator_Put_Num_String(char *num_string, uint8_t num_string_size, uint8_t *digits_counter)
{
	uint8_t digit = (1 << (num_string_size - 1 - *digits_counter));
	uint8_t _char = (uint8_t)num_string[*digits_counter];
	
	if (_char == ' ')
	{
		_char = LED_7SEG_74HC595_INDICATOR_CHAR_EMPTY;
	}
	else if (_char == '-')
	{
		_char = LED_7SEG_74HC595_INDICATOR_CHAR_MINUS;
	}
	else
	{
		_char = _digits[_char - 48];
	}
	
	SOFTSPI_Send_Byte(_char);
	SOFTSPI_Send_Byte(digit);
	SOFTSPI_Call_CS_OFF();
	SOFTSPI_Call_CS_ON();
	
	++(*digits_counter);
	
	if (*digits_counter == num_string_size)
	{
		*digits_counter = 0;
	}
}

void LED_7Seg_74HC595_Indicator_Put_Num_String_Reverse(char *num_string, uint8_t num_string_size, uint8_t *digits_counter)
{
	uint8_t digit = (1 << (*digits_counter));
	uint8_t _char = (uint8_t)num_string[*digits_counter];
	
	if (_char == ' ')
	{
		_char = LED_7SEG_74HC595_INDICATOR_CHAR_EMPTY;
	}
	else if (_char == '-')
	{
		_char = LED_7SEG_74HC595_INDICATOR_CHAR_MINUS;
	}
	else
	{
		_char = _digits[_char - 48];
	}
	
	SOFTSPI_Send_Byte(_char);
	SOFTSPI_Send_Byte(digit);
	SOFTSPI_Call_CS_OFF();
	SOFTSPI_Call_CS_ON();
	
	++(*digits_counter);
	
	if (*digits_counter == num_string_size)
	{
		*digits_counter = 0;
	}
}

#elif defined (LED_7SEG_74HC595_INDICATOR_USE_SOFTSPI) && !defined (LED_7SEG_74HC595_INDICATOR_USE_CS_CALLBACKS)

void LED_7Seg_74HC595_Indicator_Put_Symbols(uint8_t *simbols_arr, uint8_t simbols_arr_size, uint8_t *digits_counter)
{
	uint8_t digit = (1 << (simbols_arr_size - 1 - *digits_counter));
	uint8_t _char = simbols_arr[*digits_counter];
	
	SOFTSPI_Send_Byte(_char);
	SOFTSPI_Send_Byte(digit);
	
	++(*digits_counter);
	
	if (*digits_counter == simbols_arr_size)
	{
		*digits_counter = 0;
	}
}

void LED_7Seg_74HC595_Indicator_Put_Symbols_Reverse(uint8_t *simbols_arr, uint8_t simbols_arr_size, uint8_t *digits_counter)
{
	uint8_t digit = (1 << (*digits_counter));
	uint8_t _char = simbols_arr[*digits_counter];
	
	SOFTSPI_Send_Byte(_char);
	SOFTSPI_Send_Byte(digit);
	
	++(*digits_counter);
	
	if (*digits_counter == simbols_arr_size)
	{
		*digits_counter = 0;
	}
}

void LED_7Seg_74HC595_Indicator_Put_Num_String(char *num_string, uint8_t num_string_size, uint8_t *digits_counter)
{
	uint8_t digit = (1 << (num_string_size - 1 - *digits_counter));
	uint8_t _char = (uint8_t)num_string[*digits_counter];
	
	if (_char == ' ')
	{
		_char = LED_7SEG_74HC595_INDICATOR_CHAR_EMPTY;
	}
	else if (_char == '-')
	{
		_char = LED_7SEG_74HC595_INDICATOR_CHAR_MINUS;
	}
	else
	{
		_char = _digits[_char - 48];
	}
	
	SOFTSPI_Send_Byte(_char);
	SOFTSPI_Send_Byte(digit);
	
	++(*digits_counter);
	
	if (*digits_counter == num_string_size)
	{
		*digits_counter = 0;
	}
}

void LED_7Seg_74HC595_Indicator_Put_Num_String_Reverse(char *num_string, uint8_t num_string_size, uint8_t *digits_counter)
{
	uint8_t digit = (1 << (*digits_counter));
	uint8_t _char = (uint8_t)num_string[*digits_counter];
	
	if (_char == ' ')
	{
		_char = LED_7SEG_74HC595_INDICATOR_CHAR_EMPTY;
	}
	else if (_char == '-')
	{
		_char = LED_7SEG_74HC595_INDICATOR_CHAR_MINUS;
	}
	else
	{
		_char = _digits[_char - 48];
	}
	
	SOFTSPI_Send_Byte(_char);
	SOFTSPI_Send_Byte(digit);
	
	++(*digits_counter);
	
	if (*digits_counter == num_string_size)
	{
		*digits_counter = 0;
	}
}

#elif !defined (LED_7SEG_74HC595_INDICATOR_USE_SOFTSPI) && defined (LED_7SEG_74HC595_INDICATOR_USE_CS_CALLBACKS)

void LED_7Seg_74HC595_Indicator_Put_Symbols(uint8_t *simbols_arr, uint8_t simbols_arr_size, uint8_t *digits_counter)
{
	uint8_t digit = (1 << (simbols_arr_size - 1 - *digits_counter));
	uint8_t _char = simbols_arr[*digits_counter];
	
	SPI_Send_Byte(_char);
	SPI_Send_Byte(digit);
	SOFTSPI_Call_CS_OFF();
	SOFTSPI_Call_CS_ON();
	
	++(*digits_counter);
	
	if (*digits_counter == simbols_arr_size)
	{
		*digits_counter = 0;
	}
}

void LED_7Seg_74HC595_Indicator_Put_Symbols_Reverse(uint8_t *simbols_arr, uint8_t simbols_arr_size, uint8_t *digits_counter)
{
	uint8_t digit = (1 << (*digits_counter));
	uint8_t _char = simbols_arr[*digits_counter];
	
	SPI_Send_Byte(_char);
	SPI_Send_Byte(digit);
	SOFTSPI_Call_CS_OFF();
	SOFTSPI_Call_CS_ON();
	
	++(*digits_counter);
	
	if (*digits_counter == simbols_arr_size)
	{
		*digits_counter = 0;
	}
}

void LED_7Seg_74HC595_Indicator_Put_Num_String(char *num_string, uint8_t num_string_size, uint8_t *digits_counter)
{
	uint8_t digit = (1 << (num_string_size - 1 - *digits_counter));
	uint8_t _char = (uint8_t)num_string[*digits_counter];
	
	if (_char == ' ')
	{
		_char = LED_7SEG_74HC595_INDICATOR_CHAR_EMPTY;
	}
	else if (_char == '-')
	{
		_char = LED_7SEG_74HC595_INDICATOR_CHAR_MINUS;
	}
	else
	{
		_char = _digits[_char - 48];
	}
	
	SPI_Send_Byte(_char);
	SPI_Send_Byte(digit);
	SOFTSPI_Call_CS_OFF();
	SOFTSPI_Call_CS_ON();
	
	++(*digits_counter);
	
	if (*digits_counter == num_string_size)
	{
		*digits_counter = 0;
	}
}

void LED_7Seg_74HC595_Indicator_Put_Num_String_Reverse(char *num_string, uint8_t num_string_size, uint8_t *digits_counter)
{
	uint8_t digit = (1 << (*digits_counter));
	uint8_t _char = (uint8_t)num_string[*digits_counter];
	
	if (_char == ' ')
	{
		_char = LED_7SEG_74HC595_INDICATOR_CHAR_EMPTY;
	}
	else if (_char == '-')
	{
		_char = LED_7SEG_74HC595_INDICATOR_CHAR_MINUS;
	}
	else
	{
		_char = _digits[_char - 48];
	}
	
	SPI_Send_Byte(_char);
	SPI_Send_Byte(digit);
	SOFTSPI_Call_CS_OFF();
	SOFTSPI_Call_CS_ON();
	
	++(*digits_counter);
	
	if (*digits_counter == num_string_size)
	{
		*digits_counter = 0;
	}
}

#elif !defined (LED_7SEG_74HC595_INDICATOR_USE_SOFTSPI) && !defined (LED_7SEG_74HC595_INDICATOR_USE_CS_CALLBACKS)

void LED_7Seg_74HC595_Indicator_Put_Symbols(uint8_t *simbols_arr, uint8_t simbols_arr_size, uint8_t *digits_counter)
{
	uint8_t digit = (1 << (simbols_arr_size - 1 - *digits_counter));
	uint8_t _char = simbols_arr[*digits_counter];
	
	SPI_Send_Byte(_char);
	SPI_Send_Byte(digit);
	
	++(*digits_counter);
	
	if (*digits_counter == simbols_arr_size)
	{
		*digits_counter = 0;
	}
}

void LED_7Seg_74HC595_Indicator_Put_Symbols_Reverse(uint8_t *simbols_arr, uint8_t simbols_arr_size, uint8_t *digits_counter)
{
	uint8_t digit = (1 << (*digits_counter));
	uint8_t _char = simbols_arr[*digits_counter];
	
	SPI_Send_Byte(_char);
	SPI_Send_Byte(digit);
	
	++(*digits_counter);
	
	if (*digits_counter == simbols_arr_size)
	{
		*digits_counter = 0;
	}
}

void LED_7Seg_74HC595_Indicator_Put_Num_String(char *num_string, uint8_t num_string_size, uint8_t *digits_counter)
{
	uint8_t digit = (1 << (num_string_size - 1 - *digits_counter));
	uint8_t _char = (uint8_t)num_string[*digits_counter];
	
	if (_char == ' ')
	{
		_char = LED_7SEG_74HC595_INDICATOR_CHAR_EMPTY;
	}
	else if (_char == '-')
	{
		_char = LED_7SEG_74HC595_INDICATOR_CHAR_MINUS;
	}
	else
	{
		_char = _digits[_char - 48];
	}
	
	SPI_Send_Byte(_char);
	SPI_Send_Byte(digit);
	
	++(*digits_counter);
	
	if (*digits_counter == num_string_size)
	{
		*digits_counter = 0;
	}
}

void LED_7Seg_74HC595_Indicator_Put_Num_String_Reverse(char *num_string, uint8_t num_string_size, uint8_t *digits_counter)
{
	uint8_t digit = (1 << (*digits_counter));
	uint8_t _char = (uint8_t)num_string[*digits_counter];
	
	if (_char == ' ')
	{
		_char = LED_7SEG_74HC595_INDICATOR_CHAR_EMPTY;
	}
	else if (_char == '-')
	{
		_char = LED_7SEG_74HC595_INDICATOR_CHAR_MINUS;
	}
	else
	{
		_char = _digits[_char - 48];
	}
	
	SPI_Send_Byte(_char);
	SPI_Send_Byte(digit);
	
	++(*digits_counter);
	
	if (*digits_counter == num_string_size)
	{
		*digits_counter = 0;
	}
}

#endif

// ===============================================================================

char *LED_7Seg_74HC595_Indicator_Num_String_To_Symbols_Array(char *num_string, uint8_t num_string_size)
{
	bool decimal_char_separator_flag = false;
	uint8_t i = 0, j = 0, decimal_char_separator_pos = 0;
	
	while(i < num_string_size)
	{
		if (i != 0 && num_string[j] == '.')
		{
			decimal_char_separator_flag = true;
			decimal_char_separator_pos  = i;
			++j;
		}
		
		if (num_string[j] == ' ')
		{
			num_string[i] = LED_7SEG_74HC595_INDICATOR_CHAR_EMPTY;
		}
		else if (num_string[j] == '-')
		{
			num_string[i] = LED_7SEG_74HC595_INDICATOR_CHAR_MINUS;
		}
		else
		{
			num_string[i] = _digits[num_string[j] - 48];
		}
		
		++i;
		++j;
	}
	
	if (decimal_char_separator_flag)
	{
		num_string[decimal_char_separator_pos - 1] &= 0b01111111;
	}
	
	return num_string;
}

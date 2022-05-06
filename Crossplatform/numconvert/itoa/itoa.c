
#include "itoa.h"

static char     *_string_buffer = NULL; // buffer for string

static char    _empty_char              = ' '; // default
static char    _decimal_char_separator  = '.'; // default

static uint8_t _num_of_fract_part_chars = 3;   // default (for float type number)


// ===============================================================================

void ITOA_Set_String_Buffer(char *string_buffer_ptr)
{
	_string_buffer = string_buffer_ptr;
}

int ITOA_Set_String_Buffer_To_Dynamic_Memory(const uint8_t string_buffer_size)
{
	_string_buffer = (char*)calloc(string_buffer_size, sizeof(char));
	
	if (_string_buffer == NULL)
	{
		return 1;
	}
	
	return 0;
}

void ITOA_Delete_String_Buffer_To_Dynamic_Memory()
{
	free(_string_buffer);
}

// ===============================================================================

void ITOA_Set_Empty_Char_Symbol(const char empty_char)
{
	_empty_char = empty_char;
}

void ITOA_Set_Decimal_Char_Separator(const char char_separator)
{
	_decimal_char_separator = char_separator;
}

void ITOA_Set_Num_Of_Fract_Part_Chars(const uint8_t num_of_fract_part_chars)
{
	_num_of_fract_part_chars = num_of_fract_part_chars;
}

char *ITOA_Get_String_Buffer_Ptr()
{
	return _string_buffer;
}

char ITOA_Get_Empty_Char_Symbol()
{
	return _empty_char;
}

char ITOA_Get_Decimal_Char_Separator()
{
	return _decimal_char_separator;
}

uint8_t ITOA_Get_Num_Of_Fract_Part_Chars()
{
	return _num_of_fract_part_chars;
}

// ===============================================================================

char *ITOA_Int8_To_String(int8_t val, int8_t num_of_chars)
{
	_string_buffer[num_of_chars] = '\0';

	if (val == -128)
	{
		_string_buffer[num_of_chars - 1] = '8';
		_string_buffer[num_of_chars - 2] = '2';
		_string_buffer[num_of_chars - 3] = '1';
		_string_buffer[num_of_chars - 4] = '-';

		for (int8_t i = num_of_chars - 5; i >= 0; --i)
		{
			_string_buffer[i] = _empty_char;
		}

		return _string_buffer;
	}

	uint8_t sign = (val < 0) ? 1 : 0;

	if (sign)
	{
		--val;
		val = ~val;
	}

	int8_t i = num_of_chars - 1;

	while(i >= 0)
	{
		_string_buffer[i] = (val % 10) + 48;
		--i;
		val /= 10;

		if (val == 0)
		{
			break;
		}
	}

	if (sign)
	{
		_string_buffer[i] = '-';
		--i;
	}

	while (i >= 0)
	{
		_string_buffer[i] = _empty_char;
		--i;
	}

	return _string_buffer;
}

char *ITOA_UInt8_To_String(uint8_t val, int8_t num_of_chars)
{
	_string_buffer[num_of_chars] = '\0';

	int8_t i = num_of_chars - 1;

	while(i >= 0)
	{
		_string_buffer[i] = (val % 10) + 48;
		--i;
		val /= 10;

		if (val == 0)
		{
			break;
		}
	}

	while (i >= 0)
	{
		_string_buffer[i] = _empty_char;
		--i;
	}

	return _string_buffer;
}

char *ITOA_Int16_To_String(int16_t val, int8_t num_of_chars)
{
	_string_buffer[num_of_chars] = '\0';

	if (val == -32768)
	{
		_string_buffer[num_of_chars - 1] = '8';
		_string_buffer[num_of_chars - 2] = '6';
		_string_buffer[num_of_chars - 3] = '7';
		_string_buffer[num_of_chars - 4] = '2';
		_string_buffer[num_of_chars - 5] = '3';
		_string_buffer[num_of_chars - 6] = '-';

		for (int8_t i = num_of_chars - 7; i >= 0; --i)
		{
			_string_buffer[i] = _empty_char;
		}

		return _string_buffer;
	}

	uint8_t sign = (val < 0) ? 1 : 0;

	if (sign)
	{
		--val;
		val = ~val;
	}

	int8_t i = num_of_chars - 1;

	while(i >= 0)
	{
		_string_buffer[i] = (val % 10) + 48;
		--i;
		val /= 10;

		if (val == 0)
		{
			break;
		}
	}

	if (sign)
	{
		_string_buffer[i] = '-';
		--i;
	}

	while (i >= 0)
	{
		_string_buffer[i] = _empty_char;
		--i;
	}

	return _string_buffer;
}

char *ITOA_UInt16_To_String(uint16_t val, int8_t num_of_chars)
{
	_string_buffer[num_of_chars] = '\0';

	int8_t i = num_of_chars - 1;

	while(i >= 0)
	{
		_string_buffer[i] = (val % 10) + 48;
		--i;
		val /= 10;

		if (val == 0)
		{
			break;
		}
	}

	while (i >= 0)
	{
		_string_buffer[i] = _empty_char;
		--i;
	}

	return _string_buffer;
}

char *ITOA_Int32_To_String(int32_t val, int8_t num_of_chars)
{
	_string_buffer[num_of_chars] = '\0';

	if (val == -2147483648L)
	{
		_string_buffer[num_of_chars - 1]  = '8';
		_string_buffer[num_of_chars - 2]  = '4';
		_string_buffer[num_of_chars - 3]  = '6';
		_string_buffer[num_of_chars - 4]  = '3';
		_string_buffer[num_of_chars - 5]  = '8';
		_string_buffer[num_of_chars - 6]  = '4';
		_string_buffer[num_of_chars - 7]  = '7';
		_string_buffer[num_of_chars - 8]  = '4';
		_string_buffer[num_of_chars - 9]  = '1';
		_string_buffer[num_of_chars - 10] = '2';
		_string_buffer[num_of_chars - 11] = '-';

		for (int8_t i = num_of_chars - 12; i >= 0; --i)
		{
			_string_buffer[i] = _empty_char;
		}

		return _string_buffer;
	}

	uint8_t sign = (val < 0) ? 1 : 0;

	if (sign)
	{
		--val;
		val = ~val;
	}

	int8_t i = num_of_chars - 1;

	while(i >= 0)
	{
		_string_buffer[i] = (val % 10) + 48;
		--i;
		val /= 10;

		if (val == 0)
		{
			break;
		}
	}

	if (sign)
	{
		_string_buffer[i] = '-';
		--i;
	}

	while (i >= 0)
	{
		_string_buffer[i] = _empty_char;
		--i;
	}

	return _string_buffer;
}

char *ITOA_UInt32_To_String(uint32_t val, int8_t num_of_chars)
{
	_string_buffer[num_of_chars] = '\0';

	int8_t i = num_of_chars - 1;

	while(i >= 0)
	{
		_string_buffer[i] = (val % 10) + 48;
		--i;
		val /= 10;

		if (val == 0)
		{
			break;
		}
	}

	while (i >= 0)
	{
		_string_buffer[i] = _empty_char;
		--i;
	}

	return _string_buffer;
}

char *ITOA_Int64_To_String(int64_t val, int8_t num_of_chars)
{
	#include <limits.h>

	_string_buffer[num_of_chars] = '\0';

	if (val == LLONG_MIN)
	{
		_string_buffer[num_of_chars - 1]  = '8';
		_string_buffer[num_of_chars - 2]  = '0';
		_string_buffer[num_of_chars - 3]  = '8';
		_string_buffer[num_of_chars - 4]  = '5';
		_string_buffer[num_of_chars - 5]  = '7';
		_string_buffer[num_of_chars - 6]  = '7';
		_string_buffer[num_of_chars - 7]  = '4';
		_string_buffer[num_of_chars - 8]  = '5';
		_string_buffer[num_of_chars - 9]  = '8';
		_string_buffer[num_of_chars - 10] = '6';
		_string_buffer[num_of_chars - 11] = '3';
		_string_buffer[num_of_chars - 12] = '0';
		_string_buffer[num_of_chars - 13] = '2';
		_string_buffer[num_of_chars - 14] = '7';
		_string_buffer[num_of_chars - 15] = '3';
		_string_buffer[num_of_chars - 16] = '3';
		_string_buffer[num_of_chars - 17] = '2';
		_string_buffer[num_of_chars - 18] = '2';
		_string_buffer[num_of_chars - 19] = '9';
		_string_buffer[num_of_chars - 20] = '-';

		for (int8_t i = num_of_chars - 21; i >= 0; --i)
		{
			_string_buffer[i] = _empty_char;
		}

		return _string_buffer;
	}

	uint8_t sign = (val < 0) ? 1 : 0;

	if (sign)
	{
		--val;
		val = ~val;
	}

	int8_t i = num_of_chars - 1;

	while(i >= 0)
	{
		_string_buffer[i] = (val % 10) + 48;
		--i;
		val /= 10;

		if (val == 0)
		{
			break;
		}
	}

	if (sign)
	{
		_string_buffer[i] = '-';
		--i;
	}

	while (i >= 0)
	{
		_string_buffer[i] = _empty_char;
		--i;
	}

	return _string_buffer;
}

char *ITOA_UInt64_To_String(uint64_t val, int8_t num_of_chars)
{
	_string_buffer[num_of_chars] = '\0';

	int8_t i = num_of_chars - 1;

	while(i >= 0)
	{
		_string_buffer[i] = (val % 10) + 48;
		--i;
		val /= 10;

		if (val == 0)
		{
			break;
		}
	}

	while (i >= 0)
	{
		_string_buffer[i] = _empty_char;
		--i;
	}

	return _string_buffer;
}


#include "itoa.h"

static char     *_string_buffer = NULL; // buffer for string

static char    _empty_char              = ' '; // default
static char    _decimal_char_separator  = '.'; // default


// ===============================================================================

void ITOA_Set_String_Buffer(char *string_buffer_ptr)
{
	_string_buffer = string_buffer_ptr;
}

char *ITOA_Set_String_Buffer_To_Dynamic_Memory(const uint8_t string_buffer_size)
{
	_string_buffer = (char*)calloc(string_buffer_size, sizeof(char));
	
	return _string_buffer;
}

void ITOA_Delete_String_Buffer_To_Dynamic_Memory()
{
	free(_string_buffer);
	_string_buffer = NULL;
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

// ===============================================================================

char *ITOA_UInt8_To_String_Without_Alignment(uint8_t val, int8_t num_of_chars)
{
	_string_buffer[num_of_chars] = '\0';

	while (num_of_chars)
	{
		--num_of_chars;
		_string_buffer[num_of_chars] = (val % 10) + 48;
		val /= 10;
	}

	return _string_buffer;
}

char *ITOA_UInt16_To_String_Without_Alignment(uint16_t val, int8_t num_of_chars)
{
	_string_buffer[num_of_chars] = '\0';

	while (num_of_chars)
	{
		--num_of_chars;
		_string_buffer[num_of_chars] = (val % 10) + 48;
		val /= 10;
	}

	return _string_buffer;
}

char *ITOA_UInt32_To_String_Without_Alignment(uint32_t val, int8_t num_of_chars)
{
	_string_buffer[num_of_chars] = '\0';

	while (num_of_chars)
	{
		--num_of_chars;
		_string_buffer[num_of_chars] = (val % 10) + 48;
		val /= 10;
	}

	return _string_buffer;
}

char *ITOA_UInt64_To_String_Without_Alignment(uint64_t val, int8_t num_of_chars)
{
	_string_buffer[num_of_chars] = '\0';

	while (num_of_chars)
	{
		--num_of_chars;
		_string_buffer[num_of_chars] = (val % 10) + 48;
		val /= 10;
	}

	return _string_buffer;
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

// ===============================================================================

char* ITOA_Float_To_String(float val, int8_t num_int_digits, int8_t num_fract_digits)
{
	--num_fract_digits;
	
	static const uint32_t _pow10_u32_array[] = { 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000 };

	typedef union
	{
		float fv;
		uint32_t dv;

	} _Val;

	_Val _v = { val };

	if (_v.dv == 0x80000000)
	{
		_v.dv = 0x00000000;
	}

	if (_v.dv == 0x7f800000 || _v.dv == 0xff800000)
	{
		if (_v.dv == 0xff800000)
		{
			_string_buffer[0] = '-';
		}
		else
		{
			_string_buffer[0] = '+';
		}

		_string_buffer[1] = 'i';
		_string_buffer[2] = 'n';
		_string_buffer[3] = 'f';
		_string_buffer[4] = '\0';

		return _string_buffer;
	}

	if (isnan(val))
	{
		_string_buffer[0] = 'n';
		_string_buffer[1] = 'a';
		_string_buffer[2] = 'n';
		_string_buffer[3] = '\0';

		return _string_buffer;
	}

	_string_buffer[num_int_digits + num_fract_digits + 1] = '\0';
	
	bool fv_is_negative = false;

	if (_v.dv & 0x80000000)
	{
		_v.dv &= ~(1UL << 31);
		fv_is_negative = true;
	}

	int32_t int_part   = (int32_t)_v.fv;
	int32_t fract_part =
	(_v.fv - int_part) *
	_pow10_u32_array[num_fract_digits % (sizeof(_pow10_u32_array) / sizeof(int32_t))];
	
	
	int8_t i = (num_int_digits + num_fract_digits + 1);
	
	uint8_t rem;

	for (; i >= (num_int_digits + 1); --i)
	{
		rem = fract_part % 10;
		fract_part /= 10;
		_string_buffer[i] = rem + 48;
	}
	
	_string_buffer[i] = _decimal_char_separator;
	--i;
	
	for (uint8_t j = 0; j < num_int_digits; ++j)
	{
		if (int_part != 0)
		{
			rem = int_part % 10;
			int_part /= 10;
			_string_buffer[i] = rem + 48;
		}
		else
		{
			if (fv_is_negative)
			{
				if (j == 0)
				{
					_string_buffer[i] = '0';
				}
				else
				{
					_string_buffer[i] = '-';
					fv_is_negative = false;
				}
			}
			else
			{
				if (j == 0)
				{
					_string_buffer[i] = '0';
				}
				else
				{
					_string_buffer[i] = ' ';
				}
			}
		}

		--i;
	}

	return _string_buffer;
}


#include "itohexa.h"

static char *_string_buffer = NULL; // buffer for string

static const char _HEX_DIGIT_CHARS[] =
	{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

// ===============================================================================

void ITOHEXA_Set_String_Buffer(char *string_buffer_ptr)
{
	_string_buffer = string_buffer_ptr;
}

char *ITOHEXA_Set_String_Buffer_To_Dynamic_Memory(const uint8_t string_buffer_size)
{
	_string_buffer = (char*)calloc(string_buffer_size, sizeof(char));
	
	return _string_buffer;
}

void ITOHEXA_Delete_String_Buffer_To_Dynamic_Memory()
{
	free(_string_buffer);
	_string_buffer = NULL;
}

// ===============================================================================

char *ITOHEXA_8bitNum_To_HexString(uint8_t val, bool is_lower_case)
{
	for (int8_t i = 1; i >= 0; --i)
	{
		if (is_lower_case)
		{
			_string_buffer[i] = (char)tolower(_HEX_DIGIT_CHARS[val & 0x0F]);
		}
		else
		{
			_string_buffer[i] = _HEX_DIGIT_CHARS[val & 0x0F];
		}

		val >>= 4;
	}

	_string_buffer[2] = '\0';
	
	return _string_buffer;
}

char *ITOHEXA_16bitNum_To_HexString(uint16_t val, bool is_lower_case)
{
	for (int8_t i = 3; i >= 0; --i)
	{
		if (is_lower_case)
		{
			_string_buffer[i] = (char)tolower(_HEX_DIGIT_CHARS[val & 0x0F]);
		}
		else
		{
			_string_buffer[i] = _HEX_DIGIT_CHARS[val & 0x0F];
		}

		val >>= 4;
	}

	_string_buffer[4] = '\0';
	
	return _string_buffer;
}

char *ITOHEXA_32bitNum_To_HexString(uint32_t val, bool is_lower_case)
{
	for (int8_t i = 7; i >= 0; --i)
	{
		if (is_lower_case)
		{
			_string_buffer[i] = (char)tolower(_HEX_DIGIT_CHARS[val & 0x0F]);
		}
		else
		{
			_string_buffer[i] = _HEX_DIGIT_CHARS[val & 0x0F];
		}

		val >>= 4;
	}

	_string_buffer[8] = '\0';
	
	return _string_buffer;
}

char *ITOHEXA_64bitNum_To_HexString(uint64_t val, bool is_lower_case)
{
	for (int8_t i = 15; i >= 0; --i)
	{
		if (is_lower_case)
		{
			_string_buffer[i] = (char)tolower(_HEX_DIGIT_CHARS[val & 0x0F]);
		}
		else
		{
			_string_buffer[i] = _HEX_DIGIT_CHARS[val & 0x0F];
		}

		val >>= 4;
	}

	_string_buffer[16] = '\0';
	
	return _string_buffer;
}

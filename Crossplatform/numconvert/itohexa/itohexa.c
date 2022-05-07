
#include "itohexa.h"

static char *_string_buffer = NULL; // buffer for string

// ===============================================================================

void ITOHEXA_Set_String_Buffer(char *string_buffer_ptr)
{
	_string_buffer = string_buffer_ptr;
}

int  ITOHEXA_Set_String_Buffer_To_Dynamic_Memory(const uint8_t string_buffer_size)
{
	_string_buffer = (char*)calloc(string_buffer_size, sizeof(char));
	
	if (_string_buffer == NULL)
	{
		return 1;
	}
	
	return 0;
}

void ITOHEXA_Delete_String_Buffer_To_Dynamic_Memory()
{
	free(_string_buffer);
	_string_buffer = NULL;
}

// ===============================================================================

static char *_nbyte_num_to_hex_string(uint64_t val, bool is_lower_case, const uint8_t val_nbytes)
{
	static const char _HEX_DIGIT_CHARS[] =
        { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

	for (int8_t i = (val_nbytes * 2 - 1); i >= 0; --i)
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

	_string_buffer[val_nbytes * 2] = '\0';

	return _string_buffer;
}

char *ITOHEXA_8bitNum_To_HexString(uint8_t val, bool is_lower_case)
{
	return _nbyte_num_to_hex_string(val, is_lower_case, 1);
}

char *ITOHEXA_16bitNum_To_HexString(uint16_t val, bool is_lower_case)
{
	return _nbyte_num_to_hex_string(val, is_lower_case, 2);
}

char *ITOHEXA_32bitNum_To_HexString(uint32_t val, bool is_lower_case)
{
	return _nbyte_num_to_hex_string(val, is_lower_case, 4);
}

char *ITOHEXA_64bitNum_To_HexString(uint64_t val, bool is_lower_case)
{
	return _nbyte_num_to_hex_string(val, is_lower_case, 8);
}
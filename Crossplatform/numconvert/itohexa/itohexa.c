// =============================================================================================================
//  Source              : itohexa.c                                                                            -
//  Created             : 20.02.2022                                                                           -
//  Author              : Denis Chicherov (dippinest)                                                          -
//  Description         : Defining of functions for converting integer types to a HEX format C-type string     -
// =============================================================================================================

#include "itohexa.h"

static char *_nbyte_num_to_hex_string(uint64_t val, char *string_buf, bool is_lower_case, const uint8_t val_nbytes)
{
	static const char _HEX_DIGIT_CHARS[] =
        { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

	for (int8_t i = (val_nbytes * 2 - 1); i >= 0; --i)
	{
		if (is_lower_case)
		{
			string_buf[i] = (char)tolower(_HEX_DIGIT_CHARS[val & 0x0F]);
		}
		else
		{
			string_buf[i] = _HEX_DIGIT_CHARS[val & 0x0F];
		}

		val >>= 4;
	}

	string_buf[val_nbytes * 2] = '\0';

	return string_buf;
}

char *ITOHEXA_8bitNum_To_Hex_String(uint8_t val, bool is_lower_case, char *string_buf)
{
	return _nbyte_num_to_hex_string(val, string_buf, is_lower_case, 1);
}

char *ITOHEXA_16bitNum_To_Hex_String(uint16_t val, bool is_lower_case, char *string_buf)
{
	return _nbyte_num_to_hex_string(val, string_buf, is_lower_case, 2);
}

char *ITOHEXA_32bitNum_To_Hex_String(uint32_t val, bool is_lower_case, char *string_buf)
{
	return _nbyte_num_to_hex_string(val, string_buf, is_lower_case, 4);
}

char *ITOHEXA_64bitNum_To_Hex_String(uint64_t val, bool is_lower_case, char *string_buf)
{
	return _nbyte_num_to_hex_string(val, string_buf, is_lower_case, 8);
}
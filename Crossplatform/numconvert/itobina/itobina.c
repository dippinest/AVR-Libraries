
#include "itobina.h"

static char *_string_buffer = NULL; // buffer for string

// ===============================================================================

void ITOBINA_Set_String_Buffer(char *string_buffer_ptr)
{
	_string_buffer = string_buffer_ptr;
}

char *ITOBINA_Set_String_Buffer_To_Dynamic_Memory(const uint8_t string_buffer_size)
{
	_string_buffer = (char*)calloc(string_buffer_size, sizeof(char));
	
	return _string_buffer;
}

void ITOBINA_Delete_String_Buffer_To_Dynamic_Memory()
{
	free(_string_buffer);
	_string_buffer = NULL;
}

// ===============================================================================

char *ITOBINA_8bitNum_To_BinString(uint8_t val)
{
	uint8_t i = 0;
	
	for (; i < sizeof(uint8_t) * 8; ++i)
	{
		if ((val << i) & 0x80)
		{
			_string_buffer[i] = '1';
		}
		else
		{
			_string_buffer[i] = '0';
		}
	}
	
	_string_buffer[i] = '\0';
	
	return _string_buffer;
}

char *ITOBINA_16bitNum_To_BinString(uint16_t val)
{
	uint8_t i = 0;
	
	for (; i < sizeof(uint16_t) * 8; ++i)
	{
		if ((val << i) & 0x8000)
		{
			_string_buffer[i] = '1';
		}
		else
		{
			_string_buffer[i] = '0';
		}
	}
	
	_string_buffer[i] = '\0';
	
	return _string_buffer;
}

char *ITOBINA_32bitNum_To_BinString(uint32_t val)
{
	uint8_t i = 0;
	
	for (; i < sizeof(uint32_t) * 8; ++i)
	{
		if ((val << i) & 0x80000000)
		{
			_string_buffer[i] = '1';
		}
		else
		{
			_string_buffer[i] = '0';
		}
	}
	
	_string_buffer[i] = '\0';
	
	return _string_buffer;
}

char *ITOBINA_64bitNum_To_BinString(uint64_t val)
{
	uint8_t i = 0;
	
	for (; i < sizeof(uint64_t) * 8; ++i)
	{
		if ((val << i) & 0x8000000000000000)
		{
			_string_buffer[i] = '1';
		}
		else
		{
			_string_buffer[i] = '0';
		}
	}
	
	_string_buffer[i] = '\0';
	
	return _string_buffer;
}

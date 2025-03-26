
#include "tm74hc595.h"


static const uint8_t _digits[] =
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


static TM74HC595_t *target_object = NULL;


TM74HC595_t TM74HC595_Create_Object()
{
	TM74HC595_t tm74hc595;
	
	tm74hc595.digits_counter = 0;
	
	return tm74hc595;
}

void TM74HC595_Set_Target_Object(TM74HC595_t *tm74hc595)
{
	target_object = tm74hc595;
}

TM74HC595_t *TM74HC595_Get_Target_Object()
{
	return target_object;
}

const uint8_t *TM74HC595_Get_Digits_Table()
{
	return _digits;
}


// ===============================================================================


#if defined (TM74HC595_USE_SOFTSPI) && defined (TM74HC595_USE_CS_CALLBACKS)

#include "softspi.h"

void TM74HC595_Clear()
{
	SOFTSPI_Send_Byte(TM74HC595_EMPTY);
	SOFTSPI_Send_Byte(TM74HC595_EMPTY);
	SOFTSPI_Call_CS_OFF();
	SOFTSPI_Call_CS_ON();
}

void TM74HC595_Put_Symbols(uint8_t *simbols_arr, uint8_t simbols_arr_size)
{
	uint8_t digit = (1 << (simbols_arr_size - 1 - target_object->digits_counter));
	uint8_t _char = simbols_arr[target_object->digits_counter];
	
	SOFTSPI_Send_Byte(_char);
	SOFTSPI_Send_Byte(digit);
	SOFTSPI_Call_CS_OFF();
	SOFTSPI_Call_CS_ON();
	
	++(target_object->digits_counter);
	
	if (target_object->digits_counter >= simbols_arr_size)
	{
		target_object->digits_counter = 0;
	}
}

void TM74HC595_Put_Symbols_Reverse(uint8_t *simbols_arr, uint8_t simbols_arr_size)
{
	uint8_t digit = (1 << (target_object->digits_counter));
	uint8_t _char = simbols_arr[target_object->digits_counter];
	
	SOFTSPI_Send_Byte(_char);
	SOFTSPI_Send_Byte(digit);
	SOFTSPI_Call_CS_OFF();
	SOFTSPI_Call_CS_ON();
	
	++(target_object->digits_counter);
	
	if (target_object->digits_counter >= simbols_arr_size)
	{
		target_object->digits_counter = 0;
	}
}

void TM74HC595_Put_Num_String(char *num_string, uint8_t num_string_size)
{
	uint8_t digit = (1 << (num_string_size - 1 - target_object->digits_counter));
	uint8_t _char = (uint8_t)num_string[target_object->digits_counter];
	
	if (_char == ' ')
	{
		_char = TM74HC595_EMPTY;
	}
	else if (_char == '-')
	{
		_char = TM74HC595_MINUS;
	}
	else
	{
		_char = _digits[_char - 48];
	}
	
	SOFTSPI_Send_Byte(_char);
	SOFTSPI_Send_Byte(digit);
	SOFTSPI_Call_CS_OFF();
	SOFTSPI_Call_CS_ON();
	
	++(target_object->digits_counter);
	
	if (target_object->digits_counter >= num_string_size)
	{
		target_object->digits_counter = 0;
	}
}

void TM74HC595_Put_Num_String_Reverse(char *num_string, uint8_t num_string_size)
{
	uint8_t digit = (1 << (target_object->digits_counter));
	uint8_t _char = (uint8_t)num_string[target_object->digits_counter];
	
	if (_char == ' ')
	{
		_char = TM74HC595_EMPTY;
	}
	else if (_char == '-')
	{
		_char = TM74HC595_MINUS;
	}
	else
	{
		_char = _digits[_char - 48];
	}
	
	SOFTSPI_Send_Byte(_char);
	SOFTSPI_Send_Byte(digit);
	SOFTSPI_Call_CS_OFF();
	SOFTSPI_Call_CS_ON();
	
	++(target_object->digits_counter);
	
	if (target_object->digits_counter >= num_string_size)
	{
		target_object->digits_counter = 0;
	}
}

#elif defined (TM74HC595_USE_SOFTSPI) && !defined (TM74HC595_USE_CS_CALLBACKS)

#include "softspi.h"

void TM74HC595_Clear()
{
	SOFTSPI_Send_Byte(TM74HC595_EMPTY);
	SOFTSPI_Send_Byte(TM74HC595_EMPTY);
}

void TM74HC595_Put_Symbols(uint8_t *simbols_arr, uint8_t simbols_arr_size)
{
	uint8_t digit = (1 << (simbols_arr_size - 1 - target_object->digits_counter));
	uint8_t _char = simbols_arr[target_object->digits_counter];
	
	SOFTSPI_Send_Byte(_char);
	SOFTSPI_Send_Byte(digit);
	
	++(target_object->digits_counter);
	
	if (target_object->digits_counter >= simbols_arr_size)
	{
		target_object->digits_counter = 0;
	}
}

void TM74HC595_Put_Symbols_Reverse(uint8_t *simbols_arr, uint8_t simbols_arr_size)
{
	uint8_t digit = (1 << (target_object->digits_counter));
	uint8_t _char = simbols_arr[target_object->digits_counter];
	
	SOFTSPI_Send_Byte(_char);
	SOFTSPI_Send_Byte(digit);
	
	++(target_object->digits_counter);
	
	if (target_object->digits_counter >= simbols_arr_size)
	{
		target_object->digits_counter = 0;
	}
}

void TM74HC595_Put_Num_String(char *num_string, uint8_t num_string_size)
{
	uint8_t digit = (1 << (num_string_size - 1 - target_object->digits_counter));
	uint8_t _char = (uint8_t)num_string[target_object->digits_counter];
	
	if (_char == ' ')
	{
		_char = TM74HC595_EMPTY;
	}
	else if (_char == '-')
	{
		_char = TM74HC595_MINUS;
	}
	else
	{
		_char = _digits[_char - 48];
	}
	
	SOFTSPI_Send_Byte(_char);
	SOFTSPI_Send_Byte(digit);
	
	++(target_object->digits_counter);
	
	if (target_object->digits_counter >= num_string_size)
	{
		target_object->digits_counter = 0;
	}
}

void TM74HC595_Put_Num_String_Reverse(char *num_string, uint8_t num_string_size)
{
	uint8_t digit = (1 << (target_object->digits_counter));
	uint8_t _char = (uint8_t)num_string[target_object->digits_counter];
	
	if (_char == ' ')
	{
		_char = TM74HC595_EMPTY;
	}
	else if (_char == '-')
	{
		_char = TM74HC595_MINUS;
	}
	else
	{
		_char = _digits[_char - 48];
	}
	
	SOFTSPI_Send_Byte(_char);
	SOFTSPI_Send_Byte(digit);
	
	++(target_object->digits_counter);
	
	if (target_object->digits_counter >= num_string_size)
	{
		target_object->digits_counter = 0;
	}
}

#elif !defined (TM74HC595_USE_SOFTSPI) && defined (TM74HC595_USE_CS_CALLBACKS)

#include "spi.h"

void TM74HC595_Clear()
{
	SPI_Send_Byte(TM74HC595_EMPTY);
	SPI_Send_Byte(TM74HC595_EMPTY);
	SPI_Call_CS_OFF();
	SPI_Call_CS_ON();
}

void TM74HC595_Put_Symbols(uint8_t *simbols_arr, uint8_t simbols_arr_size)
{
	uint8_t digit = (1 << (simbols_arr_size - 1 - target_object->digits_counter));
	uint8_t _char = simbols_arr[target_object->digits_counter];
	
	SPI_Send_Byte(_char);
	SPI_Send_Byte(digit);
	SPI_Call_CS_OFF();
	SPI_Call_CS_ON();
	
	++(target_object->digits_counter);
	
	if (target_object->digits_counter >= simbols_arr_size)
	{
		target_object->digits_counter = 0;
	}
}

void TM74HC595_Put_Symbols_Reverse(uint8_t *simbols_arr, uint8_t simbols_arr_size)
{
	uint8_t digit = (1 << (target_object->digits_counter));
	uint8_t _char = simbols_arr[target_object->digits_counter];
	
	SPI_Send_Byte(_char);
	SPI_Send_Byte(digit);
	SPI_Call_CS_OFF();
	SPI_Call_CS_ON();
	
	++(target_object->digits_counter);
	
	if (target_object->digits_counter >= simbols_arr_size)
	{
		target_object->digits_counter = 0;
	}
}

void TM74HC595_Put_Num_String(char *num_string, uint8_t num_string_size)
{
	uint8_t digit = (1 << (num_string_size - 1 - target_object->digits_counter));
	uint8_t _char = (uint8_t)num_string[target_object->digits_counter];
	
	if (_char == ' ')
	{
		_char = TM74HC595_EMPTY;
	}
	else if (_char == '-')
	{
		_char = TM74HC595_MINUS;
	}
	else
	{
		_char = _digits[_char - 48];
	}
	
	SPI_Send_Byte(_char);
	SPI_Send_Byte(digit);
	SPI_Call_CS_OFF();
	SPI_Call_CS_ON();
	
	++(target_object->digits_counter);
	
	if (target_object->digits_counter >= num_string_size)
	{
		target_object->digits_counter = 0;
	}
}

void TM74HC595_Put_Num_String_Reverse(char *num_string, uint8_t num_string_size)
{
	uint8_t digit = (1 << (target_object->digits_counter));
	uint8_t _char = (uint8_t)num_string[target_object->digits_counter];
	
	if (_char == ' ')
	{
		_char = TM74HC595_EMPTY;
	}
	else if (_char == '-')
	{
		_char = TM74HC595_MINUS;
	}
	else
	{
		_char = _digits[_char - 48];
	}
	
	SPI_Send_Byte(_char);
	SPI_Send_Byte(digit);
	SPI_Call_CS_OFF();
	SPI_Call_CS_ON();
	
	++(target_object->digits_counter);
	
	if (target_object->digits_counter >= num_string_size)
	{
		target_object->digits_counter = 0;
	}
}

#elif !defined (TM74HC595_USE_SOFTSPI) && !defined (TM74HC595_USE_CS_CALLBACKS)

#include "spi.h"

void TM74HC595_Clear()
{
	SPI_Send_Byte(TM74HC595_EMPTY);
	SPI_Send_Byte(TM74HC595_EMPTY);
}

void TM74HC595_Put_Symbols(uint8_t *simbols_arr, uint8_t simbols_arr_size)
{
	uint8_t digit = (1 << (simbols_arr_size - 1 - target_object->digits_counter));
	uint8_t _char = simbols_arr[target_object->digits_counter];
	
	SPI_Send_Byte(_char);
	SPI_Send_Byte(digit);
	
	++(target_object->digits_counter);
	
	if (target_object->digits_counter >= simbols_arr_size)
	{
		target_object->digits_counter = 0;
	}
}

void TM74HC595_Put_Symbols_Reverse(uint8_t *simbols_arr, uint8_t simbols_arr_size)
{
	uint8_t digit = (1 << (target_object->digits_counter));
	uint8_t _char = simbols_arr[target_object->digits_counter];
	
	SPI_Send_Byte(_char);
	SPI_Send_Byte(digit);
	
	++(target_object->digits_counter);
	
	if (target_object->digits_counter >= simbols_arr_size)
	{
		target_object->digits_counter = 0;
	}
}

void TM74HC595_Put_Num_String(char *num_string, uint8_t num_string_size)
{
	uint8_t digit = (1 << (num_string_size - 1 - target_object->digits_counter));
	uint8_t _char = (uint8_t)num_string[target_object->digits_counter];
	
	if (_char == ' ')
	{
		_char = TM74HC595_EMPTY;
	}
	else if (_char == '-')
	{
		_char = TM74HC595_MINUS;
	}
	else
	{
		_char = _digits[_char - 48];
	}
	
	SPI_Send_Byte(_char);
	SPI_Send_Byte(digit);
	
	++(target_object->digits_counter);
	
	if (target_object->digits_counter >= num_string_size)
	{
		target_object->digits_counter = 0;
	}
}

void TM74HC595_Put_Num_String_Reverse(char *num_string, uint8_t num_string_size)
{
	uint8_t digit = (1 << (target_object->digits_counter));
	uint8_t _char = (uint8_t)num_string[target_object->digits_counter];
	
	if (_char == ' ')
	{
		_char = TM74HC595_EMPTY;
	}
	else if (_char == '-')
	{
		_char = TM74HC595_MINUS;
	}
	else
	{
		_char = _digits[_char - 48];
	}
	
	SPI_Send_Byte(_char);
	SPI_Send_Byte(digit);
	
	++(target_object->digits_counter);
	
	if (target_object->digits_counter >= num_string_size)
	{
		target_object->digits_counter = 0;
	}
}


#endif // ===============================================================================


char *TM74HC595_Convert_Num_String_To_Symbols_Array(char *num_string, uint8_t num_string_size)
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
			num_string[i] = TM74HC595_EMPTY;
		}
		else if (num_string[j] == '-')
		{
			num_string[i] = TM74HC595_MINUS;
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





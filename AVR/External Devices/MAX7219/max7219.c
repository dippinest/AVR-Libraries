

#include "max7219.h"



// таблица символов (цифры от 0 до 9 и буквы A, B, C, D, E и F)
//
// -------------------------------------------------------------------------------
// symbol table (numbers from 0 to 9 and letters A, B, C, D, E and F)
//
const uint8_t _max7219_digits_symbols_table[] PROGMEM =
{
	MAX7219_0, // 0
	MAX7219_1, // 1
	MAX7219_2, // 2
	MAX7219_3, // 3
	MAX7219_4, // 4
	MAX7219_5, // 5
	MAX7219_6, // 6
	MAX7219_7, // 7
	MAX7219_8, // 8
	MAX7219_9  // 9
};



// ===============================================================================



#if defined (MAX7219_USE_SOFTSPI) && defined (MAX7219_USE_CS_CALLBACKS)


#include "softspi.h"



static void _MAX7219_Send_Command(uint8_t reg, uint8_t data)
{
	SOFTSPI_CS_Set_Active();
	
	SOFTSPI_Send_Byte(reg);
	SOFTSPI_Send_Byte(data);
	
	SOFTSPI_CS_Set_Inactive();
}

#elif defined (MAX7219_USE_SOFTSPI) && !defined (MAX7219_USE_CS_CALLBACKS)


#include "softspi.h"



static void _MAX7219_Send_Command(uint8_t reg, uint8_t data)
{
	SOFTSPI_Send_Byte(reg);
	SOFTSPI_Send_Byte(data);
}

#elif !defined (MAX7219_USE_SOFTSPI) && defined (MAX7219_USE_CS_CALLBACKS)


#include "spi.h"



static void _MAX7219_Send_Command(uint8_t reg, uint8_t data)
{
	SPI_CS_Set_Active();
	
	SPI_Send_Byte(reg);
	SPI_Send_Byte(data);
	
	SPI_CS_Set_Inactive();
}

#elif !defined (MAX7219_USE_SOFTSPI) && !defined (MAX7219_USE_CS_CALLBACKS)


#include "spi.h"



static void _MAX7219_Send_Command(uint8_t reg, uint8_t data)
{
	SPI_Send_Byte(reg);
	SPI_Send_Byte(data);
}

#endif




void MAX7219_Set_Enable(bool is_enable)
{
	if (is_enable)
	{
		_MAX7219_Send_Command(0x0C, 0x01);
	}
	else
	{
		_MAX7219_Send_Command(0x0C, 0x00);
	}
}

void MAX7219_Set_Decode_Mode(uint8_t decode_mode)
{
	_MAX7219_Send_Command(0x09, decode_mode);
}

void MAX7219_Set_Num_Of_Involved_Digits(uint8_t num_of_involved_digits)
{
	_MAX7219_Send_Command(0x0B, num_of_involved_digits);
}

void MAX7219_Set_Brightness(uint8_t brightness_coef)
{
	_MAX7219_Send_Command(0x0A, brightness_coef);
}



// ===============================================================================



void MAX7219_Set_Digit(uint8_t single_digit_pos, uint8_t digit_value)
{
	_MAX7219_Send_Command((single_digit_pos + 1), digit_value);
}

void MAX7219_Clear_Single_Digit(uint8_t single_digit_pos)
{
	_MAX7219_Send_Command((single_digit_pos + 1), 0x00);
}

void MAX7219_Clear_All(uint8_t num_of_involved_digits)
{
	++num_of_involved_digits;
	
	while (num_of_involved_digits--)
	{
		_MAX7219_Send_Command(num_of_involved_digits, 0x00);
	}
}

void MAX7219_Decode_Mode_Clear_Single_Digit(uint8_t single_digit_pos)
{
	_MAX7219_Send_Command((single_digit_pos + 1), 0x0F);
}

void MAX7219_Decode_Mode_Clear_All(uint8_t num_of_involved_digits)
{
	while (num_of_involved_digits--)
	{
		_MAX7219_Send_Command(num_of_involved_digits, 0x0F);
	}
}

void MAX7219_Display_Test()
{
	_MAX7219_Send_Command(0x0F, 0x0F);
}



// ===============================================================================



#ifdef MAX7219_USE_CS_CALLBACKS


void MAX7219_Initialize(bool is_enable, uint8_t decode_mode, uint8_t num_of_involved_digits, uint8_t brightness_coef)
{
	MAX7219_Set_Enable(is_enable);
	MAX7219_Set_Decode_Mode(decode_mode);
	MAX7219_Set_Num_Of_Involved_Digits(num_of_involved_digits);
	MAX7219_Set_Brightness(brightness_coef);
	
	MAX7219_Decode_Mode_Clear_All(num_of_involved_digits);
}



// ===============================================================================



void MAX7219_Put_Symbols(const uint8_t *symbols_arr, uint8_t symbols_arr_size, bool output_direction)
{
	if (output_direction == MAX7219_DATA_DIRECTION_NORMAL)
	{
		for (uint8_t i = 0; i < symbols_arr_size; ++i)
		{
			MAX7219_Set_Digit(i, ((uint8_t*)symbols_arr)[symbols_arr_size - 1 - i]);
		}
	}
	else
	{
		for (uint8_t i = 0; i < symbols_arr_size; ++i)
		{
			MAX7219_Set_Digit(i, ((uint8_t*)symbols_arr)[i]);
		}
	}
}

void MAX7219_Put_Num_String_With_Using_Decode_Mode(const char *num_string, uint8_t num_string_size, const uint8_t max_num_digits)
{
	for (uint8_t i = 0; i < num_string_size; ++i)
	{
		if (num_string[i] == ' ')
		{
			MAX7219_Set_Digit(max_num_digits - i - 1, 15);
		}
		else
		{
			MAX7219_Set_Digit(max_num_digits - i - 1, num_string[i] - 48);
		}
	}
}



void MAX7219_Put_Num_String_With_Using_Program_Decoder(const char *num_string, uint8_t num_string_size)
{
	bool point_char_separator_flag = false;
	
	uint8_t j = 0;
	
	
	for (uint8_t i = 0; i < num_string_size; ++i)
	{
		uint8_t symbol_pointer = (num_string_size - i - 1);
		
		uint8_t symbol = num_string[symbol_pointer] - 48;
		
		
		if ((symbol >= 0) && (symbol < 10))
		{
			symbol = pgm_read_byte(&_max7219_digits_symbols_table[symbol]);
		}
		else
		{
			switch (num_string[symbol_pointer])
			{
				case 'a':
				case 'A':
				
				symbol = MAX7219_A;
				
				break;
				
				
				case 'b':
				case 'B':
				
				symbol = MAX7219_B;
				
				break;
				
				
				case 'c':
				case 'C':
				
				symbol = MAX7219_C;
				
				break;
				
				
				case 'd':
				case 'D':
				
				symbol = MAX7219_D;
				
				break;
				
				
				case 'e':
				case 'E':
				
				symbol = MAX7219_E;
				
				break;
				
				
				case 'f':
				case 'F':
				
				symbol = MAX7219_F;
				
				break;
				
				
				case '-':
				
				symbol = MAX7219_MINUS;
				
				break;
				
				
				case '.':
				
				point_char_separator_flag = true; continue;
				
				break;
				
				
				default:
				
				symbol = MAX7219_EMPTY;
				
				break;
			}
		}
		
		
		if (point_char_separator_flag)
		{
			point_char_separator_flag = false;
			
			symbol = MAX7219_SET_POINT(symbol);
		}
		
		MAX7219_Set_Digit(j, symbol);
		
		++j;
	}
}

void MAX7219_Put_Num_String_Reverse_With_Using_Program_Decoder(const char *num_string, uint8_t num_string_size)
{
	bool point_char_separator_flag = false;
	
	uint8_t j = 0;
	
	
	for (uint8_t i = 0; i < num_string_size; ++i)
	{
		uint8_t symbol_pointer = i;
		
		uint8_t symbol = num_string[symbol_pointer] - 48;
		
		
		if ((symbol >= 0) && (symbol < 10))
		{
			symbol = pgm_read_byte(&_max7219_digits_symbols_table[symbol]);
		}
		else
		{
			switch (num_string[symbol_pointer])
			{
				case 'a':
				case 'A':
				
				symbol = MAX7219_A;
				
				break;
				
				
				case 'b':
				case 'B':
				
				symbol = MAX7219_B;
				
				break;
				
				
				case 'c':
				case 'C':
				
				symbol = MAX7219_C;
				
				break;
				
				
				case 'd':
				case 'D':
				
				symbol = MAX7219_D;
				
				break;
				
				
				case 'e':
				case 'E':
				
				symbol = MAX7219_E;
				
				break;
				
				
				case 'f':
				case 'F':
				
				symbol = MAX7219_F;
				
				break;
				
				
				case '-':
				
				symbol = MAX7219_MINUS;
				
				break;
				
				
				case '.':
				
				point_char_separator_flag = true; continue;
				
				break;
				
				
				default:
				
				symbol = MAX7219_EMPTY;
				
				break;
			}
		}
		
		
		if (point_char_separator_flag)
		{
			point_char_separator_flag = false;
			
			symbol = MAX7219_SET_POINT(symbol);
		}
		
		MAX7219_Set_Digit(j, symbol);
		
		++j;
	}
}



#endif



// ===============================================================================



char *MAX7219_Convert_Num_String_To_Symbols_Array(char *num_string, uint8_t num_string_size)
{
	uint8_t j = 0;
	
	
	for (uint8_t i = 0; i < num_string_size; ++i)
	{
		uint8_t symbol_pointer = i;
		
		uint8_t symbol = num_string[symbol_pointer] - 48;
		
		
		if ((symbol >= 0) && (symbol < 10))
		{
			symbol = pgm_read_byte(&_max7219_digits_symbols_table[symbol]);
		}
		else
		{
			switch (num_string[symbol_pointer])
			{
				case 'a':
				case 'A':
				
				symbol = MAX7219_A;
				
				break;
				
				
				case 'b':
				case 'B':
				
				symbol = MAX7219_B;
				
				break;
				
				
				case 'c':
				case 'C':
				
				symbol = MAX7219_C;
				
				break;
				
				
				case 'd':
				case 'D':
				
				symbol = MAX7219_D;
				
				break;
				
				
				case 'e':
				case 'E':
				
				symbol = MAX7219_E;
				
				break;
				
				
				case 'f':
				case 'F':
				
				symbol = MAX7219_F;
				
				break;
				
				
				case '-':
				
				symbol = MAX7219_MINUS;
				
				break;
				
				
				case '.':
				
				continue;
				
				break;
				
				
				default:
				
				symbol = MAX7219_EMPTY;
				
				break;
			}
		}
		
		
		if (num_string[i + 1] == '.')
		{
			symbol = MAX7219_SET_POINT(symbol);
		}
		
		num_string[j] = symbol;
		
		++j;
	}
	
	return num_string;
}









#include "hc595sevsegind.h"


// таблица символов (цифры от 0 до 9 и буквы A, B, C, D, E и F)
//
// -------------------------------------------------------------------------------
// symbol table (numbers from 0 to 9 and letters A, B, C, D, E and F)
//
const uint8_t _hc595sevsegind_digits_symbols_table[] PROGMEM =
{
	HC595SEVSEGIND_0, // 0
	HC595SEVSEGIND_1, // 1
	HC595SEVSEGIND_2, // 2
	HC595SEVSEGIND_3, // 3
	HC595SEVSEGIND_4, // 4
	HC595SEVSEGIND_5, // 5
	HC595SEVSEGIND_6, // 6
	HC595SEVSEGIND_7, // 7
	HC595SEVSEGIND_8, // 8
	HC595SEVSEGIND_9  // 9
};



// ===============================================================================

#ifdef HC595SEVSEGIND_USE_SOFTSPI


#include "softspi.h"

#define _SPI_Send_Byte  SOFTSPI_Send_Byte


#else


#include "spi.h"

#define _SPI_Send_Byte  SPI_Send_Byte

#endif

// ===============================================================================




void HC595SevSegInd_Clear_Display(const int8_t num_of_segments, void (*latch_callback)())
{
	for (uint8_t i = 0; i < num_of_segments; ++i)
	{
		_SPI_Send_Byte(HC595SEVSEGIND_EMPTY);
	}
	
	if ((latch_callback) != NULL)
	{
		latch_callback();
	}
}


void HC595SevSegInd_Put_Symbols(const uint8_t *symbols_arr, int8_t symbols_arr_size, void (*latch_callback)())
{
	for (uint8_t i = 0; i < symbols_arr_size; ++i)
	{
		uint8_t symbol_pointer = (symbols_arr_size - 1 - i);

		_SPI_Send_Byte(symbols_arr[symbol_pointer]);
	}
	
	if ((latch_callback) != NULL)
	{
		latch_callback();
	}
}


void HC595SevSegInd_Put_Symbols_Reverse(const uint8_t *symbols_arr, int8_t symbols_arr_size, void (*latch_callback)())
{
	for (int8_t i = 0; i < symbols_arr_size; ++i)
	{
		_SPI_Send_Byte(symbols_arr[i]);
	}
	
	if ((latch_callback) != NULL)
	{
		latch_callback();
	}
}


void HC595SevSegInd_Put_Num_String(const char *num_string, uint8_t num_string_size, void (*latch_callback)())
{
	bool point_char_separator_flag = false;
	
	
	for (uint8_t i = 0; i < num_string_size; ++i)
	{
		uint8_t symbol_pointer = (num_string_size - 1 - i);
		
		uint8_t symbol = num_string[symbol_pointer] - 48;
		
		
		if ((symbol >= 0) && (symbol < 10))
		{
			symbol = pgm_read_byte(&_hc595sevsegind_digits_symbols_table[symbol]);
		}
		else
		{
			switch (num_string[symbol_pointer])
			{
				case 'a':
				case 'A':
				
				symbol = HC595SEVSEGIND_A;
				
				break;
				
				
				case 'b':
				case 'B':
				
				symbol = HC595SEVSEGIND_B;
				
				break;
				
				
				case 'c':
				case 'C':
				
				symbol = HC595SEVSEGIND_C;
				
				break;
				
				
				case 'd':
				case 'D':
				
				symbol = HC595SEVSEGIND_D;
				
				break;
				
				
				case 'e':
				case 'E':
				
				symbol = HC595SEVSEGIND_E;
				
				break;
				
				
				case 'f':
				case 'F':
				
				symbol = HC595SEVSEGIND_F;
				
				break;
				
				
				case '-':
				
				symbol = HC595SEVSEGIND_MINUS;
				
				break;
				
				
				case '.':
				
				point_char_separator_flag = true; continue;
				
				break;
				
				
				default:
				
				symbol = HC595SEVSEGIND_EMPTY;
				
				break;
			}
		}
		
		
		if (point_char_separator_flag)
		{
			point_char_separator_flag = false;
			
			symbol = HC595SEVSEGIND_SET_POINT(symbol);
		}
		
		_SPI_Send_Byte(symbol);
	}
	
	
	if ((latch_callback) != NULL)
	{
		latch_callback();
	}
}


void HC595SevSegInd_Put_Num_String_Reverse(const char *num_string, uint8_t num_string_size, void (*latch_callback)())
{
	bool point_char_separator_flag = false;
	
	
	for (uint8_t i = 0; i < num_string_size; ++i)
	{
		uint8_t symbol = num_string[i] - 48;
		
		
		if ((symbol >= 0) && (symbol < 10))
		{
			symbol = pgm_read_byte(&_hc595sevsegind_digits_symbols_table[symbol]);
		}
		else
		{
			switch (num_string[i])
			{
				case 'a':
				case 'A':
				
				symbol = HC595SEVSEGIND_A;
				
				break;
				
				
				case 'b':
				case 'B':
				
				symbol = HC595SEVSEGIND_B;
				
				break;
				
				
				case 'c':
				case 'C':
				
				symbol = HC595SEVSEGIND_C;
				
				break;
				
				
				case 'd':
				case 'D':
				
				symbol = HC595SEVSEGIND_D;
				
				break;
				
				
				case 'e':
				case 'E':
				
				symbol = HC595SEVSEGIND_E;
				
				break;
				
				
				case 'f':
				case 'F':
				
				symbol = HC595SEVSEGIND_F;
				
				break;
				
				
				case '-':
				
				symbol = HC595SEVSEGIND_MINUS;
				
				break;
				
				
				case '.':
				
				point_char_separator_flag = true; continue;
				
				break;
				
				
				default:
				
				symbol = HC595SEVSEGIND_EMPTY;
				
				break;
			}
		}
		
		
		if (point_char_separator_flag)
		{
			point_char_separator_flag = false;
			
			symbol = HC595SEVSEGIND_SET_POINT(symbol);
		}
		
		_SPI_Send_Byte(symbol);
	}
	
	
	if ((latch_callback) != NULL)
	{
		latch_callback();
	}
}



// ===============================================================================



char *HC595SevSegInd_Convert_Num_String_To_Symbols_Array(char *num_string, uint8_t num_string_size)
{
	bool point_char_separator_flag = false;
	
	
	for (uint8_t i = 0; i < num_string_size; ++i)
	{
		uint8_t symbol = num_string[i] - 48;
		
		
		if ((symbol >= 0) && (symbol < 10))
		{
			symbol = pgm_read_byte(&_hc595sevsegind_digits_symbols_table[symbol]);
		}
		else
		{
			switch (num_string[i])
			{
				case 'a':
				case 'A':
				
				symbol = HC595SEVSEGIND_A;
				
				break;
				
				
				case 'b':
				case 'B':
				
				symbol = HC595SEVSEGIND_B;
				
				break;
				
				
				case 'c':
				case 'C':
				
				symbol = HC595SEVSEGIND_C;
				
				break;
				
				
				case 'd':
				case 'D':
				
				symbol = HC595SEVSEGIND_D;
				
				break;
				
				
				case 'e':
				case 'E':
				
				symbol = HC595SEVSEGIND_E;
				
				break;
				
				
				case 'f':
				case 'F':
				
				symbol = HC595SEVSEGIND_F;
				
				break;
				
				
				case '-':
				
				symbol = HC595SEVSEGIND_MINUS;
				
				break;
				
				
				case '.':
				
				point_char_separator_flag = true; continue;
				
				break;
				
				
				default:
				
				symbol = HC595SEVSEGIND_EMPTY;
				
				break;
			}
		}
		
		
		if (point_char_separator_flag)
		{
			point_char_separator_flag = false;
			
			symbol = HC595SEVSEGIND_SET_POINT(symbol);
		}
		
		num_string[i] = symbol;
	}
	
	
	return num_string;
}






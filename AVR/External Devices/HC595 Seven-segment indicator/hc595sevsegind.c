
#include "hc595sevsegind.h"


// таблица значений степенной аппроксимации
//
// -------------------------------------------------------------------------------
// table of power approximation values
//
const uint8_t _hc595sevsegind_symbols_table[] PROGMEM =
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
	HC595SEVSEGIND_9, // 9
	HC595SEVSEGIND_A, // A
	HC595SEVSEGIND_B, // B
	HC595SEVSEGIND_C, // C
	HC595SEVSEGIND_D, // D
	HC595SEVSEGIND_E, // E
	HC595SEVSEGIND_F  // F
};



// ===============================================================================



static HC595SevSegInd_t *target_object = NULL;


HC595SevSegInd_t HC595SevSegInd_Create_Object(const int8_t num_of_segments, void (*latch_callback)())
{
	HC595SevSegInd_t indicator;
	
	indicator.num_of_segments = num_of_segments;
	indicator.latch_callback  = latch_callback;
	
	return indicator;
}


void HC595SevSegInd_Set_Target_Object(HC595SevSegInd_t *indicator)
{
	target_object = indicator;
}


HC595SevSegInd_t *HC595SevSegInd_Get_Target_Object()
{
	return target_object;
}


void _HC595SevSegInd_Latching_Data()
{
	if ((target_object->latch_callback) != NULL)
	{
		target_object->latch_callback();
	}
}



// ===============================================================================



#if defined (HC595SEVSEGIND_USE_SOFTSPI)


#include "softspi.h"



void HC595SevSegInd_Clear_Display()
{
	for (uint8_t i = 0; i < target_object->num_of_segments; ++i)
	{
		SOFTSPI_Send_Byte(HC595SEVSEGIND_EMPTY);
	}
	
	_HC595SevSegInd_Latching_Data();
}


void HC595SevSegInd_Put_Symbols(uint8_t *symbols_arr, int8_t symbols_arr_size)
{
	for (uint8_t i = 0; i < symbols_arr_size; ++i)
	{
		uint8_t symbol_pointer = (symbols_arr_size - 1 - i);

		SOFTSPI_Send_Byte(symbols_arr[symbol_pointer]);
	}
	
	_HC595SevSegInd_Latching_Data();
}


void HC595SevSegInd_Put_Symbols_Reverse(uint8_t *symbols_arr, int8_t symbols_arr_size)
{
	for (int8_t i = 0; i < symbols_arr_size; ++i)
	{
		SOFTSPI_Send_Byte(symbols_arr[i]);
	}
	
	_HC595SevSegInd_Latching_Data();
}


void HC595SevSegInd_Put_Num_String(char *num_string, uint8_t num_string_size)
{
	bool point_char_separator_flag = false;
	
	
	for (uint8_t i = 0; i < num_string_size; ++i)
	{
		uint8_t symbol_pointer = (num_string_size - 1 - i);
		
		uint8_t symbol = num_string[symbol_pointer] - 48;
		
		
		if ((symbol >= 0) && (symbol < 10))
		{
			symbol = pgm_read_byte(&_hc595sevsegind_symbols_table[symbol]);
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
		
		SOFTSPI_Send_Byte(symbol);
	}
	
	
	_HC595SevSegInd_Latching_Data();
}


void HC595SevSegInd_Put_Num_String_Reverse(char *num_string, uint8_t num_string_size)
{
	bool point_char_separator_flag = false;
	
	
	for (uint8_t i = 0; i < num_string_size; ++i)
	{
		uint8_t symbol = num_string[i] - 48;
		
		
		if ((symbol >= 0) && (symbol < 10))
		{
			symbol = pgm_read_byte(&_hc595sevsegind_symbols_table[symbol]);
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
		
		SOFTSPI_Send_Byte(symbol);
	}
	
	
	_HC595SevSegInd_Latching_Data();
}



#else


#include "spi.h"



void HC595SevSegInd_Clear_Display()
{
	for (uint8_t i = 0; i < target_object->num_of_segments; ++i)
	{
		SPI_Send_Byte(HC595SEVSEGIND_EMPTY);
	}
	
	_HC595SevSegInd_Latching_Data();
}


void HC595SevSegInd_Put_Symbols(uint8_t *symbols_arr, int8_t symbols_arr_size)
{
	for (uint8_t i = 0; i < symbols_arr_size; ++i)
	{
		uint8_t symbol_pointer = (symbols_arr_size - 1 - i);

		SPI_Send_Byte(symbols_arr[symbol_pointer]);
	}
	
	_HC595SevSegInd_Latching_Data();
}


void HC595SevSegInd_Put_Symbols_Reverse(uint8_t *symbols_arr, int8_t symbols_arr_size)
{
	for (int8_t i = 0; i < symbols_arr_size; ++i)
	{
		SPI_Send_Byte(symbols_arr[i]);
	}
	
	_HC595SevSegInd_Latching_Data();
}


void HC595SevSegInd_Put_Num_String(char *num_string, uint8_t num_string_size)
{
	bool point_char_separator_flag = false;
	
	
	for (uint8_t i = 0; i < num_string_size; ++i)
	{
		uint8_t symbol_pointer = (num_string_size - 1 - i);
		
		uint8_t symbol = num_string[symbol_pointer] - 48;
		
		
		if ((symbol >= 0) && (symbol < 10))
		{
			symbol = pgm_read_byte(&_hc595sevsegind_symbols_table[symbol]);
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
		
		SPI_Send_Byte(symbol);
	}
	
	
	_HC595SevSegInd_Latching_Data();
}


void HC595SevSegInd_Put_Num_String_Reverse(char *num_string, uint8_t num_string_size)
{
	bool point_char_separator_flag = false;
	
	
	for (uint8_t i = 0; i < num_string_size; ++i)
	{
		uint8_t symbol = num_string[i] - 48;
		
		
		if ((symbol >= 0) && (symbol < 10))
		{
			symbol = pgm_read_byte(&_hc595sevsegind_symbols_table[symbol]);
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
		
		SPI_Send_Byte(symbol);
	}
	
	
	_HC595SevSegInd_Latching_Data();
}


#endif


char *HC595SevSegInd_Convert_Num_String_To_Symbols_Array(char *num_string, uint8_t num_string_size)
{
	bool point_char_separator_flag = false;
	
	
	for (uint8_t i = 0; i < num_string_size; ++i)
	{
		uint8_t symbol = num_string[i] - 48;
		
		
		if ((symbol >= 0) && (symbol < 10))
		{
			symbol = pgm_read_byte(&_hc595sevsegind_symbols_table[symbol]);
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





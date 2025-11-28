

#include "tm74hc595.h"



// таблица символов (цифры от 0 до 9)
//
// -------------------------------------------------------------------------------
// symbol table (numbers from 0 to 9)
//
const uint8_t _tm74hc595_symbol_pointers_symbols_table[] PROGMEM =
{
	TM74HC595_0, // 0
	TM74HC595_1, // 1
	TM74HC595_2, // 2
	TM74HC595_3, // 3
	TM74HC595_4, // 4
	TM74HC595_5, // 5
	TM74HC595_6, // 6
	TM74HC595_7, // 7
	TM74HC595_8, // 8
	TM74HC595_9  // 9
};



// ===============================================================================



static TM74HC595_t *target_object = NULL;


TM74HC595_t TM74HC595_Create_Object()
{
	TM74HC595_t tm74hc595;
	
	tm74hc595.symbols_counter = 0;
	
	tm74hc595.point_char_separator_counter = 0;
	
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



// ===============================================================================



#if defined (TM74HC595_USE_SOFTSPI) && defined (TM74HC595_USE_CS_CALLBACKS)


#include "softspi.h"



void TM74HC595_Clear()
{
	SOFTSPI_Send_Byte(TM74HC595_EMPTY);
	SOFTSPI_Send_Byte(TM74HC595_EMPTY);
	
	SOFTSPI_CS_Low();
	SOFTSPI_CS_High();
}

void TM74HC595_Put_Symbols(uint8_t *symbols_arr, uint8_t symbols_arr_size)
{
	uint8_t symbol_pointer = (1 << (symbols_arr_size - 1 - target_object->symbols_counter));
	
	uint8_t symbol = symbols_arr[target_object->symbols_counter];
	
	
	
	SOFTSPI_Send_Byte(symbol);
	SOFTSPI_Send_Byte(symbol_pointer);
	
	SOFTSPI_CS_Low();
	SOFTSPI_CS_High();
	
	
	target_object->symbols_counter = (target_object->symbols_counter + 1) % symbols_arr_size;
}

void TM74HC595_Put_Symbols_Reverse(uint8_t *symbols_arr, uint8_t symbols_arr_size)
{
	uint8_t symbol_pointer = (1 << (target_object->symbols_counter));
	
	uint8_t symbol = symbols_arr[target_object->symbols_counter];
	
	
	
	SOFTSPI_Send_Byte(symbol);
	SOFTSPI_Send_Byte(symbol_pointer);
	
	SOFTSPI_CS_Low();
	SOFTSPI_CS_High();
	
	
	target_object->symbols_counter = (target_object->symbols_counter + 1) % symbols_arr_size;
}

void TM74HC595_Put_Num_String(char *num_string, uint8_t num_string_size)
{
	if (target_object->symbols_counter == 0)
	{
		target_object->point_char_separator_counter = 0;
	}
	
	uint8_t symbol_pointer, symbol;
	
	
	LABEL:
	
	symbol_pointer = (1 << (num_string_size - 1 - target_object->symbols_counter));
	
	symbol = num_string[target_object->symbols_counter + target_object->point_char_separator_counter] - 48;
	
	
	if ((symbol >= 0) && (symbol < 10))
	{
		symbol = pgm_read_byte(&_tm74hc595_symbol_pointers_symbols_table[symbol]);
	}
	else
	{
		switch (num_string[target_object->symbols_counter + target_object->point_char_separator_counter])
		{
			case 'a':
			case 'A':
			
			symbol = TM74HC595_A;
			
			break;
			
			
			case 'b':
			case 'B':
			
			symbol = TM74HC595_B;
			
			break;
			
			
			case 'c':
			case 'C':
			
			symbol = TM74HC595_C;
			
			break;
			
			
			case 'd':
			case 'D':
			
			symbol = TM74HC595_D;
			
			break;
			
			
			case 'e':
			case 'E':
			
			symbol = TM74HC595_E;
			
			break;
			
			
			case 'f':
			case 'F':
			
			symbol = TM74HC595_F;
			
			break;
			
			
			case '-':
			
			symbol = TM74HC595_MINUS;
			
			break;
			
			
			case '.':
			
			++(target_object->point_char_separator_counter);
			
			goto LABEL;
			
			
			break;
			
			
			default:
			
			symbol = TM74HC595_EMPTY;
			
			break;
		}
	}
	
	
	if (num_string[(target_object->symbols_counter + 1) % num_string_size] == '.')
	{
		symbol = TM74HC595_SET_POINT(symbol);
	}
	
	
	SOFTSPI_Send_Byte(symbol);
	SOFTSPI_Send_Byte(symbol_pointer);
	
	SOFTSPI_CS_Low();
	SOFTSPI_CS_High();
	
	
	target_object->symbols_counter = (target_object->symbols_counter + 1) % num_string_size;
}

void TM74HC595_Put_Num_String_Reverse(char *num_string, uint8_t num_string_size)
{
	if (target_object->symbols_counter == 0)
	{
		target_object->point_char_separator_counter = 0;
	}
	
	uint8_t symbol_pointer, symbol;
	
	
	LABEL:
	
	symbol_pointer = (1 << target_object->symbols_counter);
	
	symbol = num_string[target_object->symbols_counter + target_object->point_char_separator_counter] - 48;
	
	
	if ((symbol >= 0) && (symbol < 10))
	{
		symbol = pgm_read_byte(&_tm74hc595_symbol_pointers_symbols_table[symbol]);
	}
	else
	{
		switch (num_string[target_object->symbols_counter + target_object->point_char_separator_counter])
		{
			case 'a':
			case 'A':
			
			symbol = TM74HC595_A;
			
			break;
			
			
			case 'b':
			case 'B':
			
			symbol = TM74HC595_B;
			
			break;
			
			
			case 'c':
			case 'C':
			
			symbol = TM74HC595_C;
			
			break;
			
			
			case 'd':
			case 'D':
			
			symbol = TM74HC595_D;
			
			break;
			
			
			case 'e':
			case 'E':
			
			symbol = TM74HC595_E;
			
			break;
			
			
			case 'f':
			case 'F':
			
			symbol = TM74HC595_F;
			
			break;
			
			
			case '-':
			
			symbol = TM74HC595_MINUS;
			
			break;
			
			
			case '.':
			
			++(target_object->point_char_separator_counter);
			
			goto LABEL;
			
			
			break;
			
			
			default:
			
			symbol = TM74HC595_EMPTY;
			
			break;
		}
	}
	
	
	if (num_string[(target_object->symbols_counter) % num_string_size] == '.')
	{
		symbol = TM74HC595_SET_POINT(symbol);
	}
	
	
	SOFTSPI_Send_Byte(symbol);
	SOFTSPI_Send_Byte(symbol_pointer);
	
	SOFTSPI_CS_Low();
	SOFTSPI_CS_High();
	
	
	target_object->symbols_counter = (target_object->symbols_counter + 1) % num_string_size;
}


#elif defined (TM74HC595_USE_SOFTSPI) && !defined (TM74HC595_USE_CS_CALLBACKS)


#include "softspi.h"



void TM74HC595_Clear()
{
	SOFTSPI_Send_Byte(TM74HC595_EMPTY);
	SOFTSPI_Send_Byte(TM74HC595_EMPTY);
}

void TM74HC595_Put_Symbols(uint8_t *symbols_arr, uint8_t symbols_arr_size)
{
	uint8_t symbol_pointer = (1 << (symbols_arr_size - 1 - target_object->symbols_counter));
	
	uint8_t symbol = symbols_arr[target_object->symbols_counter];
	
	
	
	SOFTSPI_Send_Byte(symbol);
	SOFTSPI_Send_Byte(symbol_pointer);
	
	
	target_object->symbols_counter = (target_object->symbols_counter + 1) % symbols_arr_size;
}

void TM74HC595_Put_Symbols_Reverse(uint8_t *symbols_arr, uint8_t symbols_arr_size)
{
	uint8_t symbol_pointer = (1 << (target_object->symbols_counter));
	
	uint8_t symbol = symbols_arr[target_object->symbols_counter];
	
	
	
	SOFTSPI_Send_Byte(symbol);
	SOFTSPI_Send_Byte(symbol_pointer);
	
	
	target_object->symbols_counter = (target_object->symbols_counter + 1) % symbols_arr_size;
}

void TM74HC595_Put_Num_String(char *num_string, uint8_t num_string_size)
{
	if (target_object->symbols_counter == 0)
	{
		target_object->point_char_separator_counter = 0;
	}
	
	uint8_t symbol_pointer, symbol;
	
	
	LABEL:
	
	symbol_pointer = (1 << (num_string_size - 1 - target_object->symbols_counter));
	
	symbol = num_string[target_object->symbols_counter + target_object->point_char_separator_counter] - 48;
	
	
	if ((symbol >= 0) && (symbol < 10))
	{
		symbol = pgm_read_byte(&_tm74hc595_symbol_pointers_symbols_table[symbol]);
	}
	else
	{
		switch (num_string[target_object->symbols_counter + target_object->point_char_separator_counter])
		{
			case 'a':
			case 'A':
			
			symbol = TM74HC595_A;
			
			break;
			
			
			case 'b':
			case 'B':
			
			symbol = TM74HC595_B;
			
			break;
			
			
			case 'c':
			case 'C':
			
			symbol = TM74HC595_C;
			
			break;
			
			
			case 'd':
			case 'D':
			
			symbol = TM74HC595_D;
			
			break;
			
			
			case 'e':
			case 'E':
			
			symbol = TM74HC595_E;
			
			break;
			
			
			case 'f':
			case 'F':
			
			symbol = TM74HC595_F;
			
			break;
			
			
			case '-':
			
			symbol = TM74HC595_MINUS;
			
			break;
			
			
			case '.':
			
			++(target_object->point_char_separator_counter);
			
			goto LABEL;
			
			
			break;
			
			
			default:
			
			symbol = TM74HC595_EMPTY;
			
			break;
		}
	}
	
	
	if (num_string[(target_object->symbols_counter + 1) % num_string_size] == '.')
	{
		symbol = TM74HC595_SET_POINT(symbol);
	}
	
	
	SOFTSPI_Send_Byte(symbol);
	SOFTSPI_Send_Byte(symbol_pointer);
	
	
	target_object->symbols_counter = (target_object->symbols_counter + 1) % num_string_size;
}

void TM74HC595_Put_Num_String_Reverse(char *num_string, uint8_t num_string_size)
{
	if (target_object->symbols_counter == 0)
	{
		target_object->point_char_separator_counter = 0;
	}
	
	uint8_t symbol_pointer, symbol;
	
	
	LABEL:
	
	symbol_pointer = (1 << target_object->symbols_counter);
	
	symbol = num_string[target_object->symbols_counter + target_object->point_char_separator_counter] - 48;
	
	
	if ((symbol >= 0) && (symbol < 10))
	{
		symbol = pgm_read_byte(&_tm74hc595_symbol_pointers_symbols_table[symbol]);
	}
	else
	{
		switch (num_string[target_object->symbols_counter + target_object->point_char_separator_counter])
		{
			case 'a':
			case 'A':
			
			symbol = TM74HC595_A;
			
			break;
			
			
			case 'b':
			case 'B':
			
			symbol = TM74HC595_B;
			
			break;
			
			
			case 'c':
			case 'C':
			
			symbol = TM74HC595_C;
			
			break;
			
			
			case 'd':
			case 'D':
			
			symbol = TM74HC595_D;
			
			break;
			
			
			case 'e':
			case 'E':
			
			symbol = TM74HC595_E;
			
			break;
			
			
			case 'f':
			case 'F':
			
			symbol = TM74HC595_F;
			
			break;
			
			
			case '-':
			
			symbol = TM74HC595_MINUS;
			
			break;
			
			
			case '.':
			
			++(target_object->point_char_separator_counter);
			
			goto LABEL;
			
			
			break;
			
			
			default:
			
			symbol = TM74HC595_EMPTY;
			
			break;
		}
	}
	
	
	if (num_string[(target_object->symbols_counter) % num_string_size] == '.')
	{
		symbol = TM74HC595_SET_POINT(symbol);
	}
	
	
	SOFTSPI_Send_Byte(symbol);
	SOFTSPI_Send_Byte(symbol_pointer);
	
	
	target_object->symbols_counter = (target_object->symbols_counter + 1) % num_string_size;
}


#elif !defined (TM74HC595_USE_SOFTSPI) && defined (TM74HC595_USE_CS_CALLBACKS)


#include "spi.h"



void TM74HC595_Clear()
{
	SPI_Send_Byte(TM74HC595_EMPTY);
	SPI_Send_Byte(TM74HC595_EMPTY);
	
	SPI_CS_Low();
	SPI_CS_High();
}

void TM74HC595_Put_Symbols(uint8_t *symbols_arr, uint8_t symbols_arr_size)
{
	uint8_t symbol_pointer = (1 << (symbols_arr_size - 1 - target_object->symbols_counter));
	
	uint8_t symbol = symbols_arr[target_object->symbols_counter];
	
	
	
	SPI_Send_Byte(symbol);
	SPI_Send_Byte(symbol_pointer);
	
	SPI_CS_Low();
	SPI_CS_High();
	
	
	target_object->symbols_counter = (target_object->symbols_counter + 1) % symbols_arr_size;
}

void TM74HC595_Put_Symbols_Reverse(uint8_t *symbols_arr, uint8_t symbols_arr_size)
{
	uint8_t symbol_pointer = (1 << (target_object->symbols_counter));
	
	uint8_t symbol = symbols_arr[target_object->symbols_counter];
	
	
	
	SPI_Send_Byte(symbol);
	SPI_Send_Byte(symbol_pointer);
	
	SPI_CS_Low();
	SPI_CS_High();
	
	
	target_object->symbols_counter = (target_object->symbols_counter + 1) % symbols_arr_size;
}

void TM74HC595_Put_Num_String(char *num_string, uint8_t num_string_size)
{
	if (target_object->symbols_counter == 0)
	{
		target_object->point_char_separator_counter = 0;
	}
	
	uint8_t symbol_pointer, symbol;
	
	
	LABEL:
	
	symbol_pointer = (1 << (num_string_size - 1 - target_object->symbols_counter));
	
	symbol = num_string[target_object->symbols_counter + target_object->point_char_separator_counter] - 48;
	
	
	if ((symbol >= 0) && (symbol < 10))
	{
		symbol = pgm_read_byte(&_tm74hc595_symbol_pointers_symbols_table[symbol]);
	}
	else
	{
		switch (num_string[target_object->symbols_counter + target_object->point_char_separator_counter])
		{
			case 'a':
			case 'A':
			
			symbol = TM74HC595_A;
			
			break;
			
			
			case 'b':
			case 'B':
			
			symbol = TM74HC595_B;
			
			break;
			
			
			case 'c':
			case 'C':
			
			symbol = TM74HC595_C;
			
			break;
			
			
			case 'd':
			case 'D':
			
			symbol = TM74HC595_D;
			
			break;
			
			
			case 'e':
			case 'E':
			
			symbol = TM74HC595_E;
			
			break;
			
			
			case 'f':
			case 'F':
			
			symbol = TM74HC595_F;
			
			break;
			
			
			case '-':
			
			symbol = TM74HC595_MINUS;
			
			break;
			
			
			case '.':
			
			++(target_object->point_char_separator_counter);
			
			goto LABEL;
			
			
			break;
			
			
			default:
			
			symbol = TM74HC595_EMPTY;
			
			break;
		}
	}
	
	
	if (num_string[(target_object->symbols_counter + 1) % num_string_size] == '.')
	{
		symbol = TM74HC595_SET_POINT(symbol);
	}
	
	
	SPI_Send_Byte(symbol);
	SPI_Send_Byte(symbol_pointer);
	
	SPI_CS_Low();
	SPI_CS_High();
	
	
	target_object->symbols_counter = (target_object->symbols_counter + 1) % num_string_size;
}

void TM74HC595_Put_Num_String_Reverse(char *num_string, uint8_t num_string_size)
{
	if (target_object->symbols_counter == 0)
	{
		target_object->point_char_separator_counter = 0;
	}
	
	uint8_t symbol_pointer, symbol;
	
	
	LABEL:
	
	symbol_pointer = (1 << target_object->symbols_counter);
	
	symbol = num_string[target_object->symbols_counter + target_object->point_char_separator_counter] - 48;
	
	
	if ((symbol >= 0) && (symbol < 10))
	{
		symbol = pgm_read_byte(&_tm74hc595_symbol_pointers_symbols_table[symbol]);
	}
	else
	{
		switch (num_string[target_object->symbols_counter + target_object->point_char_separator_counter])
		{
			case 'a':
			case 'A':
			
			symbol = TM74HC595_A;
			
			break;
			
			
			case 'b':
			case 'B':
			
			symbol = TM74HC595_B;
			
			break;
			
			
			case 'c':
			case 'C':
			
			symbol = TM74HC595_C;
			
			break;
			
			
			case 'd':
			case 'D':
			
			symbol = TM74HC595_D;
			
			break;
			
			
			case 'e':
			case 'E':
			
			symbol = TM74HC595_E;
			
			break;
			
			
			case 'f':
			case 'F':
			
			symbol = TM74HC595_F;
			
			break;
			
			
			case '-':
			
			symbol = TM74HC595_MINUS;
			
			break;
			
			
			case '.':
			
			++(target_object->point_char_separator_counter);
			
			goto LABEL;
			
			
			break;
			
			
			default:
			
			symbol = TM74HC595_EMPTY;
			
			break;
		}
	}
	
	
	if (num_string[(target_object->symbols_counter) % num_string_size] == '.')
	{
		symbol = TM74HC595_SET_POINT(symbol);
	}
	
	
	SPI_Send_Byte(symbol);
	SPI_Send_Byte(symbol_pointer);
	
	SPI_CS_Low();
	SPI_CS_High();
	
	
	target_object->symbols_counter = (target_object->symbols_counter + 1) % num_string_size;
}


#elif !defined (TM74HC595_USE_SOFTSPI) && !defined (TM74HC595_USE_CS_CALLBACKS)


#include "spi.h"



void TM74HC595_Clear()
{
	SPI_Send_Byte(TM74HC595_EMPTY);
	SPI_Send_Byte(TM74HC595_EMPTY);
}

void TM74HC595_Put_Symbols(uint8_t *symbols_arr, uint8_t symbols_arr_size)
{
	uint8_t symbol_pointer = (1 << (symbols_arr_size - 1 - target_object->symbols_counter));
	
	uint8_t symbol = symbols_arr[target_object->symbols_counter];
	
	
	
	SPI_Send_Byte(symbol);
	SPI_Send_Byte(symbol_pointer);
	
	
	target_object->symbols_counter = (target_object->symbols_counter + 1) % symbols_arr_size;
}

void TM74HC595_Put_Symbols_Reverse(uint8_t *symbols_arr, uint8_t symbols_arr_size)
{
	uint8_t symbol_pointer = (1 << (target_object->symbols_counter));
	
	uint8_t symbol = symbols_arr[target_object->symbols_counter];
	
	
	
	SPI_Send_Byte(symbol);
	SPI_Send_Byte(symbol_pointer);
	
	
	target_object->symbols_counter = (target_object->symbols_counter + 1) % symbols_arr_size;
}

void TM74HC595_Put_Num_String(char *num_string, uint8_t num_string_size)
{
	if (target_object->symbols_counter == 0)
	{
		target_object->point_char_separator_counter = 0;
	}
	
	uint8_t symbol_pointer, symbol;
	
	
	LABEL:
	
	symbol_pointer = (1 << (num_string_size - 1 - target_object->symbols_counter));
	
	symbol = num_string[target_object->symbols_counter + target_object->point_char_separator_counter] - 48;
	
	
	if ((symbol >= 0) && (symbol < 10))
	{
		symbol = pgm_read_byte(&_tm74hc595_symbol_pointers_symbols_table[symbol]);
	}
	else
	{
		switch (num_string[target_object->symbols_counter + target_object->point_char_separator_counter])
		{
			case 'a':
			case 'A':
			
			symbol = TM74HC595_A;
			
			break;
			
			
			case 'b':
			case 'B':
			
			symbol = TM74HC595_B;
			
			break;
			
			
			case 'c':
			case 'C':
			
			symbol = TM74HC595_C;
			
			break;
			
			
			case 'd':
			case 'D':
			
			symbol = TM74HC595_D;
			
			break;
			
			
			case 'e':
			case 'E':
			
			symbol = TM74HC595_E;
			
			break;
			
			
			case 'f':
			case 'F':
			
			symbol = TM74HC595_F;
			
			break;
			
			
			case '-':
			
			symbol = TM74HC595_MINUS;
			
			break;
			
			
			case '.':
			
			++(target_object->point_char_separator_counter);
			
			goto LABEL;
			
			
			break;
			
			
			default:
			
			symbol = TM74HC595_EMPTY;
			
			break;
		}
	}
	
	
	if (num_string[(target_object->symbols_counter + 1) % num_string_size] == '.')
	{
		symbol = TM74HC595_SET_POINT(symbol);
	}
	
	
	SPI_Send_Byte(symbol);
	SPI_Send_Byte(symbol_pointer);
	
	
	target_object->symbols_counter = (target_object->symbols_counter + 1) % num_string_size;
}

void TM74HC595_Put_Num_String_Reverse(char *num_string, uint8_t num_string_size)
{
	if (target_object->symbols_counter == 0)
	{
		target_object->point_char_separator_counter = 0;
	}
	
	uint8_t symbol_pointer, symbol;
	
	
	LABEL:
	
	symbol_pointer = (1 << target_object->symbols_counter);
	
	symbol = num_string[target_object->symbols_counter + target_object->point_char_separator_counter] - 48;
	
	
	if ((symbol >= 0) && (symbol < 10))
	{
		symbol = pgm_read_byte(&_tm74hc595_symbol_pointers_symbols_table[symbol]);
	}
	else
	{
		switch (num_string[target_object->symbols_counter + target_object->point_char_separator_counter])
		{
			case 'a':
			case 'A':
			
			symbol = TM74HC595_A;
			
			break;
			
			
			case 'b':
			case 'B':
			
			symbol = TM74HC595_B;
			
			break;
			
			
			case 'c':
			case 'C':
			
			symbol = TM74HC595_C;
			
			break;
			
			
			case 'd':
			case 'D':
			
			symbol = TM74HC595_D;
			
			break;
			
			
			case 'e':
			case 'E':
			
			symbol = TM74HC595_E;
			
			break;
			
			
			case 'f':
			case 'F':
			
			symbol = TM74HC595_F;
			
			break;
			
			
			case '-':
			
			symbol = TM74HC595_MINUS;
			
			break;
			
			
			case '.':
			
			++(target_object->point_char_separator_counter);
			
			goto LABEL;
			
			
			break;
			
			
			default:
			
			symbol = TM74HC595_EMPTY;
			
			break;
		}
	}
	
	
	if (num_string[(target_object->symbols_counter) % num_string_size] == '.')
	{
		symbol = TM74HC595_SET_POINT(symbol);
	}
	
	
	SPI_Send_Byte(symbol);
	SPI_Send_Byte(symbol_pointer);
	
	
	target_object->symbols_counter = (target_object->symbols_counter + 1) % num_string_size;
}


#endif // ===============================================================================



char *TM74HC595_Convert_Num_String_To_Symbols_Array(char *num_string, uint8_t num_string_size)
{
	target_object->point_char_separator_counter = 0;
	
	uint8_t symbol;
	
	
	for (uint8_t i = 0; i < num_string_size; ++i)
	{
		LABEL:
		
		symbol = num_string[i + target_object->point_char_separator_counter] - 48;
		
		
		if ((symbol >= 0) && (symbol < 10))
		{
			symbol = pgm_read_byte(&_tm74hc595_symbol_pointers_symbols_table[symbol]);
		}
		else
		{
			switch (num_string[i + target_object->point_char_separator_counter])
			{
				case 'a':
				case 'A':
				
				symbol = TM74HC595_A;
				
				break;
				
				
				case 'b':
				case 'B':
				
				symbol = TM74HC595_B;
				
				break;
				
				
				case 'c':
				case 'C':
				
				symbol = TM74HC595_C;
				
				break;
				
				
				case 'd':
				case 'D':
				
				symbol = TM74HC595_D;
				
				break;
				
				
				case 'e':
				case 'E':
				
				symbol = TM74HC595_E;
				
				break;
				
				
				case 'f':
				case 'F':
				
				symbol = TM74HC595_F;
				
				break;
				
				
				case '-':
				
				symbol = TM74HC595_MINUS;
				
				break;
				
				
				case '.':
				
				++(target_object->point_char_separator_counter);
				
				goto LABEL;
				
				
				break;
				
				
				default:
				
				symbol = TM74HC595_EMPTY;
				
				break;
			}
		}
		
		
		if (num_string[(i + 1) % num_string_size] == '.')
		{
			symbol = TM74HC595_SET_POINT(symbol);
		}
		
		
		num_string[i] = symbol;
	}
	
	return num_string;
}









#include "tm74hc595.h"



// таблица символов (цифры от 0 до 9)
//
// -------------------------------------------------------------------------------
// symbol table (numbers from 0 to 9)
//
const uint8_t _tm74hc595_digits_symbols_table[] PROGMEM =
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



void TM74HC595_Initialize_Object(TM74HC595_t *tm74hc595, void (*latch_callback)())
{
	(*tm74hc595).symbols_counter = 0;
	
	(*tm74hc595).point_char_separator_counter = 0;
	
	(*tm74hc595).latch_callback = latch_callback;
}



// ===============================================================================




#if defined (TM74HC595_USE_SOFTSPI)


#include "softspi.h"



void TM74HC595_Clear(TM74HC595_t *tm74hc595)
{
	SOFTSPI_Send_Byte(TM74HC595_EMPTY);
	SOFTSPI_Send_Byte(TM74HC595_EMPTY);
	
	if ((tm74hc595->latch_callback) != NULL)
	{
		tm74hc595->latch_callback();
	}
}


void TM74HC595_Put_Symbols(TM74HC595_t *tm74hc595, const uint8_t *symbols_arr, uint8_t symbols_arr_size)
{
	uint8_t symbol_pointer = (1 << (symbols_arr_size - 1 - tm74hc595->symbols_counter));
	
	uint8_t symbol = symbols_arr[tm74hc595->symbols_counter];
	
	
	
	SOFTSPI_Send_Byte(symbol);
	SOFTSPI_Send_Byte(symbol_pointer);
	
	
	if ((tm74hc595->latch_callback) != NULL)
	{
		tm74hc595->latch_callback();
	}
	
	
	tm74hc595->symbols_counter = (tm74hc595->symbols_counter + 1) % symbols_arr_size;
}


void TM74HC595_Put_Symbols_Reverse(TM74HC595_t *tm74hc595, const uint8_t *symbols_arr, uint8_t symbols_arr_size)
{
	uint8_t symbol_pointer = (1 << (tm74hc595->symbols_counter));
	
	uint8_t symbol = symbols_arr[tm74hc595->symbols_counter];
	
	
	
	SOFTSPI_Send_Byte(symbol);
	SOFTSPI_Send_Byte(symbol_pointer);
	
	
	if ((tm74hc595->latch_callback) != NULL)
	{
		tm74hc595->latch_callback();
	}
	
	
	tm74hc595->symbols_counter = (tm74hc595->symbols_counter + 1) % symbols_arr_size;
}


void TM74HC595_Put_Num_String(TM74HC595_t *tm74hc595, const char *num_string, uint8_t num_string_size)
{
	if (tm74hc595->symbols_counter == 0)
	{
		tm74hc595->point_char_separator_counter = 0;
	}
	
	uint8_t symbol_pointer, symbol;
	
	
	LABEL:
	
	symbol_pointer = (1 << (num_string_size - 1 - tm74hc595->symbols_counter));
	
	symbol = num_string[tm74hc595->symbols_counter + tm74hc595->point_char_separator_counter] - 48;
	
	
	if ((symbol >= 0) && (symbol < 10))
	{
		symbol = pgm_read_byte(&_tm74hc595_digits_symbols_table[symbol]);
	}
	else
	{
		switch (num_string[tm74hc595->symbols_counter + tm74hc595->point_char_separator_counter])
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
			
			++(tm74hc595->point_char_separator_counter);
			
			goto LABEL;
			
			
			break;
			
			
			default:
			
			symbol = TM74HC595_EMPTY;
			
			break;
		}
	}
	
	
	if (num_string[(tm74hc595->symbols_counter + 1) % num_string_size] == '.')
	{
		symbol = TM74HC595_SET_POINT(symbol);
	}
	
	
	SOFTSPI_Send_Byte(symbol);
	SOFTSPI_Send_Byte(symbol_pointer);
	
	
	if ((tm74hc595->latch_callback) != NULL)
	{
		tm74hc595->latch_callback();
	}
	
	
	tm74hc595->symbols_counter = (tm74hc595->symbols_counter + 1) % num_string_size;
}


void TM74HC595_Put_Num_String_Reverse(TM74HC595_t *tm74hc595, const char *num_string, uint8_t num_string_size)
{
	if (tm74hc595->symbols_counter == 0)
	{
		tm74hc595->point_char_separator_counter = 0;
	}
	
	uint8_t symbol_pointer, symbol;
	
	
	LABEL:
	
	symbol_pointer = (1 << tm74hc595->symbols_counter);
	
	symbol = num_string[tm74hc595->symbols_counter + tm74hc595->point_char_separator_counter] - 48;
	
	
	if ((symbol >= 0) && (symbol < 10))
	{
		symbol = pgm_read_byte(&_tm74hc595_digits_symbols_table[symbol]);
	}
	else
	{
		switch (num_string[tm74hc595->symbols_counter + tm74hc595->point_char_separator_counter])
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
			
			++(tm74hc595->point_char_separator_counter);
			
			goto LABEL;
			
			
			break;
			
			
			default:
			
			symbol = TM74HC595_EMPTY;
			
			break;
		}
	}
	
	
	if (num_string[(tm74hc595->symbols_counter) % num_string_size] == '.')
	{
		symbol = TM74HC595_SET_POINT(symbol);
	}
	
	
	SOFTSPI_Send_Byte(symbol);
	SOFTSPI_Send_Byte(symbol_pointer);
	
	
	if ((tm74hc595->latch_callback) != NULL)
	{
		tm74hc595->latch_callback();
	}
	
	
	tm74hc595->symbols_counter = (tm74hc595->symbols_counter + 1) % num_string_size;
}




#else




#include "spi.h"



void TM74HC595_Clear(TM74HC595_t *tm74hc595)
{
	SPI_Send_Byte(TM74HC595_EMPTY);
	SPI_Send_Byte(TM74HC595_EMPTY);
	
	SPI_CS_Set_Inactive();
	SPI_CS_Set_Active();
}


void TM74HC595_Put_Symbols(TM74HC595_t *tm74hc595, const uint8_t *symbols_arr, uint8_t symbols_arr_size)
{
	uint8_t symbol_pointer = (1 << (symbols_arr_size - 1 - tm74hc595->symbols_counter));
	
	uint8_t symbol = symbols_arr[tm74hc595->symbols_counter];
	
	
	
	SPI_Send_Byte(symbol);
	SPI_Send_Byte(symbol_pointer);
	
	
	if ((tm74hc595->latch_callback) != NULL)
	{
		tm74hc595->latch_callback();
	}
	
	
	tm74hc595->symbols_counter = (tm74hc595->symbols_counter + 1) % symbols_arr_size;
}


void TM74HC595_Put_Symbols_Reverse(const uint8_t *symbols_arr, uint8_t symbols_arr_size)
{
	uint8_t symbol_pointer = (1 << (tm74hc595->symbols_counter));
	
	uint8_t symbol = symbols_arr[tm74hc595->symbols_counter];
	
	
	
	SPI_Send_Byte(symbol);
	SPI_Send_Byte(symbol_pointer);
	
	
	if ((tm74hc595->latch_callback) != NULL)
	{
		tm74hc595->latch_callback();
	}
	
	
	tm74hc595->symbols_counter = (tm74hc595->symbols_counter + 1) % symbols_arr_size;
}


void TM74HC595_Put_Num_String(TM74HC595_t *tm74hc595, const char *num_string, uint8_t num_string_size)
{
	if (tm74hc595->symbols_counter == 0)
	{
		tm74hc595->point_char_separator_counter = 0;
	}
	
	uint8_t symbol_pointer, symbol;
	
	
	LABEL:
	
	symbol_pointer = (1 << (num_string_size - 1 - tm74hc595->symbols_counter));
	
	symbol = num_string[tm74hc595->symbols_counter + tm74hc595->point_char_separator_counter] - 48;
	
	
	if ((symbol >= 0) && (symbol < 10))
	{
		symbol = pgm_read_byte(&_tm74hc595_digits_symbols_table[symbol]);
	}
	else
	{
		switch (num_string[tm74hc595->symbols_counter + tm74hc595->point_char_separator_counter])
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
			
			++(tm74hc595->point_char_separator_counter);
			
			goto LABEL;
			
			
			break;
			
			
			default:
			
			symbol = TM74HC595_EMPTY;
			
			break;
		}
	}
	
	
	if (num_string[(tm74hc595->symbols_counter + 1) % num_string_size] == '.')
	{
		symbol = TM74HC595_SET_POINT(symbol);
	}
	
	
	SPI_Send_Byte(symbol);
	SPI_Send_Byte(symbol_pointer);
	
	
	if ((tm74hc595->latch_callback) != NULL)
	{
		tm74hc595->latch_callback();
	}
	
	
	tm74hc595->symbols_counter = (tm74hc595->symbols_counter + 1) % num_string_size;
}


void TM74HC595_Put_Num_String_Reverse(TM74HC595_t *tm74hc595, const char *num_string, uint8_t num_string_size)
{
	if (tm74hc595->symbols_counter == 0)
	{
		tm74hc595->point_char_separator_counter = 0;
	}
	
	uint8_t symbol_pointer, symbol;
	
	
	LABEL:
	
	symbol_pointer = (1 << tm74hc595->symbols_counter);
	
	symbol = num_string[tm74hc595->symbols_counter + tm74hc595->point_char_separator_counter] - 48;
	
	
	if ((symbol >= 0) && (symbol < 10))
	{
		symbol = pgm_read_byte(&_tm74hc595_digits_symbols_table[symbol]);
	}
	else
	{
		switch (num_string[tm74hc595->symbols_counter + tm74hc595->point_char_separator_counter])
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
			
			++(tm74hc595->point_char_separator_counter);
			
			goto LABEL;
			
			
			break;
			
			
			default:
			
			symbol = TM74HC595_EMPTY;
			
			break;
		}
	}
	
	
	if (num_string[(tm74hc595->symbols_counter) % num_string_size] == '.')
	{
		symbol = TM74HC595_SET_POINT(symbol);
	}
	
	
	SPI_Send_Byte(symbol);
	SPI_Send_Byte(symbol_pointer);
	
	
	if ((tm74hc595->latch_callback) != NULL)
	{
		tm74hc595->latch_callback();
	}
	
	
	tm74hc595->symbols_counter = (tm74hc595->symbols_counter + 1) % num_string_size;
}



#endif









#include "max7219.h"


#if defined (MAX7219_USE_SOFTSPI) && defined (MAX7219_USE_CS_CALLBACKS)

static void _MAX7219_Send_Command(uint8_t reg, uint8_t data)
{
	SOFTSPI_Call_CS_ON();
	SOFTSPI_Send_Byte(reg);
	SOFTSPI_Send_Byte(data);
	SOFTSPI_Call_CS_OFF();
}

#elif defined (MAX7219_USE_SOFTSPI) && !defined (MAX7219_USE_CS_CALLBACKS)

static void _MAX7219_Send_Command(uint8_t reg, uint8_t data)
{
	SOFTSPI_Send_Byte(reg);
	SOFTSPI_Send_Byte(data);
}

#elif !defined (MAX7219_USE_SOFTSPI) && defined (MAX7219_USE_CS_CALLBACKS)

static void _MAX7219_Send_Command(uint8_t reg, uint8_t data)
{
	SPI_Call_CS_ON();
	SPI_Send_Byte(reg);
	SPI_Send_Byte(data);
	SPI_Call_CS_OFF();
}

#elif !defined (MAX7219_USE_SOFTSPI) && !defined (MAX7219_USE_CS_CALLBACKS)

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

void MAX7219_Set_Data(void *data, uint8_t data_size, bool output_direction)
{
	if (output_direction == MAX7219_DATA_DIRECTION_NORMAL)
	{
		for (uint8_t i = 0; i < data_size; ++i)
		{
			MAX7219_Set_Digit(i, ((uint8_t*)data)[data_size - 1 - i]);
		}
	}
	else
	{
		for (uint8_t i = 0; i < data_size; ++i)
		{
			MAX7219_Set_Digit(i, ((uint8_t*)data)[i]);
		}
	}
}

void MAX7219_Set_Char_Digits(char *data, uint8_t data_size, const uint8_t max_num_digits)
{
	for (uint8_t i = 0; i < data_size; ++i)
	{
		if (data[i] == ' ')
		{
			MAX7219_Set_Digit(max_num_digits - i - 1, 15);
		}
		else
		{
			MAX7219_Set_Digit(max_num_digits - i - 1, data[i] - 48);
		}
	}
}

#endif

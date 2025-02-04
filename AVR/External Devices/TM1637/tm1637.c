

#include "tm1637.h"


static const uint8_t _digits[] =
{
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
};


// ===============================================================================


#define TM1637_DELAY_1  _delay_us(10)
#define TM1637_DELAY_2  _delay_us(20)


#ifndef TM1637_USE_MULTIPLE_INTERFACE




#define TM1637_DIO_SET_LOW	  TM1637_DIO_DDR |=  (1 << TM1637_DIO_PIN)
#define TM1637_DIO_SET_HIGH   TM1637_DIO_DDR &= ~(1 << TM1637_DIO_PIN)

#define TM1637_DIO_GET_VALUE (TM1637_DIO_PINX & (1 << TM1637_DIO_PIN))

#define TM1637_SCL_SET_LOW	  TM1637_CLK_DDR |=  (1 << TM1637_CLK_PIN)
#define TM1637_SCL_SET_HIGH   TM1637_CLK_DDR &= ~(1 << TM1637_CLK_PIN)


static uint8_t _tm1637_configuration_register_buffer = 0b10000000;


// ===============================================================================


static inline void _TM1637_Start()
{
	TM1637_DIO_SET_LOW;
	TM1637_DELAY_2;
}

static inline void _TM1637_Stop()
{
	TM1637_SCL_SET_LOW;
	TM1637_DELAY_1;
	
	TM1637_DIO_SET_LOW;
	TM1637_DELAY_1;
	
	TM1637_SCL_SET_HIGH;
	TM1637_DELAY_2;
	
	TM1637_DIO_SET_HIGH;
	TM1637_DELAY_2;
}


uint8_t _TM1637_Send_Byte(uint8_t byte)
{
	for (uint8_t i = 0; i < 8; ++i)
	{
		TM1637_SCL_SET_LOW;
		TM1637_DELAY_1;
		
		if (byte & 0b1)
		{
			TM1637_DIO_SET_HIGH;
		}
		else
		{
			TM1637_DIO_SET_LOW;
		}
		
		TM1637_DELAY_1;
		
		TM1637_SCL_SET_HIGH;
		TM1637_DELAY_2;
		
		byte >>= 1;
	}
	
	TM1637_SCL_SET_LOW;
	TM1637_DIO_SET_HIGH;
	TM1637_DELAY_2;
	
	TM1637_SCL_SET_HIGH;
	TM1637_DELAY_1;

	uint8_t ack = TM1637_DIO_GET_VALUE;
	
	if (ack == NACK)
	{
		TM1637_DIO_SET_LOW;
	}
	
	TM1637_DELAY_1;

	return ack;
}


// ===============================================================================


void TM1637_Initialize(bool is_enable, uint8_t brightness_coef)
{
	TM1637_DIO_PORT &= ~(1 << TM1637_DIO_PIN);
	TM1637_CLK_PORT &= ~(1 << TM1637_CLK_PIN);
	
	if (is_enable == true)
	{
		_tm1637_configuration_register_buffer |= (1 << 3);
	}
	
	_tm1637_configuration_register_buffer |= (brightness_coef & 0b111);
	
	
	_TM1637_Start();
	
	_TM1637_Send_Byte(_tm1637_configuration_register_buffer);
	
	_TM1637_Stop();
}

void TM1637_Set_Enable(bool is_enable)
{
	if (is_enable == true)
	{
		_tm1637_configuration_register_buffer |= (1 << 3);
	}
	else
	{
		_tm1637_configuration_register_buffer &= ~(1 << 3);
	}
	
	
	_TM1637_Start();
	
	_TM1637_Send_Byte(_tm1637_configuration_register_buffer);
	
	_TM1637_Stop();
}

void TM1637_Set_Brightness(uint8_t brightness_coef)
{
	_tm1637_configuration_register_buffer &= 0b11111000;
	
	_tm1637_configuration_register_buffer |= (brightness_coef & 0b111);
	
	
	_TM1637_Start();
	
	_TM1637_Send_Byte(_tm1637_configuration_register_buffer);
	
	_TM1637_Stop();
}



#else // ===============================================================================


static TM1637_t *target_indicator_object = NULL;


#define TM1637_DIO_SET_LOW	  *(target_indicator_object->dio_ddr) |=  (1 << (target_indicator_object->dio_pin))
#define TM1637_DIO_SET_HIGH   *(target_indicator_object->dio_ddr) &= ~(1 << (target_indicator_object->dio_pin))

#define TM1637_DIO_GET_VALUE (*(target_indicator_object->dio_pinx) & (1 << (target_indicator_object->dio_pin)))

#define TM1637_SCL_SET_LOW	  *(target_indicator_object->clk_ddr) |=  (1 << (target_indicator_object->clk_pin))
#define TM1637_SCL_SET_HIGH   *(target_indicator_object->clk_ddr) &= ~(1 << (target_indicator_object->clk_pin))


static inline void _TM1637_Start()
{
	TM1637_DIO_SET_LOW;
	TM1637_DELAY_2;
}

static inline void _TM1637_Stop()
{
	TM1637_SCL_SET_LOW;
	TM1637_DELAY_1;
	
	TM1637_DIO_SET_LOW;
	TM1637_DELAY_1;
	
	TM1637_SCL_SET_HIGH;
	TM1637_DELAY_2;
	
	TM1637_DIO_SET_HIGH;
	TM1637_DELAY_2;
}


uint8_t _TM1637_Send_Byte(uint8_t byte)
{
	for (uint8_t i = 0; i < 8; ++i)
	{
		TM1637_SCL_SET_LOW;
		TM1637_DELAY_1;
		
		if (byte & 0b1)
		{
			TM1637_DIO_SET_HIGH;
		}
		else
		{
			TM1637_DIO_SET_LOW;
		}
		
		TM1637_DELAY_1;
		
		TM1637_SCL_SET_HIGH;
		TM1637_DELAY_2;
		
		byte >>= 1;
	}
	
	TM1637_SCL_SET_LOW;
	TM1637_DIO_SET_HIGH;
	TM1637_DELAY_2;
	
	TM1637_SCL_SET_HIGH;
	TM1637_DELAY_1;

	uint8_t ack = TM1637_DIO_GET_VALUE;
	
	if (ack == NACK)
	{
		TM1637_DIO_SET_LOW;
	}
	
	TM1637_DELAY_1;

	return ack;
}


// ===============================================================================


TM1637_t TM1637_Create_Object(

	uint8_t *clk_ddr,
	uint8_t *clk_port,
	uint8_t  clk_pin,

	uint8_t *dio_ddr,
	uint8_t *dio_pinx,
	uint8_t *dio_port,
	uint8_t  dio_pin,

	bool is_enable,
	uint8_t brightness_coef
)
{
	TM1637_t device;
	
	device.clk_ddr  = clk_ddr;
	device.clk_port = clk_port;
	device.clk_pin  = clk_pin;
	
	device.dio_ddr  = dio_ddr;
	device.dio_pinx = dio_pinx;
	device.dio_port = dio_port;
	device.dio_pin  = dio_pin;
	
	device.configuration_register_buffer = 0b10000000;
	
	
	*(dio_port) &= ~(1 << dio_pin);
	*(clk_port) &= ~(1 << clk_pin);
	
	
	if (is_enable == true)
	{
		device.configuration_register_buffer |= (1 << 3);
	}
	
	device.configuration_register_buffer |= (brightness_coef & 0b111);
	
	
	target_indicator_object = &device;
	
	
	_TM1637_Start();
	
	_TM1637_Send_Byte(device.configuration_register_buffer);
	
	_TM1637_Stop();
	
	return device;
}

void TM1637_Set_Target_Object(TM1637_t *device)
{
	target_indicator_object = device;
}

TM1637_t *TM1637_Get_Target_Object()
{
	return target_indicator_object;
}


// ===============================================================================


void TM1637_Set_Enable(bool is_enable)
{
	if (is_enable == true)
	{
		target_indicator_object->configuration_register_buffer |= (1 << 3);
	}
	else
	{
		target_indicator_object->configuration_register_buffer &= ~(1 << 3);
	}
	
	
	_TM1637_Start();
	
	_TM1637_Send_Byte(target_indicator_object->configuration_register_buffer);
	
	_TM1637_Stop();
}

void TM1637_Set_Brightness(uint8_t brightness_coef)
{
	target_indicator_object->configuration_register_buffer &= 0b11111000;
	
	target_indicator_object->configuration_register_buffer |= (brightness_coef & 0b111);
	
	
	_TM1637_Start();
	
	_TM1637_Send_Byte(target_indicator_object->configuration_register_buffer);
	
	_TM1637_Stop();
}


#endif




void TM1637_Put_Symbols(uint8_t *simbols_arr, uint8_t simbols_arr_size)
{
	_TM1637_Start();
	
	_TM1637_Send_Byte(0b11000000);
	
	for (int8_t i = 0; i < simbols_arr_size; ++i)
	{
		_TM1637_Send_Byte(simbols_arr[i]);
	}
	
	_TM1637_Stop();
}


void TM1637_Put_Symbols_Reverse(uint8_t *simbols_arr, uint8_t simbols_arr_size)
{
	_TM1637_Start();
	
	_TM1637_Send_Byte(0b11000000);
	
	for (int8_t i = 0; i < simbols_arr_size; ++i)
	{
		_TM1637_Send_Byte(simbols_arr[(simbols_arr_size - i - 1)]);
	}
	
	_TM1637_Stop();
}


void TM1637_Put_Num_String(char *num_string, uint8_t num_string_size)
{
	uint8_t s = 0x00;
	
	
	_TM1637_Start();
	
	_TM1637_Send_Byte(0b11000000);
	
	for (int8_t i = 0; i < num_string_size; ++i)
	{
		if (num_string[i] == ' ')
		{
			s = TM1637_EMPTY;
		}
		else if (num_string[i] == '-')
		{
			s = TM1637_MINUS;
		}
		else
		{
			uint8_t ch = num_string[i] - 48;
			
			if (ch < 10)
			{
				s = _digits[ch];
			}
			else
			{
				s = TM1637_EMPTY;
			}
		}
		
		_TM1637_Send_Byte(s);
	}
	
	_TM1637_Stop();
}


void TM1637_Put_Num_String_Reverse(char *num_string, uint8_t num_string_size)
{
	uint8_t s = 0x00;
	
	
	_TM1637_Start();
	
	_TM1637_Send_Byte(0b11000000);
	
	for (int8_t i = 0; i < num_string_size; ++i)
	{
		if (num_string[(num_string_size - i - 1)] == ' ')
		{
			s = TM1637_EMPTY;
		}
		else if (num_string[(num_string_size - i - 1)] == '-')
		{
			s = TM1637_MINUS;
		}
		else
		{
			uint8_t ch = num_string[(num_string_size - i - 1)] - 48;
			
			if (ch < 10)
			{
				s = _digits[ch];
			}
			else
			{
				s = TM1637_EMPTY;
			}
		}
		
		_TM1637_Send_Byte(s);
	}
	
	_TM1637_Stop();
}


void TM1637_Clear()
{
	_TM1637_Start();
	
	_TM1637_Send_Byte(0b11000000);
	
	for (uint8_t i = 0; i < 4; ++i)
	{
		_TM1637_Send_Byte(TM1637_EMPTY);
	}
	
	_TM1637_Stop();
}


char *TM1637_Convert_Num_String_To_Symbols_Array(char *num_string, uint8_t num_string_size)
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
			num_string[i] = TM1637_EMPTY;
		}
		else if (num_string[j] == '-')
		{
			num_string[i] = TM1637_MINUS;
		}
		else
		{
			uint8_t ch = num_string[j] - 48;
			
			if (ch < 10)
			{
				num_string[i] = _digits[ch];
			}
			else
			{
				num_string[i] = TM1637_EMPTY;
			}
		}
		
		++i;
		++j;
	}
	
	if (decimal_char_separator_flag)
	{
		num_string[decimal_char_separator_pos - 1] |= 0b10000000;
	}
	
	return num_string;
}




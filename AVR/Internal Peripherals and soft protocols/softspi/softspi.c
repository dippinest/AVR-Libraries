
#include "softspi.h"
#include "softspi_configuration.h"

// ===============================================================================

void SOFTSPI_Initialize()
{
	SOFTSPI_MISO_DDR &= ~(1 << SOFTSPI_MISO_PIN);
	SOFTSPI_MOSI_DDR |=  (1 << SOFTSPI_MOSI_PIN);
	SOFTSPI_CLK_DDR  |=  (1 << SOFTSPI_CLK_PIN);
	
	#if defined(SOFTSPI_MODE_0) || defined(SOFTSPI_MODE_1)
	_SOFTSPI_CLK_SET_LOW;
	#else
	_SOFTSPI_CLK_SET_HIGH;
	#endif
}

// ===============================================================================

#if (SOFTSPI_DATA_ORDER == SOFTSPI_DATA_IS_ORDER_HIGHEST_BIT) && (SOFTSPI_MODE == SOFTSPI_MODE_0)
void SOFTSPI_Send_Byte(uint8_t byte)
{
	for (int8_t i = 7; i >= 0; --i)
	{
		_SOFTSPI_Mode0_Set_Bit(byte & (1 << i));
	}
}

#elif (SOFTSPI_DATA_ORDER == SOFTSPI_DATA_IS_ORDER_HIGHEST_BIT) && (SOFTSPI_MODE == SOFTSPI_MODE_1)
void SOFTSPI_Send_Byte(uint8_t byte)
{
	for (int8_t i = 7; i >= 0; --i)
	{
		_SOFTSPI_Mode1_Set_Bit(byte & (1 << i));
	}
}

#elif (SOFTSPI_DATA_ORDER == SOFTSPI_DATA_IS_ORDER_HIGHEST_BIT) && (SOFTSPI_MODE == SOFTSPI_MODE_2)
void SOFTSPI_Send_Byte(uint8_t byte)
{
	for (int8_t i = 7; i >= 0; --i)
	{
		_SOFTSPI_Mode2_Set_Bit(byte & (1 << i));
	}
}

#elif (SOFTSPI_DATA_ORDER == SOFTSPI_DATA_IS_ORDER_HIGHEST_BIT) && (SOFTSPI_MODE == SOFTSPI_MODE_3)
void SOFTSPI_Send_Byte(uint8_t byte)
{
	for (int8_t i = 7; i >= 0; --i)
	{
		_SOFTSPI_Mode3_Set_Bit(byte & (1 << i));
	}
}

#elif (SOFTSPI_DATA_ORDER == SOFTSPI_DATA_IS_ORDER_LOWEST_BIT) && (SOFTSPI_MODE == SOFTSPI_MODE_0)
void SOFTSPI_Send_Byte(uint8_t byte)
{
	for (int8_t i = 0; i < 8; ++i)
	{
		_SOFTSPI_Mode0_Set_Bit(byte & (1 << i));
	}
}

#elif (SOFTSPI_DATA_ORDER == SOFTSPI_DATA_IS_ORDER_LOWEST_BIT) && (SOFTSPI_MODE == SOFTSPI_MODE_1)
void SOFTSPI_Send_Byte(uint8_t byte)
{
	for (int8_t i = 0; i < 8; ++i)
	{
		_SOFTSPI_Mode1_Set_Bit(byte & (1 << i));
	}
}

#elif (SOFTSPI_DATA_ORDER == SOFTSPI_DATA_IS_ORDER_LOWEST_BIT) && (SOFTSPI_MODE == SOFTSPI_MODE_2)
void SOFTSPI_Send_Byte(uint8_t byte)
{
	for (int8_t i = 0; i < 8; ++i)
	{
		_SOFTSPI_Mode2_Set_Bit(byte & (1 << i));
	}
}

#elif (SOFTSPI_DATA_ORDER == SOFTSPI_DATA_IS_ORDER_LOWEST_BIT) && (SOFTSPI_MODE == SOFTSPI_MODE_3)
void SOFTSPI_Send_Byte(uint8_t byte)
{
	for (int8_t i = 0; i < 8; ++i)
	{
		_SOFTSPI_Mode3_Set_Bit(byte & (1 << i));
	}
}

#endif

void SOFTSPI_Send_Data(void* data, uint16_t data_size)
{
	for (uint16_t i = 0; i < data_size; ++i)
	{
		SOFTSPI_Send_Byte(((uint8_t*)data)[i]);
	}
}

uint8_t SOFTSPI_Get_Byte()
{
	uint8_t data = 0x00;
	
	#if (SOFTSPI_DATA_ORDER == SOFTSPI_DATA_IS_ORDER_HIGHEST_BIT) && (SOFTSPI_MODE == SOFTSPI_MODE_0)
	for (int8_t i = 7; i >= 0; --i)
	{
		if (_SOFTSPI_Mode0_Get_Bit())
		{
			data |= (1 << i);
		}
	}
	#endif
	
	#if (SOFTSPI_DATA_ORDER == SOFTSPI_DATA_IS_ORDER_HIGHEST_BIT) && (SOFTSPI_MODE == SOFTSPI_MODE_1)
	for (int8_t i = 7; i >= 0; --i)
	{
		if (_SOFTSPI_Mode1_Get_Bit())
		{
			data |= (1 << i);
		}
	}
	#endif
	
	#if (SOFTSPI_DATA_ORDER == SOFTSPI_DATA_IS_ORDER_HIGHEST_BIT) && (SOFTSPI_MODE == SOFTSPI_MODE_2)
	for (int8_t i = 7; i >= 0; --i)
	{
		if (_SOFTSPI_Mode2_Get_Bit())
		{
			data |= (1 << i);
		}
	}
	#endif
	
	#if (SOFTSPI_DATA_ORDER == SOFTSPI_DATA_IS_ORDER_HIGHEST_BIT) && (SOFTSPI_MODE == SOFTSPI_MODE_3)
	for (int8_t i = 7; i >= 0; --i)
	{
		if (_SOFTSPI_Mode3_Get_Bit())
		{
			data |= (1 << i);
		}
	}
	#endif
	
	#if (SOFTSPI_DATA_ORDER == SOFTSPI_DATA_IS_ORDER_LOWEST_BIT) && (SOFTSPI_MODE == SOFTSPI_MODE_0)
	for (int8_t i = 0; i < 8; ++i)
	{
		if (_SOFTSPI_Mode0_Get_Bit())
		{
			data |= (1 << i);
		}
	}
	#endif
	
	#if (SOFTSPI_DATA_ORDER == SOFTSPI_DATA_IS_ORDER_LOWEST_BIT) && (SOFTSPI_MODE == SOFTSPI_MODE_1)
	for (int8_t i = 0; i < 8; ++i)
	{
		if (_SOFTSPI_Mode1_Get_Bit())
		{
			data |= (1 << i);
		}
	}
	#endif
	
	#if (SOFTSPI_DATA_ORDER == SOFTSPI_DATA_IS_ORDER_LOWEST_BIT) && (SOFTSPI_MODE == SOFTSPI_MODE_2)
	for (int8_t i = 0; i < 8; ++i)
	{
		if (_SOFTSPI_Mode2_Get_Bit())
		{
			data |= (1 << i);
		}
	}
	#endif
	
	#if (SOFTSPI_DATA_ORDER == SOFTSPI_DATA_IS_ORDER_LOWEST_BIT) && (SOFTSPI_MODE == SOFTSPI_MODE_3)
	for (int8_t i = 0; i < 8; ++i)
	{
		if (_SOFTSPI_Mode3_Get_Bit())
		{
			data |= (1 << i);
		}
	}
	#endif
	
	return data;
}

// ===============================================================================

static void (*_cs_set_on)()  = NULL;
static void (*_cs_set_off)() = NULL;

void SOFTSPI_Set_CS_CallBack_Functions(void (*cs_on_callback)(), void (*cs_off_callback)())
{
	_cs_set_on  = cs_on_callback;
	_cs_set_off = cs_off_callback;
}

void SOFTSPI_Call_CS_ON()
{
	_cs_set_on();
}

void SOFTSPI_Call_CS_OFF()
{
	_cs_set_off();
}

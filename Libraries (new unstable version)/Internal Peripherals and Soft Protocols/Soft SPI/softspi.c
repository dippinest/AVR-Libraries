
#include "softspi.h"
#include "softspi_configuration.h"

// ===============================================================================

#ifndef SOFTSPI_USE_MULTIPLE_INTERFACE

void _SOFTSPI_Mode0_Set_Bit(bool bit)
{
	if (bit)
	{
		_SOFTSPI_MOSI_SET_HIGH;
	}
	else
	{
		_SOFTSPI_MOSI_SET_LOW;
	}
	
	_SOFTSPI_CLK_SET_HIGH;
	_SOFTSPI_CLK_SET_LOW;
}

void _SOFTSPI_Mode1_Set_Bit(bool bit)
{
	_SOFTSPI_CLK_SET_HIGH;
	
	if (bit)
	{
		_SOFTSPI_MOSI_SET_HIGH;
	}
	else
	{
		_SOFTSPI_MOSI_SET_LOW;
	}
	
	_SOFTSPI_CLK_SET_LOW;
}

void _SOFTSPI_Mode2_Set_Bit(bool bit)
{
	if (bit)
	{
		_SOFTSPI_MOSI_SET_HIGH;
	}
	else
	{
		_SOFTSPI_MOSI_SET_LOW;
	}
	
	_SOFTSPI_CLK_SET_LOW;
	_SOFTSPI_CLK_SET_HIGH;
}

void _SOFTSPI_Mode3_Set_Bit(bool bit)
{
	_SOFTSPI_CLK_SET_LOW;
	
	if (bit)
	{
		_SOFTSPI_MOSI_SET_HIGH;
	}
	else
	{
		_SOFTSPI_MOSI_SET_LOW;
	}
	
	_SOFTSPI_CLK_SET_HIGH;
}

// ===============================================================================

bool _SOFTSPI_Mode0_Get_Bit()
{
	bool bit;
	
	if (_SOFTSPI_MISO_GET)
	{
		bit = true;
	}
	else
	{
		bit = false;
	}
	
	_SOFTSPI_CLK_SET_HIGH;
	_SOFTSPI_CLK_SET_LOW;
	
	return bit;
}

bool _SOFTSPI_Mode1_Get_Bit()
{
	bool bit;
	
	_SOFTSPI_CLK_SET_HIGH;
	
	if (_SOFTSPI_MISO_GET)
	{
		bit = true;
	}
	else
	{
		bit = false;
	}
	
	_SOFTSPI_CLK_SET_LOW;
	
	return bit;
}

bool _SOFTSPI_Mode2_Get_Bit()
{
	bool bit;
	
	if (_SOFTSPI_MISO_GET)
	{
		bit = true;
	}
	else
	{
		bit = false;
	}
	
	_SOFTSPI_CLK_SET_LOW;
	_SOFTSPI_CLK_SET_HIGH;
	
	return bit;
}

bool _SOFTSPI_Mode3_Get_Bit()
{
	bool bit;
	
	_SOFTSPI_CLK_SET_LOW;
	
	if (_SOFTSPI_MISO_GET)
	{
		bit = true;
	}
	else
	{
		bit = false;
	}
	
	_SOFTSPI_CLK_SET_HIGH;
	
	return bit;
}

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

void *SOFTSPI_Get_Data(void* data, uint16_t data_size)
{
	for (uint16_t j = 0; j < data_size; ++j)
	{
		((uint8_t*)data)[j] = SOFTSPI_Get_Byte();
	}
	
	return data;
}



#else // ===============================================================================



static SOFTSPI_t *target_softspi_interface_object = NULL;

void SOFTSPI_Initialize_Object
(
	SOFTSPI_t *softspi,

	uint8_t *miso_ddr,
	uint8_t *miso_pinx,
	uint8_t  miso_pin,

	uint8_t *mosi_ddr,
	uint8_t *mosi_port,
	uint8_t  mosi_pin,

	uint8_t *clk_ddr,
	uint8_t *clk_port,
	uint8_t  clk_pin,

	uint8_t  spi_mode,
	bool     data_order
)
{
	(*softspi).miso_ddr    = miso_ddr;
	(*softspi).miso_pinx   = miso_pinx;
	(*softspi).miso_pin    = miso_pin;
	
	(*softspi).mosi_ddr    = mosi_ddr;
	(*softspi).mosi_port   = mosi_port;
	(*softspi).mosi_pin    = mosi_pin;
	
	(*softspi).clk_ddr     = clk_ddr;
	(*softspi).clk_port    = clk_port;
	(*softspi).clk_pin     = clk_pin;
	
	(*softspi).mode        = spi_mode;
	(*softspi).data_order  = data_order;
}

void SOFTSPI_Set_Target_Object(SOFTSPI_t *softspi)
{
	*(softspi->miso_ddr) &= ~(1 << softspi->miso_pin);
	*(softspi->mosi_ddr) |=  (1 << softspi->mosi_pin);
	*(softspi->clk_ddr)  |=  (1 << softspi->clk_pin);
	
	if (softspi->mode == SOFTSPI_MODE_0 || softspi->mode == SOFTSPI_MODE_1)
	{
		*(softspi->clk_port) &= ~(1 << softspi->clk_pin);
	}
	else
	{
		*(softspi->clk_port) |=  (1 << softspi->clk_pin);
	}
	
	target_softspi_interface_object = softspi;
}

SOFTSPI_t *SOFTSPI_Get_Target_Object()
{
	return target_softspi_interface_object;
}



// ===============================================================================



static inline void _SOFTSPI_CLK_Set_High()
{
	*(target_softspi_interface_object->clk_port) |= (1 << target_softspi_interface_object->clk_pin);
}

static inline void _SOFTSPI_CLK_Set_Low()
{
	*(target_softspi_interface_object->clk_port) &= ~(1 << target_softspi_interface_object->clk_pin);
}

static inline void _SOFTSPI_MOSI_Set_High()
{
	*(target_softspi_interface_object->mosi_port) |= (1 << target_softspi_interface_object->mosi_pin);
}

static inline void _SOFTSPI_MOSI_Set_Low()
{
	*(target_softspi_interface_object->mosi_port) &= ~(1 << target_softspi_interface_object->mosi_pin);
}

static inline uint8_t _SOFTSPI_MISO_Get()
{
	return *(target_softspi_interface_object->miso_pinx) & (1 << target_softspi_interface_object->miso_pin);
}

// ===============================================================================

void SOFTSPI_Send_Byte(uint8_t byte)
{
	const uint8_t target_softspi_data_order = target_softspi_interface_object->data_order;
	const uint8_t target_softspi_mode       = target_softspi_interface_object->mode;
	
	if (target_softspi_data_order == SOFTSPI_DATA_IS_ORDER_HIGHEST_BIT)
	{
		for (int8_t i = 7; i >= 0; --i)
		{
			switch (target_softspi_mode)
			{
				case SOFTSPI_MODE_0:
				
				if (byte & (1 << i))
				{
					_SOFTSPI_MOSI_Set_High();
				}
				else
				{
					_SOFTSPI_MOSI_Set_Low();
				}
				
				_SOFTSPI_CLK_Set_High();
				_SOFTSPI_CLK_Set_Low();
				
				break;
				
				case SOFTSPI_MODE_1:
				
				_SOFTSPI_CLK_Set_High();
				
				if (byte & (1 << i))
				{
					_SOFTSPI_MOSI_Set_High();
				}
				else
				{
					_SOFTSPI_MOSI_Set_Low();
				}
				
				_SOFTSPI_CLK_Set_Low();
				
				break;
				
				case SOFTSPI_MODE_2:
				
				if (byte & (1 << i))
				{
					_SOFTSPI_MOSI_Set_High();
				}
				else
				{
					_SOFTSPI_MOSI_Set_Low();
				}
				
				_SOFTSPI_CLK_Set_Low();
				_SOFTSPI_CLK_Set_High();
				
				break;
				
				case SOFTSPI_MODE_3:
				
				_SOFTSPI_CLK_Set_Low();
				
				if (byte & (1 << i))
				{
					_SOFTSPI_MOSI_Set_High();
				}
				else
				{
					_SOFTSPI_MOSI_Set_Low();
				}
				
				_SOFTSPI_CLK_Set_High();
				
				break;
				
				default: break;
			}
		}
	}
	else
	{
		for (int8_t i = 0; i < 8; ++i)
		{
			switch (target_softspi_mode)
			{
				case SOFTSPI_MODE_0:
				
				if (byte & (1 << i))
				{
					_SOFTSPI_MOSI_Set_High();
				}
				else
				{
					_SOFTSPI_MOSI_Set_Low();
				}
				
				_SOFTSPI_CLK_Set_High();
				_SOFTSPI_CLK_Set_Low();
				
				break;
				
				case SOFTSPI_MODE_1:
				
				_SOFTSPI_CLK_Set_High();
				
				if (byte & (1 << i))
				{
					_SOFTSPI_MOSI_Set_High();
				}
				else
				{
					_SOFTSPI_MOSI_Set_Low();
				}
				
				_SOFTSPI_CLK_Set_Low();
				
				break;
				
				case SOFTSPI_MODE_2:
				
				if (byte & (1 << i))
				{
					_SOFTSPI_MOSI_Set_High();
				}
				else
				{
					_SOFTSPI_MOSI_Set_Low();
				}
				
				_SOFTSPI_CLK_Set_Low();
				_SOFTSPI_CLK_Set_High();
				
				break;
				
				case SOFTSPI_MODE_3:
				
				_SOFTSPI_CLK_Set_Low();
				
				if (byte & (1 << i))
				{
					_SOFTSPI_MOSI_Set_High();
				}
				else
				{
					_SOFTSPI_MOSI_Set_Low();
				}
				
				_SOFTSPI_CLK_Set_High();
				
				break;
				
				default: break;
			}
		}
	}
}

void SOFTSPI_Send_Data(void* data, uint16_t data_size)
{
	for (uint16_t i = 0; i < data_size; ++i)
	{
		SOFTSPI_Send_Byte(((uint8_t*)data)[i]);
	}
}

// ===============================================================================

uint8_t SOFTSPI_Get_Byte()
{
	uint8_t data = 0x00;
	
	const uint8_t target_softspi_data_order = target_softspi_interface_object->data_order;
	const uint8_t target_softspi_mode       = target_softspi_interface_object->mode;
	
	
	if (target_softspi_data_order == SOFTSPI_DATA_IS_ORDER_HIGHEST_BIT)
	{
		for (int8_t i = 7; i >= 0; --i)
		{
			switch (target_softspi_mode)
			{
				case SOFTSPI_MODE_0:
				
				if (_SOFTSPI_MISO_Get())
				{
					data |= (1 << i);
				}
				
				_SOFTSPI_CLK_Set_High();
				_SOFTSPI_CLK_Set_Low();
				
				break;
				
				case SOFTSPI_MODE_1:
				
				_SOFTSPI_CLK_Set_High();
				
				if (_SOFTSPI_MISO_Get())
				{
					data |= (1 << i);
				}
				
				_SOFTSPI_CLK_Set_Low();
				
				break;
				
				case SOFTSPI_MODE_2:
				
				if (_SOFTSPI_MISO_Get())
				{
					data |= (1 << i);
				}
				
				_SOFTSPI_CLK_Set_Low();
				_SOFTSPI_CLK_Set_High();
				
				break;
				
				case SOFTSPI_MODE_3:
				
				_SOFTSPI_CLK_Set_Low();
				
				if (_SOFTSPI_MISO_Get())
				{
					data |= (1 << i);
				}
				
				_SOFTSPI_CLK_Set_High();
				
				break;
				
				default: break;
			}
		}
	}
	else
	{
		for (int8_t i = 0; i < 8; ++i)
		{
			switch (target_softspi_mode)
			{
				case SOFTSPI_MODE_0:
				
				if (_SOFTSPI_MISO_Get())
				{
					data |= (1 << i);
				}
				
				_SOFTSPI_CLK_Set_High();
				_SOFTSPI_CLK_Set_Low();
				
				break;
				
				case SOFTSPI_MODE_1:
				
				_SOFTSPI_CLK_Set_High();
				
				if (_SOFTSPI_MISO_Get())
				{
					data |= (1 << i);
				}
				
				_SOFTSPI_CLK_Set_Low();
				
				break;
				
				case SOFTSPI_MODE_2:
				
				if (_SOFTSPI_MISO_Get())
				{
					data |= (1 << i);
				}
				
				_SOFTSPI_CLK_Set_Low();
				_SOFTSPI_CLK_Set_High();
				
				break;
				
				case SOFTSPI_MODE_3:
				
				_SOFTSPI_CLK_Set_Low();
				
				if (_SOFTSPI_MISO_Get())
				{
					data |= (1 << i);
				}
				
				_SOFTSPI_CLK_Set_High();
				
				break;
				
				default: break;
			}
		}
	}
	
	return data;
}


void *SOFTSPI_Get_Data(void* data, uint16_t data_size)
{
	for (uint16_t j = 0; j < data_size; ++j)
	{
		((uint8_t*)data)[j] = SOFTSPI_Get_Byte();
	}
	
	return data;
}


#endif // ===============================================================================


static void (*_cs_set_active)()   = NULL;
static void (*_cs_set_inactive)() = NULL;

void SOFTSPI_Set_CS_Callback_Functions(void (*cs_active_callback)(), void (*cs_inactive_callback)())
{
	_cs_set_active   = cs_active_callback;
	_cs_set_inactive = cs_inactive_callback;
}

void SOFTSPI_CS_Set_Active()
{
	if (_cs_set_active != NULL)
	{
		_cs_set_active();
	}
}

void SOFTSPI_CS_Set_Inactive()
{
	if (_cs_set_inactive != NULL)
	{
		_cs_set_inactive();
	}
}




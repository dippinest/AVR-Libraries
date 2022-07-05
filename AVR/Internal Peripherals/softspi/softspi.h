
#ifndef SOFTSPI_H_
#define SOFTSPI_H_

#include <avr/io.h>
#include <stdlib.h>
#include <stdbool.h>

#include "softspi_configuration.h"

#define SOFTSPI_DATA_IS_ORDER_HIGHEST_BIT false
#define SOFTSPI_DATA_IS_ORDER_LOWEST_BIT  true

#define SOFTSPI_MODE_0  0 // CPOL = 0; CPHA = 0
#define SOFTSPI_MODE_1  1 // CPOL = 0; CPHA = 1
#define SOFTSPI_MODE_2  2 // CPOL = 1; CPHA = 0
#define SOFTSPI_MODE_3  3 // CPOL = 1; CPHA = 1

// ===============================================================================

#define _SOFTSPI_CLK_SET_HIGH (SOFTSPI_CLK_PORT |=  (1 << SOFTSPI_CLK_PIN))
#define _SOFTSPI_CLK_SET_LOW  (SOFTSPI_CLK_PORT &= ~(1 << SOFTSPI_CLK_PIN))

#define _SOFTSPI_MOSI_SET_HIGH (SOFTSPI_MOSI_PORT |=  (1 << SOFTSPI_MOSI_PIN))
#define _SOFTSPI_MOSI_SET_LOW  (SOFTSPI_MOSI_PORT &= ~(1 << SOFTSPI_MOSI_PIN))

#define _SOFTSPI_MISO_GET (SOFTSPI_MISO_PINX & (1 << SOFTSPI_MISO_PIN))

// ===============================================================================

inline void _SOFTSPI_Mode0_Set_Bit(bool bit)
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

inline void _SOFTSPI_Mode1_Set_Bit(bool bit)
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

inline void _SOFTSPI_Mode2_Set_Bit(bool bit)
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

inline void _SOFTSPI_Mode3_Set_Bit(bool bit)
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

// ===============================================================================

inline bool _SOFTSPI_Mode0_Get_Bit()
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

inline bool _SOFTSPI_Mode1_Get_Bit()
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

inline bool _SOFTSPI_Mode2_Get_Bit()
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

inline bool _SOFTSPI_Mode3_Get_Bit()
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

// ===============================================================================

void SOFTSPI_Initialize();

// ===============================================================================

void SOFTSPI_Send_Byte(uint8_t byte);

void SOFTSPI_Send_Data(void* data, uint16_t data_size);

uint8_t SOFTSPI_Get_Byte();

// ===============================================================================

void SOFTSPI_Set_CS_CallBack_Functions(void (*cs_on_callback)(), void (*cs_off_callback)());

void SOFTSPI_Call_CS_ON();

void SOFTSPI_Call_CS_OFF();


#endif



// ===============================================================================
//
// Библиотека для работы с внутренним модулем SPI
//
// -------------------------------------------------------------------------------
//
// Library for working with the internal SPI module
//
// ===============================================================================


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "spi_configuration.h"

#define SPI_COLLISION_STATUS_ERROR    true
#define SPI_COLLISION_STATUS_NOERROR  false

#define SPI_SPEED_FCPU_DIV_2    0b100
#define SPI_SPEED_FCPU_DIV_4    0b000
#define SPI_SPEED_FCPU_DIV_8    0b101
#define SPI_SPEED_FCPU_DIV_16   0b001
#define SPI_SPEED_FCPU_DIV_32   0b110
#define SPI_SPEED_FCPU_DIV_64   0b111
#define SPI_SPEED_FCPU_DIV_128  0b011

#define SPI_DATA_IS_ORDER_HIGHEST_BIT         false
#define SPI_DATA_IS_ORDER_LOWEST_BIT          true

#define SPI_DEV_IS_MASTER                     true
#define SPI_DEV_IS_SLAVE                      false

#define SPI_MODE_0  0 // CPOL = 0; CPHA = 0
#define SPI_MODE_1  1 // CPOL = 0; CPHA = 1
#define SPI_MODE_2  2 // CPOL = 1; CPHA = 0
#define SPI_MODE_3  3 // CPOL = 1; CPHA = 1


// ===============================================================================


inline void SPI_Set_Enable(bool is_enable)
{
	if (is_enable)
	{
		SPCR |=  (1 << SPE);
	}
	else
	{
		SPCR &= ~(1 << SPE);
	}
}

inline void SPI_Set_Speed(uint8_t speed_macros)
{
	if (speed_macros & 0b100)
	{
		SPSR |= (1 << SPI2X);
	}
	else
	{
		SPSR &= ~(1 << SPI2X);
	}
	
	if (speed_macros & 0b10)
	{
		SPCR |= (1 << SPR1);
	}
	else
	{
		SPCR &= ~(1 << SPR1);
	}
	
	if (speed_macros & 0b1)
	{
		SPCR |= (1 << SPR0);
	}
	else
	{
		SPCR &= ~(1 << SPR0);
	}
}

inline void SPI_Set_Interrupt_Enable(bool is_enable)
{
	if (is_enable)
	{
		SPCR |=  (1 << SPIE);
	}
	else
	{
		SPCR &= ~(1 << SPIE);
	}
}

inline void SPI_Set_Data_Order(bool spi_data_order)
{
	if (spi_data_order)
	{
		SPCR |=  (1 << DORD);
	}
	else
	{
		SPCR &= ~(1 << DORD);
	}
}

inline void SPI_Set_MCU_Mode(bool is_master)
{
	if (is_master)
	{
		SPCR       |=  (1 << MSTR);
		SPI_SS_DDR |= (1 << SPI_SS_PIN);
	}
	else
	{
		SPCR       &= ~(1 << MSTR);
		SPI_SS_DDR &= ~(1 << SPI_SS_PIN);
	}
}

inline void SPI_Set_Mode(uint8_t spi_dev_mode)
{
	if (spi_dev_mode & 0b10)
	{
		SPCR |=  (1 << CPOL);
	}
	else
	{
		SPCR &= ~(1 << CPOL);
	}
	
	if (spi_dev_mode & 0b1)
	{
		SPCR |=  (1 << CPHA);
	}
	else
	{
		SPCR &= ~(1 << CPHA);
	}
}


// ===============================================================================


inline bool SPI_Is_Enable()
{
	if (SPCR & (1 << SPE))
	{
		return true;
	}
	
	return false;
}

inline uint8_t SPI_Get_Speed()
{
	uint8_t speed_macros = 0;
	
	if (SPSR & (1 << SPI2X))
	{
		speed_macros |= 0b100;
	}
	
	if (SPSR & (1 << SPR1))
	{
		speed_macros |= 0b10;
	}
	
	if (SPSR & (1 << SPR0))
	{
		speed_macros |= 0b1;
	}
	
	return speed_macros;
}

inline bool SPI_Interrupt_Is_Enable()
{
	if (SPCR & (1 << SPIE))
	{
		return true;
	}
	
	return false;
}

inline bool SPI_Get_Data_Order()
{
	if (SPCR & (1 << DORD))
	{
		return SPI_DATA_IS_ORDER_LOWEST_BIT;
	}
	
	return SPI_DATA_IS_ORDER_HIGHEST_BIT;
}

inline bool SPI_Get_MCU_Mode()
{
	if (SPCR & (1 << MSTR))
	{
		return SPI_DEV_IS_MASTER;
	}
	
	return SPI_DEV_IS_SLAVE;
}

inline uint8_t SPI_Get_Mode()
{
	uint8_t spi_dev_mode = 0;
	
	if (SPCR & (1 << CPOL))
	{
		spi_dev_mode |= 0b10;
	}
	
	if (SPCR &= (1 << CPHA))
	{
		spi_dev_mode |= 0b1;
	}
	
	return spi_dev_mode;
}


// ===============================================================================


inline void SPI_Initialize(bool spi_is_enable, bool is_master, uint8_t spi_dev_mode, uint8_t speed_macros)
{
	SPI_MOSI_DDR  |=  (1 << SPI_MOSI_PIN);
	SPI_MISO_DDR  |=  (1 << SPI_MISO_PIN);
	SPI_SCK_DDR   |=  (1 << SPI_SCK_PIN);
	
	SPI_MOSI_PORT &= ~(1 << SPI_MOSI_PIN);
	SPI_MISO_PORT &= ~(1 << SPI_MISO_PIN);
	
	SPI_Set_MCU_Mode(is_master);
	SPI_Set_Speed(speed_macros);
	SPI_Set_Enable(spi_is_enable);
	SPI_Set_Mode(spi_dev_mode);
	
	if (spi_dev_mode == SPI_MODE_0 || spi_dev_mode == SPI_MODE_1)
	{
		SPI_SCK_PORT &= ~(1 << SPI_SCK_PIN);
	}
	else
	{
		SPI_SCK_PORT |=  (1 << SPI_SCK_PIN);
	}
}


// ===============================================================================


void SPI_Send_Byte(uint8_t byte);

void SPI_Send_Data(void* data, uint16_t data_size);

uint8_t SPI_Get_Byte(uint8_t data);


// ===============================================================================


void SPI_Set_CS_CallBack_Functions(void (*cs_high_callback)(), void (*cs_low_callback)());

void SPI_Set_CS_High();

void SPI_Set_CS_Low();

#endif




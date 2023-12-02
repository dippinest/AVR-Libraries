

// ===============================================================================
//
// Библиотека для работы с программным SPI. Библиотека позволяет работать
// как с одиночным программным модулем SPI, так и с их множеством (это настраивается
// в файле softspi_configuration.h)
//
// -------------------------------------------------------------------------------
//
// Library for working with software SPI. The library allows you to work with
// a single SPI software module, as well as with many of them (this is configured
// in the softspi_configuration.h file)
//
// ===============================================================================


#ifndef SOFTSPI_H_
#define SOFTSPI_H_

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdbool.h>

#include "softspi_configuration.h"

#define SOFTSPI_DATA_IS_ORDER_HIGHEST_BIT false
#define SOFTSPI_DATA_IS_ORDER_LOWEST_BIT  true

#define SOFTSPI_MODE_0  0 // CPOL = 0; CPHA = 0
#define SOFTSPI_MODE_1  1 // CPOL = 0; CPHA = 1
#define SOFTSPI_MODE_2  2 // CPOL = 1; CPHA = 0
#define SOFTSPI_MODE_3  3 // CPOL = 1; CPHA = 1


#ifndef SOFTSPI_USE_MULTIPLE_INTERFACE


#define _SOFTSPI_CLK_SET_HIGH  (SOFTSPI_CLK_PORT |=  (1 << SOFTSPI_CLK_PIN))
#define _SOFTSPI_CLK_SET_LOW   (SOFTSPI_CLK_PORT &= ~(1 << SOFTSPI_CLK_PIN))

#define _SOFTSPI_MOSI_SET_HIGH (SOFTSPI_MOSI_PORT |=  (1 << SOFTSPI_MOSI_PIN))
#define _SOFTSPI_MOSI_SET_LOW  (SOFTSPI_MOSI_PORT &= ~(1 << SOFTSPI_MOSI_PIN))

#define _SOFTSPI_MISO_GET (SOFTSPI_MISO_PINX & (1 << SOFTSPI_MISO_PIN))


// ===============================================================================


void _SOFTSPI_Mode0_Set_Bit(bool bit);

void _SOFTSPI_Mode1_Set_Bit(bool bit);

void _SOFTSPI_Mode2_Set_Bit(bool bit);

void _SOFTSPI_Mode3_Set_Bit(bool bit);


// ===============================================================================


bool _SOFTSPI_Mode0_Get_Bit();

bool _SOFTSPI_Mode1_Get_Bit();

bool _SOFTSPI_Mode2_Get_Bit();

bool _SOFTSPI_Mode3_Get_Bit();

void SOFTSPI_Initialize();

void SOFTSPI_Send_Byte(uint8_t byte);

void SOFTSPI_Send_Data(void* data, uint16_t data_size);

uint8_t SOFTSPI_Get_Byte();

void *SOFTSPI_Get_Data(void* data, uint16_t data_size);


#else // ===============================================================================


#ifndef T
#define T(P) ((uint8_t*)&P)
#endif


typedef struct
{
	uint8_t *miso_ddr;
	uint8_t *miso_pinx;
	uint8_t  miso_pin;
	
	uint8_t *mosi_ddr;
	uint8_t *mosi_port;
	uint8_t  mosi_pin;
	
	uint8_t *clk_ddr;
	uint8_t *clk_port;
	uint8_t  clk_pin;
	
	uint8_t  mode;
	bool     data_order;
	
} SOFTSPI_t;


// ===============================================================================


SOFTSPI_t SOFTSPI_Get_Interface_Object(

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
);


void SOFTSPI_Set_Target_Interface_Object(SOFTSPI_t *spi_interface);

SOFTSPI_t *SOFTSPI_Get_Target_Interface_Object();


// ===============================================================================


void SOFTSPI_Send_Byte(uint8_t byte);

void SOFTSPI_Send_Data(void* data, uint16_t data_size);

uint8_t SOFTSPI_Get_Byte();

void *SOFTSPI_Get_Data(void* data, uint16_t data_size);


#endif // ===============================================================================


void SOFTSPI_Set_CS_CallBack_Functions(void (*cs_on_callback)(), void (*cs_off_callback)());

void SOFTSPI_Call_CS_ON();

void SOFTSPI_Call_CS_OFF();


#endif




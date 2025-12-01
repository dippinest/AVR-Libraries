



// ===============================================================================
//
// Библиотека для работы с программным I2C. Библиотека позволяет работать
// как с одиночным программным модулем I2C, так и с их множеством (это настраивается
// в файле softi2c_configuration.h)
//
// -------------------------------------------------------------------------------
//
// Library for working with software I2C. The library allows you to work with
// a single I2C software module, as well as with many of them (this is configured
// in the softi2c_configuration.h file)
//
// ===============================================================================


#ifndef SOFTI2C_H_
#define SOFTI2C_H_

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdbool.h>

#include "softi2c_configuration.h"

#ifndef ACK
#define ACK true
#endif

#ifndef NACK
#define NACK false
#endif


#ifndef SOFTI2C_USE_MULTIPLE_INTERFACE

#define SOFTI2C_DELAY (_delay_loop_2(SOTFI2C_CLOCK_DELAY))


#define SOTFI2C_SDA_SET_LOW	  SOTFI2C_SDA_DDR |=  (1 << SOTFI2C_SDA_PIN)
#define SOTFI2C_SDA_SET_HIGH  SOTFI2C_SDA_DDR &= ~(1 << SOTFI2C_SDA_PIN)

#define SOTFI2C_SCL_SET_LOW	  SOTFI2C_SCL_DDR |=  (1 << SOTFI2C_SCL_PIN)
#define SOTFI2C_SCL_SET_HIGH  SOTFI2C_SCL_DDR &= ~(1 << SOTFI2C_SCL_PIN)


// ===============================================================================


void SOFTI2C_Initialize();

void SOFTI2C_Start();

void SOFTI2C_Stop();

void SOFTI2C_Restart();

uint8_t SOFTI2C_Send_Byte(uint8_t data);

void SOFTI2C_Read_Byte(uint8_t *data, bool ack);


#else // ===============================================================================


#ifndef T
#define T(P) ((uint8_t*)&P)
#endif


typedef struct
{
	volatile uint8_t *scl_ddr;
	volatile uint8_t *scl_pinx;
	volatile uint8_t *scl_port;

	uint8_t  scl_pin;


	volatile uint8_t *sda_ddr;
	volatile uint8_t *sda_pinx;
	volatile uint8_t *sda_port;

	uint8_t  sda_pin;


	uint8_t  clock_delay;
	
} SOFTI2C_t;


// ===============================================================================


SOFTI2C_t SOFTI2C_Create_Object(

uint8_t *scl_ddr,
uint8_t *scl_pinx,
uint8_t *scl_port,
uint8_t  scl_pin,

uint8_t *sda_ddr,
uint8_t *sda_pinx,
uint8_t *sda_port,
uint8_t  sda_pin,

uint8_t  clock_delay
);

void SOFTI2C_Set_Target_Object(SOFTI2C_t *softi2c_interface);

SOFTI2C_t *SOFTI2C_Get_Target_Object();

void SOFTI2C_Start();

void SOFTI2C_Stop();

void SOFTI2C_Restart();

uint8_t SOFTI2C_Send_Byte(uint8_t data);

void SOFTI2C_Read_Byte(uint8_t *data, bool ack);


#endif


#endif




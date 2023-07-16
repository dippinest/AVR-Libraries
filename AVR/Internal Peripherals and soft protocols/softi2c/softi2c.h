
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

#define SOTFI2C_SDA_SET_LOW	  SOTFI2C_SDA_PIN_DDR |=  (1 << SOTFI2C_SDA_PIN)
#define SOTFI2C_SDA_SET_HIGH  SOTFI2C_SDA_PIN_DDR &= ~(1 << SOTFI2C_SDA_PIN)

#define SOTFI2C_SCL_SET_LOW	  SOTFI2C_SCL_PIN_DDR |=  (1 << SOTFI2C_SCL_PIN)
#define SOTFI2C_SCL_SET_HIGH  SOTFI2C_SCL_PIN_DDR &= ~(1 << SOTFI2C_SCL_PIN)

// ===============================================================================

void SOFTI2C_Initialize();

void SOFTI2C_Start();

void SOFTI2C_Stop();

void SOFTI2C_Restart();

uint8_t SOFTI2C_Send_Byte(uint8_t data);

void SOFTI2C_Read_Byte(uint8_t *data, bool ack);

#else // ===============================================================================

#ifndef _T

#define _T(P) ((uint8_t*)&P)

#endif

typedef struct
{
	uint8_t *softi2c_scl_ddr;
	uint8_t *softi2c_scl_pinx;
	uint8_t *softi2c_scl_port;
	uint8_t  softi2c_scl_pin;
	
	uint8_t *softi2c_sda_ddr;
	uint8_t *softi2c_sda_pinx;
	uint8_t *softi2c_sda_port;
	uint8_t  softi2c_sda_pin;
	
	uint8_t  softi2c_clock_delay;
	
} SOFTI2C_t;

// ===============================================================================

SOFTI2C_t SOFTI2C_Get_Interface_Object(

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

void SOFTI2C_Set_Target_Interface_Object(SOFTI2C_t *softi2c_interface);

SOFTI2C_t *SOFTI2C_Get_Target_Interface_Object();

void SOFTI2C_Start();

void SOFTI2C_Stop();

void SOFTI2C_Restart();

uint8_t SOFTI2C_Send_Byte(uint8_t data);

void SOFTI2C_Read_Byte(uint8_t *data, bool ack);

#endif


#endif

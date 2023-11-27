

// ===============================================================================
//
// Библиотека для работы с программным 1-Wire. Библиотека позволяет работать
// как с одиночным программным модулем 1-Wire, так и с их множеством (это настраивается
// в файле onewire_configuration.h)
//
// -------------------------------------------------------------------------------
//
// Library for working with software 1-Wire. The library allows you to work with
// a single 1-Wire software module, as well as with many of them (this is configured
// in the onewire_configuration.h file)
//
// ===============================================================================


#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include <stdlib.h>
#include <stdbool.h>

#include "onewire_configuration.h"


#define ONEWIRE_DEVICES_WAS_FOUND 0
#define ONEWIRE_NO_DEVICES_FOUND  1



#ifndef ONEWIRE_USE_MULTIPLE_INTERFACE


inline void ONEWIRE_Set_Low()
{
	ONEWIRE_DDR |= (1 << ONEWIRE_PIN);
}

inline void ONEWIRE_Set_High()
{
	ONEWIRE_DDR &= ~(1 << ONEWIRE_PIN);
}

inline uint8_t ONEWIRE_Get_Level()
{
	return ONEWIRE_PINX & (1 << ONEWIRE_PIN);
}


#else // ===============================================================================


#ifndef T
#define T(P) ((uint8_t*)&P)
#endif


typedef struct
{
	uint8_t *data_ddr;
	uint8_t *data_pinx;
	uint8_t  data_pin;
	
} ONEWIRE_t;



ONEWIRE_t ONEWIRE_Get_Interface_Object(

	uint8_t *data_ddr,
	uint8_t *data_pinx,
	uint8_t  data_pin
);

void ONEWIRE_Set_Target_Interface_Object(ONEWIRE_t *onewire_interface);

volatile ONEWIRE_t *ONEWIRE_Get_Target_Interface_Object();


// ===============================================================================


void ONEWIRE_Set_Low();

void ONEWIRE_Set_High();

uint8_t ONEWIRE_Get_Level();


#endif // ===============================================================================


uint8_t ONEWIRE_Reset();

void ONEWIRE_Send_Bit(uint8_t bit);

void ONEWIRE_Send_Byte(uint8_t data);

uint8_t ONEWIRE_Read_Bit();

uint8_t ONEWIRE_Read_Byte();


// ===============================================================================


void ONEWIRE_Apply_By_Unique_ROM_ID(uint8_t *_8byte_unique_rom_id_buf);

uint8_t ONEWIRE_Get_Unique_ROM_ID(uint8_t *_8byte_unique_rom_id_buf);

uint8_t ONEWIRE_Get_CRC8(void *data, const uint8_t data_size);

bool ONEWIRE_Check_CRC8_From_Unique_ROM_ID(uint8_t *_8byte_unique_rom_id_buf);


#endif



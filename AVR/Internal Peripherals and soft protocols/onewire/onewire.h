
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

// ===============================================================================

inline void _ONEWIRE_Set_Low()
{
	ONEWIRE_DDR |= (1 << ONEWIRE_PIN);
}

inline void _ONEWIRE_Set_High()
{
	ONEWIRE_DDR &= ~(1 << ONEWIRE_PIN);
}

inline uint8_t _ONEWIRE_Get_Level()
{
	return ONEWIRE_PINX & (1 << ONEWIRE_PIN);
}

// ===============================================================================

uint8_t ONEWIRE_Reset();

// ===============================================================================

void ONEWIRE_Send_Bit(uint8_t bit);

void ONEWIRE_Send_Byte(uint8_t data);

// ===============================================================================

uint8_t ONEWIRE_Read_Bit();

uint8_t ONEWIRE_Read_Byte();

// ===============================================================================

void ONEWIRE_Apply_By_Unique_ROM_ID(uint8_t *unique_rom_id);

uint8_t ONEWIRE_Get_Unique_ROM_ID(uint8_t *unique_rom_id);

// ===============================================================================

uint8_t ONEWIRE_Get_CRC8(void *data, const uint8_t data_size);

bool ONEWIRE_Check_CRC8_From_Unique_ROM_ID(uint8_t *unique_rom_id);

#endif

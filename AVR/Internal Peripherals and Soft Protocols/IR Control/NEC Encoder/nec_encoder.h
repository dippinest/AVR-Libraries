
// ===============================================================================
//
// Библиотека программного кодера протокола ИК управления NEC.
//
// Данная библиотека генерирует как сами пакеты, так и несущую сигнала.
// Для своей работы библиотека требует 2 аппаратных таймера.
//
// -------------------------------------------------------------------------------
//
// NEC IR Control protocol software encoder library
//
// This library generates both the packets themselves and the signal carrier.
// The library requires 2 hardware timers for its operation.
//
// ===============================================================================


#ifndef NEC_ENCODER_H_
#define NEC_ENCODER_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "nec_encoder_configuration.h"


enum NEC_Encoder_Reception_Status
{
	DISABLE,
	TRANSMITTION_START,
	TRANSMITTION_POSTSTART,
	TRANSMITTION_ADDRESS,
	TRANSMITTION_INV_ADDRESS,
	TRANSMITTION_COMMAND,
	TRANSMITTION_INV_COMMAND,
	TRANSMITTION_REPEAT_SAMPLE,
	TRANSMITTION_REPEAT_TIMEOUT
};

enum NEC_Encoder_Repeatition_Status
{
	NO_REPEAT,
	IDLE_REPEAT,
	RUN_REPEAT
};

#define _NEC_ENCODER_BIT0_TIMEOUT                      1
#define _NEC_ENCODER_BIT1_TIMEOUT                      3
#define _NEC_ENCODER_NUM_OF_START_SAMPLES             16
#define _NEC_ENCODER_NUM_OF_POSTSTART_SAMPLES          8
#define _NEC_ENCODER_NUM_OF_POSTSTART_REPEAT_SAMPLES   4

#define _NEC_ENCODER_MAX_NUM_OF_IDLE_PERIOD_SAMPLES  193


typedef struct
{
	uint8_t addr;
	uint8_t addr_inv;
	uint8_t commmand;
	uint8_t commmand_inv;
	
} NEC_Protocol_Data_t;


// ===============================================================================

void NEC_Encoder_Initialize();

// ===============================================================================

bool NEC_Encoder_Is_Active();

void NEC_Encoder_Set_Disable_Repetition_Transmittion_Packet();

void NEC_Encoder_Stop_Transmittion();

void NEC_Encoder_Wait_Complete_And_Stop_Transmittion();

enum NEC_Encoder_Reception_Status NEC_Encoder_Get_FSM_Status();

// ===============================================================================


void NEC_Encoder_Transmit_Packet(uint8_t address, uint8_t command, bool is_repeating);


#endif







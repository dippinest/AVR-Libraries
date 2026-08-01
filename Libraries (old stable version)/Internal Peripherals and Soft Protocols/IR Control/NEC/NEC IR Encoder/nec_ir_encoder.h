
// ===============================================================================
//
// Библиотека программного кодера протокола ИК управления компании NEC
//
// Данная библиотека генерирует как сами пакеты, так и несущую сигнала.
// Для своей работы библиотека требует 2 аппаратных таймера
//
// -------------------------------------------------------------------------------
//
// NEC's IR Control Protocol Software Encoder Library
//
// This library generates both the packets themselves and the signal carrier.
// The library requires 2 hardware timers for its operation
//
// ===============================================================================


#ifndef NEC_IR_ENCODER_H_
#define NEC_IR_ENCODER_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "nec_ir_encoder_configuration.h"


enum NEC_IR_Encoder_Reception_Status
{
	DISABLE,
	TRANSMITTION_START,
	TRANSMITTION_REPEATING_START,
	TRANSMITTION_POSTSTART,
	TRANSMITTION_ADDRESS_1,
	TRANSMITTION_ADDRESS_2,
	TRANSMITTION_COMMAND_1,
	TRANSMITTION_COMMAND_2,
	TRANSMITTION_REPEAT_SAMPLE,
	TRANSMITTION_REPEAT_TIMEOUT
};

enum NEC_IR_Encoder_Repeatition_Status
{
	NO_REPEAT,
	IDLE_REPEAT,
	RUN_REPEAT
};

#define _NEC_IR_ENCODER_BIT0_TIMEOUT                      1
#define _NEC_IR_ENCODER_BIT1_TIMEOUT                      3
#define _NEC_IR_ENCODER_NUM_OF_START_SAMPLES             16
#define _NEC_IR_ENCODER_NUM_OF_POSTSTART_SAMPLES          8
#define _NEC_IR_ENCODER_NUM_OF_POSTSTART_REPEAT_SAMPLES   4

#define _NEC_IR_ENCODER_MAX_NUM_OF_IDLE_PERIOD_SAMPLES  193


typedef struct
{
	uint8_t addr_1;
	uint8_t addr_2;
	uint8_t commmand_1;
	uint8_t commmand_2;
	
} NEC_IR_Protocol_Data_t;


// ===============================================================================

void NEC_IR_Encoder_Initialize();

// ===============================================================================

bool NEC_IR_Encoder_Is_Active();

void NEC_IR_Encoder_Set_Disable_Repetition_Transmittion_Packet();

void NEC_IR_Encoder_Stop_Transmittion();

void NEC_IR_Encoder_Wait_Complete_And_Stop_Transmittion();

enum NEC_IR_Encoder_Reception_Status NEC_IR_Encoder_Get_FSM_Status();

// ===============================================================================


void NEC_IR_Encoder_Transmit_Standart_Packet(uint8_t addr, uint8_t command, bool is_repeating);

void NEC_IR_Encoder_Transmit_Custom_Packet(const NEC_IR_Protocol_Data_t data, bool is_repeating);


#endif







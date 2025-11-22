
// ===============================================================================
//
// Библиотека программного кодера протокола ИК управления компании Samsung
//
// Данная библиотека генерирует как сами пакеты, так и несущую сигнала.
// Для своей работы библиотека требует 2 аппаратных таймера
//
// -------------------------------------------------------------------------------
//
// Samsung's IR Control Protocol Software Encoder Library
//
// This library generates both the packets themselves and the signal carrier.
// The library requires 2 hardware timers for its operation
//
// ===============================================================================


#ifndef SAMSUNG_IR_ENCODER_H_
#define SAMSUNG_IR_ENCODER_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "samsung_ir_encoder_configuration.h"


enum Samsung_IR_Encoder_Reception_Status
{
	DISABLE,
	TRANSMITTION_START,
	TRANSMITTION_REPEATING_START,
	TRANSMITTION_POSTSTART,
	TRANSMITTION_ADDRESS_1,
	TRANSMITTION_ADDRESS_2,
	TRANSMITTION_COMMAND_1,
	TRANSMITTION_COMMAND_2,
	REPEATING_IDLE_WAIT
};

enum Samsung_IR_Encoder_Repeatition_Status
{
	NO_REPEAT,
	REPEAT_IS_ALLOWED
};

#define _SAMSUNG_IR_ENCODER_BIT0_TIMEOUT                      1
#define _SAMSUNG_IR_ENCODER_BIT1_TIMEOUT                      3
#define _SAMSUNG_IR_ENCODER_NUM_OF_START_SAMPLES              8
#define _SAMSUNG_IR_ENCODER_NUM_OF_POSTSTART_SAMPLES          8

#define _SAMSUNG_IR_ENCODER_MAX_NUM_OF_REPEAT_IDLE_PERIOD_SAMPLES  81


typedef struct
{
	uint8_t addr_1;
	uint8_t addr_2;
	uint8_t commmand_1;
	uint8_t commmand_2;
	
} Samsung_IR_Protocol_Data_t;


// ===============================================================================

void Samsung_IR_Encoder_Initialize();

// ===============================================================================

bool Samsung_IR_Encoder_Is_Active();

void Samsung_IR_Encoder_Set_Disable_Repetition_Transmittion_Packet();

void Samsung_IR_Encoder_Stop_Transmittion();

void Samsung_IR_Encoder_Wait_Complete_And_Stop_Transmittion();

enum Samsung_IR_Encoder_Reception_Status NEC_Encoder_Get_FSM_Status();

// ===============================================================================


void Samsung_IR_Encoder_Transmit_Standart_Packet(uint8_t addr, uint8_t command, bool is_repeating);

void Samsung_IR_Encoder_Transmit_Custom_Packet(const Samsung_IR_Protocol_Data_t data, bool is_repeating);


#endif







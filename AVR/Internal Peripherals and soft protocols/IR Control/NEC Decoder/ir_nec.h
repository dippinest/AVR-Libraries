
// ===============================================================================
//
// Библиотека программного декодера протокола ИК управления NEC
//
// -------------------------------------------------------------------------------
//
// NEC IR Control protocol software decoder library
//
// ===============================================================================


#ifndef IR_NEC_H_
#define IR_NEC_H_


#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "ir_nec_configuration.h"


enum IR_NEC_Reception_Status
{
	NO_RECEPTION,
	RECEPTION_START,
	RECEPTION_POSTSTART_TIMEOUT,
	RECEPTION_ADDRESS,
	RECEPTION_INV_ADDRESS,
	RECEPTION_COMMAND,
	RECEPTION_INV_COMMAND,
	RECEPTION_REPEAT_SAMPLE
};

#define _IR_NEC_INPUT_LEVEL_LOW        false
#define _IR_NEC_INPUT_LEVEL_HIGH       true

#define _IR_NEC_BIT0_TIMEOUT                      4
#define _IR_NEC_BIT1_TIMEOUT                      8
#define _IR_NEC_NUM_OF_START_SAMPLES             32
#define _IR_NEC_NUM_OF_POSTSTART_SAMPLES         16
#define _IR_NEC_NUM_OF_POSTSTART_REPEAT_SAMPLES   8

#define _IR_NEC_MAX_NUM_OF_IDLE_PERIOD_SAMPLES  450


typedef struct
{
	uint8_t addr;
	uint8_t addr_inv;
	uint8_t commmand;
	uint8_t commmand_inv;
	
} IR_NEC_Protocol_t;


// ===============================================================================

void IR_NEC_Initialize(void (*reception_callback_function)(), void (*repeat_reception_callback_function)());


void IR_NEC_Set_Reception_Callback_Function(void (*reception_callback_function)());

void *IR_NEC_Get_Reception_Callback_Function();

void IR_NEC_Set_Repeat_Reception_Callback_Function(void (*repeat_reception_callback_function)());

void *IR_NEC_Get_Repeat_Reception_Callback_Function();

// ===============================================================================


IR_NEC_Protocol_t IR_NEC_Get_Data();

void IR_NEC_Reset();

void IR_NEC_FSM();



#endif







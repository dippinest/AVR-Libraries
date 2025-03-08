
// ===============================================================================
//
// Библиотека программного декодера протокола ИК управления NEC
//
// -------------------------------------------------------------------------------
//
// NEC IR Control protocol software decoder library
//
// ===============================================================================


#ifndef NEC_DECODER_H_
#define NEC_DECODER_H_


#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "nec_decoder_configuration.h"


enum NEC_Decoder_Reception_Status
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

#define _NEC_DECODER_INPUT_LEVEL_LOW        false
#define _NEC_DECODER_INPUT_LEVEL_HIGH       true

#define _NEC_DECODER_BIT0_TIMEOUT                      4
#define _NEC_DECODER_BIT1_TIMEOUT                      8
#define _NEC_DECODER_NUM_OF_START_SAMPLES             32
#define _NEC_DECODER_NUM_OF_POSTSTART_SAMPLES         16
#define _NEC_DECODER_NUM_OF_POSTSTART_REPEAT_SAMPLES   8

#define _NEC_DECODER_MAX_NUM_OF_IDLE_PERIOD_SAMPLES  450


typedef struct
{
	uint8_t addr;
	uint8_t addr_inv;
	uint8_t commmand;
	uint8_t commmand_inv;
	
} NEC_Protocol_Data_t;


// ===============================================================================

void NEC_Decoder_Initialize(void (*reception_callback_function)(), void (*repeat_reception_callback_function)());


void NEC_Decoder_Set_Reception_Callback_Function(void (*reception_callback_function)());

void *NEC_Decoder_Get_Reception_Callback_Function();

void NEC_Decoder_Set_Repeat_Reception_Callback_Function(void (*repeat_reception_callback_function)());

void *NEC_Decoder_Get_Repeat_Reception_Callback_Function();

// ===============================================================================


NEC_Protocol_Data_t NEC_Decoder_Get_Data();

void NEC_Decoder_Reset();



#endif







// ===============================================================================
//
// Библиотека программного декодера протокола ИК управления компании NEC
//
// Данная библиотека позволяет или же принимать принятые данные
// без предварительной проверки. Для своей работы библиотека требует
// одного аппаратного таймера и одного внешнего прерывания EXINT
//
// -------------------------------------------------------------------------------
//
// NEC's IR Control Protocol Software Decoder Library
//
// This library allows you to either accept the received data
// without prior verification. For its operation, the library requires
// one hardware timer and one external EXINT interrupt
//
// ===============================================================================


#ifndef NEC_IR_IR_DECODER_H_
#define NEC_IR_IR_DECODER_H_


#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "nec_ir_decoder_configuration.h"


enum NEC_IR_IR_Decoder_Reception_Status
{
	NO_RECEPTION,
	RECEPTION_START,
	RECEPTION_POSTSTART,
	RECEPTION_ADDRESS_1,
	RECEPTION_ADDRESS_2,
	RECEPTION_COMMAND_1,
	RECEPTION_COMMAND_2,
	RECEPTION_REPEAT_SAMPLE
};

#define _NEC_IR_DECODER_INPUT_LEVEL_LOW        false
#define _NEC_IR_DECODER_INPUT_LEVEL_HIGH       true

#define _NEC_IR_DECODER_BIT0_TIMEOUT                      4
#define _NEC_IR_DECODER_BIT1_TIMEOUT                      8
#define _NEC_IR_DECODER_NUM_OF_START_SAMPLES             32
#define _NEC_IR_DECODER_NUM_OF_POSTSTART_SAMPLES         16
#define _NEC_IR_DECODER_NUM_OF_POSTSTART_REPEAT_SAMPLES   8

#define _NEC_IR_DECODER_MAX_NUM_OF_IDLE_PERIOD_SAMPLES  450


typedef struct
{
	uint8_t addr_1;
	uint8_t addr_2;
	uint8_t command_1;
	uint8_t command_2;
	
} NEC_IR_Protocol_Data_t;


// ===============================================================================

void NEC_IR_Decoder_Initialize(void (*reception_callback_function)(), void (*repeat_reception_callback_function)());


void NEC_IR_Decoder_Set_Reception_Callback_Function(void (*reception_callback_function)());

void *NEC_IR_Decoder_Get_Reception_Callback_Function();

void NEC_IR_Decoder_Set_Repeat_Reception_Callback_Function(void (*repeat_reception_callback_function)());

void *NEC_IR_Decoder_Get_Repeat_Reception_Callback_Function();

// ===============================================================================


NEC_IR_Protocol_Data_t NEC_IR_Decoder_Get_Data();

void NEC_IR_Decoder_Reset();

bool NEC_IR_Check_Package_Integrity_For_Standart_Protocol(const NEC_IR_Protocol_Data_t *nec_ir_data);



#endif





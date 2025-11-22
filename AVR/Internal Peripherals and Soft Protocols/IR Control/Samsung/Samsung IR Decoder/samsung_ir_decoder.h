
// ===============================================================================
//
// Библиотека программного декодера протокола ИК управления компании Samsung
//
// Данная библиотека позволяет или же принимать принятые данные
// без предварительной проверки. Для своей работы библиотека требует
// одного аппаратного таймера и одного внешнего прерывания EXINT
//
// -------------------------------------------------------------------------------
//
// Samsung's IR Control Protocol Software Decoder Library
//
// This library allows you to either accept the received data
// without prior verification. For its operation, the library requires
// one hardware timer and one external EXINT interrupt
//
// ===============================================================================


#ifndef SAMSUNG_IR_DECODER_H_
#define SAMSUNG_IR_DECODER_H_


#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "samsung_ir_decoder_configuration.h"


enum Samsung_IR_Decoder_Reception_Status
{
	IDLE,
	RECEPTION_START,
	RECEPTION_POSTSTART,
	RECEPTION_ADDRESS_1,
	RECEPTION_ADDRESS_2,
	RECEPTION_COMMAND_1,
	RECEPTION_COMMAND_2
};

#define _SAMSUNG_IR_DECODER_INPUT_LEVEL_LOW        false
#define _SAMSUNG_IR_DECODER_INPUT_LEVEL_HIGH       true

#define _SAMSUNG_IR_DECODER_BIT0_TIMEOUT                      4
#define _SAMSUNG_IR_DECODER_BIT1_TIMEOUT                      8
#define _SAMSUNG_IR_DECODER_NUM_OF_START_SAMPLES             16
#define _SAMSUNG_IR_DECODER_NUM_OF_POSTSTART_SAMPLES         16

#define _SAMSUNG_IR_DECODER_MAX_NUM_OF_IDLE_PERIOD_SAMPLES  168


typedef struct
{
	uint8_t addr_1;
	uint8_t addr_2;
	uint8_t commmand_1;
	uint8_t commmand_2;
	
} Samsung_IR_Protocol_Data_t;


// ===============================================================================

void Samsung_IR_Decoder_Initialize(void (*reception_callback_function)());


void Samsung_IR_Decoder_Set_Reception_Callback_Function(void (*reception_callback_function)());

void *Samsung_IR_Decoder_Get_Reception_Callback_Function();

// ===============================================================================


Samsung_IR_Protocol_Data_t Samsung_IR_Decoder_Get_Data();

void Samsung_IR_Decoder_Reset();

bool Samsung_IR_Decoder_Received_Package_Is_Repeated();

bool Samsung_IR_Check_Package_Integrity_For_Standart_Protocol(const Samsung_IR_Protocol_Data_t *samsung_ir_data);



#endif








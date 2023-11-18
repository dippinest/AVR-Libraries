

// ===============================================================================
//
// Библиотека для работы с инкрементальным энкодером, подключенных
// к портам GPIO микроконтроллера.
// Максимальная отслеживаемая скорость вращения энкодера зависит
// исключительно от частоты его опроса, задающейся логикой работы программы.
//
// Библиотека позволяет опрашивать несколько энкодеров независимо.
// Чтобы активировать эту аозможность, раскомментируйте соответствующий дефайн
// в файле конфигурации encoder_configuration.h
//
// -------------------------------------------------------------------------------
//
// Library for working with an incremental encoder connected
// to the GPIO ports of the microcontroller.
// The maximum tracked rotation speed of the encoder depends
// solely on the frequency of its polling, which is set by
// the logic of the program.
//
// The library allows you to poll multiple encoders independently.
// To activate this feature, uncomment the corresponding define
// in the encoder_configuration.h configuration file
//
// ===============================================================================


#ifndef ENCODER_H_
#define ENCODER_H_

#include <avr/io.h>

#include <stdint.h>
#include <stddef.h>

#include "encoder_configuration.h"


#ifndef ENCODER_USE_MULTIPLE_DEVICES

#ifndef _Bit_Is_Set
#define _Bit_Is_Set(port, bit)    ((port & (1 << bit)))
#endif

#ifndef _Bit_Is_Reset
#define _Bit_Is_Reset(port, bit) !((port & (1 << bit)))
#endif



void Encoder_Initialize();

void Encoder_Polling();

// ===============================================================================

void Encoder_Set_Left_Turn_CallBack_Function(void (*callback_function)());

void Encoder_Set_Right_Turn_CallBack_Function(void (*callback_function)());

void *Encoder_Get_Left_Turn_CallBack_Function();

void *Encoder_Get_Right_Turn_CallBack_Function();


#else // ===============================================================================


#ifndef T
#define T(P) ((uint8_t*)&P)
#endif


#ifndef _Bit_Is_Set_P
#define _Bit_Is_Set_P(port, bit)    ((*port) & (1 << bit))
#endif

#ifndef _Bit_Is_Reset_P
#define _Bit_Is_Reset_P(port, bit) !((*port) & (1 << bit))
#endif


typedef struct 
{
	uint8_t *input0_ddr;
	uint8_t *input0_pinx;
	uint8_t  input0_pin;
	
	uint8_t *input1_ddr;
	uint8_t *input1_pinx;
	uint8_t  input1_pin;
	
	void (*_left_turn_callback)();
	void (*_right_turn_callback)();
	
	int8_t   status;
	
} Encoder_t;


Encoder_t Encoder_Get_Device_Object(

	uint8_t *input0_ddr,
	uint8_t *input0_pinx,
	uint8_t  input0_pin,
	
	uint8_t *input1_ddr,
	uint8_t *input1_port,
	uint8_t  input1_pin,

	void (*_left_turn_callback)(),
	void (*_right_turn_callback)()
);

// ===============================================================================

void Encoder_Polling(Encoder_t *encoder);

// ===============================================================================

void Encoder_Set_Left_Turn_CallBack_Function(Encoder_t *encoder, void (*callback_function)());

void Encoder_Set_Right_Turn_CallBack_Function(Encoder_t *encoder, void (*callback_function)());

void *Encoder_Get_Left_Turn_CallBack_Function(Encoder_t *encoder);

void *Encoder_Get_Right_Turn_CallBack_Function(Encoder_t *encoder);

// ===============================================================================


#endif


#endif



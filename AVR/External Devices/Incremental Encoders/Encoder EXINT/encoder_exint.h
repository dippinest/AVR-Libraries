

// ===============================================================================
//
// Библиотека для работы с инкрементальным энкодером.
// Максимальная отслеживаемая скорость вращения энкодера зависит
// исключительно от частоты его опроса, задающейся логикой работы программы.
//
// Библиотека позволяет опрашивать несколько энкодеров независимо.
// Чтобы активировать эту аозможность, раскомментируйте соответствующий дефайн
// в файле конфигурации encoder_configuration.h
//
// -------------------------------------------------------------------------------
//
// Library for working with an incremental encoder.
// The maximum tracked rotation speed of the encoder depends
// solely on the frequency of its polling, which is set by
// the logic of the program.
//
// The library allows you to poll multiple encoders independently.
// To activate this feature, uncomment the corresponding define
// in the encoder_configuration.h configuration file
//
// ===============================================================================


#ifndef ENCODER_EXINT_H_
#define ENCODER_EXINT_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>
#include <stddef.h>

#include "encoder_exint_configuration.h"


#ifndef ENCODER_EXINT_USE_MULTIPLE_DEVICES


void Encoder_EXINT_Initialize();

void Encoder_EXINT_Processing();


// ===============================================================================


void Encoder_EXINT_Set_Left_Turn_CallBack_Function(void (*callback_function)());

void Encoder_EXINT_Set_Right_Turn_CallBack_Function(void (*callback_function)());

void *Encoder_EXINT_Get_Left_Turn_CallBack_Function();

void *Encoder_EXINT_Get_Right_Turn_CallBack_Function();



#else // ===============================================================================



#ifndef T
#define T(P) ((uint8_t*)&P)
#endif


typedef struct
{
	uint8_t *input0_ddr_exint;
	uint8_t *input0_pinx_exint;
	uint8_t  input0_pin_exint;
	
	uint8_t *input1_ddr;
	uint8_t *input1_pinx;
	uint8_t  input1_pin;
	
	void (*_left_turn_callback)();
	void (*_right_turn_callback)();
	
} Encoder_EXINT_t;



// ===============================================================================



Encoder_EXINT_t Encoder_EXINT_Create_Object(

	uint8_t *input0_ddr_exint,
	uint8_t *input0_pinx_exint,
	uint8_t  input0_pin_exint,

	uint8_t *input1_ddr,
	uint8_t *input1_port,
	uint8_t  input1_pin,

	void (*_left_turn_callback)(),
	void (*_right_turn_callback)()
);



// ===============================================================================



void Encoder_EXINT_Processing(Encoder_EXINT_t *encoder);



// ===============================================================================



void Encoder_EXINT_Set_Left_Turn_CallBack_Function(Encoder_EXINT_t *encoder, void (*callback_function)());

void Encoder_EXINT_Set_Right_Turn_CallBack_Function(Encoder_EXINT_t *encoder, void (*callback_function)());

void *Encoder_EXINT_Get_Left_Turn_CallBack_Function(Encoder_EXINT_t *encoder);

void *Encoder_EXINT_Get_Right_Turn_CallBack_Function(Encoder_EXINT_t *encoder);



// ===============================================================================



#endif


#endif



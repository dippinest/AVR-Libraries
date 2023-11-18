

// ===============================================================================
//
// Библиотека для опроса кнопок, подключенных к портам GPIO микроконтроллера
//
// Библиотека позволяет работать с кнопками, подтянутыми как к Vcc
// (плюсу питания), так и к GND (к земле).
//
// Имеется возможность постоянного опроса кнопки, однократного нажатия,
// отпускания кнопки, а также длительного нажатия
//
// -------------------------------------------------------------------------------
//
// Library for polling buttons connected to the GPIO ports of the microcontroller
//
// The library allows you to work with buttons pulled up to Vcc or to GND
//
// It's possible to continuously poll the button, press once,
// release the button, as well as long-term pressing
//
// ===============================================================================


#ifndef BUTTON_H_
#define BUTTON_H_

#include <avr/io.h>

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


#define BUTTON_INPUT_PULLUP   true
#define BUTTON_INPUT_PULLDOWN false


#ifndef T
#define T(P) ((uint8_t*)&P)
#endif


typedef struct
{
	uint8_t *input_ddr;
	uint8_t *input_pinx;
	uint8_t  input_pin;
	
	bool     pull;
	
	uint16_t status;
	
} Button_t;


Button_t Button_Get_Device_Object(

	uint8_t *input_ddr,
	uint8_t *input_pinx,
	uint8_t  input_pin,

	bool     pull
);

// ===============================================================================

bool Button_Is_Pressed(Button_t *button);

void Button_Hold_Polling(Button_t *button, void (*callback_function)());

void Button_Hold_With_Timeout_Polling(Button_t *button, uint16_t press_timeout, void (*callback_function)());

void Button_Pressed_Polling(Button_t *button, void (*callback_function)());

void Button_Pressed_And_Released_Polling(Button_t *button, void (*press_callback_function)(), void (*release_callback_function)());

void Button_Long_Pressed_Polling(Button_t *button, uint16_t press_timeout, void (*callback_function)());


#endif


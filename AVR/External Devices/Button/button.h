

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
// A small library with software delay functions. The functions
// presented in the library are an add-on to the _delay_ms() and
// _delay_us() functions from avr-libc. Unlike these original
// inline functions, the void Delay_Ms and void Delay_Us functions
// of the library allow you to pass a variable as arguments.
//
// The library can be used in simple projects and prototyping,
// where high energy efficiency and speed are not required.
// Otherwise, I do not recommend using this library - in this
// case, use timer interrupts and power-saving functions for
// more efficient operation.
//
// In addition, during the execution of the delay, there is
// a specific possibility of pseudo-parallel execution of a
// separate light operation (for the Delay_Ms function) every
// 1 millisecond, for which there is a corresponding define
// in the delay_configuration.h file. You can see an example
// of the work in the corresponding directory with code examples
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

void Button_Pressed_Polling(Button_t *button, void (*callback_function)());

void Button_Pressed_And_Released_Polling(Button_t *button, void (*press_callback_function)(), void (*release_callback_function)());

void Button_Long_Pressed_Polling(Button_t *button, uint16_t press_duration_counter, void (*callback_function)());


#endif


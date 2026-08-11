

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
// Библиотека не предусматривает обработку дребезга контактов.
// Автор рекомендует аппаратное подавление дребезга контактов
// (с помощью внешней RC цепи или с помощью триггера Шмидта)
//
// UPD: советую рассмотреть возможность использования библиотеки "virtualbutton",
// которая имеет больше возможностей и более оптимизированная представленной
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
// The library does not provide for handling contact bounce.
// The author recommends hardware-based contact bounce suppression
// (using an external RC circuit or a Schmitt trigger)
//
// UPD: I advise you to consider using the virtualbutton library,
// which has more features and is more optimized.
//
// ===============================================================================


#ifndef BUTTON_H_
#define BUTTON_H_

#include <avr/io.h>

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


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
	volatile uint8_t *input_ddr;
	volatile uint8_t *input_pinx;
	
	uint8_t  input_pin;
	
	volatile uint16_t press_counter;
	volatile uint16_t long_press_counter;
	
} Button_t;


void Button_Initialize_Object
(
	Button_t *button,

	uint8_t  *input_ddr,
	uint8_t  *input_pinx,
	uint8_t   input_pin
);



// ===============================================================================



bool Button_PULLUP_Is_Pressed(Button_t *button);

void Button_PULLUP_Hold_Polling(Button_t *button, void (*callback_function)());

void Button_PULLUP_Hold_With_Timeout_Polling(Button_t *button, uint16_t press_timeout, void (*callback_function)());

void Button_PULLUP_Pressed_Polling(Button_t *button, void (*callback_function)());

void Button_PULLUP_Pressed_And_Released_Polling(Button_t *button, void (*press_callback_function)(), void (*release_callback_function)());

void Button_PULLUP_Long_Pressed_Polling(Button_t *button, uint16_t press_timeout, void (*callback_function)());



// ===============================================================================



bool Button_PULLDOWN_Is_Pressed(Button_t *button);

void Button_PULLDOWN_Hold_Polling(Button_t *button, void (*callback_function)());

void Button_PULLDOWN_Hold_With_Timeout_Polling(Button_t *button, uint16_t press_timeout, void (*callback_function)());

void Button_PULLDOWN_Pressed_Polling(Button_t *button, void (*callback_function)());

void Button_PULLDOWN_Pressed_And_Released_Polling(Button_t *button, void (*press_callback_function)(), void (*release_callback_function)());

void Button_PULLDOWN_Long_Pressed_Polling(Button_t *button, uint16_t press_timeout, void (*callback_function)());


#endif



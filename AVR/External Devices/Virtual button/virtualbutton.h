

// ===============================================================================
//
// Библиотека для опроса кнопок
//
// Библиотека позволяет работать с кнопками, подтянутыми как к Vcc
// (плюсу питания), так и к GND (к земле). В отличии от библиотеки
// "button.h", кнопки можно подключать не только к портам GPIO, но и отслеживать
// их состояние косвенно (когда кнопки подключены, например, к сдвиговому регистру 74HC165)
//
// Имеется возможность постоянного опроса кнопки, однократного нажатия,
// отпускания кнопки, а также длительного нажатия
//
// -------------------------------------------------------------------------------
//
// Library for polling buttons connected to the GPIO ports of the microcontroller
//
// The library allows you to work with buttons pulled up to Vcc or to GND.
// Unlike the "button.h" library, buttons can be connected not only to GPIO ports,
// but also to monitor their status indirectly (when buttons are connected,
// for example, to the 74HC165 shift register)
//
// It's possible to continuously poll the button, press once,
// release the button, as well as long-term pressing
//
// ===============================================================================


#ifndef VIRTUALBUTTON_H_
#define VIRTUALBUTTON_H_


#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


#ifndef _Bit_Is_Set
#define _Bit_Is_Set(port, bit)    (port & (1 << bit))
#endif

#ifndef _Bit_Is_Reset
#define _Bit_Is_Reset(port, bit) !(port & (1 << bit))
#endif


#define VIRTUALBUTTON_INPUT_LOGICAL_LEVEL_HIGH  true
#define VIRTUALBUTTON_INPUT_LOGICAL_LEVEL_LOW   false


#ifndef T
#define T(P) ((uint8_t*)&P)
#endif


typedef struct
{
	uint8_t* virtual_port;
	uint8_t  virtual_pin;

	bool     pull;

	uint16_t status;

} VirtualButton_t;


VirtualButton_t VirtualButton_Create_Object(

	uint8_t* virtual_port,
	uint8_t  virtual_pin,

	bool     pull
);

// ===============================================================================


bool VirtualButton_Is_Pressed(VirtualButton_t* vbutton);

void VirtualButton_Hold_Polling(VirtualButton_t* vbutton, void (*callback_function)());

void VirtualButton_Hold_With_Timeout_Polling(VirtualButton_t* vbutton, uint16_t press_timeout, void (*callback_function)());

void VirtualButton_Pressed_Polling(VirtualButton_t* vbutton, void (*callback_function)());

void VirtualButton_Pressed_And_Released_Polling(VirtualButton_t* vbutton, void (*press_callback_function)(), void (*release_callback_function)());

void VirtualButton_Long_Pressed_Polling(VirtualButton_t* vbutton, uint16_t press_timeout, void (*callback_function)());


#endif






// ===============================================================================
//
// Небольшая библиотека с функциями программных задержек. Функции,
// представленные в библиотеке представляют собой надстройку над
// функциями _delay_ms() и _delay_us() из avr-libc. В отличии от
// этих изначальных инлайн-функций функции Delay_Ms и Delay_Us
// библиотеки позволяют передавать в качестве аргументов переменную.
//
// Библиотеку можно использовать в простых проектах и при
// прототипировании, где не требуется высокая энергоэффективность
// и скорость. В противном случае я не рекомендую пользоваться
// данной библиотекой - в таком случае используйте прерывания
// таймеров и функции энергосбережения для более эффективной работы.
//
// Кроме того, во время выполнения задержки есть специфическая
// возможность псевдопараллельного выполнения отдельной лёгкой
// операции (для функции Delay_Ms) каждую миллисекунду, для чего
// в файле delay_configuration.h есть соответствующий дефайн.
// Пример работы вы сможете посмотреть в соответствующей директории
// с примерами кода.
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


#ifndef DELAY_H_
#define DELAY_H_

#include <util/delay.h>
#include <stdint.h>
#include <stddef.h>

#include "delay_configuration.h"


#ifdef DELAY_MS_USE_YIELD

void Delay_Ms_Set_Yield_CallBack_Function(void (*delay_yield_ms)());

#endif


void Delay_Ms(uint16_t ms_delay);

void Delay_Us(uint16_t us_delay);


#endif


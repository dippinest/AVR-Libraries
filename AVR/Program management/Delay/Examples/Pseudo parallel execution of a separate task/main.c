

// ===============================================================================
//
// В этом примере показано, как можно осуществить псевдопараллельную обработку
// сторонней задачи при выполнении функции задержки Delay_Ms.
//
// В качестве основной задачи выступает обычная операция переключения пина
// из одного состояния в другое в цикле (мигание светодиодом). Второстепенная
// задача, которая будет выполняться во время задержки каждую миллисекунду будет
// функция-обработчик внешней кнопки, которая в свою очередь меняет состояние
// другого пина на противоположенное при каждом нажатии.
//
// При использовании такого механизма помните, что второстепенная задача должна
// выполнять как можно быстрее, иначе задержка в основной задаче будет увеличена
// пропорционально времени выполнения второстепенной задачи. Не используйте во
// второстепенной задаче сложные и долгие вычисления и тем более не используйте
// в них другие задержки!
//
// -------------------------------------------------------------------------------
//
// This example shows how to perform pseudo-parallel processing of a third-party
// task when executing the Delay_Ms delay function.
//
// The main task is the usual operation of switching the pin from one state to
// another in a cycle (LED flashing). A secondary task that will be performed
// during the delay every millisecond will be the handler function of the external
// button, which in turn changes the state of the other pin to the opposite one
// each time it is pressed.
//
// When using such a mechanism, remember that the secondary task must be
// completed as quickly as possible, otherwise the delay in the main task
// will be increased in proportion to the execution time of the secondary task.
// Do not use complex and lengthy calculations in a secondary task, and even more
// so do not use other delays in them!
//
// ===============================================================================


#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>

#include "delay.h"

// функция-обработчик кнопки, реализующая конечный автомат
// -------------------------------------------------------------------------------
// this is the button handler function that implements a finite state machine
void Button_Press_Check()
{
	static bool state = false;
	
	if (PIND & (1 << 4))
	{
		if (state)
		{
			state = false;
			PORTB ^= (1 << 1);
		}
	}
	else
	{
		state = true;
	}
}


int main(void)
{
	// настраиваем пины 0 и 1 порта PORTB на выход. Пин 0 будет отвечать
	// за постоянное мигание светодиодом в цикле, в то время как состояние
	// пина 1 будет управляться кнопкой
	// -------------------------------------------------------------------------------
	// configure pins 0 and 1 of the PORTB port to output.
	// Pin 0 will be responsible for the constant flashing of the LED
	// in the cycle, while the state of pin 1 will be controlled by the button
	DDRB  = (1 << 0) | (1 << 1);
	PORTB = (1 << 1) | (1 << 1);
	
	// настраиваем пин 4 порта PORTD на вход. К нему будет подключена кнопка
	// -------------------------------------------------------------------------------
	// configure the pin 4 PORTD ports for input. The button will be connected to it
	DDRD  &= ~(0 << 4);
	
	
	// устанавливаем коллбек обработчика кнопки
	// -------------------------------------------------------------------------------
	// installing the button handler callback
	Delay_Ms_Set_Yield_CallBack_Function(Button_Press_Check);
	
	while (1)
	{
		// Теперь переключение пина 1 по кнопке будет выполняться параллельно (почти)
		// переключению пина 0 в цикле
		// -------------------------------------------------------------------------------
		// Now switching pin 1 by the button will be performed in parallel
		// (almost paralleled) switching pin 0 in the loop
		
		PORTB ^= (1 << 0);
		
		Delay_Ms(250);
	}
}



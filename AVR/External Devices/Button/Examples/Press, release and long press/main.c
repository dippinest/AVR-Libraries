

#include <util/delay.h>

#include "button.h"
#include "uart.h"


// колбэк для обработки однократного нажатия кнопки
// -------------------------------------------------------------------------------
// callback for processing a single button press
//
void Press()
{
	UART_StringLn_Transmit("Button was pressed!");
}

// колбэк для обработки отжатия (отпускания) кнопки
// -------------------------------------------------------------------------------
// flask for processing the pressing (releasing) of the button
//
void Release()
{
	UART_StringLn_Transmit("Button was released!");
}

// колбэк для обработки долгого удержания кнопки
// -------------------------------------------------------------------------------
// callback for handling long button hold
//
void Long_Press()
{
	UART_StringLn_Transmit("Button is pressed very long...");
}

int main(void)
{
	// кнопка подтянута к Vcc (к плюсу питания)
	// -------------------------------------------------------------------------------
	// button is pulled up to Vcc
	//
	Button_t button = Button_Get_Device_Object(T(DDRD), T(PIND), 2, BUTTON_INPUT_PULLUP);
	
	
	UART_Initialize(115200, true, false);
	
	while (1)
	{
		// функция опроса однократного нажатия и отпускания кнопки
		// 
		// P.S. Для опроса ТОЛЬКО нажатия я рекомендую использовать функцию
		//
		// Button_Pressed_Polling(Button_t *button, void (*callback_function)()).
		// 
		// Кроме того, если Вам нужно отрабатывать только отжатие (отпускание)
		// кнопки, Вы можете не использовать колбэк для обработки нажатия,
		// например, вот так:
		//
		// Button_Pressed_And_Released_Polling(&button, NULL, Release);
		// -------------------------------------------------------------------------------
		// polling function of pressing and releasing the button once
		//
		// P.S. To poll ONLY clicks, I recommend using the
		// Button_Pressed_Polling(Button_t *button, void (*callback_function)()).
		//
		// In addition, if you only need to work out pressing (releasing)
		// the button, you can not use the callback to process the pressing,
		// for example, like this:
		//
		// Button_Pressed_And_Released_Polling(&button, NULL, Release);
		Button_Pressed_And_Released_Polling(&button, Press, Release);
		
		
		// функция опроса длительного нажатия кнопки
		//
		// Второй параметр '50' является значением внутреннего счётчика.
		// При достижении 50-й итерации вызова этой функции сработает колбэк Long_Press()
		// -------------------------------------------------------------------------------
		// long-press polling function
		//
		// The second parameter '50' is the value of the internal counter.
		// When the 50th iteration of calling this function is reached,
		// the Long_Press() callback will trigger
		Button_Long_Pressed_Polling(&button, 50, Long_Press);
		
		
		// вызываем функции опроса каждые 20 мс
		// -------------------------------------------------------------------------------
		// calling the polling functions every 20 ms
		//
		_delay_ms(20);
	}
}




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

// колбэк для обработки нажатия кнопки через таймаут
// -------------------------------------------------------------------------------
// callback for processing button clicks via timeout
//
void Hold_With_Timeout()
{
	UART_StringLn_Transmit("Button is constantly being pressed...");
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
	Button_t button = Button_Create_Object(T(DDRD), T(PIND), 2, BUTTON_INPUT_PULLUP);
	
	
	UART_Initialize(115200, true, false);
	
	while (1)
	{
		// функция опроса однократного нажатия и отпускания кнопки
		//
		// -------------------------------------------------------------------------------
		// polling function of pressing and releasing the button once
		//
		Button_Pressed_And_Released_Polling(&button, Press, Release);
		
		
		// функция опроса нажатия кнопки через таймаут
		//
		// Второй параметр '10' является значением таймаута.
		// При достижении 10-й итерации вызова этой функции сработает колбэк
		// Hold_With_Timeout(), затем счётчик таймаута сбросится в 0
		// -------------------------------------------------------------------------------
		// function of polling button presses after a timeout
		//
		// The second parameter '10' is the timeout value.
		// When the 10th iteration of calling this function is reached,
		// the Hold_With_Timeout() callback will trigger, then the timeout counter
		// will reset to 0
		Button_Hold_With_Timeout_Polling(&button, 10, Hold_With_Timeout);
		
		
		// функция опроса длительного нажатия кнопки
		//
		// Второй параметр '50' является значением таймаута.
		// При достижении 50-й итерации вызова этой функции сработает колбэк Long_Press()
		// -------------------------------------------------------------------------------
		// long-press polling function
		//
		// The second parameter '50' is the timeout value.
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





#include <util/delay.h>

#include "virtualbutton.h"
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
	DDRD &= ~(1 << 2);
	
	uint8_t button_status = 0;
	
	VirtualButton_t vbutton = VirtualButton_Create_Object(&button_status, 2, VIRTUALBUTTON_INPUT_LOGICAL_LEVEL_HIGH);
	
	
	UART_Initialize(9600, true, false);
	
	while (1)
	{
		// опрос логического уровня GPIO PD2
		//
		// -------------------------------------------------------------------------------
		// GPIO PD2 logic level polling
		//
		if (PIND & (1 << 2))
		{
			button_status |=  (1 << 2);
		}
		else
		{
			button_status &= ~(1 << 2);
		}
		
		
		// функция опроса однократного нажатия и отпускания кнопки
		//
		// -------------------------------------------------------------------------------
		// polling function of pressing and releasing the button once
		//
		VirtualButton_Pressed_And_Released_Polling(&vbutton, Press, Release);
		
		
		// функция опроса нажатия кнопки через таймаут
		//
		// Второй параметр '10' является значением таймаута.
		// При достижении 10-й итерации вызова этой функции сработает колбэк Hold_With_Timeout()
		// -------------------------------------------------------------------------------
		// function of polling button presses after a timeout
		//
		// The second parameter '10' is the timeout value.
		// When the 10th iteration of calling this function is reached,
		// the Long_Press() callback will trigger
		VirtualButton_Hold_With_Timeout_Polling(&vbutton, 10, Hold_With_Timeout);
		
		
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
		VirtualButton_Long_Pressed_Polling(&vbutton, 50, Long_Press);
		
		
		// вызываем функции опроса каждые 50 мс
		// -------------------------------------------------------------------------------
		// calling the polling functions every 50 ms
		//
		_delay_ms(50);
	}
}




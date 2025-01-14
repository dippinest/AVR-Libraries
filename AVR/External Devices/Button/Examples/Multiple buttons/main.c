

#include <util/delay.h>

#include "button.h"
#include "uart.h"

// колбэк для обработки однократного нажатия кнопки
// -------------------------------------------------------------------------------
// callback for processing a single button press
//
void Press()
{
	UART_StringLn_Transmit("Button 1 was pressed!");
}

// колбэк для обработки отжатия (отпускания) кнопки
// -------------------------------------------------------------------------------
// flask for processing the pressing (releasing) of the button
//
void Release()
{
	UART_StringLn_Transmit("Button 2 was released!");
}

// колбэк для обработки долгого удержания кнопки
// -------------------------------------------------------------------------------
// callback for handling long button hold
//
void Long_Press()
{
	UART_StringLn_Transmit("Button 3 is pressed very long...");
}

// колбэк для обработки постоянного нажатия кнопки
// -------------------------------------------------------------------------------
// callback for processing constant button pressing
//
void Hold()
{
	UART_StringLn_Transmit("Button 4 is constantly held down");
}

int main(void)
{
	// все кнопки подтянуты к Vcc (к плюсу питания)
	// -------------------------------------------------------------------------------
	// all buttons are pulled up to Vcc
	//
	Button_t button1 = Button_Get_Object(T(DDRD), T(PIND), 2, BUTTON_INPUT_PULLUP);
	Button_t button2 = Button_Get_Object(T(DDRD), T(PIND), 3, BUTTON_INPUT_PULLUP);
	Button_t button3 = Button_Get_Object(T(DDRD), T(PIND), 4, BUTTON_INPUT_PULLUP);
	
	// эта кнопка подтянута к GND (к земле)
	// -------------------------------------------------------------------------------
	// this button is pulled up to GND
	//
	Button_t button4 = Button_Get_Device_Object(T(DDRC), T(PINC), 0, BUTTON_INPUT_PULLDOWN);
	
	
	UART_Initialize(115200, true, false);
	
	while (1)
	{
		// функция опроса однократного нажатия кнопки button1
		//
		// -------------------------------------------------------------------------------
		// polling function of pressing the button 'button1' once
		//
		Button_Pressed_Polling(&button1, Press);
		
		// функция опроса отпускания (отжатия) кнопки button2
		//
		// -------------------------------------------------------------------------------
		// button release (release) polling function 'button2'
		//
		Button_Pressed_And_Released_Polling(&button2, NULL, Release);
		
		
		// функция опроса длительного нажатия кнопки button3
		//
		// -------------------------------------------------------------------------------
		// long-press polling function 'button3'
		//
		Button_Long_Pressed_Polling(&button3, 50, Long_Press);
		
		
		// функция опроса постоянного нажатия кнопки button4.
		// (функция постоянно проверяет условие Button_Is_Pressed(Button_t *button))
		//
		// -------------------------------------------------------------------------------
		// function of polling the constant pressing of the 'button4' button.
		// (the function constantly checks the condition Button_Is_Pressed(Button_t *button))
		//
		Button_Hold_Polling(&button4, Hold);
		
		
		// вызываем функции опроса каждые 20 мс
		// -------------------------------------------------------------------------------
		// calling the polling functions every 20 ms
		//
		_delay_ms(20);
	}
}


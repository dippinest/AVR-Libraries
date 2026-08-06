

#include <util/delay.h>

#include "encoder.h"
#include "uart.h"




volatile uint8_t i = 0;


// колбэк для обработки поворота энкодера влево.
//
// Внимание! Не используйте длительные по времени выполнения функции
// в обработчиках! Функция вывода данных по UART здесь
// только в качестве демонстративного примера!
// -------------------------------------------------------------------------------
// callback for processing the encoder rotation to the left.
//
// Attention! Do not use long-running functions in handlers!
// The UART data output function is here only
// as a demonstrative example!
void Left()
{
	--i;
	
	UART_StringFmt_Transmit("L: i = %d\r\n", i);
}


// колбэк для обработки поворота энкодера вправо.
//
// Внимание! Не используйте длительные по времени выполнения функции
// в обработчиках! Функция вывода данных по UART здесь
// только в качестве демонстративного примера!
// -------------------------------------------------------------------------------
// callback for processing the encoder rotation to the right.
//
// Attention! Do not use long-running functions in handlers!
// The UART data output function is here only
// as a demonstrative example!
void Right()
{
	++i;
	
	UART_StringFmt_Transmit("R: i = %d\r\n", i);
}



int main(void)
{
	Encoder_Initialize(Left, Right);
	
	
	UART_Initialize(115200, true, false);
	
	
	while (1)
	{
		Encoder_Polling();
		
		// частота опроса энкодера = 1 / 5 мс = 200 Гц
		// -------------------------------------------------------------------------------
		// encoder polling frequency = 1 / 5 ms = 200 Hz
		_delay_ms(5);
	}
}






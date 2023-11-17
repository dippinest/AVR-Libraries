
#include <util/delay.h>

#include "encoder.h"
#include "uart.h"
#include "itoa.h"

static char strbuf[8];

uint8_t i = 0;

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
	UART_String_Transmit("L: i = ");
	UART_StringLn_Transmit(ITOA_UInt8_To_String(i, 3));
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
	UART_String_Transmit("R: i = ");
	UART_StringLn_Transmit(ITOA_UInt8_To_String(i, 3));
}

int main(void)
{
	Encoder_Initialize();
	
	Encoder_Set_Left_Turn_CallBack_Function(Left);
	Encoder_Set_Right_Turn_CallBack_Function(Right);
	
	
	UART_Initialize(115200, true, false);
	
	ITOA_Set_String_Buffer(strbuf);
	
	
	while (1)
	{
		// частота опроса энкодера = 1 / 2 мс = 500 Гц
		// -------------------------------------------------------------------------------
		// encoder polling frequency = 1 / 2 ms = 500 Hz
		Encoder_Polling();
		
		_delay_ms(2);
	}
}


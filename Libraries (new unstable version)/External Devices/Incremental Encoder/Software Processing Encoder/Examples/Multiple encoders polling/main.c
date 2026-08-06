

#include <avr/sleep.h>

#include <util/delay.h>

#include "encoder.h"
#include "uart.h"



Encoder_t encoder1;
Encoder_t encoder2;

volatile uint8_t i1 = 0;
volatile uint8_t i2 = 0;




// колбэк для обработки поворота энкодера 1 влево.
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
void Encoder1_Left()
{
	--i1;
	
	UART_StringFmt_Transmit("Enc 1 L: i1 = %d\r\n", i1);
}


// колбэк для обработки поворота энкодера 1 вправо.
//
// Внимание! Не используйте длительные по времени выполнения функции
// в обработчиках! Функция вывода данных по UART здесь
// только в качестве демонстративного примера!
// -------------------------------------------------------------------------------
// callback for processing the encoder 1 rotation to the right.
//
// Attention! Do not use long-running functions in handlers!
// The UART data output function is here only
// as a demonstrative example!
void Encoder1_Right()
{
	++i1;
	
	UART_StringFmt_Transmit("Enc 1 R: i1 = %d\r\n", i1);
}


// колбэк для обработки поворота энкодера 2 влево.
//
// Внимание! Не используйте длительные по времени выполнения функции
// в обработчиках! Функция вывода данных по UART здесь
// только в качестве демонстративного примера!
// -------------------------------------------------------------------------------
// callback for processing the encoder 2 rotation to the left.
//
// Attention! Do not use long-running functions in handlers!
// The UART data output function is here only
// as a demonstrative example!
void Encoder2_Left()
{
	--i2;
	
	UART_StringFmt_Transmit("Enc 2 L: i2= %d\r\n", i2);
}


// колбэк для обработки поворота энкодера 2 вправо.
//
// Внимание! Не используйте длительные по времени выполнения функции
// в обработчиках! Функция вывода данных по UART здесь
// только в качестве демонстративного примера!
// -------------------------------------------------------------------------------
// callback for processing the encoder 2 rotation to the right.
//
// Attention! Do not use long-running functions in handlers!
// The UART data output function is here only
// as a demonstrative example!
void Encoder2_Right()
{
	++i2;
	
	UART_StringFmt_Transmit("Enc 2 R: i2= %d\r\n", i2);
}



int main(void)
{
	Encoder_Initialize_Object(&encoder1, T(DDRA), T(PINA), 0, T(DDRA), T(PINA), 1, Encoder1_Left, Encoder1_Right);
	Encoder_Initialize_Object(&encoder2, T(DDRA), T(PINA), 2, T(DDRA), T(PINA), 3, Encoder2_Left, Encoder2_Right);
	
	
	UART_Initialize(115200, true, false);
	
	
	while (1)
	{
		Encoder_Polling(&encoder1);
		Encoder_Polling(&encoder2);
		
		// частота опроса энкодеров = 1 / 5 мс = 200 Гц
		// -------------------------------------------------------------------------------
		// encoders polling frequency = 1 / 5 ms = 200 Hz
		_delay_ms(5);
	}
}





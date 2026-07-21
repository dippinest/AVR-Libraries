

#include <avr/sleep.h>

#include "encoder.h"
#include "uart.h"
#include "itoa.h"

#include "systimer.h"



static char strbuf[8];


volatile uint8_t i1 = 0;
volatile uint8_t i2 = 0;


Encoder_t encoder1;
Encoder_t encoder2;




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
	
	UART_String_Transmit("Enc 1 L: i1 = ");
	UART_StringLn_Transmit(ITOA_UInt8_To_String(i1, 3));
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
	
	UART_String_Transmit("Enc 1 R: i1 = ");
	UART_StringLn_Transmit(ITOA_UInt8_To_String(i1, 3));
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
	
	UART_String_Transmit("Enc 2 L: i2 = ");
	UART_StringLn_Transmit(ITOA_UInt8_To_String(i2, 3));
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
	
	UART_String_Transmit("Enc 2 R: i2 = ");
	UART_StringLn_Transmit(ITOA_UInt8_To_String(i2, 3));
}


// Задача для опроса энкодеров
// -------------------------------------------------------------------------------
// task for interrogating encoders
void Task_Encoders_Polling()
{
	Encoder_Polling(&encoder1);
	Encoder_Polling(&encoder2);
}



int main(void)
{
	encoder1 = Encoder_Create_Object(T(DDRA), T(PINA), 0, T(DDRA), T(PINA), 1, Encoder1_Left, Encoder1_Right);
	encoder2 = Encoder_Create_Object(T(DDRA), T(PINA), 2, T(DDRA), T(PINA), 3, Encoder2_Left, Encoder2_Right);
	
	
	UART_Initialize(115200, true, false);
	
	ITOA_Set_String_Buffer(strbuf);
	
	
	SYSTIMER_Task_Params_t encoders_polling_task_params = SYSTIMER_Create_Task_Params(5); // run every 5 ms
	
	SYSTIMER_Initialize();
	
	sei();
	
	
	while (1)
	{
		// опрос энкодеров
		// -------------------------------------------------------------------------------
		// polling encoders
		SYSTIMER_Run_Task(&encoders_polling_task_params, Task_Encoders_Polling);
		
		
		
		// при желании после отработки всех задач вы можете
		// усыпить процессор с целью экономии энергии
		//
		// -------------------------------------------------------------------------------
		// if desired, after working out all the tasks,
		// you can put the processor to sleep in order to save energy
		//
		sleep_enable();
		sleep_cpu();
	}
}





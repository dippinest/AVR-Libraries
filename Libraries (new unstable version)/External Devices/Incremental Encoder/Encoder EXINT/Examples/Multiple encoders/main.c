

// ===============================================================================
//
// В данном примере демонстрируется обработка двух инкрементальных энкодеров
// с помощью внешних прерываний EXINT (INT0 и INT1).
//
// Выход A энкодера необходимо подключить к внешнему прерыванию.
// Выход B энкодера можно подключить к любому другому GPIO микроконтроллера
//
// -------------------------------------------------------------------------------
//
// This example demonstrates the processing of two incremental encoders
// using external EXINT interrupts (INT0 and INT1).
//
// The output A of the encoder must be connected to an external interrupt.
// The output B of the encoder can be connected to any other GPIO microcontroller
//
// ===============================================================================



#include <avr/sleep.h>

#include "encoder_exint.h"
#include "uart.h"
#include "itoa.h"




Encoder_EXINT_t encoder1;
Encoder_EXINT_t encoder2;

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



// обработчик внешнего прерывания INT0, в котором обрабатывается энкодер 1
// -------------------------------------------------------------------------------
// the external interrupt INT0 handler in which the encoder 1 is processed
//
ISR(INT0_vect)
{
	Encoder_EXINT_Processing(&encoder1);
}

// обработчик внешнего прерывания INT1, в котором обрабатывается энкодер 2
// -------------------------------------------------------------------------------
// the external interrupt INT1 handler in which the encoder 2 is processed
//
ISR(INT1_vect)
{
	Encoder_EXINT_Processing(&encoder2);
}



int main(void)
{
	// настройка внешних прерываний INT0 и INT1 на срабатывание по восходящему фронту.
	//
	// Внимание! Прерывания можно настроить
	// на восходящий или нисходящий фронт, а также на оба фронта
	// (в последнем случае разрешение энкодера на полный поворот увеличится вдвое)
	//
	// -------------------------------------------------------------------------------
	// setting the external INT0 and INT1 interrupts to trigger on the rising edge.
	//
	// Attention! Interrupts can be set to
	// an rising or falling edge, as well as any edges
	// (in the latter case, the encoder's resolution for full rotation will double)
	GICR  |= ( (1 << INT0)  |  (1 << INT1) );
	MCUCR |= ( (1 << ISC01) | (1 << ISC00) )   |   ( (1 << ISC11) | (1 << ISC10) );
	


	// инициализируем энкодеры и определяем колбек-функции поворота влево и вправо
	// -------------------------------------------------------------------------------
	// initialize encoders and define the callback functions
	// for left and right rotation.
	//
	Encoder_EXINT_Initialize_Object(&encoder1, T(DDRD), T(PIND), 2, T(DDRA), T(PINA), 2, Encoder1_Left, Encoder1_Right);
	Encoder_EXINT_Initialize_Object(&encoder2, T(DDRD), T(PIND), 3, T(DDRA), T(PINA), 3, Encoder2_Left, Encoder2_Right);
	
	
	UART_Initialize(115200, true, false);
	
	
	
	// не забудьте включить глобальные прерывания
	// -------------------------------------------------------------------------------
	// don't forget to enable global interrupts
	//
	sei();
	
	
	while (1)
	{
		// при желании после обработки энкодеров (и других задач) вы можете
		// усыпить процессор с целью экономии энергии
		//
		// -------------------------------------------------------------------------------
		// if desired, after processing encoders (and other tasks),
		// you can put the processor to sleep in order to save energy
		//
		sleep_enable();
		sleep_cpu();
	}
}









// ===============================================================================
//
// В данном примере демонстрируется обработка инкрементального энкодера
// с помощью внешнего прерывания EXINT (INT0).
//
// Выход A энкодера необходимо подключить к внешнему прерыванию.
// Выход B энкодера можно подключить к любому другому GPIO микроконтроллера.
//
// GPIO настраиваются в конфигурационном файле encoder_exint_configuration.h
//
// -------------------------------------------------------------------------------
//
// This example demonstrates the processing of an incremental encoder
// using an external interrupt EXINT (INT0).
//
// The output A of the encoder must be connected to an external interrupt.
// The output B of the encoder can be connected to any other GPIO microcontroller.
//
// GPIOs are configured in the encoder_exint_configuration.h configuration file
//
// ===============================================================================



#include <avr/sleep.h>

#include "encoder_exint.h"
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



// обработчик внешнего прерывания INT0, в котором обрабатывается энкодер
// -------------------------------------------------------------------------------
// the external interrupt INT0 handler in which the encoder is processed
//
ISR(INT0_vect)
{
	Encoder_EXINT_Processing();
}



int main(void)
{
	// настройка внешнего прерывания INT0 на срабатывание по восходящему фронту.
	//
	// Внимание! Прерывание можно настроить
	// на восходящий или нисходящий фронт, а также на оба фронта
	// (в последнем случае разрешение энкодера на полный поворот увеличится вдвое)
	//
	// -------------------------------------------------------------------------------
	// setting the INT0 external interrupt to trigger on the rising edge.
	//
	// Attention! The interrupt can be set to
	// an rising or falling edge, as well as any edges
	// (in the latter case, the encoder's resolution for full rotation will double)
	GICR  |= (1 << INT0);
	MCUCR |= (1 << ISC01) | (1 << ISC00);
	

	// инициализируем энкодер и определяем колбек-функции поворота влево и вправо
	// -------------------------------------------------------------------------------
	// initialize the encoder and define the callback functions
	// for left and right rotation.
	//
	Encoder_EXINT_Initialize(Left, Right);
	
	
	
	UART_Initialize(115200, true, false);
	
	
	
	// не забудьте включить глобальные прерывания
	// -------------------------------------------------------------------------------
	// don't forget to enable global interrupts
	//
	sei();
	
	
	while (1)
	{
		// при желании после обработки энкодера (и других задач) вы можете
		// усыпить процессор с целью экономии энергии
		//
		// -------------------------------------------------------------------------------
		// if desired, after processing the encoder (and other tasks),
		// you can put the processor to sleep in order to save energy.
		//
		sleep_enable();
		sleep_cpu();
	}
}






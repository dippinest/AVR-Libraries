
#ifndef SYSTIMER_CONFIGURATION_H_
#define SYSTIMER_CONFIGURATION_H_


// если вы хотите, чтобы размер системного таймера был равен 32 бит,
// раскомментируйте этот дефайн (иначе закомментируйте его для размера 16 бит)
// -------------------------------------------------------------------------------
// if you want the size of the system timer to be 32 bits, uncomment
// this define (otherwise comment it out for the size of 16 bits)

#define SYSTIMER_WIDE_32BIT


// определение вектора прерывания системного таймера
//
// -------------------------------------------------------------------------------
// determining the interrupt vector of the system timer

#define SYSTIMER_VECTOR_INTERRUPT TIMER0_COMP_vect


// инлайн-функция инициализация системного таймера. По дефолту
// используется 8-ми битный Timer1 и при частоте тактирования
// микроконтроллера в 16 МГц таймер настроен на прерывания
// по совпадению каждую 1 мс.
//
// Эта инлайн-функция специально вынесена в файл конфигурации,
// чтобы при необходимости можно было изменить параметры системного таймера
//
// -------------------------------------------------------------------------------
// inline function initialization of the system timer. By default,
// an 8-bit Timer1 is used and with a clock frequency of the
// microcontroller at 16 MHz, the timer is configured to interrupt
// coincidentally every 1 ms.
//
// This inline function is specially placed in the configuration
// file so that, if necessary, you can change the parameters
// of the system timer

inline void SYSTIMER_Initialize()
{
	TIMSK = (1 << OCIE0);
	TCCR0 = (1 << CS01) | (1 << CS00) | (1 << WGM01);
	
	TCNT0 = 6;
	OCR0  = 249;
}


#endif



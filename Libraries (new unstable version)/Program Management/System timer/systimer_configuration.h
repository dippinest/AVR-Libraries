

#ifndef SYSTIMER_CONFIGURATION_H_
#define SYSTIMER_CONFIGURATION_H_



// выбор разрядности системного таймера (8, 16 или 32 бита)
// -------------------------------------------------------------------------------
// selecting the bit width of the system timer (8, 16, or 32 bits)

//#define SYSTIMER_WIDE_8BIT
//#define SYSTIMER_WIDE_16BIT
#define SYSTIMER_WIDE_32BIT




// если вы хотите, чтобы обновление системного таймера
// происходило автоматически в прерывании назначенного аппаратного таймера,
// (иначе закомментируйте его, если необходимо обновлять системный таймер вручную
// (например, извне с помощью аппаратного прерывания GPIO))
// -------------------------------------------------------------------------------
// if you want the system timer to be updated automatically in the interrupt
// of the designated hardware timer, (otherwise, comment it out if you need
// to update the system timer manually
// (for example, from outside using a GPIO hardware interrupt))

//#define SYSTIMER_USE_INTERNAL_AVR_TIMER_INTERRUPT_FOR_UPDATE







// ===============================================================================

#ifdef SYSTIMER_USE_INTERNAL_AVR_TIMER_INTERRUPT_FOR_UPDATE



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

// ===============================================================================



#endif







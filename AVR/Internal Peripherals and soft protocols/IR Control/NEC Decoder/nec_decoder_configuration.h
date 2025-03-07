


#ifndef NEC_DECODER_CONFIGURATION_H_
#define NEC_DECODER_CONFIGURATION_H_

#include <avr/io.h>



// определения порта EXINT GPIO
// -------------------------------------------------------------------------------
// EXINT GPIO port definitions

#define NEC_DECODER_EXINT_IN_GPIO_DDR   DDRD
#define NEC_DECODER_EXINT_IN_GPIO_PINX  PIND
#define NEC_DECODER_EXINT_IN_GPIO_PIN   2




// переопределение имён векторов прерывания
// -------------------------------------------------------------------------------
// redefining interrupt vector names

#define NEC_DECODER_EXINT_VECTOR_INTERRUPT INT0_vect
#define NEC_DECODER_TIMER_VECTOR_INTERRUPT TIMER2_COMP_vect




// inline-функция настройки прерывания таймера по совпадению.
// Прерывание вызывается каждые 280 мкс. Вы можете изменить настройки,
// однако не изменяйте период прерывания, поскольку это приведёт к неработоспособности библиотеки!
// -------------------------------------------------------------------------------
// inline function for setting timer interruptions by coincidence.
// An interrupt is called every 280 microseconds. You can change the settings,
// but do not change the interruption period, as this will cause the library to malfunction!

inline void NEC_Decoder_FSM_Timer_Initialize()
{
	TIMSK = (1 << OCIE2);
	TCCR2 = (0 << CS22) | (1 << CS21) | (1 << CS20) | (1 << WGM21);
	
	TCNT2 = 0xDD;
	OCR2  = 0x22;
}




// inline-функция настройки внешнего прерывания по любому
// изменению уровня сигнала. Вы можете выбрать другой доступный источник
// внешнего прерывания, однако не изменяйте условие вызова прерывания,
// поскольку это приведёт к неработоспособности библиотеки!
// -------------------------------------------------------------------------------
// inline is the function of setting an external interrupt for any change
// in signal strength. You can select another available external interrupt
// source, but do not change the interrupt call condition, as this will cause
// the library to malfunction!

inline void NEC_Decoder_EXINT_Interrupt_Initialize()
{
	GICR  |= (1 << INT0);
	MCUCR |= (0 << ISC01) | (1 << ISC00);
}


#endif



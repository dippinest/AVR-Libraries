


#ifndef SAMSUNG_IR_DECODER_CONFIGURATION_H_
#define SAMSUNG_IR_DECODER_CONFIGURATION_H_

#include <avr/io.h>



// определения порта EXINT GPIO (INT0)
//
// К этому выводу подключается ИК приёмник,
// расчитанный на частоту несущей 38 КГц (например, TSOP1738)
//
// -------------------------------------------------------------------------------
// EXINT GPIO port definitions (INT0)
//
// An IR receiver is connected to this pin,
// designed for a carrier frequency of 38 kHz (for example, TSOP1738)
//
#define SAMSUNG_IR_DECODER_EXINT_IN_GPIO_DDR   DDRD
#define SAMSUNG_IR_DECODER_EXINT_IN_GPIO_PINX  PIND
#define SAMSUNG_IR_DECODER_EXINT_IN_GPIO_PIN   2




// переопределение имён векторов прерывания
// -------------------------------------------------------------------------------
// redefining interrupt vector names
//
#define SAMSUNG_IR_DECODER_EXINT_VECTOR_INTERRUPT INT0_vect
#define SAMSUNG_IR_DECODER_TIMER_VECTOR_INTERRUPT TIMER2_COMP_vect




// inline-функция настройки прерывания таймера по совпадению.
// Прерывание вызывается каждые 280 мкс. Вы можете изменить настройки,
// однако не изменяйте период прерывания, поскольку это приведёт
// к неработоспособности библиотеки!
//
// (данные настройки актуальны для ATmega32A, 16 MHz)
//
// -------------------------------------------------------------------------------
// inline function for setting timer interruptions by coincidence.
// An interrupt is called every 280 microseconds. You can change the settings,
// but do not change the interruption period, as this will cause the library
// to malfunction!
//
// (these settings are relevant for ATmega32A, 16 MHz)
//
inline void Samsung_IR_Decoder_FSM_Timer_Interrupt_Initialize()
{
	TIMSK = (1 << OCIE2);
	TCCR2 = (0 << CS22) | (1 << CS21) | (1 << CS20) | (1 << WGM21);
	
	TCNT2 = 0x00;
	OCR2  = 0x8B;
}




// inline-функция настройки внешнего прерывания по любому
// изменению уровня сигнала. Вы можете выбрать другой доступный источник
// внешнего прерывания, однако не изменяйте условие вызова прерывания,
// поскольку это приведёт к неработоспособности библиотеки!
//
// (данные настройки актуальны для ATmega32A, 16 MHz)
//
// -------------------------------------------------------------------------------
// inline is the function of setting an external interrupt for any change
// in signal strength. You can select another available external interrupt
// source, but do not change the interrupt call condition, as this will cause
// the library to malfunction!
//
// (these settings are relevant for ATmega32A, 16 MHz)
//
inline void Samsung_IR_Decoder_EXINT_Interrupt_Initialize()
{
	GICR  |= (1 << INT0);
	MCUCR |= (0 << ISC01) | (1 << ISC00);
}


#endif






#ifndef SAMSUNG_IR_ENCODER_CONFIGURATION_H_
#define SAMSUNG_IR_ENCODER_CONFIGURATION_H_


#include <avr/io.h>
#include <avr/interrupt.h>


// определение вывода ИК сигнала (вывод ШИМ таймера 2)
//
// К этому выводу подключается излучающий ИК светодиод
// (желательно через драйвер в виде транзисторного ключа)
//
// -------------------------------------------------------------------------------
// determination of the IR signal output (PWM timer2 output)
//
// An IR-emitting LED is connected to this pin
// (preferably through a transistor key driver)
//
//
#define SAMSUNG_IR_ENCODER_IR_OUT_GPIO_DDR    DDRB
#define SAMSUNG_IR_ENCODER_IR_OUT_GPIO_PORT   PORTB
#define SAMSUNG_IR_ENCODER_IR_OUT_GPIO_PIN    1




// переопределение вектора прерывания таймера
// -------------------------------------------------------------------------------
// redefining the timer interrupt vector
//
#define SAMSUNG_IR_ENCODER_TIMER_VECTOR_INTERRUPT TIMER2_COMP_vect




// inline-функция настройки прерывания таймера по совпадению.
// Прерывание вызывается каждые 560 мкс. Вы можете изменить настройки,
// однако не изменяйте период прерывания, поскольку это приведёт к неработоспособности библиотеки!
//
// (данные настройки актуальны для ATmega8A, 16 MHz)
//
// -------------------------------------------------------------------------------
// inline function for setting timer interruptions by coincidence.
// An interrupt is called every 560 microseconds. You can change the settings,
// but do not change the interruption period, as this will cause the library to malfunction!
//
// (these settings are relevant for ATmega8A, 16 MHz)
//
inline void Samsung_IR_Encoder_FSM_Timer_Interrupt_Initialize()
{
	TIMSK  = (1 << OCIE2);
	
	TCCR2 = (1 << WGM21) | (1 << CS22) | (1 << CS21);
	
	TCNT2 = 0xDD;
	OCR2  = 0x22;
}




// inline-функция настройки таймера
// Данная функция настраивает таймер на переключение вывода OCRx на противоположенное
// состояние с частотой 78 кГц. Таким образом, данный таймер отвечает за генерацию
// несущей ИК сигнала с частотой 38 кГц.
// Вы можете изменить настройки, однако не изменяйте период таймера,
// поскольку это приведёт к неработоспособности библиотеки!
//
// (данные настройки актуальны для ATmega8A, 16 MHz)
//
// -------------------------------------------------------------------------------
// inline function timer setting
// This function adjusts the timer to switch the OCRx output to the opposite state
// with a frequency of 78 kHz. Thus, this timer is responsible for generating
// an IR carrier signal with a frequency of 38 kHz. You can change the settings,
// but do not change the timer period, as this will cause the library to malfunction!
//
// (these settings are relevant for ATmega8A, 16 MHz)
//
inline void Samsung_IR_Encoder_Carrier_Frequency_Generator_Timer_Initialize()
{
	TCNT1 = 0xFF22;
	OCR1A = 0x00DD;
	
	TCCR1B = (1 << CS10) | (1 << WGM12);
}




// inline-функции управления состоянием вывода ИК сигнала
// -------------------------------------------------------------------------------
// inline function for the status of the IR signal output control
//
inline void _Samsung_IR_Encoder_Set_IR_Out_Level_High()
{
	TCCR1A = (1 << COM1A0);
}

inline void _Samsung_IR_Encoder_Set_IR_Out_Level_Low()
{
	TCCR1A = (1 << COM1A1);
	
	SAMSUNG_IR_ENCODER_IR_OUT_GPIO_PORT &= ~(1 << SAMSUNG_IR_ENCODER_IR_OUT_GPIO_PIN);
}




#endif






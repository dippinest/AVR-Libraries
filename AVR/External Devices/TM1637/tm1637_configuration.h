
#ifndef TM1637_CONFIGURATION_H_
#define TM1637_CONFIGURATION_H_


// Минимальная длина импульса протокола TM1637
//
// Если вы используете модуль TM1637, то как правило, на нём распаена RC цепь,
// подключенная к сигнальным линиям. В некоторых случаях постоянная времени RC цепи
// слишком велика, поэтому TM1637 может не успеть среагировать на минимальный импульс
// и модуль может не работать. В данном случае можно поступить так:
//
// 1. Снизить сопротивление резисторов RC цепи
// 2. Снизить ёмкость конденсаторов RC цепи или удалить их (не рекомендовано!)
// 3. Увеличить значение константы TM1637_MIN_PULSE_DURATION_DELAY_US (оптимально 20 - 40 мкс)
//
// -------------------------------------------------------------------------------
//
// Minimum pulse length of the TM1637 protocol
//
// If you are using the TM1637 module, then as a rule, the RC circuit connected
// to the signal lines is soldered on it. In some cases, the time constant of
// the RC circuit is too high, so the TM1637 may not have time to react to the
// minimum pulse and the module may not work. In this case, you can do this:
//
// 1. Reduce the resistance of the RC circuit resistors
// 2. Reduce the capacitance of the RC circuit capacitors or remove them (not recommended!)
// 3. Increase the value of the constant TM1637_MIN_PULSE_DURATION_DELAY_US (optimally 20 - 40 us)

#define TM1637_MIN_PULSE_DURATION_DELAY_US 20




// если вы хотите работать с несколькими индикаторами TM1637, раскомментируйте
// этот дефайн (иначе закомментируйте его)
// -------------------------------------------------------------------------------
// if you want to work with multiple TM1637 indicators, uncomment this define
// (otherwise comment it out)

//#define TM1637_USE_MULTIPLE_INTERFACE




#ifndef TM1637_USE_MULTIPLE_INTERFACE

// определения GPIO для CLK TM1637
// -------------------------------------------------------------------------------
// GPIO definitions for CLK TM1637

#define TM1637_CLK_DDR	 DDRC
#define TM1637_CLK_PORT  PORTC
#define TM1637_CLK_PIN   5


// определения GPIO для DIO TM1637
// -------------------------------------------------------------------------------
// GPIO definitions for DIO TM1637

#define TM1637_DIO_DDR	 DDRC
#define TM1637_DIO_PINX  PINC
#define TM1637_DIO_PORT  PORTC
#define TM1637_DIO_PIN   4

#endif


#endif







// ===============================================================================
//
// Пример получения случайного значения для начальной инициализации ГПСЧ с помощью внешней  RC цепи.
//
// Для различных реализаций ГПСЧ (генераторов псевдослучайных чисел) для их
// инициализации необходимо начальное значение, на основе которого в дальнейшем
// генерируется псевдослучайная последовательность. Очевидно, что такое начальное
// значение ГПСЧ при каждом запуске программы должно быть разным, иначе генерируемая
// последовательность будет каждый раз повторяться.
//
// Получить такое начальное значение можно из внешней периферии:
// АЦП, внешних устройств и т.д. Однако в некоторых ситуациях эти источники
// энтропии использовать затруднительно или вовсе невозможно (к примеру, в некоторых
// старых моделях микроконтроллеров отсутсвует АЦП). В таком случае одним из решений
// может быть использование внешней RC цепи, подключенной к любому GPIO микроконтроллеру
// и измерение времени заряда конденсатора. Для реализации этого необходимо соответствующим
// образом подключить внешнюю RC цепь из резистора и конденсатора следующим образом:
//
//
//   Vcc
//    *
//    |
//    _
//   | |
//   | | R (резистор)
//   |_|                    _______
//    |        R'          |       |
//    |      ____          |       |
//    *-----|____|-- GPIO -|  MCU  |
//    |                    |       |
//    |                    |_______|
//  _____
//  _____ C (конденсатор)
//    |
//    |
//    *
//   GND
//
//
// Суть предложенного алгоритма заключается в первичной разрядке конденсатора C
// и дальнейшей его зарядке через резистор R с замером времени его заряда. Поскольку
// на время заряда RC влияют множество факторов (напряжение питания, температура
// окружающей среды, воздействие внешних помех, дробового и теплового шума в резисторе
// и т.д.), оно не является детерминированным и может меняться при каждом измерении
// в некоторых пределах. Это свойство RC цепи используется для получения начального
// значения для ГПСЧ.
//
// Резистор R', подключенный к GPIO, необходим для ограничения тока разряда
// конденсатора C. Его номинал должен быть в пределах 100 - 500 Ом и значительно меньше
// значения резистора R (как минимум в 15-20 раз)
//
// Внимание! Не используйте значения измерений времени звряда RC как случайные числа
// непосредственно, поскольку статистические характеристики такого "ГПСЧ" очень плохи.
// Используйте такие значения только для начальной инициализации ГПСЧ.
//
// Также рекомендую в RC цепи использовать электролитические конденсаторы,
// поскольку их температурная стабильность меньше, чем другие типы конденсаторов,
// что позволит получить более случайные значения времени заряда RC цепи
//
// -------------------------------------------------------------------------------
//
// An example of obtaining a random value for initializing the PRNG using an external RC circuit.
//
// For various implementations of PRNGs (pseudorandom number generators) to
// initialize them, an initial value is needed, based on which a pseudorandom
// sequence is subsequently generated.
// Obviously, this initial value of the RNG must be different each time
// the program is started, otherwise the generated sequence will be repeated each time.
//
// You can get this initial value from external peripherals: ADCs, external
// devices, etc. However, in some situations, it is difficult or impossible
// to use these entropy sources (for example, some older microcontroller models
// lack an ADC). In this case, one solution may be to use an external RC circuit
// connected to any GPIO microcontroller and measure the charging time of
// the capacitor. To implement this, an external RC circuit consisting
// of a resistor and a capacitor must be properly connected as follows:
//
//
//   Vcc
//    *
//    |
//    _
//   | |
//   | | R (resistor)
//   |_|                    _______
//    |        R'          |       |
//    |      ____          |       |
//    *-----|____|-- GPIO -|  MCU  |
//    |                    |       |
//    |                    |_______|
//  _____
//  _____ C (capacitor)
//    |
//    |
//    *
//   GND
//
//
// The essence of the proposed algorithm is the primary discharge of
// the capacitor C and it is further charging through the resistor R
// with measurements of its charge time.
// Since the RC charge time is influenced by many factors (supply voltage,
// ambient temperature, exposure to external interference, shot and thermal
// noise in the resistor, etc.), it is not deterministic and may vary with
// each measurement within certain limits. This property
// of the RC circuit is used to obtain the initial value for the PRNG.
//
// The resistor R' connected to the GPIO is necessary to limit the discharge
// current of the capacitor C. Its nominal value should be in the range
// of 100 - 500 ohms and significantly less than the value
// of the resistor R (at least 15-20 times)
//
// Attention! Do not use the values of the RC discharge time measurements
// as random numbers directly, because the statistical characteristics
// of such a "PRNG" are very poor.
// Use these values only for the initial initialization of the PRNG.
//
// I also recommend using electrolytic capacitors in the RC circuit,
// since their temperature stability is lower than other types of capacitors,
// which will allow you to get more random values of the charge time
// of the RC circuit
//
// ===============================================================================




#include <avr/io.h>
#include <util/delay.h>

#include <stdint.h>

#include "uart.h"





// функция измерения времени заряда внешней RC цепи
//
// -------------------------------------------------------------------------------
// external RC circuit charge time measurement function
//
uint16_t Get_Entropy_From_External_RC_Circuit()
{
	// определения GPIO, к которому подключена средняя точка внешней RC цепи
	//
	// -------------------------------------------------------------------------------
	// definitions of the GPIO to which the midpoint of the external RC circuit is connected
	//
	#define GPIO_DDR    DDRD
	#define GPIO_PINX   PIND
	#define GPIO_PORT   PORTD
	#define GPIO_PIN    7
	
	
	// время разряда RC цепи в мс.
	// Значение времени разряда должно быть не меньше значения 3*R*C
	// (в примере я использовал резистор 10 кОм и конденсатор 100 мкФ)
	//
	// -------------------------------------------------------------------------------
	// discharge time of the RC circuit in ms. The value of the discharge
	// time must be at least 3*R*C (in the example, I used a 10 kOhm resistor
	// and a 100uF capacitor)
	//
	#define T_RC_DISCHARGE_MS 3000


	uint16_t counter = 0;
	
	
	// режим GPIO - выход, притянутый к низкому уровню (GND). Разряжаем RC цепь
	//
	// -------------------------------------------------------------------------------
	// GPIO mode is a low-level output (GND). Discharging the RC circuit
	//
	GPIO_DDR  |=  (1 << GPIO_PIN);
	GPIO_PORT &= ~(1 << GPIO_PIN);
	
	_delay_ms(T_RC_DISCHARGE_MS);
	
	
	// режим GPIO - вход. RC цепь начинает заряжаться
	//
	// -------------------------------------------------------------------------------
	// GPIO mode is input. The RC circuit starts charging
	//
	GPIO_DDR  &= ~(1 << GPIO_PIN);
	
	
	while(!(GPIO_PINX & (1 << GPIO_PIN)))
	{
		// пока RC полностью не зарядится, инкрементируем переменную "counter".
		//
		// В данной реализации значение данной переменной определяется не только
		// временем заряда RC цепи, но и частотой тактирования ядра процессора
		//
		// -------------------------------------------------------------------------------
		// until the RC is fully charged, increment the variable "counter"
		//
		// In this implementation, the value of this variable is determined
		// not only by the charge time of the RC circuit, but also by the clock
		// frequency of the CPU core
		//
		++counter;
	}
	
	return counter;
}



int main(void)
{
	UART_Initialize(9600, true, false);
	
	
	while (1)
	{
		uint16_t value = Get_Entropy_From_External_RC_Circuit();
		
		
		// вывод полученного значения
		//
		// -------------------------------------------------------------------------------
		// output of the received value
		//
		UART_StringFmt_Transmit("Value: %u\r\n\r\n", value);
	}
}














// ===============================================================================
//
// В этом примере показан процесс подстройки частоты внутреннего генератора
// с помощью массива внутренних конденсаторов. Корректировка осуществляется
// путём занесения значения во внутренний регистр Aging Offset.
//
// Для подстройки частоты необходимо вывести меандр частотой 1 Гц
// на вывод SQW и измерения частоты с помощью осциллографа или логического
// анализатора. Если частота на выводе SQW больше 1 Гц, необходимо внести
// в регистр отрицательное значение и подстроить его до получения необходимой
// точности (если частота меньше - соответственно внести положительное значение).
//
// Необходимо отметить, что оригинальные DS3231/DS3231M уже имеют хорошую
// точность хода и в дополнительной подстройке, как правило, не нуждаются
//
// -------------------------------------------------------------------------------
//
// This example shows the process of adjusting the frequency
// of an internal oscillator using an array of internal capacitors.
// The correction is performed by entering the value into the internal
// Aging Offset register.
//
// To adjust the frequency, it is necessary to output a 1 Hz meander
// to the SQW output and measure the frequency using an oscilloscope
// or logic analyzer. If the frequency on the SQW pin is greater than 1 Hz,
// a negative value must be entered into the register and adjusted to obtain
// the required accuracy (if the frequency is lower, a positive value must
// be entered accordingly).
//
// It should be noted that the original DS3231/DS3231M already have good
// running accuracy and, as a rule, do not need additional adjustment.
//
// ===============================================================================




#include "softi2c.h"
#include "ds3231.h"
#include "uart.h"


int main(void)
{
	SOFTI2C_Initialize();
	
	UART_Initialize(9600, true, false);
	
	
	
	// включение вывода сигнала на выводе SQW частотой 1 Гц
	//
	// -------------------------------------------------------------------------------
	// enabling the signal output on the SQW pin with a frequency of 1 Hz
	//
	DS3231_Set_SQW_Enable(true);
	
	DS3231_Set_SQW_Frequency(DS3231_SQW_FREQUENCY_1_HZ);
	
	
	// внесение корректирующего коэффициента во внутренний регистр Aging Offset
	//
	// -------------------------------------------------------------------------------
	// adding a correction factor to the internal Aging Offset register
	//
	DS3231_Set_Aging_Offset(-10);
	
	// после внесения корректирующего коэффициента необходимо
	// принудительно запустить процесс температурной компенсации генератора
	//
	// -------------------------------------------------------------------------------
	// after applying the correction factor, the generator temperature
	// compensation process must be forcibly started
	//
	DS3231_Start_Temperature_Compensation_Process();

	
	while (1)
	{
	}
}




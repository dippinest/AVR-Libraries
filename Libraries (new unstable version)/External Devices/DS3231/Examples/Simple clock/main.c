

#include <avr/io.h>
#include <avr/interrupt.h>

#include "softi2c.h"
#include "ds3231.h"
#include "uart.h"



ISR(INT0_vect)
{
	// 1 раз в секунду обновляем и выводим данные
	//
	// -------------------------------------------------------------------------------
	// update and output data 1 time per second
	//
	DS3231_Data_t dt;
	
	DS3231_Get_Data_To_Struct(&dt);
	
	
	UART_StringFmt_Transmit("%02d/%02d/%04d, Day of week: %d\r\n", dt.day_of_month, dt.month, (2000 + dt.year), dt.weekday);
	
	UART_StringFmt_Transmit("%02d:%02d:%02d\r\n", dt.hours, dt.minutes, dt.seconds);
	
	
	UART_StringFmt_Transmit("Temperature = %d *C\r\n\r\n", DS3231_Get_Integer_Temperature());
}


int main(void)
{
	// включение внешнего прерывания INT0 по спаду сигнала
	//
	// -------------------------------------------------------------------------------
	// enabling an external INT0 interrupt for falling edge
	//
	GICR  |=  (1 << INT0);
	MCUCR |= ((1 << ISC01) | (0 << ISC00));
	
	
	
	SOFTI2C_Initialize();
	
	UART_Initialize(9600, true, false);
	
	
	
	// включение вывода сигнала на выводе SQW частотой 1 Гц
	//
	// -------------------------------------------------------------------------------
	// enabling the signal output on the SQW pin with a frequency of 1 Hz
	//
	DS3231_Set_SQW_Enable(true);
	
	DS3231_Set_SQW_Frequency(DS3231_SQW_FREQUENCY_1_HZ);
	
	
	
	
	// первоначальная установка даты и времени (закомментировано)
	// -------------------------------------------------------------------------------
	// initial date and time setting (commented out)
	//
	//DS3231_Data_t data;
	//
	//data.seconds      =  0;
	//data.minutes      = 18;
	//data.hours        = 19;
	//data.weekday      = THURSDAY;
	//data.day_of_month = 13;
	//data.month        = NOVEMBER;
	//data.year         = 25;
	//
	//DS3231_Set_Data_From_Struct(&data);
	
	
	
	// не забудьте включить глобальные прерывания
	//
	// -------------------------------------------------------------------------------
	// don't forget to enable global interrupts
	//
	sei();

	
	while (1)
	{
	}
}





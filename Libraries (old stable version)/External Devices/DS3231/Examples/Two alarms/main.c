

#include <avr/io.h>
#include <avr/interrupt.h>

#include "softi2c.h"
#include "ds3231.h"
#include "uart.h"


ISR(INT0_vect)
{
	// если сработал будильник 1, выводим время срабатывания
	//
	// -------------------------------------------------------------------------------
	// if the alarm 1 is triggered, output the alarm time
	//
	if (DS3231_Alarm_1_Is_Triggered())
	{
		UART_StringFmt_Transmit("ALARM 1 IS TRIGGERED!\r\n\r\n");
		
		
		UART_StringFmt_Transmit("%02d/%02d/%04d\r\n", DS3231_Get_Day_Of_Month(), DS3231_Get_Month(), (2000 + DS3231_Get_Year()));
		
		UART_StringFmt_Transmit("%02d:%02d:%02d\r\n\r\n\r\n", DS3231_Get_Hours(), DS3231_Get_Minutes(), DS3231_Get_Seconds());
		
		
		// после срабатывания обязательно нужно сбросить флаг срабатывания,
		// иначе в следующий раз будильник не сработает
		//
		// -------------------------------------------------------------------------------
		// after the alarm is triggered, it is necessary to reset the alarm flag,
		// otherwise the alarm will not work next time
		//
		DS3231_Alarm_1_Flag_Reset();
	}
	
	
	
	// если сработал будильник 2, выводим время срабатывания
	//
	// -------------------------------------------------------------------------------
	// if the alarm 2 is triggered, output the alarm time
	//
	if (DS3231_Alarm_2_Is_Triggered())
	{
		UART_StringFmt_Transmit("ALARM 2 IS TRIGGERED!\r\n\r\n");
		
		
		UART_StringFmt_Transmit("%02d/%02d/%04d\r\n", DS3231_Get_Day_Of_Month(), DS3231_Get_Month(), (2000 + DS3231_Get_Year()));
		
		UART_StringFmt_Transmit("%02d:%02d:%02d\r\n\r\n\r\n", DS3231_Get_Hours(), DS3231_Get_Minutes(), DS3231_Get_Seconds());
		
		
		// после срабатывания обязательно нужно сбросить флаг срабатывания,
		// иначе в следующий раз будильник не сработает
		//
		// -------------------------------------------------------------------------------
		// after the alarm is triggered, it is necessary to reset the alarm flag,
		// otherwise the alarm will not work next time
		//
		DS3231_Alarm_2_Flag_Reset();
	}
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
	
	
	
	// установка времени срабатывания будильника 1
	//
	// -------------------------------------------------------------------------------
	// setting the alarm 1 time
	//
	DS3231_Set_Alarm_1_Seconds(5);
	DS3231_Set_Alarm_1_Minutes(28);
	DS3231_Set_Alarm_1_Hours(19);
	
	
	// включение будильника 1 и установка его режима
	// (сработает при совпадении часов, минут и секунд с значениями основных часов)
	//
	// -------------------------------------------------------------------------------
	// turning on the alarm clock 1 and setting its mode
	// (it will trigger if the hours, minutes, and seconds match the values of the main clock)
	//
	DS3231_Set_Alarm_1_Enable(true);
	DS3231_Set_Alarm_1_Mode(DS3231_ALARM_1_MODE_HOURS_MINUTES_AND_SECONDS_MATCH);
	
	
	
	
	
	
	// включение будильника 2 и установка его режима
	// (будильник будет срабатывать каждую минуту)
	//
	// -------------------------------------------------------------------------------
	// turning on the alarm clock 2 and setting its mode
	// (the alarm will trigger every minute)
	//
	DS3231_Set_Alarm_2_Enable(true);
	DS3231_Set_Alarm_2_Mode(DS3231_ALARM_2_MODE_EVERY_MINUTE);
	
	
	
	// разрешение общего прерывания от будильников
	//
	// -------------------------------------------------------------------------------
	// allowing general interruptions from alarm clocks
	//
	DS3231_Set_Alarms_Interrupt_Enable(true);
	
	
	
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




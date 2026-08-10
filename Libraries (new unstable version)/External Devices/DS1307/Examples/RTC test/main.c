

#include <util/delay.h>

#include "softi2c.h"
#include "ds1307.h"
#include "uart.h"



// объект RTC DS1307
//
// ===============================================================================
// DS1307 RTC object
//
DS1307_Data_t current_time_data;


int main(void)
{
	SOFTI2C_Initialize();
	
	UART_Initialize(9600, true, false);
	
	
	
	// это - закомментированный код установки времени и даты.
	// В реальном проекке установка будет осуществляться в рантайме
	// пользователем через интерфейс UI
	//
	// ===============================================================================
	// this is the commented code for setting the time and date.
	// In the actual project, the setting will be done at runtime
	// by the user via the UI interface
	//
	//
	//	current_time_data.seconds      = 12;
	//	current_time_data.minutes      = 48;
	//	current_time_data.hours        = 11;
	//	current_time_data.weekday      = SUNDAY;
	//	current_time_data.day_of_month = 9;
	//	current_time_data.month        = AUGUST;
	//	current_time_data.year         = 26;
	//
	//	DS1307_Set_Data_From_Struct(&current_time_data);
	
	
	
	
	// если микросхема отключена (если на неё только подняли питание),
	// её обязательно надо включить
	//
	// ===============================================================================
	// If the microchip is turned off (if power has just been applied to it),
	// it must be turned on
	//
	DS1307_Set_Enable(true);
	
	
	while (1)
	{
		// получаем значения даты и времени в структуру DS1307_Data_t
		//
		// ===============================================================================
		// obtaining the date and time value into the DS1307_Data_t structure
		//
		DS1307_Get_Data_To_Struct(&current_time_data);
		
		
		
		// вывод дня, месяца и года
		//
		// ===============================================================================
		// output of the day, month, and year
		//
		UART_StringFmt_Transmit("%02d/%02d/%04d\r\n", current_time_data.day_of_month, current_time_data.month, (2000 + current_time_data.year));
		
		
		// вывод часов, минут и секунд
		//
		// ===============================================================================
		// output of hours, minutes, and seconds
		//
		UART_StringFmt_Transmit("%02d:%02d:%02d\r\n", current_time_data.hours, current_time_data.minutes, current_time_data.seconds);
		
		
		
		UART_NEW_LINE;
		UART_NEW_LINE;
		
		
		_delay_ms(1000);
	}
}







// ATN! to work with multiple sensors, uncomment the macro
// "DS18B20_USE_MULTIPLE_SENSORS" in the file "ds18b20_configuration.h"!

#define F_CPU 16000000UL

#include <util/delay.h>

#include "uart.h"
#include "itoa.h"
#include "onewire.h"
#include "ds18b20.h"

static uint8_t ds18b20_1_thermometer_address[] = { 0x28, 0xFF, 0x75, 0x35, 0x16, 0x20, 0x8A, 0x96 };
static uint8_t ds18b20_2_thermometer_address[] = { 0x28, 0x3D, 0xF7, 0x46, 0x92, 0x0D, 0x02, 0xF5 };

static char buf[16];

int main(void)
{
	UART_Initialize(9600, true, false);
	ITOA_Set_String_Buffer(buf);
	
	DS18B20_Set_Resolution(DS18B20_12BIT_RESOLUTION);
	
	float ds18b20_1_thermometer_data, ds18b20_2_thermometer_data;
	
	while (1)
	{
		DS18B20_Start_Convert_With_Skip_ROM(); _delay_ms(DS18B20_12BIT_RESOLUTION_CONVERT_TIMEOUT_MS);
		
		DS18B20_Set_Target_DS18B20_Address(ds18b20_1_thermometer_address);
		ds18b20_1_thermometer_data = DS18B20_Get_Float_Temperature_With_Increased_Accuracy();
		
		DS18B20_Set_Target_DS18B20_Address(ds18b20_2_thermometer_address);
		ds18b20_2_thermometer_data = DS18B20_Get_Float_Temperature_With_Increased_Accuracy();
		

		UART_String_Transmit("TEMP 1 = ");
		UART_String_Transmit(ITOA_Float_To_String(ds18b20_1_thermometer_data, 3, 2));
		UART_String_Transmit(" *C\r\n");

		UART_String_Transmit("TEMP 2 = ");
		UART_String_Transmit(ITOA_Float_To_String(ds18b20_2_thermometer_data, 3, 2));
		UART_String_Transmit(" *C\r\n\r\n");
	}
}

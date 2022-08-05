
// For example, I connect DS18B20 sensor on 1-wire bus

#define F_CPU 16000000UL

#include <util/delay.h>

#include "uart.h"
#include "itohexa.h"

#include "onewire.h"

static char buf[8];

int main(void)
{
	UART_Initialize(9600, true, false);
	ITOHEXA_Set_String_Buffer(buf);

	if (ONEWIRE_Reset() == ONEWIRE_DEVICES_WAS_FOUND)
	{
		UART_StringLn_Transmit("DEVICE WAS FOUND!\r\n");
		
		uint8_t onewire_id_device[8];
		ONEWIRE_Get_Unique_ROM_ID(onewire_id_device);
		
		UART_String_Transmit("1-WIRE ID (HEX): ");
		
		for (uint8_t i = 0; i < 8; ++i)
		{
			UART_String_Transmit(ITOHEXA_8bitNum_To_HexString(onewire_id_device[i], false));
			UART_String_Transmit(" ");
		}
	}
	else
	{
		UART_StringLn_Transmit("ERROR!");
	}
	
	while (1)
	{
	}
}

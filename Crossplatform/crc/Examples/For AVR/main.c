
#define F_CPU 16000000UL
#include <util/delay.h>

#include "uart.h"
#include "itohexa.h"
#include "crc.h"

typedef struct
{
	char c;
	uint16_t u16_val_1;
	uint16_t u16_val_2;
	int64_t  i64_val;

} Data;

static char str_buf[16];

int main(void)
{
	UART_Initialize(9600, true, false);
	ITOHEXA_Set_String_Buffer(str_buf);
	
	Data d = { 'a', 232, 7633, 684567387573458769 };
	
	UART_StringLn_Transmit(
		ITOHEXA_32bitNum_To_HexString(
			CRC32_Get(&d, sizeof(Data), 0xA0435757, 0xFF457436, true, false, 0x00446774), false));
	
	while (1)
	{
	}
}

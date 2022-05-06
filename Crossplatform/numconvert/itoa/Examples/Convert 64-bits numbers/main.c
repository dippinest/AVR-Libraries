
#include <stdbool.h>

#include "uart.h"
#include "itoa.h"
#include "deftypes.h"

int main(void)
{
	UART_Initialize(9600, true, false);
	
	ITOA_Set_String_Buffer_To_Dynamic_Memory(32); // example of creating a buffer in dynamic memory with a size of 32 bytes
	
	UART_String_Transmit("Converting 64-bits numbers to C-type string\r\n\r\n");
	
	UART_String_Transmit("Macro \"MIN_QWORD_VAL\"     = "); UART_StringLn_Transmit(ITOA_UInt64_To_String(MIN_QWORD_VAL,     21));
	UART_String_Transmit("Macro \"MAX_QWORD_VAL\"     = "); UART_StringLn_Transmit(ITOA_UInt64_To_String(MAX_QWORD_VAL,     21));
	UART_String_Transmit("Macro \"MIN_SQWORD_VAL\"    = "); UART_StringLn_Transmit(ITOA_Int64_To_String(MIN_SQWORD_VAL,     21));
	UART_String_Transmit("Macro \"MAX_SQWORD_VAL\"    = "); UART_StringLn_Transmit(ITOA_Int64_To_String(MAX_SQWORD_VAL,     21));
	UART_String_Transmit("Macro \"MIN_INT64_VAL\"     = "); UART_StringLn_Transmit(ITOA_Int64_To_String(MIN_INT64_VAL,      21));
	UART_String_Transmit("Macro \"MAX_INT64_VAL\"     = "); UART_StringLn_Transmit(ITOA_Int64_To_String(MAX_INT64_VAL,      21));
	UART_String_Transmit("Macro \"MIN_UINT64_VAL\"    = "); UART_StringLn_Transmit(ITOA_UInt64_To_String(MIN_UINT64_VAL,    21));
	UART_String_Transmit("Macro \"MAX_UINT64_VAL\"    = "); UART_StringLn_Transmit(ITOA_UInt64_To_String(MAX_UINT64_VAL,    21));
	UART_String_Transmit("Macro \"MIN_S64_VAL\"       = "); UART_StringLn_Transmit(ITOA_Int64_To_String(MIN_S64_VAL,        21));
	UART_String_Transmit("Macro \"MAX_S64_VAL\"       = "); UART_StringLn_Transmit(ITOA_Int64_To_String(MAX_S64_VAL,        21));
	UART_String_Transmit("Macro \"MIN_U64_VAL\"       = "); UART_StringLn_Transmit(ITOA_UInt64_To_String(MIN_U64_VAL,       21));
	UART_String_Transmit("Macro \"MAX_U64_VAL\"       = "); UART_StringLn_Transmit(ITOA_UInt64_To_String(MAX_U64_VAL,       21));
	UART_String_Transmit("Macro \"MIN_NATURAL64_VAL\" = "); UART_StringLn_Transmit(ITOA_UInt64_To_String(MIN_NATURAL64_VAL, 21));
	UART_String_Transmit("Macro \"MAX_NATURAL64_VAL\" = "); UART_StringLn_Transmit(ITOA_UInt64_To_String(MAX_NATURAL64_VAL, 21));
	
	UART_NEW_LINE;
	
	
	while (1)
	{
	}
}

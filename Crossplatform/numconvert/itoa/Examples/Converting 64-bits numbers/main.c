#include "AVR/Internal Peripherals/uart/uart.h"
#include "Crossplatform/numconvert/itoa/itoa.h"
#include "Crossplatform/deftypes.h"

static char str_buf[32];

int main(void)
{
	UART_Initialize(9600, true, true, false, false, false, UART_NUM_OF_DATA_BITS_8, UART_NUM_OF_STOP_BITS_1, UART_PARITY_BIT_NONE);
	
	UART_String_Transmit("Converting 64-bits numbers to C-type string\r\n\r\n"); // (uint8_t val, int8_t num_of_chars, const char empty_character, char *string_buf)
	
	UART_String_Transmit("Macro \"MIN_QWORD_VAL\"     = "); UART_StringLn_Transmit(ITOA_UInt64_To_String(MIN_QWORD_VAL,     21, ' ', str_buf));
	UART_String_Transmit("Macro \"MAX_QWORD_VAL\"     = "); UART_StringLn_Transmit(ITOA_UInt64_To_String(MAX_QWORD_VAL,     21, ' ', str_buf));
	UART_String_Transmit("Macro \"MIN_SQWORD_VAL\"    = "); UART_StringLn_Transmit(ITOA_Int64_To_String(MIN_SQWORD_VAL,     21, ' ', str_buf));
	UART_String_Transmit("Macro \"MAX_SQWORD_VAL\"    = "); UART_StringLn_Transmit(ITOA_Int64_To_String(MAX_SQWORD_VAL,     21, ' ', str_buf));
	UART_String_Transmit("Macro \"MIN_INT64_VAL\"     = "); UART_StringLn_Transmit(ITOA_Int64_To_String(MIN_INT64_VAL,      21, ' ', str_buf));
	UART_String_Transmit("Macro \"MAX_INT64_VAL\"     = "); UART_StringLn_Transmit(ITOA_Int64_To_String(MAX_INT64_VAL,      21, ' ', str_buf));
	UART_String_Transmit("Macro \"MIN_UINT64_VAL\"    = "); UART_StringLn_Transmit(ITOA_UInt64_To_String(MIN_UINT64_VAL,    21, ' ', str_buf));
	UART_String_Transmit("Macro \"MAX_UINT64_VAL\"    = "); UART_StringLn_Transmit(ITOA_UInt64_To_String(MAX_UINT64_VAL,    21, ' ', str_buf));
	UART_String_Transmit("Macro \"MIN_S64_VAL\"       = "); UART_StringLn_Transmit(ITOA_Int64_To_String(MIN_S64_VAL,        21, ' ', str_buf));
	UART_String_Transmit("Macro \"MAX_S64_VAL\"       = "); UART_StringLn_Transmit(ITOA_Int64_To_String(MAX_S64_VAL,        21, ' ', str_buf));
	UART_String_Transmit("Macro \"MIN_U64_VAL\"       = "); UART_StringLn_Transmit(ITOA_UInt64_To_String(MIN_U64_VAL,       21, ' ', str_buf));
	UART_String_Transmit("Macro \"MAX_U64_VAL\"       = "); UART_StringLn_Transmit(ITOA_UInt64_To_String(MAX_U64_VAL,       21, ' ', str_buf));
	UART_String_Transmit("Macro \"MIN_NATURAL64_VAL\" = "); UART_StringLn_Transmit(ITOA_UInt64_To_String(MIN_NATURAL64_VAL, 21, ' ', str_buf));
	UART_String_Transmit("Macro \"MAX_NATURAL64_VAL\" = "); UART_StringLn_Transmit(ITOA_UInt64_To_String(MAX_NATURAL64_VAL, 21, ' ', str_buf));
	
	UART_NEW_LINE;
	
	
	while (1)
	{
	}
}

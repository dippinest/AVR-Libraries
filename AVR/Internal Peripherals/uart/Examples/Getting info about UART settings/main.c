
#define  F_CPU 16000000UL
#include "uart.h"

int main(void)
{
	UART_Initialize(9600, true, true, false, false, false, UART_NUM_OF_DATA_BITS_8, UART_NUM_OF_STOP_BITS_1, UART_PARITY_BIT_NONE);
	
	UART_String_Transmit("This is a params configurations of UART:\r\n\r\n");
	
	UART_StringFmt_Transmit("Baudrate: ------------------------------- %lu\r\n", UART_Get_Baudrate());
	UART_StringFmt_Transmit("Transmittion is allowed: ---------------- %s\r\n",  UART_Transmission_Is_Allowed()                  ? "true" : "false");
	UART_StringFmt_Transmit("Reception is allowed: ------------------- %s\r\n",  UART_Reception_Is_Allowed()                     ? "true" : "false");
	UART_StringFmt_Transmit("Buffer emptying interrupt is allowed: --- %s\r\n",  UART_Buffer_Emptying_Interrupt_Is_Allowed()     ? "true" : "false");
	UART_StringFmt_Transmit("End of transmittion interrupt is allowed: %s\r\n",  UART_End_Of_Transmittion_Interrupt_Is_Allowed() ? "true" : "false");
	UART_StringFmt_Transmit("End of reception interrupt is allowed: -- %s\r\n",  UART_End_Of_Reception_Interrupt_Is_Allowed()    ? "true" : "false");
	UART_StringFmt_Transmit("Num of data bits: ----------------------- %d\r\n",  UART_Get_Num_Of_Data_Bits());
	UART_StringFmt_Transmit("Num of stop bits: ----------------------- %d\r\n",  UART_Get_Num_Of_Stop_Bits());
	
	UART_String_Transmit("Parity bit: ----------------------------- ");
	
	switch(UART_Get_Parity_Bit())
	{
		case UART_PARITY_BIT_NONE:
		UART_StringLn_Transmit("NONE");
		break;
		case UART_PARITY_BIT_EVEN:
		UART_StringLn_Transmit("EVEN");
		break;
		default:
		UART_StringLn_Transmit("ODD");
	}
	
	while (1)
	{
	}
}


#include "uart1.h"

int main(void)
{
	UART1_Initialize(9600, true, false);
	
	UART1_String_Transmit("This is a params configurations of UART1:\r\n\r\n");
	
	UART1_StringFmt_Transmit("Baudrate: ------------------------------- %lu\r\n", UART1_Get_Baudrate());
	UART1_StringFmt_Transmit("Transmittion is enable: ----------------- %s\r\n",  UART1_Transmittion_Is_Enable()                  ? "true" : "false");
	UART1_StringFmt_Transmit("Reception is enable: -------------------- %s\r\n",  UART1_Reception_Is_Enable()                     ? "true" : "false");
	UART1_StringFmt_Transmit("Buffer emptying interrupt is enable: ---- %s\r\n",  UART1_Buffer_Emptying_Interrupt_Is_Enable()     ? "true" : "false");
	UART1_StringFmt_Transmit("End of transmittion interrupt is enable:  %s\r\n",  UART1_End_Of_Transmittion_Interrupt_Is_Enable() ? "true" : "false");
	UART1_StringFmt_Transmit("End of reception interrupt is enable: --- %s\r\n",  UART1_End_Of_Reception_Interrupt_Is_Enable()    ? "true" : "false");
	UART1_StringFmt_Transmit("Num of data bits: ----------------------- %d\r\n",  UART1_Get_Num_Of_Data_Bits());
	UART1_StringFmt_Transmit("Num of stop bits: ----------------------- %d\r\n",  UART1_Get_Num_Of_Stop_Bits());
	
	UART1_String_Transmit("Parity bit: ----------------------------- ");
	
	switch(UART1_Get_Parity_Bit())
	{
		case UART1_PARITY_BIT_NONE:
		UART1_StringLn_Transmit("NONE");
		break;
		case UART1_PARITY_BIT_EVEN:
		UART1_StringLn_Transmit("EVEN");
		break;
		default:
		UART1_StringLn_Transmit("ODD");
	}
	
	while (1)
	{
	}
}



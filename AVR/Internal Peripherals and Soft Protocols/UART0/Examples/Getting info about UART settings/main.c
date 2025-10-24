
#include "uart0.h"

int main(void)
{
	UART0_Initialize(9600, true, false);
	
	UART0_String_Transmit("This is a params configurations of UART0:\r\n\r\n");
	
	UART0_StringFmt_Transmit("Baudrate: ------------------------------- %lu\r\n", UART0_Get_Baudrate());
	UART0_StringFmt_Transmit("Transmittion is enable: ----------------- %s\r\n",  UART0_Transmittion_Is_Enable()                  ? "true" : "false");
	UART0_StringFmt_Transmit("Reception is enable: -------------------- %s\r\n",  UART0_Reception_Is_Enable()                     ? "true" : "false");
	UART0_StringFmt_Transmit("Buffer emptying interrupt is enable: ---- %s\r\n",  UART0_Buffer_Emptying_Interrupt_Is_Enable()     ? "true" : "false");
	UART0_StringFmt_Transmit("End of transmittion interrupt is enable:  %s\r\n",  UART0_End_Of_Transmittion_Interrupt_Is_Enable() ? "true" : "false");
	UART0_StringFmt_Transmit("End of reception interrupt is enable: --- %s\r\n",  UART0_End_Of_Reception_Interrupt_Is_Enable()    ? "true" : "false");
	UART0_StringFmt_Transmit("Num of data bits: ----------------------- %d\r\n",  UART0_Get_Num_Of_Data_Bits());
	UART0_StringFmt_Transmit("Num of stop bits: ----------------------- %d\r\n",  UART0_Get_Num_Of_Stop_Bits());
	
	UART0_String_Transmit("Parity bit: ----------------------------- ");
	
	switch(UART0_Get_Parity_Bit())
	{
		case UART0_PARITY_BIT_NONE:
		UART0_StringLn_Transmit("NONE");
		break;
		case UART0_PARITY_BIT_EVEN:
		UART0_StringLn_Transmit("EVEN");
		break;
		default:
		UART0_StringLn_Transmit("ODD");
	}
	
	while (1)
	{
	}
}



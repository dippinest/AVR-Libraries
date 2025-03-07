
#include "uart0.h"

int main(void)
{
	UART0_Initialize(9600, true, false);
	
	UART0_String_Transmit("Hello from UART0!");
	
	while (1)
	{
	}
}

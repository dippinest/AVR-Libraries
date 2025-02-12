
#include "uart1.h"

int main(void)
{
	UART1_Initialize(9600, true, false);
	
	UART1_String_Transmit("Hello from UART1!");
	
	while (1)
	{
	}
}


#include "uart1.h"
#include "uart1_async.h"

#define RX_BUFFER_SIZE 10
static char rx_buffer[RX_BUFFER_SIZE];

void send_buffer()
{
	UART1_Async_Data_Transmit(rx_buffer, RX_BUFFER_SIZE);
	
	UART1_Async_Start_Reception_Data_To_Buffer();
}

int main(void)
{
	UART1_Initialize(9600, true, true);
	
	sei();
	
	UART1_Async_Set_Transmittion_Enable(true);
	UART1_Async_Set_Reception_Enable(true);
	
	UART1_Async_Set_Reception_Buffer_Ptr(rx_buffer);
	UART1_Async_Set_Reception_Buffer_Size(RX_BUFFER_SIZE);
	
	UART1_Async_Set_Reception_CallBack_Function(send_buffer);
	
	UART1_Async_Start_Reception_Data_To_Buffer();
	
	while (1)
	{
	}
}



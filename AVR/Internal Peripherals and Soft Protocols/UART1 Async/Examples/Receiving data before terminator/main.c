
#include "uart1.h"
#include "uart1_async.h"

#define RX_BUFFER_SIZE 32

uint8_t rx_buffer[RX_BUFFER_SIZE];


#define TERMINATOR_SYMBOL ';'


void send_buffer()
{
	UART1_Data_Transmit(rx_buffer, UART1_Async_Get_Reception_Buffer_Counter()); UART1_NEW_LINE;
	
	UART1_Async_Start_Reception_Data_To_Buffer();
}

int main(void)
{
	UART1_Initialize(9600, true, true);
	
	
	UART1_Async_Set_Transmittion_Enable(true);
	UART1_Async_Set_Reception_Enable(true);
	
	UART1_Async_Set_Reception_Buffer_Ptr(rx_buffer);
	UART1_Async_Set_Reception_Buffer_Size(RX_BUFFER_SIZE);
	
	UART1_Async_Set_Reception_Terminator(TERMINATOR_SYMBOL);
	UART1_Async_Set_Reception_Terminator_Enable(true);
	
	UART1_Async_Set_Reception_CallBack_Function(send_buffer);
	
	UART1_Async_Start_Reception_Data_To_Buffer();
	
	
	sei();
	
	while (1)
	{
	}
}




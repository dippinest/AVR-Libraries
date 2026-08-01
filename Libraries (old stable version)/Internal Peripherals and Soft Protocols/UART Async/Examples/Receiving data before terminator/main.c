
#include "uart.h"
#include "uart_async.h"

#define RX_BUFFER_SIZE 32

uint8_t rx_buffer[RX_BUFFER_SIZE];


#define TERMINATOR_SYMBOL ';'


void send_buffer()
{
	UART_Data_Transmit(rx_buffer, UART_Async_Get_Reception_Buffer_Counter()); UART_NEW_LINE;
	
	UART_Async_Start_Reception_Data_To_Buffer();
}

int main(void)
{
	UART_Initialize(9600, true, true);
	
	
	UART_Async_Set_Transmittion_Enable(true);
	UART_Async_Set_Reception_Enable(true);
	
	UART_Async_Set_Reception_Buffer_Ptr(rx_buffer);
	UART_Async_Set_Reception_Buffer_Size(RX_BUFFER_SIZE);
	
	UART_Async_Set_Reception_Terminator(TERMINATOR_SYMBOL);
	UART_Async_Set_Reception_Terminator_Enable(true);
	
	UART_Async_Set_Reception_Callback_Function(send_buffer);
	
	UART_Async_Start_Reception_Data_To_Buffer();
	
	
	sei();
	
	while (1)
	{
	}
}





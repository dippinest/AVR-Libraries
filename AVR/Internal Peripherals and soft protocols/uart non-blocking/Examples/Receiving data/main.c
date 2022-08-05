
#include "uart.h"
#include "uart_non_blocking.h"

#define RX_BUFFER_SIZE 10
static char rx_buffer[RX_BUFFER_SIZE];

void send_buffer()
{
	UART_NB_Data_Transmit(rx_buffer, RX_BUFFER_SIZE);
	
	while(UART_NB_Get_Transmittion_Status() == UART_NON_BLOCKING_TRANSMITTION_IS_ACTIVE);
	
	UART_NB_Start_Reception_Data_To_Buffer();
}

int main(void)
{
	UART_Initialize(9600, true, true);
	
	sei();
	
	UART_NB_Set_Transmittion_Enable(true);
	UART_NB_Set_Reception_Enable(true);
	
	UART_NB_Set_Reception_Buffer_Ptr(rx_buffer);
	UART_NB_Set_Reception_Buffer_Size(RX_BUFFER_SIZE);
	
	UART_NB_Set_Reception_CallBack_Function(send_buffer);
	
	UART_NB_Start_Reception_Data_To_Buffer();
	
	while (1)
	{
	}
}

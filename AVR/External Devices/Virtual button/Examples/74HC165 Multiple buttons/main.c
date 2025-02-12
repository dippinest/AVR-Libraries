

#include <util/delay.h>

#include "softspi.h"
#include "virtualbutton.h"
#include "uart.h"



void VButton1_Press()
{
	UART_StringLn_Transmit("Button 1 was pressed!");
}

void VButton1_Long_Press()
{
	UART_StringLn_Transmit("Button 1 is pressed very long...");
}



void VButton2_Press()
{
	UART_StringLn_Transmit("Button 2 was pressed!");
}

void VButton2_Long_Press()
{
	UART_StringLn_Transmit("Button 2 is pressed very long...");
}



void VButton3_Press()
{
	UART_StringLn_Transmit("Button 3 was pressed!");
}

void VButton3_Long_Press()
{
	UART_StringLn_Transmit("Button 3 is pressed very long...");
}



void VButton4_Press()
{
	UART_StringLn_Transmit("Button 4 was pressed!");
}

void VButton4_Long_Press()
{
	UART_StringLn_Transmit("Button 4 is pressed very long...");
}



// macro enabling latches that transmit data to the storage register
#define HC165_LATCHES         \
	PORTA &= ~(1 << PORTA0);  \
	PORTA |=  (1 << PORTA0);


int main(void)
{
	DDRA |= (1 << PORTA0);
	
	
	uint8_t hc165_data;
	
	
	VirtualButton_t vbutton1 = VirtualButton_Create_Object(&hc165_data, 0, VIRTUALBUTTON_INPUT_LOGICAL_LEVEL_HIGH);
	VirtualButton_t vbutton2 = VirtualButton_Create_Object(&hc165_data, 1, VIRTUALBUTTON_INPUT_LOGICAL_LEVEL_HIGH);
	VirtualButton_t vbutton3 = VirtualButton_Create_Object(&hc165_data, 2, VIRTUALBUTTON_INPUT_LOGICAL_LEVEL_HIGH);
	VirtualButton_t vbutton4 = VirtualButton_Create_Object(&hc165_data, 3, VIRTUALBUTTON_INPUT_LOGICAL_LEVEL_HIGH);
	
	
	UART_Initialize(9600, true, false);
	
	SOFTSPI_Initialize();
	
	while (1)
	{
		HC165_LATCHES; hc165_data = SOFTSPI_Get_Byte();
		
		VirtualButton_Pressed_Polling(&vbutton1, VButton1_Press);
		VirtualButton_Long_Pressed_Polling(&vbutton1, 100, VButton1_Long_Press);
		
		VirtualButton_Pressed_Polling(&vbutton2, VButton2_Press);
		VirtualButton_Long_Pressed_Polling(&vbutton2, 100, VButton2_Long_Press);
		
		VirtualButton_Pressed_Polling(&vbutton3, VButton3_Press);
		VirtualButton_Long_Pressed_Polling(&vbutton3, 100, VButton3_Long_Press);
		
		VirtualButton_Pressed_Polling(&vbutton4, VButton4_Press);
		VirtualButton_Long_Pressed_Polling(&vbutton4, 100, VButton4_Long_Press);
		
		
		// вызываем функции опроса каждые 20 мс
		// -------------------------------------------------------------------------------
		// calling the polling functions every 20 ms
		//
		_delay_ms(20);
	}
}




#include "softi2c.h"
#include "frami2c.h"

#include "uart.h"

typedef struct
{
	int8_t   i8_1;
	int8_t   i8_2;
	
	uint16_t u16_1;
	uint16_t u16_2;
	
} Data_t;

static Data_t data1, data2;


int main(void)
{
	SOFTI2C_Initialize();
	
	
	FRAMI2C_t fram = FRAMI2C_Create_Object(FRAMI2C_DEV_ADDR_A2F_A1F_A0F, FM24C256_MAX_MEM_ADDR);
	
	FRAMI2C_Set_Target_Object(&fram);
	
	
	UART_Initialize(9600, true, false);
	
	
	// запись данных из структуры типа Data_t в FRAM по адресу 0x0000 (закомментировано)
	// -------------------------------------------------------------------------------
	// writing data from the Data_t type structure to FRAM at 0x0000 (commented out)
	
	//data1.i8_1  = -34;
	//data1.i8_2  =  45;
	//data1.u16_1 =  1234;
	//data1.u16_2 = -13623;
	
	//FRAMI2C_Write_Data(0x0000, &data1, sizeof(Data_t));
	
	
	
	// запись данных из FRAM по адресу 0x0000 в структуру типа Data_t
	// -------------------------------------------------------------------------------
	// writing data from FRAM at address 0x0000 to a Data_t type structure
	FRAMI2C_Read_Data(0x0000, &data2, sizeof(Data_t));
	
	UART_StringFmt_Transmit("i8_1  = %i\r\n", data2.i8_1);
	UART_StringFmt_Transmit("i8_2  = %i\r\n", data2.i8_2);
	UART_StringFmt_Transmit("u16_1 = %i\r\n", data2.u16_1);
	UART_StringFmt_Transmit("u16_2 = %i\r\n", data2.u16_2);
	
	while (1)
	{
	}
}




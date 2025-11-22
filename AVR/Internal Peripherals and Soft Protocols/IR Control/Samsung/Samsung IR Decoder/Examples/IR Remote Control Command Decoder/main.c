
// ===============================================================================
//
// Внимание!!! Не забудьте настроить работу библиотеки
// в файле samsung_ir_decoder_configuration.h !!!
//
// -------------------------------------------------------------------------------
//
// Attention!!! Don't forget to configure the library
// in the samsung_ir_decoder_configuration.h file!!!
//
// ===============================================================================


#include "uart.h"
#include "samsung_ir_decoder.h"


// функция-колбэк, срабатывающая при принятии пакета данных
//
// -------------------------------------------------------------------------------
// callback function that is triggered when a data packet is received
//
void Samsung_IR_Decoder_Callback()
{
	// получение значения данных принятого пакета
	//
	// -------------------------------------------------------------------------------
	// getting the data value of the received packet
	//
	Samsung_IR_Protocol_Data_t samsung_ir = Samsung_IR_Decoder_Get_Data();
	
	
	// если формат данных соответствует стандарту протокола Samsung
	// (addr -> addr -> cmd -> ~cmd), выводим данные.
	//
	// Если вы используете самодельный пульт с нестандартным форматом,
	// то обрабатывайте данные "как есть"
	//
	// -------------------------------------------------------------------------------
	// if the data format conforms to the Samsung protocol standard
	// (addr -> addr -> cmd -> ~cmd), output the data.
	//
	// If you are using a homemade remote control with a non-standard format,
	// then process the data "as is".
	//
	if (Samsung_IR_Check_Package_Integrity_For_Standart_Protocol(&samsung_ir))
	{
		UART_StringFmt_Transmit
		(
			"ADDR1 = %X, ADDR2 = %X, CMD1 = %X, CMD2 = %X, is repeat = %d\r\n",
			samsung_ir.addr_1,
			samsung_ir.addr_2,
			samsung_ir.commmand_1,
			samsung_ir.commmand_2,
			Samsung_IR_Decoder_Received_Package_Is_Repeated()
		);	
	}
	else
	{
		UART_StringLn_Transmit("Error.");
	}
}


int main(void)
{
	UART_Initialize(115200, true, false);
	
	
	// инициализация декодера
	//
	// -------------------------------------------------------------------------------
	// decoder initializing
	//
	Samsung_IR_Decoder_Initialize(Samsung_IR_Decoder_Callback);
	
	
	// не забудьте включить глобальные прерывания
	//
	// -------------------------------------------------------------------------------
	// don't forget to enable global interrupts
	//
	sei();
	
	while (1)
	{
	}
}





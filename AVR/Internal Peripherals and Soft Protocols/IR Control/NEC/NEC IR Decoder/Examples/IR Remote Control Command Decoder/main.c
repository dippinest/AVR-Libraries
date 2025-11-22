
// ===============================================================================
//
// Внимание!!! Не забудьте настроить работу библиотеки
// в файле nec_ir_decoder_configuration.h !!!
//
// -------------------------------------------------------------------------------
//
// Attention!!! Don't forget to configure the library
// in the nec_ir_decoder_configuration.h file!!!
//
// ===============================================================================


#include "uart.h"
#include "nec_ir_decoder.h"


// функция-колбэк, срабатывающая при принятии пакета данных
//
// -------------------------------------------------------------------------------
// callback function that is triggered when a data packet is received
//
void NEC_IR_Decoder_Callback()
{
	// получение значения данных принятого пакета
	//
	// -------------------------------------------------------------------------------
	// getting the data value of the received packet
	//
	NEC_IR_Protocol_Data_t nec_ir = NEC_IR_Decoder_Get_Data();
	
	
	// если формат данных соответствует стандарту протокола NEC
	// (addr -> ~addr -> cmd -> ~cmd), выводим данные.
	//
	// Если вы используете самодельный пульт с нестандартным форматом,
	// то обрабатывайте данные "как есть"
	//
	// -------------------------------------------------------------------------------
	// if the data format conforms to the NEC protocol standard
	// (addr -> ~addr -> cmd -> ~cmd), output the data.
	//
	// If you are using a homemade remote control with a non-standard format,
	// then process the data "as is".
	//
	if (NEC_IR_Check_Package_Integrity_For_Standart_Protocol(&nec_ir))
	{
		UART_StringFmt_Transmit
		(
		"ADDR1 = %X, ADDR2 = %X, CMD1 = %X, CMD2 = %X\r\n",
		nec_ir.addr_1,
		nec_ir.addr_2,
		nec_ir.command_1,
		nec_ir.command_2
		);
	}
	else
	{
		UART_StringLn_Transmit("Error.");
	}
}


// функция-колбэк, срабатывающая при повторном принятии пакета данных
//
// -------------------------------------------------------------------------------
// A callback function that is triggered when a data packet is received again
//
void NEC_IR_Decoder_Repeat_Callback()
{
	UART_StringLn_Transmit("Repeat package...");
}


int main(void)
{
	UART_Initialize(115200, true, false);
	
	
	// инициализация декодера
	//
	// Первая передаваемая функция срабатывает при первом принятии
	// пакета NEC протокола; вторая - при повторных принятиях пакета
	//
	// -------------------------------------------------------------------------------
	// decoder initializing
	//
	// first transmitted function is triggered when the NEC protocol
	// packet is received for the first time; the second is triggered
	// when the packet is received again
	//
	NEC_IR_Decoder_Initialize(NEC_IR_Decoder_Callback, NEC_IR_Decoder_Repeat_Callback);
	
	
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





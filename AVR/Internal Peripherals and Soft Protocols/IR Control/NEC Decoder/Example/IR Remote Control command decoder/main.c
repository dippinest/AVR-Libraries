
// ===============================================================================
//
// Внимание!!! Не забудьте настроить работу библиотеки
// в файле nec_decoder_configuration.h !!!
//
// -------------------------------------------------------------------------------
//
// Attention!!! Don't forget to configure the library
// in the nec_decoder_configuration.h file!!!
//
// ===============================================================================




#include "uart.h"
#include "nec_decoder.h"


void NEC_Decoder_Callback()
{
	NEC_Protocol_Data_t nec = NEC_Decoder_Get_Data();
	
	UART_StringFmt_Transmit("ADDR = %X, CMD = %X\r\n", nec.addr, nec.commmand);
}


int main(void)
{
	UART_Initialize(9600, true, false);
	
	
	// первая передаваемая функция срабатывает при первом принятии
	// пакета NEC протокола; вторая - при повторных принятиях пакета
	// -------------------------------------------------------------------------------
	// first transmitted function is triggered when the NEC protocol
	// packet is received for the first time; the second is triggered
	// when the packet is received again.
	
	NEC_Decoder_Initialize(NEC_Decoder_Callback, NULL);
	
	
	// не забудьте включить глобальные прерывания
	// -------------------------------------------------------------------------------
	// don't forget to enable global interrupts
	sei();
	
	while (1)
	{
	}
}





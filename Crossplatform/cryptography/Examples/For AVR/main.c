
#include <string.h>

#define F_CPU 16000000UL
#include "uart.h"
#include "xtea3.h"

static char data[]      = "This is my a supersecret data";
static const char key[] = "Supersecret key!";

static void print_hex_data(uint16_t str_len)
{
	for (uint16_t i = 0; i < str_len; ++i)
	{
		UART_StringFmt_Transmit("%X ", data[i]);
	}
}

int main(void)
{
	UART_Initialize(9600, true, false);
	
	UART_StringFmt_Transmit("\r\n\r\nOpen data:    "); print_hex_data(strlen(data));
	
	uint16_t encrypt_data_size = XTEA3_Encrypt_ECB(data, sizeof(data), key, 32);
	UART_StringFmt_Transmit("\r\n\r\nEncrypt data: "); print_hex_data(encrypt_data_size);
	
	uint16_t decrypt_data_size = XTEA3_Decrypt_ECB(data, sizeof(data), key, 32);
	UART_StringFmt_Transmit("\r\n\r\nDecrypt data: "); print_hex_data(decrypt_data_size);
	
	while (1)
	{
	}
}

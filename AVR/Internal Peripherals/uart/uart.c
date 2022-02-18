// ======================================================================================================
//  Source              : uart.c                                                                        -
//  Created             : 11.02.2022                                                                    -
//  Author              : Denis Chicherov (dippinest)                                                   -
//  Description         : Defining functions and macros for working with the UART module                -
// ======================================================================================================

#include "uart.h"

static volatile uint8_t  _UCSRC            = 0;
static volatile uint32_t _baudrate_code    = 0;
static volatile uint32_t _current_baudrate = 0;

static void UART_Set_Baudrate(uint32_t baudrate)
{
	_current_baudrate = baudrate;
	_baudrate_code    = _UART_SET_CODE_BAUDRATE(_current_baudrate);

	UCSRA |=  (1 << U2X);
	UBRRH = (uint8_t)(_baudrate_code >> 8);
	UBRRL = (uint8_t)(_baudrate_code);
}

static void UART_Set_Transmission_Is_Allowed(bool transmission_is_allowed)
{
	if (transmission_is_allowed)
	{
		UCSRB |=  (1 << TXEN);
	}
	else
	{
		UCSRB &= ~(1 << TXEN);
	}
}

static void UART_Set_Reception_Is_Allowed(bool reception_is_allowed)
{
	if (reception_is_allowed)
	{
		UCSRB |=  (1 << RXEN);
	}
	else
	{
		UCSRB &= ~(1 << RXEN);
	}
}

static void UART_Set_Buffer_Emptying_Interrupt_Is_Allowed(bool buffer_emptying_interrupt_is_allowed)
{
	if (buffer_emptying_interrupt_is_allowed)
	{
		UCSRB |=  (1 << UDRIE);
	}
	else
	{
		UCSRB &= ~(1 << UDRIE);
	}
}

static void UART_Set_End_Of_Transmittion_Interrupt_Is_Allowed(bool end_of_transmittion_interrupt_is_allowed)
{
	if (end_of_transmittion_interrupt_is_allowed)
	{
		UCSRB |=  (1 << TXCIE);
	}
	else
	{
		UCSRB &= ~(1 << TXCIE);
	}
}

static void UART_Set_End_Of_Reception_Interrupt_Is_Allowed(bool end_of_reception_interrupt_is_allowed)
{
	if (end_of_reception_interrupt_is_allowed)
	{
		UCSRB |=  (1 << RXCIE);
	}
	else
	{
		UCSRB &= ~(1 << RXCIE);
	}
}

static void UART_Set_Num_Of_Data_Bits(uint8_t num_of_data_bits)
{
	_UCSRC &= ~((1 << UCSZ1) | (1 << UCSZ0));
	
	switch (num_of_data_bits)
	{
		case UART_NUM_OF_DATA_BITS_5:
		break;
		case UART_NUM_OF_DATA_BITS_6:
		_UCSRC |= (1 << UCSZ0) | (1 << URSEL);
		break;
		case UART_NUM_OF_DATA_BITS_7:
		_UCSRC |= (1 << UCSZ1) | (1 << URSEL);
		break;
		case UART_NUM_OF_DATA_BITS_8:
		default:
		_UCSRC |= (1 << UCSZ1) | (1 << UCSZ0) | (1 << URSEL);
	}
}

static void UART_Set_Num_Of_Stop_Bits(uint8_t num_of_stop_bits)
{
	_UCSRC &= ~(1 << USBS);
	
	switch (num_of_stop_bits)
	{
		case UART_NUM_OF_STOP_BITS_1:
		break;
		case UART_NUM_OF_STOP_BITS_2:
		_UCSRC |= (1 << USBS);
		break;
		default: break;
	}
}

static void UART_Set_Parity_Bit(uint8_t parity_bit)
{
	_UCSRC &= ~((1 << UPM1) | (1 << UPM0));
	
	switch (parity_bit)
	{
		case UART_PARITY_BIT_NONE:
		break;
		case UART_PARITY_BIT_EVEN:
		_UCSRC |= (1 << UPM1);
		break;
		case UART_PARITY_BIT_ODD:
		_UCSRC |= (1 << UPM1) | (1 << UPM0);
		break;
		default: break;
	}
}

uint32_t UART_Get_Baudrate()
{
	return _current_baudrate;
}

bool UART_Transmission_Is_Allowed()
{
	return (bool)(UCSRB & (1 << TXEN));
}

bool UART_Reception_Is_Allowed()
{
	return (bool)(UCSRB & (1 << RXEN));
}

bool UART_Buffer_Emptying_Interrupt_Is_Allowed()
{
	return (bool)(UCSRB & (1 << UDRIE));
}

bool UART_End_Of_Transmittion_Interrupt_Is_Allowed()
{
	return (bool)(UCSRB & (1 << TXCIE));
}

bool UART_End_Of_Reception_Interrupt_Is_Allowed()
{
	return (bool)(UCSRB & (1 << RXCIE));
}

uint8_t UART_Get_Num_Of_Data_Bits()
{
	return ((_UCSRC & ((1 << UCSZ1) | (1 << UCSZ0))) >> 1) + 5;
}

uint8_t UART_Get_Num_Of_Stop_Bits()
{
	if (_UCSRC & (1 << USBS))
	{
		return 2;
	}
	else
	{
		return 1;
	}
}

uint8_t UART_Get_Parity_Bit()
{
	return _UCSRC & ((1 << UPM1) | (1 << UPM0));
}

void UART_Initialize
(
uint32_t baudrate,
bool transmission_is_allowed,
bool reception_is_allowed,
bool buffer_emptying_interrupt_is_allowed,
bool end_of_transmittion_interrupt_is_allowed,
bool end_of_reception_interrupt_is_allowed,
uint8_t num_of_data_bits,
uint8_t num_of_stop_bits,
uint8_t parity_bit
)
{	
	UART_Set_Baudrate(baudrate);
	
	UART_Set_Transmission_Is_Allowed(transmission_is_allowed);
	UART_Set_Reception_Is_Allowed(reception_is_allowed);
	UART_Set_Buffer_Emptying_Interrupt_Is_Allowed(buffer_emptying_interrupt_is_allowed);
	UART_Set_End_Of_Transmittion_Interrupt_Is_Allowed(end_of_transmittion_interrupt_is_allowed);
	UART_Set_End_Of_Reception_Interrupt_Is_Allowed(end_of_reception_interrupt_is_allowed);
	
	UART_Set_Num_Of_Data_Bits(num_of_data_bits);
	UART_Set_Num_Of_Stop_Bits(num_of_stop_bits);
	UART_Set_Parity_Bit(parity_bit);
	
	UCSRC = (1 << URSEL) | _UCSRC;
}

void UART_Byte_Transmit(uint8_t byte)
{
	while ( !(UCSRA & (1 << UDRE)) );
	UDR = byte;
}

void UART_Data_Transmit(const void *data, uint16_t data_size)
{
	for (uint16_t i = 0; i < data_size; ++i)
	{
		UART_Byte_Transmit(((uint8_t*)data)[i]);
	}
}

void UART_String_Transmit(const char *string)
{
	for (uint16_t i = 0; string[i] != '\0'; ++i)
	{
		UART_Byte_Transmit(string[i]);
	}
}

void UART_StringLn_Transmit(const char *string)
{
	UART_String_Transmit(string);
	UART_String_Transmit("\r\n");
}

static int UART_Char_Transmit(char c, FILE *stream)
{
	while ( !(UCSRA & (1 << UDRE)) );
	UDR = c;
	return 0;
}

void UART_StringFmt_Transmit(const char *string_fmt, ...)
{
	va_list argptr;
	va_start(argptr, string_fmt);
	static FILE uartstdout = FDEV_SETUP_STREAM(UART_Char_Transmit, NULL, _FDEV_SETUP_WRITE);
	stdout = &uartstdout;
	vfprintf(stdout, string_fmt, argptr);
	va_end(argptr);
}

void UART_Safe_String_Transmit(const char *string, uint16_t max_string_len)
{
	for (uint16_t i = 0; string[i] != '\0' && i < max_string_len; ++i)
	{
		UART_Byte_Transmit(string[i]);
	}
}

void UART_Safe_StringLn_Transmit(const char *string, uint16_t max_string_len)
{
	UART_Safe_String_Transmit(string, max_string_len);
	UART_Safe_String_Transmit("\r\n", 2);
}

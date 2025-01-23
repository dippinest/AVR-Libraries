
#include "uart.h"

static volatile uint8_t  _UCSRC            = 0;
static volatile uint32_t _baudrate_code    = 0;
static volatile uint32_t _current_baudrate = 0;

// ===============================================================================

void UART_Set_Baudrate(uint32_t baudrate)
{
	_current_baudrate = baudrate;
	_baudrate_code    = _UART_SET_CODE_BAUDRATE(_current_baudrate);

	UCSRA |=  (1 << U2X);
	UBRRH = (uint8_t)(_baudrate_code >> 8);
	UBRRL = (uint8_t)(_baudrate_code);
}


uint32_t UART_Get_Baudrate()
{
	return _current_baudrate;
}

void UART_Set_Num_Of_Data_Bits(uint8_t num_of_data_bits)
{
	_UCSRC &= ~((1 << UCSZ1) | (1 << UCSZ0));
	
	switch (num_of_data_bits)
	{
		case UART_NUM_OF_DATA_BITS_5:
		break;
		case UART_NUM_OF_DATA_BITS_6:
		
		#ifdef URSEL
		_UCSRC |= (1 << UCSZ0) | (1 << URSEL);
		#else
		_UCSRC |= (1 << UCSZ0);
		#endif
		
		break;
		case UART_NUM_OF_DATA_BITS_7:
		
		#ifdef URSEL
		_UCSRC |= (1 << UCSZ1) | (1 << URSEL);
		#else
		_UCSRC |= (1 << UCSZ1);
		#endif
		
		break;
		case UART_NUM_OF_DATA_BITS_8:
		default:
		
		#ifdef URSEL
		_UCSRC |= (1 << UCSZ1) | (1 << UCSZ0) | (1 << URSEL);
		#else
		_UCSRC |= (1 << UCSZ1) | (1 << UCSZ0);
		#endif
	}
	
	#ifdef URSEL
	UCSRC = (1 << URSEL) | _UCSRC;
	#else
	UCSRC = _UCSRC;
	#endif
}


void UART_Set_Num_Of_Stop_Bits(uint8_t num_of_stop_bits)
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
	
	#ifdef URSEL
	UCSRC = (1 << URSEL) | _UCSRC;
	#else
	UCSRC = _UCSRC;
	#endif
	
}


void UART_Set_Parity_Bit(uint8_t parity_bit)
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
	
	#ifdef URSEL
	UCSRC = (1 << URSEL) | _UCSRC;
	#else
	UCSRC = _UCSRC;
	#endif
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

// ===============================================================================

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


// ===============================================================================


void UART_Flash_Byte_Transmit(const uint8_t *flash_byte)
{
	UART_Byte_Transmit(pgm_read_byte(flash_byte));
}


void UART_Flash_Data_Transmit(const void *flash_data, uint16_t flash_data_size)
{
	for (uint16_t i = 0; i < flash_data_size; ++i)
	{
		UART_Byte_Transmit(pgm_read_byte(&((uint8_t*)flash_data)[i]) );
	}
}


void UART_Flash_String_Transmit(const char *flash_string)
{
	char c = pgm_read_byte(&((uint8_t*)flash_string)[0]);
	uint16_t i = 0;
	
	while (c != '\0')
	{
		++i;
		UART_Byte_Transmit(c);
		c = pgm_read_byte(&((uint8_t*)flash_string)[i]);
	}
}


void UART_Flash_StringLn_Transmit(const char *flash_string)
{
	char c = pgm_read_byte(&((uint8_t*)flash_string)[0]);
	uint16_t i = 0;
	
	while (c != '\0')
	{
		++i;
		UART_Byte_Transmit(c);
		c = pgm_read_byte(&((uint8_t*)flash_string)[i]);
	}
	
	UART_String_Transmit("\r\n");
}


void UART_Flash_StringFmt_Transmit(const char *flash_string_fmt, ...)
{
	const uint16_t flash_string_size = strlen_P(flash_string_fmt);
	
	char string_buffer[flash_string_size];
	
	strcpy_P(string_buffer, flash_string_fmt);
	
	va_list argptr;
	va_start(argptr, flash_string_fmt);
	static FILE uartstdout = FDEV_SETUP_STREAM(UART_Char_Transmit, NULL, _FDEV_SETUP_WRITE);
	stdout = &uartstdout;
	vfprintf(stdout, string_buffer, argptr);
	va_end(argptr);
}


void UART_Flash_Safe_String_Transmit(const char *flash_string, uint16_t max_flash_string_len)
{
	char c = pgm_read_byte(&((uint8_t*)flash_string)[0]);
	uint16_t i = 0;
	
	while (c != '\0' && i < max_flash_string_len)
	{
		++i;
		UART_Byte_Transmit(c);
		c = pgm_read_byte(&((uint8_t*)flash_string)[i]);
	}
}


void UART_Flash_Safe_StringLn_Transmit(const char *flash_string, uint16_t max_flash_string_len)
{
	UART_Flash_Safe_String_Transmit(flash_string, max_flash_string_len);
	UART_Safe_String_Transmit("\r\n", 2);
}

// ===============================================================================

uint8_t UART_Byte_Receive()
{
	while ( !(UCSRA & (1 << RXC)) );
	return UDR;
}


void *UART_Data_Receive(void *data, uint16_t data_size)
{
	for (uint16_t i = 0; i < data_size; ++i)
	{
		((uint8_t*)data)[i] = UART_Byte_Receive();
	}
	
	return data;
}

uint16_t UART_Data_Receive_Before_Terminator(void *data, uint8_t terminator, uint16_t max_data_size)
{
	uint16_t reception_counter = 0;
	
	while (reception_counter < max_data_size)
	{
		uint8_t b = UART_Byte_Receive();
		
		((uint8_t*)data)[reception_counter] = b;
		
		++reception_counter;
		
		if (b == terminator)
		{
			break;
		}
	}
	
	return reception_counter;
}


// ===============================================================================


void UART_Initialize(uint32_t baudrate, bool transmittion_is_enable, bool reception_is_enable)
{
	UART_Set_Baudrate(baudrate);
	
	UART_Set_Num_Of_Data_Bits(UART_NUM_OF_DATA_BITS_8);
	UART_Set_Num_Of_Stop_Bits(UART_NUM_OF_STOP_BITS_1);
	UART_Set_Parity_Bit(UART_PARITY_BIT_NONE);
	
	UART_Set_Transmittion_Enable(transmittion_is_enable);
	UART_Set_Reception_Enable(reception_is_enable);
}

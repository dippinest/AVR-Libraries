
#include "uart1.h"

static volatile uint8_t  _UCSRC1            = 0;
static volatile uint32_t _baudrate_code1    = 0;
static volatile uint32_t _current_baudrate1 = 0;

// ===============================================================================

void UART1_Set_Baudrate(uint32_t baudrate)
{
	_current_baudrate1 = baudrate;
	_baudrate_code1    = _UART1_SET_CODE_BAUDRATE(_current_baudrate1);

	UCSR1A |=  (1 << U2X1);
	UBRR1H = (uint8_t)(_baudrate_code1 >> 8);
	UBRR1L = (uint8_t)(_baudrate_code1);
}


uint32_t UART1_Get_Baudrate()
{
	return _current_baudrate1;
}

void UART1_Set_Num_Of_Data_Bits(uint8_t num_of_data_bits)
{
	_UCSRC1 &= ~((1 << UCSZ11) | (1 << UCSZ10));
	
	switch (num_of_data_bits)
	{
		case UART1_NUM_OF_DATA_BITS_5:
		break;
		case UART1_NUM_OF_DATA_BITS_6:
		
		#ifdef URSEL1
		_UCSRC1 |= (1 << UCSZ10) | (1 << URSEL1);
		#else
		_UCSRC1 |= (1 << UCSZ10);
		#endif
		
		break;
		case UART1_NUM_OF_DATA_BITS_7:
		
		#ifdef URSEL1
		_UCSRC1 |= (1 << UCSZ11) | (1 << URSEL1);
		#else
		_UCSRC1 |= (1 << UCSZ11);
		#endif
		
		break;
		case UART1_NUM_OF_DATA_BITS_8:
		default:
		
		#ifdef URSEL1
		_UCSRC1 |= (1 << UCSZ11) | (1 << UCSZ10) | (1 << URSEL1);
		#else
		_UCSRC1 |= (1 << UCSZ11) | (1 << UCSZ10);
		#endif
	}
	
	#ifdef URSEL1
	UCSR1C = (1 << URSEL1) | _UCSRC1;
	#else
	UCSR1C = _UCSRC1;
	#endif
}


void UART1_Set_Num_Of_Stop_Bits(uint8_t num_of_stop_bits)
{
	_UCSRC1 &= ~(1 << USBS1);
	
	switch (num_of_stop_bits)
	{
		case UART1_NUM_OF_STOP_BITS_1:
		break;
		case UART1_NUM_OF_STOP_BITS_2:
		_UCSRC1 |= (1 << USBS1);
		break;
		default: break;
	}
	
	#ifdef URSEL1
	UCSR1C = (1 << URSEL1) | _UCSRC1;
	#else
	UCSR1C = _UCSRC1;
	#endif
	
}


void UART1_Set_Parity_Bit(uint8_t parity_bit)
{
	_UCSRC1 &= ~((1 << UPM11) | (1 << UPM10));
	
	switch (parity_bit)
	{
		case UART1_PARITY_BIT_NONE:
		break;
		case UART1_PARITY_BIT_EVEN:
		_UCSRC1 |= (1 << UPM11);
		break;
		case UART1_PARITY_BIT_ODD:
		_UCSRC1 |= (1 << UPM11) | (1 << UPM10);
		break;
		default: break;
	}
	
	#ifdef URSEL1
	UCSR1C = (1 << URSEL1) | _UCSRC1;
	#else
	UCSR1C = _UCSRC1;
	#endif
}


uint8_t UART1_Get_Num_Of_Data_Bits()
{
	return ((_UCSRC1 & ((1 << UCSZ11) | (1 << UCSZ10))) >> 1) + 5;
}


uint8_t UART1_Get_Num_Of_Stop_Bits()
{
	if (_UCSRC1 & (1 << USBS1))
	{
		return 2;
	}
	else
	{
		return 1;
	}
}

uint8_t UART1_Get_Parity_Bit()
{
	return _UCSRC1 & ((1 << UPM11) | (1 << UPM10));
}

// ===============================================================================

void UART1_Byte_Transmit(uint8_t byte)
{
	while ( !(UCSR1A & (1 << UDRE1)) );
	UDR1 = byte;
}


void UART1_Data_Transmit(const void *data, uint16_t data_size)
{
	for (uint16_t i = 0; i < data_size; ++i)
	{
		UART1_Byte_Transmit(((uint8_t*)data)[i]);
	}
}


void UART1_String_Transmit(const char *string)
{
	for (uint16_t i = 0; string[i] != '\0'; ++i)
	{
		UART1_Byte_Transmit(string[i]);
	}
}


void UART1_StringLn_Transmit(const char *string)
{
	UART1_String_Transmit(string);
	UART1_String_Transmit("\r\n");
}


static int UART1_Char_Transmit(char c, FILE *stream)
{
	while ( !(UCSR1A & (1 << UDRE1)) );
	UDR1 = c;
	return 0;
}


void UART1_StringFmt_Transmit(const char *string_fmt, ...)
{
	va_list argptr;
	va_start(argptr, string_fmt);
	static FILE uartstdout = FDEV_SETUP_STREAM(UART1_Char_Transmit, NULL, _FDEV_SETUP_WRITE);
	stdout = &uartstdout;
	vfprintf(stdout, string_fmt, argptr);
	va_end(argptr);
}


void UART1_Safe_String_Transmit(const char *string, uint16_t max_string_len)
{
	for (uint16_t i = 0; string[i] != '\0' && i < max_string_len; ++i)
	{
		UART1_Byte_Transmit(string[i]);
	}
}


void UART1_Safe_StringLn_Transmit(const char *string, uint16_t max_string_len)
{
	UART1_Safe_String_Transmit(string, max_string_len);
	UART1_Safe_String_Transmit("\r\n", 2);
}


// ===============================================================================


void UART1_Flash_Byte_Transmit(const uint8_t *flash_byte)
{
	UART1_Byte_Transmit(pgm_read_byte(flash_byte));
}


void UART1_Flash_Data_Transmit(const void *flash_data, uint16_t flash_data_size)
{
	for (uint16_t i = 0; i < flash_data_size; ++i)
	{
		UART1_Byte_Transmit(pgm_read_byte(&((uint8_t*)flash_data)[i]) );
	}
}


void UART1_Flash_String_Transmit(const char *flash_string)
{
	char c = pgm_read_byte(&((uint8_t*)flash_string)[0]);
	uint16_t i = 0;
	
	while (c != '\0')
	{
		++i;
		UART1_Byte_Transmit(c);
		c = pgm_read_byte(&((uint8_t*)flash_string)[i]);
	}
}


void UART1_Flash_StringLn_Transmit(const char *flash_string)
{
	char c = pgm_read_byte(&((uint8_t*)flash_string)[0]);
	uint16_t i = 0;
	
	while (c != '\0')
	{
		++i;
		UART1_Byte_Transmit(c);
		c = pgm_read_byte(&((uint8_t*)flash_string)[i]);
	}
	
	UART1_String_Transmit("\r\n");
}


void UART1_Flash_StringFmt_Transmit(const char *flash_string_fmt, ...)
{
	const uint16_t flash_string_size = strlen_P(flash_string_fmt);
	
	char string_buffer[flash_string_size];
	
	strcpy_P(string_buffer, flash_string_fmt);
	
	va_list argptr;
	va_start(argptr, flash_string_fmt);
	static FILE uartstdout = FDEV_SETUP_STREAM(UART1_Char_Transmit, NULL, _FDEV_SETUP_WRITE);
	stdout = &uartstdout;
	vfprintf(stdout, string_buffer, argptr);
	va_end(argptr);
}


void UART1_Flash_Safe_String_Transmit(const char *flash_string, uint16_t max_flash_string_len)
{
	char c = pgm_read_byte(&((uint8_t*)flash_string)[0]);
	uint16_t i = 0;
	
	while (c != '\0' && i < max_flash_string_len)
	{
		++i;
		UART1_Byte_Transmit(c);
		c = pgm_read_byte(&((uint8_t*)flash_string)[i]);
	}
}


void UART1_Flash_Safe_StringLn_Transmit(const char *flash_string, uint16_t max_flash_string_len)
{
	UART1_Flash_Safe_String_Transmit(flash_string, max_flash_string_len);
	UART1_Safe_String_Transmit("\r\n", 2);
}

// ===============================================================================

uint8_t UART1_Byte_Receive()
{
	while ( !(UCSR1A & (1 << RXC1)) );
	return UDR1;
}


void *UART1_Data_Receive(void *data, uint16_t data_size)
{
	for (uint16_t i = 0; i < data_size; ++i)
	{
		((uint8_t*)data)[i] = UART1_Byte_Receive();
	}
	
	return data;
}


uint16_t UART1_Data_Receive_Before_Terminator(void *data, uint8_t terminator, uint16_t max_data_size)
{
	uint16_t reception_counter = 0;
	
	while (reception_counter < max_data_size)
	{
		uint8_t b = UART1_Byte_Receive();
		
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


void UART1_Initialize(uint32_t baudrate, bool transmittion_is_enable, bool reception_is_enable)
{
	UART1_Set_Baudrate(baudrate);
	
	UART1_Set_Num_Of_Data_Bits(UART1_NUM_OF_DATA_BITS_8);
	UART1_Set_Num_Of_Stop_Bits(UART1_NUM_OF_STOP_BITS_1);
	UART1_Set_Parity_Bit(UART1_PARITY_BIT_NONE);
	
	UART1_Set_Transmittion_Enable(transmittion_is_enable);
	UART1_Set_Reception_Enable(reception_is_enable);
}



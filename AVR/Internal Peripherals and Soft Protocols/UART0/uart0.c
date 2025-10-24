
#include "uart0.h"

static volatile uint8_t  _UCSRC0            = 0;
static volatile uint32_t _baudrate_code0    = 0;
static volatile uint32_t _current_baudrate0 = 0;

// ===============================================================================

void UART0_Set_Baudrate(uint32_t baudrate)
{
	_current_baudrate0 = baudrate;
	_baudrate_code0    = _UART0_SET_CODE_BAUDRATE(_current_baudrate0);

	UCSR0A |=  (1 << U2X0);
	UBRR0H = (uint8_t)(_baudrate_code0 >> 8);
	UBRR0L = (uint8_t)(_baudrate_code0);
}


uint32_t UART0_Get_Baudrate()
{
	return _current_baudrate0;
}

void UART0_Set_Num_Of_Data_Bits(uint8_t num_of_data_bits)
{
	_UCSRC0 &= ~((1 << UCSZ01) | (1 << UCSZ00));
	
	switch (num_of_data_bits)
	{
		case UART0_NUM_OF_DATA_BITS_5:
		break;
		case UART0_NUM_OF_DATA_BITS_6:
		
		#ifdef URSEL0
		_UCSRC0 |= (1 << UCSZ00) | (1 << URSEL0);
		#else
		_UCSRC0 |= (1 << UCSZ00);
		#endif
		
		break;
		case UART0_NUM_OF_DATA_BITS_7:
		
		#ifdef URSEL0
		_UCSRC0 |= (1 << UCSZ01) | (1 << URSEL0);
		#else
		_UCSRC0 |= (1 << UCSZ01);
		#endif
		
		break;
		case UART0_NUM_OF_DATA_BITS_8:
		default:
		
		#ifdef URSEL0
		_UCSRC0 |= (1 << UCSZ01) | (1 << UCSZ00) | (1 << URSEL0);
		#else
		_UCSRC0 |= (1 << UCSZ01) | (1 << UCSZ00);
		#endif
	}
	
	#ifdef URSEL0
	UCSR0C = (1 << URSEL0) | _UCSRC0;
	#else
	UCSR0C = _UCSRC0;
	#endif
}


void UART0_Set_Num_Of_Stop_Bits(uint8_t num_of_stop_bits)
{
	_UCSRC0 &= ~(1 << USBS0);
	
	switch (num_of_stop_bits)
	{
		case UART0_NUM_OF_STOP_BITS_1:
		break;
		case UART0_NUM_OF_STOP_BITS_2:
		_UCSRC0 |= (1 << USBS0);
		break;
		default: break;
	}
	
	#ifdef URSEL0
	UCSR0C = (1 << URSEL0) | _UCSRC0;
	#else
	UCSR0C = _UCSRC0;
	#endif
	
}


void UART0_Set_Parity_Bit(uint8_t parity_bit)
{
	_UCSRC0 &= ~((1 << UPM01) | (1 << UPM00));
	
	switch (parity_bit)
	{
		case UART0_PARITY_BIT_NONE:
		break;
		case UART0_PARITY_BIT_EVEN:
		_UCSRC0 |= (1 << UPM01);
		break;
		case UART0_PARITY_BIT_ODD:
		_UCSRC0 |= (1 << UPM01) | (1 << UPM00);
		break;
		default: break;
	}
	
	#ifdef URSEL0
	UCSR0C = (1 << URSEL0) | _UCSRC0;
	#else
	UCSR0C = _UCSRC0;
	#endif
}


uint8_t UART0_Get_Num_Of_Data_Bits()
{
	return ((_UCSRC0 & ((1 << UCSZ01) | (1 << UCSZ00))) >> 1) + 5;
}


uint8_t UART0_Get_Num_Of_Stop_Bits()
{
	if (_UCSRC0 & (1 << USBS0))
	{
		return 2;
	}
	else
	{
		return 1;
	}
}

uint8_t UART0_Get_Parity_Bit()
{
	return _UCSRC0 & ((1 << UPM01) | (1 << UPM00));
}

// ===============================================================================

void UART0_Byte_Transmit(uint8_t byte)
{
	while ( !(UCSR0A & (1 << UDRE0)) );
	UDR0 = byte;
}


void UART0_Data_Transmit(const void *data, uint16_t data_size)
{
	for (uint16_t i = 0; i < data_size; ++i)
	{
		UART0_Byte_Transmit(((uint8_t*)data)[i]);
	}
}


void UART0_String_Transmit(const char *string)
{
	for (uint16_t i = 0; string[i] != '\0'; ++i)
	{
		UART0_Byte_Transmit(string[i]);
	}
}


void UART0_StringLn_Transmit(const char *string)
{
	UART0_String_Transmit(string);
	UART0_String_Transmit("\r\n");
}


static int UART0_Char_Transmit(char c, FILE *stream)
{
	while ( !(UCSR0A & (1 << UDRE0)) );
	UDR0 = c;
	return 0;
}


void UART0_StringFmt_Transmit(const char *string_fmt, ...)
{
	va_list argptr;
	va_start(argptr, string_fmt);
	static FILE uartstdout = FDEV_SETUP_STREAM(UART0_Char_Transmit, NULL, _FDEV_SETUP_WRITE);
	stdout = &uartstdout;
	vfprintf(stdout, string_fmt, argptr);
	va_end(argptr);
}


void UART0_Safe_String_Transmit(const char *string, uint16_t max_string_len)
{
	for (uint16_t i = 0; string[i] != '\0' && i < max_string_len; ++i)
	{
		UART0_Byte_Transmit(string[i]);
	}
}


void UART0_Safe_StringLn_Transmit(const char *string, uint16_t max_string_len)
{
	UART0_Safe_String_Transmit(string, max_string_len);
	UART0_Safe_String_Transmit("\r\n", 2);
}


// ===============================================================================


void UART0_Flash_Byte_Transmit(const uint8_t *flash_byte)
{
	UART0_Byte_Transmit(pgm_read_byte(flash_byte));
}


void UART0_Flash_Data_Transmit(const void *flash_data, uint16_t flash_data_size)
{
	for (uint16_t i = 0; i < flash_data_size; ++i)
	{
		UART0_Byte_Transmit(pgm_read_byte(&((uint8_t*)flash_data)[i]) );
	}
}


void UART0_Flash_String_Transmit(const char *flash_string)
{
	char c = pgm_read_byte(&((uint8_t*)flash_string)[0]);
	uint16_t i = 0;
	
	while (c != '\0')
	{
		++i;
		UART0_Byte_Transmit(c);
		c = pgm_read_byte(&((uint8_t*)flash_string)[i]);
	}
}


void UART0_Flash_StringLn_Transmit(const char *flash_string)
{
	char c = pgm_read_byte(&((uint8_t*)flash_string)[0]);
	uint16_t i = 0;
	
	while (c != '\0')
	{
		++i;
		UART0_Byte_Transmit(c);
		c = pgm_read_byte(&((uint8_t*)flash_string)[i]);
	}
	
	UART0_String_Transmit("\r\n");
}


void UART0_Flash_StringFmt_Transmit(const char *flash_string_fmt, ...)
{
	const uint16_t flash_string_size = strlen_P(flash_string_fmt);
	
	char string_buffer[flash_string_size];
	
	strcpy_P(string_buffer, flash_string_fmt);
	
	va_list argptr;
	va_start(argptr, flash_string_fmt);
	static FILE uartstdout = FDEV_SETUP_STREAM(UART0_Char_Transmit, NULL, _FDEV_SETUP_WRITE);
	stdout = &uartstdout;
	vfprintf(stdout, string_buffer, argptr);
	va_end(argptr);
}


void UART0_Flash_Safe_String_Transmit(const char *flash_string, uint16_t max_flash_string_len)
{
	char c = pgm_read_byte(&((uint8_t*)flash_string)[0]);
	uint16_t i = 0;
	
	while (c != '\0' && i < max_flash_string_len)
	{
		++i;
		UART0_Byte_Transmit(c);
		c = pgm_read_byte(&((uint8_t*)flash_string)[i]);
	}
}


void UART0_Flash_Safe_StringLn_Transmit(const char *flash_string, uint16_t max_flash_string_len)
{
	UART0_Flash_Safe_String_Transmit(flash_string, max_flash_string_len);
	UART0_Safe_String_Transmit("\r\n", 2);
}

// ===============================================================================

uint8_t UART0_Byte_Receive()
{
	while ( !(UCSR0A & (1 << RXC0)) );
	return UDR0;
}


void *UART0_Data_Receive(void *data, uint16_t data_size)
{
	for (uint16_t i = 0; i < data_size; ++i)
	{
		((uint8_t*)data)[i] = UART0_Byte_Receive();
	}
	
	return data;
}


uint16_t UART0_Data_Receive_Before_Terminator(void *data, uint8_t terminator, uint16_t max_data_size)
{
	uint16_t reception_counter = 0;
	
	while (reception_counter < max_data_size)
	{
		uint8_t b = UART0_Byte_Receive();
		
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


void UART0_Initialize(uint32_t baudrate, bool transmittion_is_enable, bool reception_is_enable)
{
	UART0_Set_Baudrate(baudrate);
	
	UART0_Set_Num_Of_Data_Bits(UART0_NUM_OF_DATA_BITS_8);
	UART0_Set_Num_Of_Stop_Bits(UART0_NUM_OF_STOP_BITS_1);
	UART0_Set_Parity_Bit(UART0_PARITY_BIT_NONE);
	
	UART0_Set_Transmittion_Enable(transmittion_is_enable);
	UART0_Set_Reception_Enable(reception_is_enable);
}



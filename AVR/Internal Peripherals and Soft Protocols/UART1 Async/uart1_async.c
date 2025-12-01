
#include "uart1_async.h"

#ifdef UART1_ASYNC_USE_TX

static volatile uint8_t   _transmittion_byte1;
static volatile uint8_t*  _transmittion_data1       = NULL;
static volatile uint16_t  _transmittion_data_size1;
static volatile uint16_t  _transmittion_counter1    = 0;
static volatile bool      _transmittion_status1     = UART1_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;


bool UART1_Async_Get_Transmittion_Status()
{
	return _transmittion_status1;
}


static void (*_transmittion_callback1)() = NULL;
static void (*_user_transmittion_callback1)() = NULL;


#endif


#ifdef UART1_ASYNC_USE_RX

static volatile uint8_t*  _reception_data_buffer1       = NULL;
static volatile uint16_t  _reception_data_buffer_size1  = 0;
static volatile uint16_t  _reception_counter1           = 0;
static volatile bool      _reception_buffer_is_filled1  = UART1_ASYNC_RECEPTION_BUFFER_IS_NOT_FILLED;
static volatile bool      _reception_status1            = UART1_ASYNC_RECEPTION_IS_NOT_ACTIVE;
static volatile uint8_t   _reception_terminator1        = 0x00;
static volatile bool      _reception_terminator_enable1 = false;


static void (*_reception_callback1)() = NULL;


#endif

// ===============================================================================

#ifdef UART1_ASYNC_USE_RX

void UART1_Async_Set_Reception_Buffer_Ptr(const void *buffer)
{
	_reception_data_buffer1 = (uint8_t*)buffer;
}


void UART1_Async_Set_Reception_Buffer_Size(const uint16_t buffer_size)
{
	_reception_data_buffer_size1 = buffer_size;
}


void UART1_Async_Set_Reception_Terminator(uint8_t terminator)
{
	_reception_terminator1 = terminator;
}


void UART1_Async_Set_Reception_Terminator_Enable(bool is_enable)
{
	_reception_terminator_enable1 = is_enable;
}


void UART1_Async_Set_Reception_Callback_Function(void (*callback_function)())
{
	_reception_callback1 = (void*)callback_function;
}


bool UART1_Async_Get_Reception_Status()
{
	return _reception_status1;
}


bool UART1_Async_Reception_Buffer_Is_Filled()
{
	return _reception_buffer_is_filled1;
}


void *UART1_Async_Get_Reception_Buffer_Ptr()
{
	return (void*)_reception_data_buffer1;
}


uint16_t UART1_Async_Get_Reception_Buffer_Size()
{
	return _reception_data_buffer_size1;
}


uint16_t UART1_Async_Get_Reception_Buffer_Counter()
{
	return _reception_counter1;
}


uint8_t UART1_Async_Get_Reception_Terminator()
{
	return _reception_terminator1;
}


bool UART1_Async_Reception_Terminator_Is_Enable()
{
	return _reception_terminator_enable1;
}


void *UART1_Async_Get_Reception_Callback_Function()
{
	return _reception_callback1;
}


uint16_t UART1_Async_Get_Current_Reception_Buffer_Fullness()
{
	return _reception_counter1;
}


#endif

// ===============================================================================

#ifdef UART1_ASYNC_USE_TX


void UART1_Async_Set_Transmittion_Callback_Function(void (*callback_function)())
{
	_user_transmittion_callback1 = (void*)callback_function;
}


void *UART1_Async_Get_Transmittion_Callback_Function()
{
	return _user_transmittion_callback1;
}

// ===============================================================================

static void _UART1_Async_Byte_Transmit()
{
	_transmittion_callback1 = _UART1_Async_Byte_Transmit;
	
	UDR1 = _transmittion_byte1;
	
	if (_transmittion_counter1)
	{
		_transmittion_counter1 = 0;
		
		if (_user_transmittion_callback1 != NULL)
		{
			_user_transmittion_callback1();
		}
		
		_transmittion_status1 = UART1_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
	
	++_transmittion_counter1;
}


static void _UART1_Async_Data_Transmit()
{
	_transmittion_callback1 = _UART1_Async_Data_Transmit;
	
	UDR1 = _transmittion_data1[_transmittion_counter1];
	
	++_transmittion_counter1;
	
	if (_transmittion_counter1 >= _transmittion_data_size1)
	{
		_transmittion_counter1 = 0;
		
		if (_user_transmittion_callback1 != NULL)
		{
			_user_transmittion_callback1();
		}
		
		_transmittion_status1 = UART1_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
}


static void _UART1_Async_String_Transmit()
{
	_transmittion_callback1 = _UART1_Async_String_Transmit;
	
	if (_transmittion_data1[_transmittion_counter1] != '\0')
	{
		UDR1 = _transmittion_data1[_transmittion_counter1];
		++_transmittion_counter1;
	}
	else
	{
		_transmittion_counter1 = 0;
		
		if (_user_transmittion_callback1 != NULL)
		{
			_user_transmittion_callback1();
		}
		
		_transmittion_status1 = UART1_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
}


static void _UART1_Async_StringLn_Transmit()
{
	_transmittion_callback1 = _UART1_Async_StringLn_Transmit;
	
	if (_transmittion_data1[_transmittion_counter1] != '\0')
	{
		UDR1 = _transmittion_data1[_transmittion_counter1];
		++_transmittion_counter1;
	}
	else
	{
		_transmittion_counter1 = 0;
		_transmittion_status1 = UART1_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		UART1_Async_String_Transmit("\r\n");
		
		return;
	}
}


static void _UART1_Async_Safe_String_Transmit()
{
	_transmittion_callback1 = _UART1_Async_Safe_String_Transmit;
	
	if (_transmittion_data1[_transmittion_counter1] != '\0' && _transmittion_counter1 < _transmittion_data_size1)
	{
		UDR1 = _transmittion_data1[_transmittion_counter1];
		++_transmittion_counter1;
	}
	else
	{
		_transmittion_counter1 = 0;
		
		if (_user_transmittion_callback1 != NULL)
		{
			_user_transmittion_callback1();
		}
		
		_transmittion_status1 = UART1_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
}


static void _UART1_Async_Safe_StringLn_Transmit()
{
	_transmittion_callback1 = _UART1_Async_Safe_StringLn_Transmit;
	
	if (_transmittion_data1[_transmittion_counter1] != '\0' && _transmittion_counter1 < _transmittion_data_size1)
	{
		UDR1 = _transmittion_data1[_transmittion_counter1];
		++_transmittion_counter1;
	}
	else
	{
		_transmittion_counter1 = 0;
		UART1_Async_Safe_String_Transmit("\r\n", 2);
		
		return;
	}
}

// ===============================================================================

static void _UART1_Async_Flash_Data_Transmit()
{
	_transmittion_callback1 = _UART1_Async_Flash_Data_Transmit;
	
	UDR1 = pgm_read_byte(&((uint8_t*)_transmittion_data1)[_transmittion_counter1]);
	
	++_transmittion_counter1;
	
	if (_transmittion_counter1 >= _transmittion_data_size1)
	{
		_transmittion_counter1 = 0;
		
		if (_user_transmittion_callback1 != NULL)
		{
			_user_transmittion_callback1();
		}
		
		_transmittion_status1 = UART1_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
}


static void _UART1_Async_Flash_String_Transmit()
{
	_transmittion_callback1 = _UART1_Async_Flash_String_Transmit;
	
	char c = pgm_read_byte(&((uint8_t*)_transmittion_data1)[_transmittion_counter1]);
	
	if (c == '\0')
	{
		_transmittion_counter1 = 0;
		
		if (_user_transmittion_callback1 != NULL)
		{
			_user_transmittion_callback1();
		}
		
		_transmittion_status1 = UART1_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
	
	UDR1 = c;
	
	++_transmittion_counter1;
}


static void _UART1_Async_Flash_StringLn_Transmit()
{
	_transmittion_callback1 = _UART1_Async_Flash_StringLn_Transmit;
	
	char c = pgm_read_byte(&((uint8_t*)_transmittion_data1)[_transmittion_counter1]);
	
	if (c == '\0')
	{
		_transmittion_counter1 = 0;
		UART1_Async_String_Transmit("\r\n");
		return;
	}
	
	UDR1 = c;
	
	++_transmittion_counter1;
}


static void _UART1_Async_Flash_Safe_String_Transmit()
{
	_transmittion_callback1 = _UART1_Async_Flash_Safe_String_Transmit;
	
	char c = pgm_read_byte(&((uint8_t*)_transmittion_data1)[_transmittion_counter1]);
	
	if (c == '\0' || _transmittion_counter1 >= _transmittion_data_size1)
	{
		_transmittion_counter1 = 0;
		
		if (_user_transmittion_callback1 != NULL)
		{
			_user_transmittion_callback1();
		}
		
		_transmittion_status1 = UART1_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
	
	UDR1 = c;
	
	++_transmittion_counter1;
}


static void _UART1_Async_Flash_Safe_StringLn_Transmit()
{
	_transmittion_callback1 = _UART1_Async_Flash_Safe_StringLn_Transmit;
	
	char c = pgm_read_byte(&((uint8_t*)_transmittion_data1)[_transmittion_counter1]);
	
	if (c == '\0' || _transmittion_counter1 >= _transmittion_data_size1)
	{
		_transmittion_counter1 = 0;
		UART1_Async_Safe_String_Transmit("\r\n", 2);
		return;
	}
	
	UDR1 = c;
	
	++_transmittion_counter1;
}

// ===============================================================================

void UART1_Async_Byte_Transmit(uint8_t byte)
{
	_transmittion_byte1 = byte;
	_transmittion_status1 = UART1_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART1_Async_Byte_Transmit();
}


void UART1_Async_Data_Transmit(const void *data, uint16_t data_size)
{
	_transmittion_data1 = (uint8_t*)data;
	_transmittion_data_size1 = data_size;
	_transmittion_status1 = UART1_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART1_Async_Data_Transmit();
}


void UART1_Async_String_Transmit(const char *string)
{
	_transmittion_data1 = (uint8_t*)string;
	_transmittion_status1 = UART1_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART1_Async_String_Transmit();
}


void UART1_Async_StringLn_Transmit(const char *string)
{
	_transmittion_data1 = (uint8_t*)string;
	_transmittion_status1 = UART1_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART1_Async_StringLn_Transmit();
}


void UART1_Async_Safe_String_Transmit(const char *string, uint16_t max_string_len)
{
	_transmittion_data1 = (uint8_t*)string;
	_transmittion_data_size1 = max_string_len;
	_transmittion_status1 = UART1_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART1_Async_Safe_String_Transmit();
}


void UART1_Async_Safe_StringLn_Transmit(const char *string, uint16_t max_string_len)
{
	_transmittion_data1 = (uint8_t*)string;
	_transmittion_data_size1 = max_string_len;
	_transmittion_status1 = UART1_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART1_Async_Safe_StringLn_Transmit();
}

// ===============================================================================

void UART1_Async_Flash_Byte_Transmit(const uint8_t *flash_byte)
{
	_transmittion_byte1 = pgm_read_byte(flash_byte);
	_transmittion_status1 = UART1_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART1_Async_Byte_Transmit();
}


void UART1_Async_Flash_Data_Transmit(const void *flash_data, uint16_t flash_data_size)
{
	_transmittion_data1 = (uint8_t*)flash_data;
	_transmittion_data_size1 = flash_data_size;
	_transmittion_status1 = UART1_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART1_Async_Flash_Data_Transmit();
}


void UART1_Async_Flash_String_Transmit(const char *flash_string)
{
	_transmittion_data1 = (uint8_t*)flash_string;
	_transmittion_status1 = UART1_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART1_Async_Flash_String_Transmit();
}


void UART1_Async_Flash_StringLn_Transmit(const char *flash_string)
{
	_transmittion_data1 = (uint8_t*)flash_string;
	_transmittion_status1 = UART1_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART1_Async_Flash_StringLn_Transmit();
}


void UART1_Async_Flash_Safe_String_Transmit(const char *flash_string, uint16_t max_flash_string_len)
{
	_transmittion_data1 = (uint8_t*)flash_string;
	_transmittion_data_size1 = max_flash_string_len;
	_transmittion_status1 = UART1_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART1_Async_Flash_Safe_String_Transmit();
}


void UART1_Async_Flash_Safe_StringLn_Transmit(const char *flash_string, uint16_t max_flash_string_len)
{
	_transmittion_data1 = (uint8_t*)flash_string;
	_transmittion_data_size1 = max_flash_string_len;
	_transmittion_status1 = UART1_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART1_Async_Flash_Safe_StringLn_Transmit();
}


#endif

// ===============================================================================

#ifdef UART1_ASYNC_USE_RX


static void _UART1_Async_Set_Reception_Data_To_Buffer(uint8_t byte)
{
	if (_reception_status1 == UART1_ASYNC_RECEPTION_IS_ACTIVE && _reception_data_buffer1 != NULL)
	{
		_reception_data_buffer1[_reception_counter1] = byte;
		
		++_reception_counter1;
		
		if ((_reception_terminator_enable1 && (byte == _reception_terminator1)) || (_reception_counter1 >= _reception_data_buffer_size1))
		{
			UART1_Async_Stop_Reception_Data_To_Buffer();
			
			if (_reception_callback1 != NULL)
			{
				_reception_callback1();
			}
			
			_reception_counter1 = 0;
			_reception_buffer_is_filled1 = UART1_ASYNC_RECEPTION_BUFFER_IS_FILLED;
		}
	}
}

// ===============================================================================

void UART1_Async_Start_Reception_Data_To_Buffer()
{
	_reception_status1 = UART1_ASYNC_RECEPTION_IS_ACTIVE;
}


void UART1_Async_Stop_Reception_Data_To_Buffer()
{
	_reception_status1 = UART1_ASYNC_RECEPTION_IS_NOT_ACTIVE;
}


void UART1_Async_Clear_Reception_Buffer()
{
	_reception_counter1 = 0;
	_reception_buffer_is_filled1 = UART1_ASYNC_RECEPTION_BUFFER_IS_NOT_FILLED;
}


#endif

// ===============================================================================

#ifdef UART1_ASYNC_USE_TX


ISR(USART1_TXC_vect)
{
	if (_transmittion_status1 == UART1_ASYNC_TRANSMITTION_IS_ACTIVE && _transmittion_callback1 != NULL)
	{
		_transmittion_callback1();
	}
}


#endif


#ifdef UART1_ASYNC_USE_RX


ISR(USART1_RXC_vect)
{
	_UART1_Async_Set_Reception_Data_To_Buffer(UDR1);
}

#endif




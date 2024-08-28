
#include "uart_async.h"

#ifdef UART_ASYNC_USE_TX

static volatile uint8_t   _transmittion_byte;
static volatile uint8_t*  _transmittion_data = NULL;
static volatile uint16_t  _transmittion_data_size;
static volatile uint16_t  _transmittion_counter    = 0;
static volatile bool      _transmittion_status     = UART_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;


bool UART_Async_Get_Transmittion_Status()
{
	return _transmittion_status;
}


static void (*_transmittion_callback)() = NULL;
static void (*_user_transmittion_callback)() = NULL;


#endif


#ifdef UART_ASYNC_USE_RX

static volatile uint8_t*  _reception_data_buffer       = NULL;
static volatile uint16_t  _reception_data_buffer_size  = 0;
static volatile uint16_t  _reception_counter           = 0;
static volatile bool      _reception_buffer_is_filled  = UART_ASYNC_RECEPTION_BUFFER_IS_NOT_FILLED;
static volatile bool      _reception_status            = UART_ASYNC_RECEPTION_IS_NOT_ACTIVE;


static void (*_reception_callback)() = NULL;


#endif

// ===============================================================================

#ifdef UART_ASYNC_USE_RX

void UART_Async_Set_Reception_Buffer_Ptr(const void *buffer)
{
	_reception_data_buffer = (uint8_t*)buffer;
}


void UART_Async_Set_Reception_Buffer_Size(const uint16_t buffer_size)
{
	_reception_data_buffer_size = buffer_size;
}


void UART_Async_Set_Reception_CallBack_Function(void (*callback_function)())
{
	_reception_callback = (void*)callback_function;
}


bool UART_Async_Get_Reception_Status()
{
	return _reception_status;
}


bool UART_Async_Reception_Buffer_Is_Filled()
{
	return _reception_buffer_is_filled;
}


void *UART_Async_Get_Reception_Buffer_Ptr()
{
	return (void*)_reception_data_buffer;
}


uint16_t UART_Async_Get_Reception_Buffer_Size()
{
	return _reception_data_buffer_size;
}


void *UART_Async_Get_Reception_CallBack_Function()
{
	return _reception_callback;
}


uint16_t UART_Async_Get_Current_Reception_Buffer_Fullness()
{
	return _reception_counter;
}


#endif

// ===============================================================================

#ifdef UART_ASYNC_USE_TX


void UART_Async_Set_Transmittion_CallBack_Function(void (*callback_function)())
{
	_user_transmittion_callback = (void*)callback_function;
}


void *UART_Async_Get_Transmittion_CallBack_Function()
{
	return _user_transmittion_callback;
}

// ===============================================================================

static void _UART_Async_Byte_Transmit()
{
	_transmittion_callback = _UART_Async_Byte_Transmit;
	
	UDR = _transmittion_byte;
	
	if (_transmittion_counter)
	{
		_transmittion_counter = 0;
		
		if (_user_transmittion_callback != NULL)
		{
			_user_transmittion_callback();
		}
		
		_transmittion_status = UART_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
	
	++_transmittion_counter;
}


static void _UART_Async_Data_Transmit()
{
	_transmittion_callback = _UART_Async_Data_Transmit;
	
	UDR = _transmittion_data[_transmittion_counter];
	
	++_transmittion_counter;
	
	if (_transmittion_counter >= _transmittion_data_size)
	{
		_transmittion_counter = 0;
		
		if (_user_transmittion_callback != NULL)
		{
			_user_transmittion_callback();
		}
		
		_transmittion_status = UART_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
}


static void _UART_Async_String_Transmit()
{
	_transmittion_callback = _UART_Async_String_Transmit;
	
	if (_transmittion_data[_transmittion_counter] != '\0')
	{
		UDR = _transmittion_data[_transmittion_counter];
		++_transmittion_counter;
	}
	else
	{
		_transmittion_counter = 0;
		
		if (_user_transmittion_callback != NULL)
		{
			_user_transmittion_callback();
		}
		
		_transmittion_status = UART_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
}


static void _UART_Async_StringLn_Transmit()
{
	_transmittion_callback = _UART_Async_StringLn_Transmit;
	
	if (_transmittion_data[_transmittion_counter] != '\0')
	{
		UDR = _transmittion_data[_transmittion_counter];
		++_transmittion_counter;
	}
	else
	{
		_transmittion_counter = 0;
		_transmittion_status = UART_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		UART_Async_String_Transmit("\r\n");
		
		return;
	}
}


static void _UART_Async_Safe_String_Transmit()
{
	_transmittion_callback = _UART_Async_Safe_String_Transmit;
	
	if (_transmittion_data[_transmittion_counter] != '\0' && _transmittion_counter < _transmittion_data_size)
	{
		UDR = _transmittion_data[_transmittion_counter];
		++_transmittion_counter;
	}
	else
	{
		_transmittion_counter = 0;
		
		if (_user_transmittion_callback != NULL)
		{
			_user_transmittion_callback();
		}
		
		_transmittion_status = UART_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
}


static void _UART_Async_Safe_StringLn_Transmit()
{
	_transmittion_callback = _UART_Async_Safe_StringLn_Transmit;
	
	if (_transmittion_data[_transmittion_counter] != '\0' && _transmittion_counter < _transmittion_data_size)
	{
		UDR = _transmittion_data[_transmittion_counter];
		++_transmittion_counter;
	}
	else
	{
		_transmittion_counter = 0;
		UART_Async_Safe_String_Transmit("\r\n", 2);
		
		return;
	}
}

// ===============================================================================

static void _UART_Async_Flash_Data_Transmit()
{
	_transmittion_callback = _UART_Async_Flash_Data_Transmit;
	
	UDR = pgm_read_byte(&((uint8_t*)_transmittion_data)[_transmittion_counter]);
	
	++_transmittion_counter;
	
	if (_transmittion_counter >= _transmittion_data_size)
	{
		_transmittion_counter = 0;
		
		if (_user_transmittion_callback != NULL)
		{
			_user_transmittion_callback();
		}
		
		_transmittion_status = UART_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
}


static void _UART_Async_Flash_String_Transmit()
{
	_transmittion_callback = _UART_Async_Flash_String_Transmit;
	
	char c = pgm_read_byte(&((uint8_t*)_transmittion_data)[_transmittion_counter]);
	
	if (c == '\0')
	{
		_transmittion_counter = 0;
		
		if (_user_transmittion_callback != NULL)
		{
			_user_transmittion_callback();
		}
		
		_transmittion_status = UART_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
	
	UDR = c;
	
	++_transmittion_counter;
}


static void _UART_Async_Flash_StringLn_Transmit()
{
	_transmittion_callback = _UART_Async_Flash_StringLn_Transmit;
	
	char c = pgm_read_byte(&((uint8_t*)_transmittion_data)[_transmittion_counter]);
	
	if (c == '\0')
	{
		_transmittion_counter = 0;
		UART_Async_String_Transmit("\r\n");
		return;
	}
	
	UDR = c;
	
	++_transmittion_counter;
}


static void _UART_Async_Flash_Safe_String_Transmit()
{
	_transmittion_callback = _UART_Async_Flash_Safe_String_Transmit;
	
	char c = pgm_read_byte(&((uint8_t*)_transmittion_data)[_transmittion_counter]);
	
	if (c == '\0' || _transmittion_counter >= _transmittion_data_size)
	{
		_transmittion_counter = 0;
		
		if (_user_transmittion_callback != NULL)
		{
			_user_transmittion_callback();
		}
		
		_transmittion_status = UART_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
	
	UDR = c;
	
	++_transmittion_counter;
}


static void _UART_Async_Flash_Safe_StringLn_Transmit()
{
	_transmittion_callback = _UART_Async_Flash_Safe_StringLn_Transmit;
	
	char c = pgm_read_byte(&((uint8_t*)_transmittion_data)[_transmittion_counter]);
	
	if (c == '\0' || _transmittion_counter >= _transmittion_data_size)
	{
		_transmittion_counter = 0;
		UART_Async_Safe_String_Transmit("\r\n", 2);
		return;
	}
	
	UDR = c;
	
	++_transmittion_counter;
}

// ===============================================================================

void UART_Async_Byte_Transmit(uint8_t byte)
{
	_transmittion_byte = byte;
	_transmittion_status = UART_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART_Async_Byte_Transmit();
}


void UART_Async_Data_Transmit(const void *data, uint16_t data_size)
{
	_transmittion_data = (uint8_t*)data;
	_transmittion_data_size = data_size;
	_transmittion_status = UART_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART_Async_Data_Transmit();
}


void UART_Async_String_Transmit(const char *string)
{
	_transmittion_data = (uint8_t*)string;
	_transmittion_status = UART_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART_Async_String_Transmit();
}


void UART_Async_StringLn_Transmit(const char *string)
{
	_transmittion_data = (uint8_t*)string;
	_transmittion_status = UART_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART_Async_StringLn_Transmit();
}


void UART_Async_Safe_String_Transmit(const char *string, uint16_t max_string_len)
{
	_transmittion_data = (uint8_t*)string;
	_transmittion_data_size = max_string_len;
	_transmittion_status = UART_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART_Async_Safe_String_Transmit();
}


void UART_Async_Safe_StringLn_Transmit(const char *string, uint16_t max_string_len)
{
	_transmittion_data = (uint8_t*)string;
	_transmittion_data_size = max_string_len;
	_transmittion_status = UART_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART_Async_Safe_StringLn_Transmit();
}

// ===============================================================================

void UART_Async_Flash_Byte_Transmit(const uint8_t *flash_byte)
{
	_transmittion_byte = pgm_read_byte(flash_byte);
	_transmittion_status = UART_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART_Async_Byte_Transmit();
}


void UART_Async_Flash_Data_Transmit(const void *flash_data, uint16_t flash_data_size)
{
	_transmittion_data = (uint8_t*)flash_data;
	_transmittion_data_size = flash_data_size;
	_transmittion_status = UART_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART_Async_Flash_Data_Transmit();
}


void UART_Async_Flash_String_Transmit(const char *flash_string)
{
	_transmittion_data = (uint8_t*)flash_string;
	_transmittion_status = UART_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART_Async_Flash_String_Transmit();
}


void UART_Async_Flash_StringLn_Transmit(const char *flash_string)
{
	_transmittion_data = (uint8_t*)flash_string;
	_transmittion_status = UART_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART_Async_Flash_StringLn_Transmit();
}


void UART_Async_Flash_Safe_String_Transmit(const char *flash_string, uint16_t max_flash_string_len)
{
	_transmittion_data = (uint8_t*)flash_string;
	_transmittion_data_size = max_flash_string_len;
	_transmittion_status = UART_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART_Async_Flash_Safe_String_Transmit();
}


void UART_Async_Flash_Safe_StringLn_Transmit(const char *flash_string, uint16_t max_flash_string_len)
{
	_transmittion_data = (uint8_t*)flash_string;
	_transmittion_data_size = max_flash_string_len;
	_transmittion_status = UART_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART_Async_Flash_Safe_StringLn_Transmit();
}


#endif

// ===============================================================================

#ifdef UART_ASYNC_USE_RX


static void _UART_Async_Set_Reception_Data_To_Buffer(uint8_t byte)
{
	if (_reception_status == UART_ASYNC_RECEPTION_IS_ACTIVE && _reception_data_buffer != NULL)
	{
		_reception_data_buffer[_reception_counter] = byte;
		
		++_reception_counter;
		
		if (_reception_counter >= _reception_data_buffer_size)
		{
			UART_Async_Stop_Reception_Data_To_Buffer();
			_reception_counter = 0;
			_reception_buffer_is_filled = UART_ASYNC_RECEPTION_BUFFER_IS_FILLED;
			
			if (_reception_callback != NULL)
			{
				_reception_callback();
				_reception_buffer_is_filled = UART_ASYNC_RECEPTION_BUFFER_IS_NOT_FILLED;
			}
		}
	}
}

// ===============================================================================

void UART_Async_Start_Reception_Data_To_Buffer()
{
	_reception_status = UART_ASYNC_RECEPTION_IS_ACTIVE;
	UART_Async_Set_Reception_Enable(true);
}


void UART_Async_Stop_Reception_Data_To_Buffer()
{
	_reception_status = UART_ASYNC_RECEPTION_IS_NOT_ACTIVE;
	UART_Async_Set_Reception_Enable(false);
}


void UART_Async_Clear_Reception_Buffer()
{
	_reception_counter = 0;
	_reception_buffer_is_filled = UART_ASYNC_RECEPTION_BUFFER_IS_NOT_FILLED;
}


#endif

// ===============================================================================

#ifdef UART_ASYNC_USE_TX


ISR(USART_TXC_vect)
{
	if (_transmittion_status == UART_ASYNC_TRANSMITTION_IS_ACTIVE && _transmittion_callback != NULL)
	{
		_transmittion_callback();
	}
}


#endif


#ifdef UART_ASYNC_USE_RX


ISR(USART_RXC_vect)
{
	_UART_Async_Set_Reception_Data_To_Buffer(UDR);
}

#endif



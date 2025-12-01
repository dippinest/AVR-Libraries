
#include "uart0_async.h"

#ifdef UART0_ASYNC_USE_TX

static volatile uint8_t   _transmittion_byte0;
static volatile uint8_t*  _transmittion_data0       = NULL;
static volatile uint16_t  _transmittion_data_size0;
static volatile uint16_t  _transmittion_counter0    = 0;
static volatile bool      _transmittion_status0     = UART0_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;


bool UART0_Async_Get_Transmittion_Status()
{
	return _transmittion_status0;
}


static void (*_transmittion_callback0)() = NULL;
static void (*_user_transmittion_callback0)() = NULL;


#endif


#ifdef UART0_ASYNC_USE_RX

static volatile uint8_t*  _reception_data_buffer0       = NULL;
static volatile uint16_t  _reception_data_buffer_size0  = 0;
static volatile uint16_t  _reception_counter0           = 0;
static volatile bool      _reception_buffer_is_filled0  = UART0_ASYNC_RECEPTION_BUFFER_IS_NOT_FILLED;
static volatile bool      _reception_status0            = UART0_ASYNC_RECEPTION_IS_NOT_ACTIVE;
static volatile uint8_t   _reception_terminator0        = 0x00;
static volatile bool      _reception_terminator_enable0 = false;


static void (*_reception_callback0)() = NULL;


#endif

// ===============================================================================

#ifdef UART0_ASYNC_USE_RX

void UART0_Async_Set_Reception_Buffer_Ptr(const void *buffer)
{
	_reception_data_buffer0 = (uint8_t*)buffer;
}


void UART0_Async_Set_Reception_Buffer_Size(const uint16_t buffer_size)
{
	_reception_data_buffer_size0 = buffer_size;
}


void UART0_Async_Set_Reception_Terminator(uint8_t terminator)
{
	_reception_terminator0 = terminator;
}


void UART0_Async_Set_Reception_Terminator_Enable(bool is_enable)
{
	_reception_terminator_enable0 = is_enable;
}


void UART0_Async_Set_Reception_Callback_Function(void (*callback_function)())
{
	_reception_callback0 = (void*)callback_function;
}


bool UART0_Async_Get_Reception_Status()
{
	return _reception_status0;
}


bool UART0_Async_Reception_Buffer_Is_Filled()
{
	return _reception_buffer_is_filled0;
}


void *UART0_Async_Get_Reception_Buffer_Ptr()
{
	return (void*)_reception_data_buffer0;
}


uint16_t UART0_Async_Get_Reception_Buffer_Size()
{
	return _reception_data_buffer_size0;
}


uint16_t UART0_Async_Get_Reception_Buffer_Counter()
{
	return _reception_counter0;
}


uint8_t UART0_Async_Get_Reception_Terminator()
{
	return _reception_terminator0;
}


bool UART0_Async_Reception_Terminator_Is_Enable()
{
	return _reception_terminator_enable0;
}


void *UART0_Async_Get_Reception_Callback_Function()
{
	return _reception_callback0;
}


uint16_t UART0_Async_Get_Current_Reception_Buffer_Fullness()
{
	return _reception_counter0;
}


#endif

// ===============================================================================

#ifdef UART0_ASYNC_USE_TX


void UART0_Async_Set_Transmittion_Callback_Function(void (*callback_function)())
{
	_user_transmittion_callback0 = (void*)callback_function;
}


void *UART0_Async_Get_Transmittion_Callback_Function()
{
	return _user_transmittion_callback0;
}

// ===============================================================================

static void _UART0_Async_Byte_Transmit()
{
	_transmittion_callback0 = _UART0_Async_Byte_Transmit;
	
	UDR0 = _transmittion_byte0;
	
	if (_transmittion_counter0)
	{
		_transmittion_counter0 = 0;
		
		if (_user_transmittion_callback0 != NULL)
		{
			_user_transmittion_callback0();
		}
		
		_transmittion_status0 = UART0_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
	
	++_transmittion_counter0;
}


static void _UART0_Async_Data_Transmit()
{
	_transmittion_callback0 = _UART0_Async_Data_Transmit;
	
	UDR0 = _transmittion_data0[_transmittion_counter0];
	
	++_transmittion_counter0;
	
	if (_transmittion_counter0 >= _transmittion_data_size0)
	{
		_transmittion_counter0 = 0;
		
		if (_user_transmittion_callback0 != NULL)
		{
			_user_transmittion_callback0();
		}
		
		_transmittion_status0 = UART0_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
}


static void _UART0_Async_String_Transmit()
{
	_transmittion_callback0 = _UART0_Async_String_Transmit;
	
	if (_transmittion_data0[_transmittion_counter0] != '\0')
	{
		UDR0 = _transmittion_data0[_transmittion_counter0];
		++_transmittion_counter0;
	}
	else
	{
		_transmittion_counter0 = 0;
		
		if (_user_transmittion_callback0 != NULL)
		{
			_user_transmittion_callback0();
		}
		
		_transmittion_status0 = UART0_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
}


static void _UART0_Async_StringLn_Transmit()
{
	_transmittion_callback0 = _UART0_Async_StringLn_Transmit;
	
	if (_transmittion_data0[_transmittion_counter0] != '\0')
	{
		UDR0 = _transmittion_data0[_transmittion_counter0];
		++_transmittion_counter0;
	}
	else
	{
		_transmittion_counter0 = 0;
		_transmittion_status0 = UART0_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		UART0_Async_String_Transmit("\r\n");
		
		return;
	}
}


static void _UART0_Async_Safe_String_Transmit()
{
	_transmittion_callback0 = _UART0_Async_Safe_String_Transmit;
	
	if (_transmittion_data0[_transmittion_counter0] != '\0' && _transmittion_counter0 < _transmittion_data_size0)
	{
		UDR0 = _transmittion_data0[_transmittion_counter0];
		++_transmittion_counter0;
	}
	else
	{
		_transmittion_counter0 = 0;
		
		if (_user_transmittion_callback0 != NULL)
		{
			_user_transmittion_callback0();
		}
		
		_transmittion_status0 = UART0_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
}


static void _UART0_Async_Safe_StringLn_Transmit()
{
	_transmittion_callback0 = _UART0_Async_Safe_StringLn_Transmit;
	
	if (_transmittion_data0[_transmittion_counter0] != '\0' && _transmittion_counter0 < _transmittion_data_size0)
	{
		UDR0 = _transmittion_data0[_transmittion_counter0];
		++_transmittion_counter0;
	}
	else
	{
		_transmittion_counter0 = 0;
		UART0_Async_Safe_String_Transmit("\r\n", 2);
		
		return;
	}
}

// ===============================================================================

static void _UART0_Async_Flash_Data_Transmit()
{
	_transmittion_callback0 = _UART0_Async_Flash_Data_Transmit;
	
	UDR0 = pgm_read_byte(&((uint8_t*)_transmittion_data0)[_transmittion_counter0]);
	
	++_transmittion_counter0;
	
	if (_transmittion_counter0 >= _transmittion_data_size0)
	{
		_transmittion_counter0 = 0;
		
		if (_user_transmittion_callback0 != NULL)
		{
			_user_transmittion_callback0();
		}
		
		_transmittion_status0 = UART0_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
}


static void _UART0_Async_Flash_String_Transmit()
{
	_transmittion_callback0 = _UART0_Async_Flash_String_Transmit;
	
	char c = pgm_read_byte(&((uint8_t*)_transmittion_data0)[_transmittion_counter0]);
	
	if (c == '\0')
	{
		_transmittion_counter0 = 0;
		
		if (_user_transmittion_callback0 != NULL)
		{
			_user_transmittion_callback0();
		}
		
		_transmittion_status0 = UART0_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
	
	UDR0 = c;
	
	++_transmittion_counter0;
}


static void _UART0_Async_Flash_StringLn_Transmit()
{
	_transmittion_callback0 = _UART0_Async_Flash_StringLn_Transmit;
	
	char c = pgm_read_byte(&((uint8_t*)_transmittion_data0)[_transmittion_counter0]);
	
	if (c == '\0')
	{
		_transmittion_counter0 = 0;
		UART0_Async_String_Transmit("\r\n");
		return;
	}
	
	UDR0 = c;
	
	++_transmittion_counter0;
}


static void _UART0_Async_Flash_Safe_String_Transmit()
{
	_transmittion_callback0 = _UART0_Async_Flash_Safe_String_Transmit;
	
	char c = pgm_read_byte(&((uint8_t*)_transmittion_data0)[_transmittion_counter0]);
	
	if (c == '\0' || _transmittion_counter0 >= _transmittion_data_size0)
	{
		_transmittion_counter0 = 0;
		
		if (_user_transmittion_callback0 != NULL)
		{
			_user_transmittion_callback0();
		}
		
		_transmittion_status0 = UART0_ASYNC_TRANSMITTION_IS_NOT_ACTIVE;
		
		return;
	}
	
	UDR0 = c;
	
	++_transmittion_counter0;
}


static void _UART0_Async_Flash_Safe_StringLn_Transmit()
{
	_transmittion_callback0 = _UART0_Async_Flash_Safe_StringLn_Transmit;
	
	char c = pgm_read_byte(&((uint8_t*)_transmittion_data0)[_transmittion_counter0]);
	
	if (c == '\0' || _transmittion_counter0 >= _transmittion_data_size0)
	{
		_transmittion_counter0 = 0;
		UART0_Async_Safe_String_Transmit("\r\n", 2);
		return;
	}
	
	UDR0 = c;
	
	++_transmittion_counter0;
}

// ===============================================================================

void UART0_Async_Byte_Transmit(uint8_t byte)
{
	_transmittion_byte0 = byte;
	_transmittion_status0 = UART0_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART0_Async_Byte_Transmit();
}


void UART0_Async_Data_Transmit(const void *data, uint16_t data_size)
{
	_transmittion_data0 = (uint8_t*)data;
	_transmittion_data_size0 = data_size;
	_transmittion_status0 = UART0_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART0_Async_Data_Transmit();
}


void UART0_Async_String_Transmit(const char *string)
{
	_transmittion_data0 = (uint8_t*)string;
	_transmittion_status0 = UART0_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART0_Async_String_Transmit();
}


void UART0_Async_StringLn_Transmit(const char *string)
{
	_transmittion_data0 = (uint8_t*)string;
	_transmittion_status0 = UART0_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART0_Async_StringLn_Transmit();
}


void UART0_Async_Safe_String_Transmit(const char *string, uint16_t max_string_len)
{
	_transmittion_data0 = (uint8_t*)string;
	_transmittion_data_size0 = max_string_len;
	_transmittion_status0 = UART0_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART0_Async_Safe_String_Transmit();
}


void UART0_Async_Safe_StringLn_Transmit(const char *string, uint16_t max_string_len)
{
	_transmittion_data0 = (uint8_t*)string;
	_transmittion_data_size0 = max_string_len;
	_transmittion_status0 = UART0_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART0_Async_Safe_StringLn_Transmit();
}

// ===============================================================================

void UART0_Async_Flash_Byte_Transmit(const uint8_t *flash_byte)
{
	_transmittion_byte0 = pgm_read_byte(flash_byte);
	_transmittion_status0 = UART0_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART0_Async_Byte_Transmit();
}


void UART0_Async_Flash_Data_Transmit(const void *flash_data, uint16_t flash_data_size)
{
	_transmittion_data0 = (uint8_t*)flash_data;
	_transmittion_data_size0 = flash_data_size;
	_transmittion_status0 = UART0_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART0_Async_Flash_Data_Transmit();
}


void UART0_Async_Flash_String_Transmit(const char *flash_string)
{
	_transmittion_data0 = (uint8_t*)flash_string;
	_transmittion_status0 = UART0_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART0_Async_Flash_String_Transmit();
}


void UART0_Async_Flash_StringLn_Transmit(const char *flash_string)
{
	_transmittion_data0 = (uint8_t*)flash_string;
	_transmittion_status0 = UART0_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART0_Async_Flash_StringLn_Transmit();
}


void UART0_Async_Flash_Safe_String_Transmit(const char *flash_string, uint16_t max_flash_string_len)
{
	_transmittion_data0 = (uint8_t*)flash_string;
	_transmittion_data_size0 = max_flash_string_len;
	_transmittion_status0 = UART0_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART0_Async_Flash_Safe_String_Transmit();
}


void UART0_Async_Flash_Safe_StringLn_Transmit(const char *flash_string, uint16_t max_flash_string_len)
{
	_transmittion_data0 = (uint8_t*)flash_string;
	_transmittion_data_size0 = max_flash_string_len;
	_transmittion_status0 = UART0_ASYNC_TRANSMITTION_IS_ACTIVE;
	_UART0_Async_Flash_Safe_StringLn_Transmit();
}


#endif

// ===============================================================================

#ifdef UART0_ASYNC_USE_RX


static void _UART0_Async_Set_Reception_Data_To_Buffer(uint8_t byte)
{
	if (_reception_status0 == UART0_ASYNC_RECEPTION_IS_ACTIVE && _reception_data_buffer0 != NULL)
	{
		_reception_data_buffer0[_reception_counter0] = byte;
		
		++_reception_counter0;
		
		if ((_reception_terminator_enable0 && (byte == _reception_terminator0)) || (_reception_counter0 >= _reception_data_buffer_size0))
		{
			UART0_Async_Stop_Reception_Data_To_Buffer();
			
			if (_reception_callback0 != NULL)
			{
				_reception_callback0();
			}
			
			_reception_counter0 = 0;
			_reception_buffer_is_filled0 = UART0_ASYNC_RECEPTION_BUFFER_IS_FILLED;
		}
	}
}

// ===============================================================================

void UART0_Async_Start_Reception_Data_To_Buffer()
{
	_reception_status0 = UART0_ASYNC_RECEPTION_IS_ACTIVE;
}


void UART0_Async_Stop_Reception_Data_To_Buffer()
{
	_reception_status0 = UART0_ASYNC_RECEPTION_IS_NOT_ACTIVE;
}


void UART0_Async_Clear_Reception_Buffer()
{
	_reception_counter0 = 0;
	_reception_buffer_is_filled0 = UART0_ASYNC_RECEPTION_BUFFER_IS_NOT_FILLED;
}


#endif

// ===============================================================================

#ifdef UART0_ASYNC_USE_TX


ISR(USART0_TXC_vect)
{
	if (_transmittion_status0 == UART0_ASYNC_TRANSMITTION_IS_ACTIVE && _transmittion_callback0 != NULL)
	{
		_transmittion_callback0();
	}
}


#endif


#ifdef UART0_ASYNC_USE_RX


ISR(USART0_RXC_vect)
{
	_UART0_Async_Set_Reception_Data_To_Buffer(UDR0);
}

#endif




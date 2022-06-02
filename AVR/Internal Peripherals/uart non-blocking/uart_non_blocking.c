
#include "uart_non_blocking.h"

static volatile uint8_t   _transmittion_byte;
static volatile uint8_t*  _transmittion_data;
static volatile uint16_t  _transmittion_data_size;
static volatile uint16_t  _transmittion_counter    = 0;
static volatile uint8_t   _transmittion_condition;
static volatile bool      _transmittion_status     = UART_NON_BLOCKING_TRANSMITTION_IS_NOT_ACTIVE;


static volatile uint8_t*  _reception_data_buffer       = NULL;
static volatile uint16_t  _reception_data_buffer_size  = 0;
static volatile uint16_t  _reception_counter           = 0;
static volatile bool      _reception_buffer_is_filled  = UART_NON_BLOCKING_RECEPTION_BUFFER_IS_NOT_FILLED;
static volatile bool      _reception_status            = UART_NON_BLOCKING_RECEPTION_IS_NOT_ACTIVE;

static void (*_reception_callback)() = NULL;

bool UART_NB_Get_Transmittion_Status()
{
	return _transmittion_status;
}

// ===============================================================================

void UART_NB_Set_Reception_Buffer_Ptr(const void *buffer)
{
	_reception_data_buffer = (uint8_t*)buffer;
}

void UART_NB_Set_Reception_Buffer_Size(const uint16_t buffer_size)
{
	_reception_data_buffer_size = buffer_size;
}

void UART_NB_Set_Reception_CallBack_Function(void (*callback_function)())
{
	_reception_callback = (void*)callback_function;
}

bool UART_NB_Get_Reception_Status()
{
	return _reception_status;
}

bool UART_NB_Reception_Buffer_Is_Filled()
{
	return _reception_buffer_is_filled;
}

void *UART_NB_Get_Reception_Buffer_Ptr()
{
	return (void*)_reception_data_buffer;
}

uint16_t UART_NB_Get_Reception_Buffer_Size()
{
	return _reception_data_buffer_size;
}

void *UART_NB_Get_Reception_CallBack_Function()
{
	return _reception_callback;
}

uint16_t UART_NB_Get_Current_Reception_Buffer_Fullness()
{
	return _reception_counter;
}

// ===============================================================================

static void _UART_NB_Byte_Transmit()
{
	UDR = _transmittion_byte;
	_transmittion_status = UART_NON_BLOCKING_TRANSMITTION_IS_NOT_ACTIVE;
}

static void _UART_NB_Data_Transmit()
{
	UDR = _transmittion_data[_transmittion_counter];
	++_transmittion_counter;
	
	if (_transmittion_counter >= _transmittion_data_size)
	{
		_transmittion_counter = 0;
		_transmittion_status = UART_NON_BLOCKING_TRANSMITTION_IS_NOT_ACTIVE;
		return;
	}
}

static void _UART_NB_String_Transmit()
{
	if (_transmittion_data[_transmittion_counter] != '\0')
	{
		UDR = _transmittion_data[_transmittion_counter];
		++_transmittion_counter;
	}
	else
	{
		_transmittion_counter = 0;
		_transmittion_status = UART_NON_BLOCKING_TRANSMITTION_IS_NOT_ACTIVE;
		return;
	}
}

static void _UART_NB_StringLn_Transmit()
{
	if (_transmittion_data[_transmittion_counter] != '\0')
	{
		UDR = _transmittion_data[_transmittion_counter];
		++_transmittion_counter;
	}
	else
	{
		_transmittion_counter = 0;
		_transmittion_status = UART_NON_BLOCKING_TRANSMITTION_IS_NOT_ACTIVE;
		
		UART_NB_String_Transmit("\r\n");
		
		return;
	}
}

static void _UART_NB_Safe_String_Transmit()
{
	if (_transmittion_data[_transmittion_counter] != '\0' && _transmittion_counter < _transmittion_data_size)
	{
		UDR = _transmittion_data[_transmittion_counter];
		++_transmittion_counter;
	}
	else
	{
		_transmittion_counter = 0;
		_transmittion_status = UART_NON_BLOCKING_TRANSMITTION_IS_NOT_ACTIVE;
		return;
	}
}

static void _UART_NB_Safe_StringLn_Transmit()
{
	if (_transmittion_data[_transmittion_counter] != '\0' && _transmittion_counter < _transmittion_data_size)
	{
		UDR = _transmittion_data[_transmittion_counter];
		++_transmittion_counter;
	}
	else
	{
		_transmittion_counter = 0;
		UART_NB_Safe_String_Transmit("\r\n", 2);
		
		return;
	}
}

// ===============================================================================

static void _UART_NB_Flash_Data_Transmit()
{	
	UDR = pgm_read_byte(&((uint8_t*)_transmittion_data)[_transmittion_counter]);
	++_transmittion_counter;
	
	if (_transmittion_counter >= _transmittion_data_size)
	{
		_transmittion_counter = 0;
		_transmittion_status = UART_NON_BLOCKING_TRANSMITTION_IS_NOT_ACTIVE;
		return;
	}
}

static void _UART_NB_Flash_String_Transmit()
{
	char c = pgm_read_byte(&((uint8_t*)_transmittion_data)[_transmittion_counter]);
	
	if (c == '\0')
	{
		_transmittion_counter = 0;
		_transmittion_status = UART_NON_BLOCKING_TRANSMITTION_IS_NOT_ACTIVE;
		return;
	}
	
	UDR = c;
	
	++_transmittion_counter;
}

static void _UART_NB_Flash_StringLn_Transmit()
{
	char c = pgm_read_byte(&((uint8_t*)_transmittion_data)[_transmittion_counter]);
	
	if (c == '\0')
	{
		_transmittion_counter = 0;
		UART_NB_String_Transmit("\r\n");
		return;
	}
	
	UDR = c;
	
	++_transmittion_counter;
}

static void _UART_NB_Flash_Safe_String_Transmit()
{
	char c = pgm_read_byte(&((uint8_t*)_transmittion_data)[_transmittion_counter]);
	
	if (c == '\0' || _transmittion_counter >= _transmittion_data_size)
	{
		_transmittion_counter = 0;
		_transmittion_status = UART_NON_BLOCKING_TRANSMITTION_IS_NOT_ACTIVE;
		return;
	}
	
	UDR = c;
	
	++_transmittion_counter;
}

static void _UART_NB_Flash_Safe_StringLn_Transmit()
{
	char c = pgm_read_byte(&((uint8_t*)_transmittion_data)[_transmittion_counter]);
	
	if (c == '\0' || _transmittion_counter >= _transmittion_data_size)
	{
		_transmittion_counter = 0;
		UART_NB_Safe_String_Transmit("\r\n", 2);
		return;
	}
	
	UDR = c;
	
	++_transmittion_counter;
}

// ===============================================================================

void UART_NB_Byte_Transmit(uint8_t byte)
{
	_transmittion_byte = byte;
	_transmittion_condition = UART_NON_BLOCKING_BYTE_TRANSMIT;
	_transmittion_status = UART_NON_BLOCKING_TRANSMITTION_IS_ACTIVE;
	_UART_NB_Byte_Transmit();
}

void UART_NB_Data_Transmit(const void *data, uint16_t data_size)
{
	_transmittion_data = (uint8_t*)data;
	_transmittion_data_size = data_size;
	_transmittion_condition = UART_NON_BLOCKING_DATA_TRANSMIT;
	_transmittion_status = UART_NON_BLOCKING_TRANSMITTION_IS_ACTIVE;
	_UART_NB_Data_Transmit();
}

void UART_NB_String_Transmit(const char *string)
{
	_transmittion_data = (uint8_t*)string;
	_transmittion_condition = UART_NON_BLOCKING_STRING_TRANSMIT;
	_transmittion_status = UART_NON_BLOCKING_TRANSMITTION_IS_ACTIVE;
	_UART_NB_String_Transmit();
}

void UART_NB_StringLn_Transmit(const char *string)
{
	_transmittion_data = (uint8_t*)string;
	_transmittion_condition = UART_NON_BLOCKING_STRINGLN_TRANSMIT;
	_transmittion_status = UART_NON_BLOCKING_TRANSMITTION_IS_ACTIVE;
	_UART_NB_StringLn_Transmit();
}

void UART_NB_Safe_String_Transmit(const char *string, uint16_t max_string_len)
{
	_transmittion_data = (uint8_t*)string;
	_transmittion_data_size = max_string_len;
	_transmittion_condition = UART_NON_BLOCKING_SAFE_STRING_TRANSMIT;
	_transmittion_status = UART_NON_BLOCKING_TRANSMITTION_IS_ACTIVE;
	_UART_NB_Safe_String_Transmit();
}

void UART_NB_Safe_StringLn_Transmit(const char *string, uint16_t max_string_len)
{
	_transmittion_data = (uint8_t*)string;
	_transmittion_data_size = max_string_len;
	_transmittion_condition = UART_NON_BLOCKING_SAFE_STRINGLN_TRANSMIT;
	_transmittion_status = UART_NON_BLOCKING_TRANSMITTION_IS_ACTIVE;
	_UART_NB_Safe_StringLn_Transmit();
}

// ===============================================================================

void UART_NB_Flash_Byte_Transmit(const uint8_t *flash_byte)
{
	_transmittion_byte = pgm_read_byte(flash_byte);
	_transmittion_condition = UART_NON_BLOCKING_BYTE_TRANSMIT;
	_transmittion_status = UART_NON_BLOCKING_TRANSMITTION_IS_ACTIVE;
	_UART_NB_Byte_Transmit();
}

void UART_NB_Flash_Data_Transmit(const void *flash_data, uint16_t flash_data_size)
{
	_transmittion_data = (uint8_t*)flash_data;
	_transmittion_data_size = flash_data_size;
	_transmittion_condition = UART_NON_BLOCKING_FLASH_DATA_TRANSMIT;
	_transmittion_status = UART_NON_BLOCKING_TRANSMITTION_IS_ACTIVE;
	_UART_NB_Flash_Data_Transmit();
}

void UART_NB_Flash_String_Transmit(const char *flash_string)
{
	_transmittion_data = (uint8_t*)flash_string;
	_transmittion_condition = UART_NON_BLOCKING_FLASH_STRING_TRANSMIT;
	_transmittion_status = UART_NON_BLOCKING_TRANSMITTION_IS_ACTIVE;
	_UART_NB_Flash_String_Transmit();
}

void UART_NB_Flash_StringLn_Transmit(const char *flash_string)
{
	_transmittion_data = (uint8_t*)flash_string;
	_transmittion_condition = UART_NON_BLOCKING_FLASH_STRINGLN_TRANSMIT;
	_transmittion_status = UART_NON_BLOCKING_TRANSMITTION_IS_ACTIVE;
	_UART_NB_Flash_StringLn_Transmit();
}

void UART_NB_Flash_Safe_String_Transmit(const char *flash_string, uint16_t max_flash_string_len)
{
	_transmittion_data = (uint8_t*)flash_string;
	_transmittion_data_size = max_flash_string_len;
	_transmittion_condition = UART_NON_BLOCKING_FLASH_SAFE_STRING_TRANSMIT;
	_transmittion_status = UART_NON_BLOCKING_TRANSMITTION_IS_ACTIVE;
	_UART_NB_Flash_Safe_String_Transmit();
}

void UART_NB_Flash_Safe_StringLn_Transmit(const char *flash_string, uint16_t max_flash_string_len)
{
	_transmittion_data = (uint8_t*)flash_string;
	_transmittion_data_size = max_flash_string_len;
	_transmittion_condition = UART_NON_BLOCKING_FLASH_SAFE_STRINGLN_TRANSMIT;
	_transmittion_status = UART_NON_BLOCKING_TRANSMITTION_IS_ACTIVE;
	_UART_NB_Flash_Safe_StringLn_Transmit();
}

// ===============================================================================

static void _UART_NB_Set_Reception_Data_To_Buffer(uint8_t byte)
{
	if (_reception_status == UART_NON_BLOCKING_RECEPTION_IS_ACTIVE && _reception_data_buffer != NULL)
	{
		_reception_data_buffer[_reception_counter] = byte;
		++_reception_counter;
		
		if (_reception_counter >= _reception_data_buffer_size)
		{
			UART_NB_Stop_Reception_Data_To_Buffer();
			_reception_counter = 0;
			_reception_buffer_is_filled = UART_NON_BLOCKING_RECEPTION_BUFFER_IS_FILLED;
			
			if (_reception_callback != NULL)
			{
				sei();
				_reception_callback();
				_reception_buffer_is_filled = UART_NON_BLOCKING_RECEPTION_BUFFER_IS_NOT_FILLED;
			}
		}
	}
}

// ===============================================================================

void UART_NB_Start_Reception_Data_To_Buffer()
{
	_reception_status = UART_NON_BLOCKING_RECEPTION_IS_ACTIVE;
	UART_NB_Set_Reception_Enable(true);
}

void UART_NB_Stop_Reception_Data_To_Buffer()
{
	_reception_status = UART_NON_BLOCKING_RECEPTION_IS_NOT_ACTIVE;
	UART_NB_Set_Reception_Enable(false);
}

void UART_NB_Clear_Reception_Buffer()
{
	_reception_counter = 0;
	_reception_buffer_is_filled = UART_NON_BLOCKING_RECEPTION_BUFFER_IS_NOT_FILLED;
}

// ===============================================================================

ISR(USART_TXC_vect)
{
	if (_transmittion_status == UART_NON_BLOCKING_TRANSMITTION_IS_ACTIVE)
	{
		switch(_transmittion_condition)
		{
			case UART_NON_BLOCKING_BYTE_TRANSMIT:
			_UART_NB_Byte_Transmit();
			break;
			case UART_NON_BLOCKING_DATA_TRANSMIT:
			_UART_NB_Data_Transmit();
			break;
			case UART_NON_BLOCKING_STRING_TRANSMIT:
			_UART_NB_String_Transmit();
			break;
			case UART_NON_BLOCKING_STRINGLN_TRANSMIT:
			_UART_NB_StringLn_Transmit();
			break;
			case UART_NON_BLOCKING_SAFE_STRING_TRANSMIT:
			_UART_NB_Safe_String_Transmit();
			break;
			case UART_NON_BLOCKING_SAFE_STRINGLN_TRANSMIT:
			_UART_NB_Safe_StringLn_Transmit();
			break;
			case UART_NON_BLOCKING_FLASH_DATA_TRANSMIT:
			_UART_NB_Flash_Data_Transmit();
			break;
			case UART_NON_BLOCKING_FLASH_STRING_TRANSMIT:
			_UART_NB_Flash_String_Transmit();
			break;
			case UART_NON_BLOCKING_FLASH_STRINGLN_TRANSMIT:
			_UART_NB_Flash_StringLn_Transmit();
			break;
			case UART_NON_BLOCKING_FLASH_SAFE_STRING_TRANSMIT:
			_UART_NB_Flash_Safe_String_Transmit();
			break;
			case UART_NON_BLOCKING_FLASH_SAFE_STRINGLN_TRANSMIT:
			_UART_NB_Flash_Safe_StringLn_Transmit();
			break;
		}
	}
}

ISR(USART_RXC_vect)
{
	_UART_NB_Set_Reception_Data_To_Buffer(UDR);
}


// ===============================================================================
//
// Библиотека для работы с аппаратным модулем UART. Функции данной библиотеки
// являются блокирующими, то есть при работе модуля процессор полностью блокируется.
// Для возможности асинхронной работы с модулем UART для приёма и передачи данных
// (с помощью прерываний) используйте библиотеку uart_async.h
//
// -------------------------------------------------------------------------------
//
// Library for working with the UART hardware module. The functions of this
// library are blocking, that is, when the module is running, the processor
// is completely blocked. To be able to work asynchronously with the UART module
// for receiving and transmitting data (using interrupts), use the uart_async.h library
//
// ===============================================================================


#ifndef UART_H_
#define UART_H_

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <avr/io.h>
#include <avr/pgmspace.h>


// макросы для определения количества битов данных
// -------------------------------------------------------------------------------
// macros for determining the number of data bits
#define UART_NUM_OF_DATA_BITS_5 5
#define UART_NUM_OF_DATA_BITS_6 6
#define UART_NUM_OF_DATA_BITS_7 7
#define UART_NUM_OF_DATA_BITS_8 8


// макросы для определения количества стоповых бит
// -------------------------------------------------------------------------------
// macros for determining the number of stop bits
#define UART_NUM_OF_STOP_BITS_1 1
#define UART_NUM_OF_STOP_BITS_2 2


// макросы для определения количества битов чётности
// -------------------------------------------------------------------------------
// macros for determining the parity bit
#define UART_PARITY_BIT_NONE 0
#define UART_PARITY_BIT_EVEN 1
#define UART_PARITY_BIT_ODD  2


// внутренний макрос для установки значений регистров,
// отвечающих за скорость передачи данных
// -------------------------------------------------------------------------------
// internal macro for setting register values
// responsible for data transfer rate
#define _UART_SET_CODE_BAUDRATE(_BAUDRATE_VALUE) (F_CPU / 8UL / _BAUDRATE_VALUE)


// ===============================================================================


// функция для активации (деактивации) передачи данных
// -------------------------------------------------------------------------------
// function for activating (deactivating) data transmission
inline void UART_Set_Transmittion_Enable(bool transmittion_is_enable)
{
	if (transmittion_is_enable)
	{
		UCSRB |=  (1 << TXEN);
	}
	else
	{
		UCSRB &= ~(1 << TXEN);
	}
}


// функция для активации (деактивации) приёма данных
// -------------------------------------------------------------------------------
// function for activating (deactivating) data reception
inline void UART_Set_Reception_Enable(bool reception_is_enable)
{
	if (reception_is_enable)
	{
		UCSRB |=  (1 << RXEN);
	}
	else
	{
		UCSRB &= ~(1 << RXEN);
	}
}


// функция для активации (деактивации) прерывания по опустошению
// буфера приёма данных
// -------------------------------------------------------------------------------
// function for activating (deactivating) an interrupt for emptying
// data reception buffer
inline void UART_Set_Buffer_Emptying_Interrupt_Enable(bool buffer_emptying_interrupt_is_enable)
{
	if (buffer_emptying_interrupt_is_enable)
	{
		UCSRB |=  (1 << UDRIE);
	}
	else
	{
		UCSRB &= ~(1 << UDRIE);
	}
}


// функция для активации (деактивации) прерывания по окончанию передачи данных
// -------------------------------------------------------------------------------
// function for activating (deactivating) the interrupt at the end of data transmission
inline void UART_Set_End_Of_Transmittion_Interrupt_Enable(bool end_of_transmittion_interrupt_is_enable)
{
	if (end_of_transmittion_interrupt_is_enable)
	{
		UCSRB |=  (1 << TXCIE);
	}
	else
	{
		UCSRB &= ~(1 << TXCIE);
	}
}


// функция для активации (деактивации) прерывания по приёму данных
// -------------------------------------------------------------------------------
// function for activating (deactivating) data reception interrupts
inline void UART_Set_End_Of_Reception_Interrupt_Enable(bool end_of_reception_interrupt_is_enable)
{
	if (end_of_reception_interrupt_is_enable)
	{
		UCSRB |=  (1 << RXCIE);
	}
	else
	{
		UCSRB &= ~(1 << RXCIE);
	}
}


// функция, возвращающая true если передача данных
// разрешена (иначе - вернёт false)
// -------------------------------------------------------------------------------
// function that returns true if data transmission
// is allowed (otherwise it will return false)
inline bool UART_Transmittion_Is_Enable()
{
	if (UCSRB & (1 << TXEN))
	{
		return true;
	}
	
	return false;
}


// функция, возвращающая true если приём данных
// разрешена (иначе - вернёт false)
// -------------------------------------------------------------------------------
// function that returns true if data reception
// is allowed (otherwise it will return false)
inline bool UART_Reception_Is_Enable()
{
	if (UCSRB & (1 << RXEN))
	{
		return true;
	}
	
	return false;
}


// функция, возвращающая true если прерывание по опустошению
// буфера приёма данных разрешено (иначе - вернёт false)
// -------------------------------------------------------------------------------
// function that returns true if an interrupt for emptying
// the data reception buffer is allowed (otherwise it will return false)
inline bool UART_Buffer_Emptying_Interrupt_Is_Enable()
{
	if (UCSRB & (1 << UDRIE))
	{
		return true;
	}
	
	return false;
}


// функция, возвращающая true если прерывание по окончанию
// передачи данных разрешено (иначе - вернёт false)
// -------------------------------------------------------------------------------
// function that returns true if an interruption at the end
// of data transmission is allowed (otherwise it will return false)
inline bool UART_End_Of_Transmittion_Interrupt_Is_Enable()
{
	if (UCSRB & (1 << TXCIE))
	{
		return true;
	}
	
	return false;
}


// функция, возвращающая true если прерывание по приёму
// данных разрешено (иначе - вернёт false)
// -------------------------------------------------------------------------------
// function that returns true if data reception interruption
// is allowed (otherwise it will return false)
inline bool UART_End_Of_Reception_Interrupt_Is_Enable()
{
	if (UCSRB & (1 << RXCIE))
	{
		return true;
	}
	
	return false;
}


// ===============================================================================


// функция для установки скорости передачи данных
// -------------------------------------------------------------------------------
// function for setting the data transfer rate
void UART_Set_Baudrate(uint32_t baudrate);


// функция для получения скорости передачи данных
// -------------------------------------------------------------------------------
// function for getting the data transfer rate
uint32_t UART_Get_Baudrate();


// функция для установки количества бит данных
// -------------------------------------------------------------------------------
// function for setting the number of data bits
void UART_Set_Num_Of_Data_Bits(uint8_t num_of_data_bits);


// функция для установки количества стоповых бит
// -------------------------------------------------------------------------------
// function for setting the number of stop bits
void UART_Set_Num_Of_Stop_Bits(uint8_t num_of_stop_bits);


// функция для установки количества бит чётности
// -------------------------------------------------------------------------------
// function for setting the number of parity bits
void UART_Set_Parity_Bit(uint8_t parity_bit);


// функция для получения количества бит данных
// -------------------------------------------------------------------------------
// function for getting the number of data bits
uint8_t UART_Get_Num_Of_Data_Bits();


// функция для получения количества стоповых бит
// -------------------------------------------------------------------------------
// function for getting the number of stop bits
uint8_t UART_Get_Num_Of_Stop_Bits();


// функция для получения количества бит чётности
// -------------------------------------------------------------------------------
// function for getting the number of parity bits
uint8_t UART_Get_Parity_Bit();


// ===============================================================================


// функция для отправки байта
// -------------------------------------------------------------------------------
// function for sending a byte
void UART_Byte_Transmit(uint8_t byte);


// функция для отправки массива данных
// -------------------------------------------------------------------------------
// function for sending an array of data
void UART_Data_Transmit(const void *data, uint16_t data_size);


// функция для отправки строки
// -------------------------------------------------------------------------------
// function for sending a string
void UART_String_Transmit(const char *string);


// функция для отправки строки с переходом на следующую строку
// -------------------------------------------------------------------------------
// function for sending a line with a transition to the next line
void UART_StringLn_Transmit(const char *string);


// функция для отправки форматированной строки
// -------------------------------------------------------------------------------
// function for sending formatted string
void UART_StringFmt_Transmit(const char *string_fmt, ...);


// функция для отправки строки с учётом её длины
// (более безопасная версия UART_String_Transmit)
// -------------------------------------------------------------------------------
// function for sending a string taking into account its length
// (a more secure version of UART_String_Transmit)
void UART_Safe_String_Transmit(const char *string, uint16_t max_string_len);


// функция для отправки строки с переходом на следующую строку и её длины
// (более безопасная версия UART_StringLn_Transmit)
// -------------------------------------------------------------------------------
// function for sending a line with a transition to the next line and its length
// ((a more secure version of UART_StringLn_Transmit)
void UART_Safe_StringLn_Transmit(const char *string, uint16_t max_string_len);


// ===============================================================================


// функция для отправки байта из flash памяти
// -------------------------------------------------------------------------------
// function for sending bytes from flash memory
void UART_Flash_Byte_Transmit(const uint8_t *flash_byte);


// функция для отправки массива данных из flash памяти
// -------------------------------------------------------------------------------
// function for sending an array of data from flash memory
void UART_Flash_Data_Transmit(const void *flash_data, uint16_t flash_data_size);


// функция для отправки строки из flash памяти
// -------------------------------------------------------------------------------
// function for sending a string from flash memory
void UART_Flash_String_Transmit(const char *flash_string);


// функция для отправки строки из flash памяти с переходом на следующую строку
// -------------------------------------------------------------------------------
// function for sending a string from flash memory with a transition to the next line
void UART_Flash_StringLn_Transmit(const char *flash_string);


// функция для отправки форматированной строки из flash памяти (не поддерживает '%s'!)
// -------------------------------------------------------------------------------
// function for sending formatted string from flash memory (does not support '%s'!)
void UART_Flash_StringFmt_Transmit(const char *flash_string_fmt, ...);


// функция для отправки строки из flash памяти с учётом её длины
// (более безопасная версия UART_Flash_String_Transmit)
// -------------------------------------------------------------------------------
// function for sending a string from flash memory, taking into account its length
// (a more secure version of UART_Flash_String_Transmit)
void UART_Flash_Safe_String_Transmit(const char *flash_string, uint16_t max_flash_string_len);


// функция для отправки строки из flash памяти с переходом на следующую строку и её длины
// (более безопасная версия UART_Flash_StringLn_Transmit)
// -------------------------------------------------------------------------------
// function for sending a string from flash memory with a transition to the next line and its length
// (a more secure version of UART_Flash_StringLn_Transmit)
void UART_Flash_Safe_StringLn_Transmit(const char *flash_string, uint16_t max_flash_string_len);


// ===============================================================================


// функция для начальной инициализации модуля UART
// -------------------------------------------------------------------------------
// function for initial initialization of the UART module
void UART_Initialize(uint32_t baudrate, bool transmittion_is_allowed, bool reception_is_allowed);


// ===============================================================================


// макрос для перехода на следующую строку в UART терминале
// -------------------------------------------------------------------------------
// macro for moving the cursor to a new line in the UART terminal
#define UART_NEW_LINE UART_String_Transmit("\r\n");

#endif

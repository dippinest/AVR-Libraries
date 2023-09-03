
// ===============================================================================
//
// Библиотека для асинхронной работой с аппаратным модулем UART (через прерывания).
// Функции данной библиотеки не являются блокирующими, то есть при передачи
// данных процессор не блокируется.
//
// -------------------------------------------------------------------------------
//
// Library for asynchronous operation with the UART hardware module
// (via interrupts). The functions of this library are not blocking, that is
// the processor is not blocked during data transfer.
//
// ===============================================================================


#ifndef UART_ASYNC_H_
#define UART_ASYNC_H_

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "uart_async_configuration.h"


// макросы для определения статуса активности асинхронной передачи данных
// -------------------------------------------------------------------------------
// macros for determining the status of asynchronous data transfer activity
#define UART_ASYNC_TRANSMITTION_IS_ACTIVE          true
#define UART_ASYNC_TRANSMITTION_IS_NOT_ACTIVE      false


// макросы для определения статуса активности асинхронного приёма данных
// -------------------------------------------------------------------------------
// macros for determining the status of asynchronous data reception activity
#define UART_ASYNC_RECEPTION_IS_ACTIVE             true
#define UART_ASYNC_RECEPTION_IS_NOT_ACTIVE         false


// макросы для определения статуса заполнения приёмного буфера
// -------------------------------------------------------------------------------
// macros for determining the filling status of the receiving buffer
#define UART_ASYNC_RECEPTION_BUFFER_IS_FILLED      true
#define UART_ASYNC_RECEPTION_BUFFER_IS_NOT_FILLED  false


// функция для активации (деактивации) асинхронной передачи данных
// -------------------------------------------------------------------------------
// function for activating (deactivating) asynchronous data transmission
inline void UART_Async_Set_Transmittion_Enable(bool is_enable)
{
	UART_Set_End_Of_Transmittion_Interrupt_Enable(is_enable);
}


// функция для активации (деактивации) асинхронного приёма данных
// -------------------------------------------------------------------------------
// function for activating (deactivating) asynchronous data reception
inline void UART_Async_Set_Reception_Enable(bool is_enable)
{
	UART_Set_End_Of_Reception_Interrupt_Enable(is_enable);
}


// функция, возвращающая true если асинхронная передача данных
// разрешена (иначе - вернёт false)
// -------------------------------------------------------------------------------
// function that returns true if asynchronous data transfer
// is allowed (otherwise it will return false)
inline bool UART_Async_Transmittion_Is_Enable()
{
	return UART_End_Of_Transmittion_Interrupt_Is_Enable();
}


// функция, возвращающая true если асинхронный приём данных
// разрешён (иначе - вернёт false)
// -------------------------------------------------------------------------------
// function that returns true if asynchronous data reception
// is allowed (otherwise it will return false)
inline bool UART_Async_Reception_Is_Enable()
{
	return UART_End_Of_Reception_Interrupt_Is_Enable();
}


// ===============================================================================


// ===============================================================================
// эти функции доступны, если определён макрос UART_ASYNC_USE_RX для
// асинхронного приёма данных (в файле uart_async_configuration.h)
// -------------------------------------------------------------------------------
// these functions are available if the UART_ASYNC_USE_RX macro is defined
// for asynchronous data reception (in the uart_async_configuration.h file)
// ===============================================================================
#ifdef UART_ASYNC_USE_RX


// функция для установки указателя приёмного буфера UART
// -------------------------------------------------------------------------------
// function for setting the UART receiving buffer pointer
void UART_Async_Set_Reception_Buffer_Ptr(const void *buffer);


// функция для установки размера приёмного буфера UART в байтах
// -------------------------------------------------------------------------------
// function for setting the size of the UART receiving buffer in bytes
void UART_Async_Set_Reception_Buffer_Size(const uint16_t buffer_size);


// функция для установки колбэка, вызывающегося при заполнении приёмного буфера
// -------------------------------------------------------------------------------
// function for setting the callback that is called when the receiving buffer is full
void UART_Async_Set_Reception_CallBack_Function(void (*callback_function)());


// функция, возвращающая статус приёма данных
// (UART_ASYNC_RECEPTION_IS_ACTIVE или UART_ASYNC_RECEPTION_IS_NOT_ACTIVE)
// -------------------------------------------------------------------------------
// function that returns the status of receiving data
// (UART_ASYNC_RECEPTION_IS_ACTIVE or UART_ASYNC_RECEPTION_IS_NOT_ACTIVE)
bool UART_Async_Get_Reception_Status();


// функция, возвращающая true, если приёмный буфер заполнен
// (иначе - вернёт false)
// -------------------------------------------------------------------------------
// function that returns true if the receiving buffer is full
// (otherwise it will return false)
bool UART_Async_Reception_Buffer_Is_Filled();


// функция, возвращающая указатель на приёмный буфер
// -------------------------------------------------------------------------------
// function that returns a pointer to the receiving buffer
void *UART_Async_Get_Reception_Buffer_Ptr();


// функция, возвращающая размер приёмного буфера в байтах
// -------------------------------------------------------------------------------
// function that returns the size of the receiving buffer in bytes
uint16_t UART_Async_Get_Reception_Buffer_Size();


// функция, возвращающая указатель на колбэк, вызывающегося
// при заполнении приёмного буфера
// -------------------------------------------------------------------------------
// function that returns a pointer to the callback
// that is called when the receiving buffer is full
void *UART_Async_Get_Reception_CallBack_Function();


// функция, возвращающая текущее количество принятых байт
// в приёмном буфере
// -------------------------------------------------------------------------------
// function that returns the current number of received bytes
// in the receiving buffer
uint16_t UART_Async_Get_Current_Reception_Buffer_Fullness();


#endif


// ===============================================================================


// ===============================================================================
// эти функции доступны, если определён макрос UART_ASYNC_USE_TX для
// асинхронной передачи данных (в файле uart_async_configuration.h)
// -------------------------------------------------------------------------------
// these functions are available if the UART_ASYNC_USE_TX macro is defined
// for asynchronous data transfer (in the uart_async_configuration.h file)
// ===============================================================================
#ifdef UART_ASYNC_USE_TX


// функция для установки колбэка, вызывающегося при завершении
// асинхронной передачи данных
// -------------------------------------------------------------------------------
// function for setting the callback that is called when
// asynchronous data transfer is completed
void UART_Async_Set_Transmittion_CallBack_Function(void (*callback_function)());


// функция, возвращающая указатель на колбэк, вызывающегося при завершении
// асинхронной передачи данных
// -------------------------------------------------------------------------------
// function that returns a pointer to the callback that is called when
// the asynchronous data transfer is completed
void *UART_Async_Get_Transmittion_CallBack_Function();


// функция, возвращающая статус передачи данных
// (UART_ASYNC_TRANSMITTION_IS_ACTIVE или UART_ASYNC_TRANSMITTION_IS_NOT_ACTIVE)
// -------------------------------------------------------------------------------
// function that returns the status of data transmission
// (UART_ASYNC_TRANSMITTION_IS_ACTIVE or UART_ASYNC_TRANSMITTION_IS_NOT_ACTIVE)
bool UART_Async_Get_Transmittion_Status();


// ===============================================================================


// функция для отправки байта
// -------------------------------------------------------------------------------
// function for sending a byte
void UART_Async_Byte_Transmit(uint8_t byte);


// функция для отправки массива данных
// -------------------------------------------------------------------------------
// function for sending an array of data
void UART_Async_Data_Transmit(const void *data, uint16_t data_size);


// функция для отправки строки
// -------------------------------------------------------------------------------
// function for sending a string
void UART_Async_String_Transmit(const char *string);


// функция для отправки строки с переходом на следующую строку
// -------------------------------------------------------------------------------
// function for sending a line with a transition to the next line
void UART_Async_StringLn_Transmit(const char *string);


// функция для отправки строки с учётом её длины
// (более безопасная версия UART_Async_String_Transmit)
// -------------------------------------------------------------------------------
// function for sending a string taking into account its length
// (a more secure version of UART_Async_String_Transmit)
void UART_Async_Safe_String_Transmit(const char *string, uint16_t max_string_len);


// функция для отправки строки с переходом на следующую строку (с учётом её длины)
// (более безопасная версия UART_Async_StringLn_Transmit)
// -------------------------------------------------------------------------------
// function for sending a string with a transition to the next line (taking into
// account its length) (a more secure version of UART_Async_StringLn_Transmit)
void UART_Async_Safe_StringLn_Transmit(const char *string, uint16_t max_string_len);


// ===============================================================================


// функция для отправки байта из flash памяти
// -------------------------------------------------------------------------------
// function for sending bytes from flash memory
void UART_Async_Flash_Byte_Transmit(const uint8_t *flash_byte);


// функция для отправки массива данных из flash памяти
// -------------------------------------------------------------------------------
// function for sending an array of data from flash memory
void UART_Async_Flash_Data_Transmit(const void *flash_data, uint16_t flash_data_size);


// функция для отправки строки из flash памяти
// -------------------------------------------------------------------------------
// function for sending a string from flash memory
void UART_Async_Flash_String_Transmit(const char *flash_string);


// функция для отправки строки из flash памяти с переходом на следующую строку
// -------------------------------------------------------------------------------
// function for sending a string from flash memory with a transition to the next line
void UART_Async_Flash_StringLn_Transmit(const char *flash_string);


// функция для отправки строки из flash памяти с учётом её длины
// (более безопасная версия UART_Async_Flash_String_Transmit)
// -------------------------------------------------------------------------------
// function for sending a string from flash memory, taking into account its length
// (a more secure version of UART_Async_Flash_String_Transmit)
void UART_Async_Flash_Safe_String_Transmit(const char *flash_string, uint16_t max_flash_string_len);


// функция для отправки строки из flash памяти с переходом на следующую строку и её длины
// (более безопасная версия UART_Async_Flash_StringLn_Transmit)
// -------------------------------------------------------------------------------
// function for sending a string from flash memory with a transition to the next line and its length
// (a more secure version of UART_Async_Flash_StringLn_Transmit)
void UART_Async_Flash_Safe_StringLn_Transmit(const char *flash_string, uint16_t max_flash_string_len);


#endif


// ===============================================================================


// ===============================================================================
// эти функции доступны, если определён макрос UART_ASYNC_USE_RX для
// асинхронного приёма данных (в файле uart_async_configuration.h)
// -------------------------------------------------------------------------------
// these functions are available if the UART_ASYNC_USE_RX macro is defined
// for asynchronous data reception (in the uart_async_configuration.h file)
// ===============================================================================
#ifdef UART_ASYNC_USE_RX


// функция, активирующая начало асинхронного приёма данных в буфер
// -------------------------------------------------------------------------------
// function that activates the start of asynchronous data reception to the buffer
void UART_Async_Start_Reception_Data_To_Buffer();


// функция, останавливающая асинхронный приём данных в буфер
// -------------------------------------------------------------------------------
// function that stops asynchronous data reception to the buffer
void UART_Async_Stop_Reception_Data_To_Buffer();


// функция, очищающая приёмный буфер
// -------------------------------------------------------------------------------
// function that clears the receiving buffer
void UART_Async_Clear_Reception_Buffer();


#endif

#endif

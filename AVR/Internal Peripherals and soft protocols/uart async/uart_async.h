
// ===============================================================================
//
// Библиотека для асинхронной работой с аппаратным модулем UART (через прерывания).
// Функции данной библиотеки не являются блокирующими, то есть при передаче и приëме
// данных процессор не блокируется.
//
// -------------------------------------------------------------------------------
//
// Library for asynchronous operation with the UART hardware module
// (via interrupts). The functions of this library are not blocking, that is
// the processor is not blocked during data transfer and receive.
//
// ===============================================================================


#ifndef UART_ASYNC_H_
#define UART_ASYNC_H_

#include "uart.h"
#include "uart_async_configuration.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>


#ifndef AVR_FLASH_DATA
#define AVR_FLASH_DATA(VAL, TYPE, DATA) const TYPE VAL[] PROGMEM = DATA
#endif



#define UART_ASYNC_TRANSMITTION_IS_ACTIVE          true
#define UART_ASYNC_TRANSMITTION_IS_NOT_ACTIVE      false

#define UART_ASYNC_RECEPTION_IS_ACTIVE             true
#define UART_ASYNC_RECEPTION_IS_NOT_ACTIVE         false

#define UART_ASYNC_RECEPTION_BUFFER_IS_FILLED      true
#define UART_ASYNC_RECEPTION_BUFFER_IS_NOT_FILLED  false



inline void UART_Async_Set_Transmittion_Enable(bool is_enable)
{
	UART_Set_End_Of_Transmittion_Interrupt_Enable(is_enable);
}

inline void UART_Async_Set_Reception_Enable(bool is_enable)
{
	UART_Set_End_Of_Reception_Interrupt_Enable(is_enable);
}

inline bool UART_Async_Transmittion_Is_Enable()
{
	return UART_End_Of_Transmittion_Interrupt_Is_Enable();
}

inline bool UART_Async_Reception_Is_Enable()
{
	return UART_End_Of_Reception_Interrupt_Is_Enable();
}


// ===============================================================================


#ifdef UART_ASYNC_USE_RX


void UART_Async_Set_Reception_Buffer_Ptr(const void *buffer);

void UART_Async_Set_Reception_Buffer_Size(const uint16_t buffer_size);

void UART_Async_Set_Reception_Terminator(uint8_t terminator);

void UART_Async_Set_Reception_Terminator_Enable(bool is_enable);

void UART_Async_Set_Reception_CallBack_Function(void (*callback_function)());

bool UART_Async_Get_Reception_Status();

bool UART_Async_Reception_Buffer_Is_Filled();

void *UART_Async_Get_Reception_Buffer_Ptr();

uint16_t UART_Async_Get_Reception_Buffer_Size();

uint16_t UART_Async_Get_Reception_Buffer_Counter();

uint8_t UART_Async_Get_Reception_Terminator();

bool UART_Async_Reception_Terminator_Is_Enable();

void *UART_Async_Get_Reception_CallBack_Function();

uint16_t UART_Async_Get_Current_Reception_Buffer_Fullness();

#endif


// ===============================================================================


#ifdef UART_ASYNC_USE_TX


void UART_Async_Set_Transmittion_CallBack_Function(void (*callback_function)());

void *UART_Async_Get_Transmittion_CallBack_Function();

bool UART_Async_Get_Transmittion_Status();


// ===============================================================================


void UART_Async_Byte_Transmit(uint8_t byte);

void UART_Async_Data_Transmit(const void *data, uint16_t data_size);

void UART_Async_String_Transmit(const char *string);

void UART_Async_StringLn_Transmit(const char *string);

void UART_Async_Safe_String_Transmit(const char *string, uint16_t max_string_len);

void UART_Async_Safe_StringLn_Transmit(const char *string, uint16_t max_string_len);


// ===============================================================================


void UART_Async_Flash_Byte_Transmit(const uint8_t *flash_byte);

void UART_Async_Flash_Data_Transmit(const void *flash_data, uint16_t flash_data_size);

void UART_Async_Flash_String_Transmit(const char *flash_string);

void UART_Async_Flash_StringLn_Transmit(const char *flash_string);

void UART_Async_Flash_Safe_String_Transmit(const char *flash_string, uint16_t max_flash_string_len);

void UART_Async_Flash_Safe_StringLn_Transmit(const char *flash_string, uint16_t max_flash_string_len);


#endif


// ===============================================================================


#ifdef UART_ASYNC_USE_RX


void UART_Async_Start_Reception_Data_To_Buffer();

void UART_Async_Stop_Reception_Data_To_Buffer();

void UART_Async_Clear_Reception_Buffer();

#endif

#endif



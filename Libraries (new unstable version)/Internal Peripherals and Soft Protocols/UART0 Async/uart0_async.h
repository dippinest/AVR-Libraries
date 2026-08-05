
// ===============================================================================
//
// Библиотека для асинхронной работой с аппаратным модулем UART0 (через прерывания).
// Функции данной библиотеки не являются блокирующими, то есть при передаче и приëме
// данных процессор не блокируется.
//
// Данная библиотека предназначена для работы с микроконтроллерами AVR,
// имеющих более одного модуля UART (в противном случае используйте
// библиотеку "uart_async.h")
//
// -------------------------------------------------------------------------------
//
// Library for asynchronous operation with the UART0 hardware module
// (via interrupts). The functions of this library are not blocking, that is
// the processor is not blocked during data transfer and receive.
//
// This library is designed to work with AVR microcontrollers with
// more than one UART module (otherwise use the "uart_async.h" library)
//
// ===============================================================================


#ifndef UART0_ASYNC_H_
#define UART0_ASYNC_H_

#include "uart0.h"
#include "uart0_async_configuration.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>


#ifndef AVR_FLASH_DATA
#define AVR_FLASH_DATA(VAL, TYPE, DATA) const TYPE VAL[] PROGMEM = DATA
#endif



#define UART0_ASYNC_TRANSMITTION_IS_ACTIVE          true
#define UART0_ASYNC_TRANSMITTION_IS_NOT_ACTIVE      false

#define UART0_ASYNC_RECEPTION_IS_ACTIVE             true
#define UART0_ASYNC_RECEPTION_IS_NOT_ACTIVE         false

#define UART0_ASYNC_RECEPTION_BUFFER_IS_FILLED      true
#define UART0_ASYNC_RECEPTION_BUFFER_IS_NOT_FILLED  false



inline void UART0_Async_Set_Transmittion_Enable(bool is_enable)
{
	UART0_Set_End_Of_Transmittion_Interrupt_Enable(is_enable);
}

inline void UART0_Async_Set_Reception_Enable(bool is_enable)
{
	UART0_Set_End_Of_Reception_Interrupt_Enable(is_enable);
}

inline bool UART0_Async_Transmittion_Is_Enable()
{
	return UART0_End_Of_Transmittion_Interrupt_Is_Enable();
}

inline bool UART0_Async_Reception_Is_Enable()
{
	return UART0_End_Of_Reception_Interrupt_Is_Enable();
}


// ===============================================================================


#ifdef UART0_ASYNC_USE_RX


void UART0_Async_Set_Reception_Buffer_Ptr(const void *buffer);

void UART0_Async_Set_Reception_Buffer_Size(const uint16_t buffer_size);

void UART0_Async_Set_Reception_Terminator(uint8_t terminator);

void UART0_Async_Set_Reception_Terminator_Enable(bool is_enable);

void UART0_Async_Set_Reception_Callback_Function(void (*callback_function)());

bool UART0_Async_Get_Reception_Status();

bool UART0_Async_Reception_Buffer_Is_Filled();

void *UART0_Async_Get_Reception_Buffer_Ptr();

uint16_t UART0_Async_Get_Reception_Buffer_Size();

uint16_t UART0_Async_Get_Reception_Buffer_Counter();

uint8_t UART0_Async_Get_Reception_Terminator();

bool UART0_Async_Reception_Terminator_Is_Enable();

void *UART0_Async_Get_Reception_Callback_Function();

uint16_t UART0_Async_Get_Current_Reception_Buffer_Fullness();

#endif


// ===============================================================================


#ifdef UART0_ASYNC_USE_TX


void UART0_Async_Set_Transmittion_Callback_Function(void (*callback_function)());

void *UART0_Async_Get_Transmittion_Callback_Function();

bool UART0_Async_Get_Transmittion_Status();


// ===============================================================================


void UART0_Async_Byte_Transmit(uint8_t byte);

void UART0_Async_Data_Transmit(const void *data, uint16_t data_size);

void UART0_Async_String_Transmit(const char *string);

void UART0_Async_StringLn_Transmit(const char *string);

void UART0_Async_Safe_String_Transmit(const char *string, uint16_t max_string_len);

void UART0_Async_Safe_StringLn_Transmit(const char *string, uint16_t max_string_len);


// ===============================================================================


void UART0_Async_Flash_Byte_Transmit(const uint8_t *flash_byte);

void UART0_Async_Flash_Data_Transmit(const void *flash_data, uint16_t flash_data_size);

void UART0_Async_Flash_String_Transmit(const char *flash_string);

void UART0_Async_Flash_StringLn_Transmit(const char *flash_string);

void UART0_Async_Flash_Safe_String_Transmit(const char *flash_string, uint16_t max_flash_string_len);

void UART0_Async_Flash_Safe_StringLn_Transmit(const char *flash_string, uint16_t max_flash_string_len);


#endif


// ===============================================================================


#ifdef UART0_ASYNC_USE_RX


void UART0_Async_Start_Reception_Data_To_Buffer();

void UART0_Async_Stop_Reception_Data_To_Buffer();

void UART0_Async_Clear_Reception_Buffer();

#endif

#endif




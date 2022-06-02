
#ifndef UART_NON_BLOCKING_H_
#define UART_NON_BLOCKING_H_

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "uart_non_blocking_configuration.h"

#define UART_NON_BLOCKING_TRANSMITTION_IS_ACTIVE          true
#define UART_NON_BLOCKING_TRANSMITTION_IS_NOT_ACTIVE      false


#define UART_NON_BLOCKING_RECEPTION_IS_ACTIVE             true
#define UART_NON_BLOCKING_RECEPTION_IS_NOT_ACTIVE         false

#define UART_NON_BLOCKING_RECEPTION_BUFFER_IS_FILLED      true
#define UART_NON_BLOCKING_RECEPTION_BUFFER_IS_NOT_FILLED  false

#define UART_NON_BLOCKING_BYTE_TRANSMIT                 0
#define UART_NON_BLOCKING_DATA_TRANSMIT                 1
#define UART_NON_BLOCKING_STRING_TRANSMIT               2
#define UART_NON_BLOCKING_STRINGLN_TRANSMIT             3
#define UART_NON_BLOCKING_SAFE_STRING_TRANSMIT          4
#define UART_NON_BLOCKING_SAFE_STRINGLN_TRANSMIT        5

#define UART_NON_BLOCKING_FLASH_DATA_TRANSMIT           6
#define UART_NON_BLOCKING_FLASH_STRING_TRANSMIT         7
#define UART_NON_BLOCKING_FLASH_STRINGLN_TRANSMIT       8
#define UART_NON_BLOCKING_FLASH_SAFE_STRING_TRANSMIT    9
#define UART_NON_BLOCKING_FLASH_SAFE_STRINGLN_TRANSMIT  10

inline void UART_NB_Set_Transmittion_Enable(bool is_enable)
{
	UART_Set_End_Of_Transmittion_Interrupt_Enable(is_enable);
}

inline void UART_NB_Set_Reception_Enable(bool is_enable)
{
	UART_Set_End_Of_Reception_Interrupt_Enable(is_enable);
}

inline bool UART_NB_Transmittion_Is_Enable()
{
	return UART_End_Of_Transmittion_Interrupt_Is_Enable();
}

inline bool UART_NB_Reception_Is_Enable()
{
	return UART_End_Of_Reception_Interrupt_Is_Enable();
}

// ===============================================================================

#ifdef UART_NON_BLOCKING_USE_RX

void UART_NB_Set_Reception_Buffer_Ptr(const void *buffer);

void UART_NB_Set_Reception_Buffer_Size(const uint16_t buffer_size);

void UART_NB_Set_Reception_CallBack_Function(void (*callback_function)());

bool UART_NB_Get_Reception_Status();

bool UART_NB_Reception_Buffer_Is_Filled();

void *UART_NB_Get_Reception_Buffer_Ptr();

uint16_t UART_NB_Get_Reception_Buffer_Size();

void *UART_NB_Get_Reception_CallBack_Function();

uint16_t UART_NB_Get_Current_Reception_Buffer_Fullness();

#endif

// ===============================================================================

#ifdef UART_NON_BLOCKING_USE_TX

bool UART_NB_Get_Transmittion_Status();

// ===============================================================================

void UART_NB_Byte_Transmit(uint8_t byte);

void UART_NB_Data_Transmit(const void *data, uint16_t data_size);

void UART_NB_String_Transmit(const char *string);

void UART_NB_StringLn_Transmit(const char *string);

void UART_NB_Safe_String_Transmit(const char *string, uint16_t max_string_len);

void UART_NB_Safe_StringLn_Transmit(const char *string, uint16_t max_string_len);

// ===============================================================================

void UART_NB_Flash_Byte_Transmit(const uint8_t *flash_byte);

void UART_NB_Flash_Data_Transmit(const void *flash_data, uint16_t flash_data_size);

void UART_NB_Flash_String_Transmit(const char *flash_string);

void UART_NB_Flash_StringLn_Transmit(const char *flash_string);

void UART_NB_Flash_Safe_String_Transmit(const char *flash_string, uint16_t max_flash_string_len);

void UART_NB_Flash_Safe_StringLn_Transmit(const char *flash_string, uint16_t max_flash_string_len);

#endif

// ===============================================================================

#ifdef UART_NON_BLOCKING_USE_RX

void UART_NB_Start_Reception_Data_To_Buffer();

void UART_NB_Stop_Reception_Data_To_Buffer();

void UART_NB_Clear_Reception_Buffer();

#endif

#endif

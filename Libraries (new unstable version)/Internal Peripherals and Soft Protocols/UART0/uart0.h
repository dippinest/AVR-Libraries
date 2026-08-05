
// ===============================================================================
//
// Библиотека для работы с аппаратным модулем UART0 и предназначена для работы
// с микроконтроллерами AVR, имеющих более одного модуля UART (в противном случае
// используйте библиотеку "uart.h")
// Функции данной библиотеки являются блокирующими, то есть при работе модуля
// процессор полностью блокируется. Для возможности асинхронной работы с модулем
// UART1 для приёма и передачи данных (с помощью прерываний) используйте
// библиотеку "uart_async0.h"
//
// -------------------------------------------------------------------------------
//
// Library is designed to work with the UART0 hardware module and is designed
// to work with AVR microcontrollers with more than one UART module (otherwise,
// use the "uart.h" library.
// The functions of this library are blocking, that is, when the module is running,
// the processor is completely blocked. To work asynchronously with the
// UART1 module for receiving and transmitting data (using interrupts),
// use the "uart_async0.h" library.
//
// ===============================================================================


#ifndef UART0_H_
#define UART0_H_

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <avr/io.h>
#include <avr/pgmspace.h>


#if defined\
(__AVR_ATmega64__)  ||\
(__AVR_ATmega64A__) ||\
(__AVR_ATmega128__) ||\
(__AVR_ATmega128A__)

#define USART0_TXC_vect USART0_TX_vect
#define USART0_RXC_vect USART0_RX_vect

#endif



#ifndef AVR_FLASH_DATA
#define AVR_FLASH_DATA(VAL, TYPE, DATA) const TYPE VAL[] PROGMEM = DATA
#endif


#define UART0_NUM_OF_DATA_BITS_5 5
#define UART0_NUM_OF_DATA_BITS_6 6
#define UART0_NUM_OF_DATA_BITS_7 7
#define UART0_NUM_OF_DATA_BITS_8 8

#define UART0_NUM_OF_STOP_BITS_1 1
#define UART0_NUM_OF_STOP_BITS_2 2

#define UART0_PARITY_BIT_NONE 0
#define UART0_PARITY_BIT_EVEN 1
#define UART0_PARITY_BIT_ODD  2


#define _UART0_SET_CODE_BAUDRATE(_BAUDRATE_VALUE) (F_CPU / 8UL / _BAUDRATE_VALUE)


// ===============================================================================


inline void UART0_Set_Transmittion_Enable(bool transmittion_is_enable)
{
	if (transmittion_is_enable)
	{
		UCSR0B |=  (1 << TXEN0);
	}
	else
	{
		UCSR0B &= ~(1 << TXEN0);
	}
}

inline void UART0_Set_Reception_Enable(bool reception_is_enable)
{
	if (reception_is_enable)
	{
		UCSR0B |=  (1 << RXEN0);
	}
	else
	{
		UCSR0B &= ~(1 << RXEN0);
	}
}

inline void UART0_Set_Buffer_Emptying_Interrupt_Enable(bool buffer_emptying_interrupt_is_enable)
{
	if (buffer_emptying_interrupt_is_enable)
	{
		UCSR0B |=  (1 << UDRIE0);
	}
	else
	{
		UCSR0B &= ~(1 << UDRIE0);
	}
}

inline void UART0_Set_End_Of_Transmittion_Interrupt_Enable(bool end_of_transmittion_interrupt_is_enable)
{
	if (end_of_transmittion_interrupt_is_enable)
	{
		UCSR0B |=  (1 << TXCIE0);
	}
	else
	{
		UCSR0B &= ~(1 << TXCIE0);
	}
}

inline void UART0_Set_End_Of_Reception_Interrupt_Enable(bool end_of_reception_interrupt_is_enable)
{
	if (end_of_reception_interrupt_is_enable)
	{
		UCSR0B |=  (1 << RXCIE0);
	}
	else
	{
		UCSR0B &= ~(1 << RXCIE0);
	}
}

inline bool UART0_Transmittion_Is_Enable()
{
	if (UCSR0B & (1 << TXEN0))
	{
		return true;
	}
	
	return false;
}

inline bool UART0_Reception_Is_Enable()
{
	if (UCSR0B & (1 << RXEN0))
	{
		return true;
	}
	
	return false;
}

inline bool UART0_Buffer_Emptying_Interrupt_Is_Enable()
{
	if (UCSR0B & (1 << UDRIE0))
	{
		return true;
	}
	
	return false;
}

inline bool UART0_End_Of_Transmittion_Interrupt_Is_Enable()
{
	if (UCSR0B & (1 << TXCIE0))
	{
		return true;
	}
	
	return false;
}

inline bool UART0_End_Of_Reception_Interrupt_Is_Enable()
{
	if (UCSR0B & (1 << RXCIE0))
	{
		return true;
	}
	
	return false;
}


// ===============================================================================


void UART0_Set_Baudrate(uint32_t baudrate);

uint32_t UART0_Get_Baudrate();

void UART0_Set_Num_Of_Data_Bits(uint8_t num_of_data_bits);

void UART0_Set_Num_Of_Stop_Bits(uint8_t num_of_stop_bits);

void UART0_Set_Parity_Bit(uint8_t parity_bit);

uint8_t UART0_Get_Num_Of_Data_Bits();

uint8_t UART0_Get_Num_Of_Stop_Bits();

uint8_t UART0_Get_Parity_Bit();


// ===============================================================================


void UART0_Byte_Transmit(uint8_t byte);

void UART0_Data_Transmit(const void *data, uint16_t data_size);

void UART0_String_Transmit(const char *string);

void UART0_StringLn_Transmit(const char *string);

void UART0_StringFmt_Transmit(const char *string_fmt, ...);

void UART0_Safe_String_Transmit(const char *string, uint16_t max_string_len);

void UART0_Safe_StringLn_Transmit(const char *string, uint16_t max_string_len);


// ===============================================================================


void UART0_Flash_Byte_Transmit(const uint8_t *flash_byte);

void UART0_Flash_Data_Transmit(const void *flash_data, uint16_t flash_data_size);

void UART0_Flash_String_Transmit(const char *flash_string);

void UART0_Flash_StringLn_Transmit(const char *flash_string);

void UART0_Flash_StringFmt_Transmit(const char *flash_string_fmt, ...);

void UART0_Flash_Safe_String_Transmit(const char *flash_string, uint16_t max_flash_string_len);

void UART0_Flash_Safe_StringLn_Transmit(const char *flash_string, uint16_t max_flash_string_len);


// ===============================================================================


uint8_t UART0_Byte_Receive();

void *UART0_Data_Receive(void *data, uint16_t data_size);

uint16_t UART0_Data_Receive_Before_Terminator(void *data, uint8_t terminator, uint16_t max_data_size);


// ===============================================================================


void UART0_Initialize(uint32_t baudrate, bool transmittion_is_allowed, bool reception_is_allowed);


// ===============================================================================


#define UART0_NEW_LINE UART0_String_Transmit("\r\n");


#ifdef DEBUG

#define DEBUGPRINT_UART0(STR)    UART0_String_Transmit(STR);

#define DEBUGPRINTLN_UART0(STR)  UART0_StringLn_Transmit(STR);

#else

#define DEBUGPRINT_UART0(STR)

#define DEBUGPRINTLN_UART0(STR)

#endif


#endif



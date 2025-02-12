
// ===============================================================================
//
// Библиотека для работы с аппаратным модулем UART1 и предназначена для работы
// с микроконтроллерами AVR, имеющих более одного модуля UART (в противном случае
// используйте библиотеку "uart.h")
// Функции данной библиотеки являются блокирующими, то есть при работе модуля
// процессор полностью блокируется. Для возможности асинхронной работы с модулем
// UART1 для приёма и передачи данных (с помощью прерываний) используйте
// библиотеку "uart_async1.h"
//
// -------------------------------------------------------------------------------
//
// Library is designed to work with the UART1 hardware module and is designed
// to work with AVR microcontrollers with more than one UART module (otherwise,
// use the "uart.h" library.
// The functions of this library are blocking, that is, when the module is running,
// the processor is completely blocked. To work asynchronously with the
// UART1 module for receiving and transmitting data (using interrupts),
// use the "uart_async1.h" library.
//
// ===============================================================================


#ifndef UART1_H_
#define UART1_H_

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

#define USART1_TXC_vect USART1_TX_vect
#define USART1_RXC_vect USART1_RX_vect

#endif



#ifndef AVR_FLASH_DATA
#define AVR_FLASH_DATA(VAL, TYPE, DATA) const TYPE VAL[] PROGMEM = DATA
#endif


#define UART1_NUM_OF_DATA_BITS_5 5
#define UART1_NUM_OF_DATA_BITS_6 6
#define UART1_NUM_OF_DATA_BITS_7 7
#define UART1_NUM_OF_DATA_BITS_8 8

#define UART1_NUM_OF_STOP_BITS_1 1
#define UART1_NUM_OF_STOP_BITS_2 2

#define UART1_PARITY_BIT_NONE 0
#define UART1_PARITY_BIT_EVEN 1
#define UART1_PARITY_BIT_ODD  2


#define _UART1_SET_CODE_BAUDRATE(_BAUDRATE_VALUE) (F_CPU / 8UL / _BAUDRATE_VALUE)


// ===============================================================================


inline void UART1_Set_Transmittion_Enable(bool transmittion_is_enable)
{
	if (transmittion_is_enable)
	{
		UCSR1B |=  (1 << TXEN1);
	}
	else
	{
		UCSR1B &= ~(1 << TXEN1);
	}
}

inline void UART1_Set_Reception_Enable(bool reception_is_enable)
{
	if (reception_is_enable)
	{
		UCSR1B |=  (1 << RXEN1);
	}
	else
	{
		UCSR1B &= ~(1 << RXEN1);
	}
}

inline void UART1_Set_Buffer_Emptying_Interrupt_Enable(bool buffer_emptying_interrupt_is_enable)
{
	if (buffer_emptying_interrupt_is_enable)
	{
		UCSR1B |=  (1 << UDRIE1);
	}
	else
	{
		UCSR1B &= ~(1 << UDRIE1);
	}
}

inline void UART1_Set_End_Of_Transmittion_Interrupt_Enable(bool end_of_transmittion_interrupt_is_enable)
{
	if (end_of_transmittion_interrupt_is_enable)
	{
		UCSR1B |=  (1 << TXCIE1);
	}
	else
	{
		UCSR1B &= ~(1 << TXCIE1);
	}
}

inline void UART1_Set_End_Of_Reception_Interrupt_Enable(bool end_of_reception_interrupt_is_enable)
{
	if (end_of_reception_interrupt_is_enable)
	{
		UCSR1B |=  (1 << RXCIE1);
	}
	else
	{
		UCSR1B &= ~(1 << RXCIE1);
	}
}

inline bool UART1_Transmittion_Is_Enable()
{
	if (UCSR1B & (1 << TXEN1))
	{
		return true;
	}
	
	return false;
}

inline bool UART1_Reception_Is_Enable()
{
	if (UCSR1B & (1 << RXEN1))
	{
		return true;
	}
	
	return false;
}

inline bool UART1_Buffer_Emptying_Interrupt_Is_Enable()
{
	if (UCSR1B & (1 << UDRIE1))
	{
		return true;
	}
	
	return false;
}

inline bool UART1_End_Of_Transmittion_Interrupt_Is_Enable()
{
	if (UCSR1B & (1 << TXCIE1))
	{
		return true;
	}
	
	return false;
}

inline bool UART1_End_Of_Reception_Interrupt_Is_Enable()
{
	if (UCSR1B & (1 << RXCIE1))
	{
		return true;
	}
	
	return false;
}


// ===============================================================================


void UART1_Set_Baudrate(uint32_t baudrate);

uint32_t UART1_Get_Baudrate();

void UART1_Set_Num_Of_Data_Bits(uint8_t num_of_data_bits);

void UART1_Set_Num_Of_Stop_Bits(uint8_t num_of_stop_bits);

void UART1_Set_Parity_Bit(uint8_t parity_bit);

uint8_t UART1_Get_Num_Of_Data_Bits();

uint8_t UART1_Get_Num_Of_Stop_Bits();

uint8_t UART1_Get_Parity_Bit();


// ===============================================================================


void UART1_Byte_Transmit(uint8_t byte);

void UART1_Data_Transmit(const void *data, uint16_t data_size);

void UART1_String_Transmit(const char *string);

void UART1_StringLn_Transmit(const char *string);

void UART1_StringFmt_Transmit(const char *string_fmt, ...);

void UART1_Safe_String_Transmit(const char *string, uint16_t max_string_len);

void UART1_Safe_StringLn_Transmit(const char *string, uint16_t max_string_len);


// ===============================================================================


void UART1_Flash_Byte_Transmit(const uint8_t *flash_byte);

void UART1_Flash_Data_Transmit(const void *flash_data, uint16_t flash_data_size);

void UART1_Flash_String_Transmit(const char *flash_string);

void UART1_Flash_StringLn_Transmit(const char *flash_string);

void UART1_Flash_StringFmt_Transmit(const char *flash_string_fmt, ...);

void UART1_Flash_Safe_String_Transmit(const char *flash_string, uint16_t max_flash_string_len);

void UART1_Flash_Safe_StringLn_Transmit(const char *flash_string, uint16_t max_flash_string_len);


// ===============================================================================


uint8_t UART1_Byte_Receive();

void *UART1_Data_Receive(void *data, uint16_t data_size);

uint16_t UART1_Data_Receive_Before_Terminator(void *data, uint8_t terminator, uint16_t max_data_size);


// ===============================================================================


void UART1_Initialize(uint32_t baudrate, bool transmittion_is_allowed, bool reception_is_allowed);


// ===============================================================================


#define UART1_NEW_LINE UART1_String_Transmit("\r\n");


#ifdef DEBUG

#define DEBUGPRINT_UART1(STR)    UART1_String_Transmit(STR);

#define DEBUGPRINTLN_UART1(STR)  UART1_StringLn_Transmit(STR);

#else

#define DEBUGPRINT_UART1(STR)

#define DEBUGPRINTLN_UART1(STR)

#endif


#endif



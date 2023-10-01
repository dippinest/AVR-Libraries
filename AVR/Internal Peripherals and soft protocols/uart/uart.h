
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



#if defined\
(__AVR_ATmega64__)   ||\
(__AVR_ATmega64A__)  ||\
(__AVR_ATmega128__)  ||\
(__AVR_ATmega128A__)

#define UDR   UDR0
#define UCSRA UCSR0A
#define UCSRB UCSR0B
#define UCSRC UCSR0C
#define UBRRL UBRR0L
#define UBRRH UBRR0H

#endif



#if defined\
(__AVR_ATmega64A__)  ||\
(__AVR_ATmega128A__)

#define U2X    U2X0
#define UCSZ0  UCSZ00
#define UCSZ1  UCSZ10
#define USBS   USBS0
#define UPM0   UPM00
#define UPM1   UPM10
#define UDRE   UDRE0
#define TXEN   TXEN0
#define RXEN   RXEN0
#define UDRIE  UDRIE0
#define TXCIE  TXCIE0
#define RXCIE  RXCIE0

#endif



#if defined\
(__AVR_ATmega64__)  ||\
(__AVR_ATmega64A__) ||\
(__AVR_ATmega128__) ||\
(__AVR_ATmega128A__)

#define USART_TXC_vect USART0_TX_vect
#define USART_RXC_vect USART0_RX_vect

#endif



#define UART_NUM_OF_DATA_BITS_5 5
#define UART_NUM_OF_DATA_BITS_6 6
#define UART_NUM_OF_DATA_BITS_7 7
#define UART_NUM_OF_DATA_BITS_8 8


#define UART_NUM_OF_STOP_BITS_1 1
#define UART_NUM_OF_STOP_BITS_2 2


#define UART_PARITY_BIT_NONE 0
#define UART_PARITY_BIT_EVEN 1
#define UART_PARITY_BIT_ODD  2



#define _UART_SET_CODE_BAUDRATE(_BAUDRATE_VALUE) (F_CPU / 8UL / _BAUDRATE_VALUE)



// ===============================================================================



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


inline bool UART_Transmittion_Is_Enable()
{
	if (UCSRB & (1 << TXEN))
	{
		return true;
	}
	
	return false;
}


inline bool UART_Reception_Is_Enable()
{
	if (UCSRB & (1 << RXEN))
	{
		return true;
	}
	
	return false;
}


inline bool UART_Buffer_Emptying_Interrupt_Is_Enable()
{
	if (UCSRB & (1 << UDRIE))
	{
		return true;
	}
	
	return false;
}


inline bool UART_End_Of_Transmittion_Interrupt_Is_Enable()
{
	if (UCSRB & (1 << TXCIE))
	{
		return true;
	}
	
	return false;
}


inline bool UART_End_Of_Reception_Interrupt_Is_Enable()
{
	if (UCSRB & (1 << RXCIE))
	{
		return true;
	}
	
	return false;
}



// ===============================================================================



void UART_Set_Baudrate(uint32_t baudrate);


uint32_t UART_Get_Baudrate();


void UART_Set_Num_Of_Data_Bits(uint8_t num_of_data_bits);


void UART_Set_Num_Of_Stop_Bits(uint8_t num_of_stop_bits);


void UART_Set_Parity_Bit(uint8_t parity_bit);


uint8_t UART_Get_Num_Of_Data_Bits();


uint8_t UART_Get_Num_Of_Stop_Bits();


uint8_t UART_Get_Parity_Bit();



// ===============================================================================



void UART_Byte_Transmit(uint8_t byte);


void UART_Data_Transmit(const void *data, uint16_t data_size);


void UART_String_Transmit(const char *string);


void UART_StringLn_Transmit(const char *string);


void UART_StringFmt_Transmit(const char *string_fmt, ...);


void UART_Safe_String_Transmit(const char *string, uint16_t max_string_len);


void UART_Safe_StringLn_Transmit(const char *string, uint16_t max_string_len);



// ===============================================================================



void UART_Flash_Byte_Transmit(const uint8_t *flash_byte);


void UART_Flash_Data_Transmit(const void *flash_data, uint16_t flash_data_size);


void UART_Flash_String_Transmit(const char *flash_string);


void UART_Flash_StringLn_Transmit(const char *flash_string);


void UART_Flash_StringFmt_Transmit(const char *flash_string_fmt, ...);


void UART_Flash_Safe_String_Transmit(const char *flash_string, uint16_t max_flash_string_len);


void UART_Flash_Safe_StringLn_Transmit(const char *flash_string, uint16_t max_flash_string_len);



// ===============================================================================


void UART_Initialize(uint32_t baudrate, bool transmittion_is_allowed, bool reception_is_allowed);


// ===============================================================================



#define UART_NEW_LINE UART_String_Transmit("\r\n");



#ifdef DEBUG

#define DEBUGPRINT(STR)    UART_String_Transmit(STR);

#define DEBUGPRINTLN(STR)  UART_StringLn_Transmit(STR);

#elif

#define DEBUGPRINT(STR)

#define DEBUGPRINTLN(STR)

#endif


#endif



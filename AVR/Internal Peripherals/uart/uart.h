
#ifndef UART_H_
#define UART_H_

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

// macros for determining the number of data bits
#define UART_NUM_OF_DATA_BITS_5 5
#define UART_NUM_OF_DATA_BITS_6 6
#define UART_NUM_OF_DATA_BITS_7 7
#define UART_NUM_OF_DATA_BITS_8 8

// macros for determining the number of stop bits
#define UART_NUM_OF_STOP_BITS_1 1
#define UART_NUM_OF_STOP_BITS_2 2

// macros for determining the parity bit
#define UART_PARITY_BIT_NONE 0
#define UART_PARITY_BIT_EVEN 1
#define UART_PARITY_BIT_ODD  2

// macro for UART speed conversion
#define _UART_SET_CODE_BAUDRATE(_BAUDRATE_VALUE) (F_CPU / 8UL / _BAUDRATE_VALUE)


// ===============================================================================

inline void UART_Set_Transmission_Enable(bool transmission_is_enable)
{
	if (transmission_is_enable)
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

inline bool UART_Transmission_Is_Enable()
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

void UART_Flash_StringFmt_Transmit(const char *flash_string_fmt, ...); // function not supported '%s' from flash!

void UART_Flash_Safe_String_Transmit(const char *flash_string, uint16_t max_flash_string_len);

void UART_Flash_Safe_StringLn_Transmit(const char *flash_string, uint16_t max_flash_string_len);

// ===============================================================================


void UART_Initialize(uint32_t baudrate, bool transmission_is_allowed, bool reception_is_allowed);

// ===============================================================================


// macro for moving the cursor to a new line in the UART terminal
#define UART_NEW_LINE UART_String_Transmit("\r\n");

#endif

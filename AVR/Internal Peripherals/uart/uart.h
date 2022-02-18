// ======================================================================================================
//  Header              : uart.h                                                                        -
//  Created             : 11.02.2022                                                                    -
//  Author              : Denis Chicherov (dippinest)                                                   -
//  Description         : Declarations of functions and macros for working with the UART module         -
// ======================================================================================================

#ifndef UART_H_
#define UART_H_

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <avr/io.h>

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

// function for getting the current speed of the UART transceiver in baud per second
uint32_t UART_Get_Baudrate();

// function for determining whether the UART transmitter has a working permit
bool UART_Transmission_Is_Allowed();

// function for determining whether the UART receiver has a working permit
bool UART_Reception_Is_Allowed();

// function for determining whether an interrupt operation
// is allowed to empty the receiving buffer
bool UART_Buffer_Emptying_Interrupt_Is_Allowed();

// function for determining whether there is a permission
// for the operation of an interrupt upon completion of data transmission
bool UART_End_Of_Transmittion_Interrupt_Is_Allowed();

// function for determining whether there is a permission for the operation
// of an interrupt upon completion of data reception
bool UART_End_Of_Reception_Interrupt_Is_Allowed();

// function for getting the number of data bits
uint8_t UART_Get_Num_Of_Data_Bits();

// function for getting the number of stop bits
uint8_t UART_Get_Num_Of_Stop_Bits();

// function to get the type of parity bit (use together with macros UART_PARITY_BIT_X)
uint8_t UART_Get_Parity_Bit();

// function for initializing UART
void UART_Initialize
(
uint32_t baudrate,
bool transmission_is_allowed,
bool reception_is_allowed,
bool buffer_emptying_interrupt_is_allowed,
bool end_of_transmittion_interrupt_is_allowed,
bool end_of_reception_interrupt_is_allowed,
uint8_t num_of_data_bits,
uint8_t num_of_stop_bits,
uint8_t parity_bit
);

// function for sending a byte of data to the UART
void UART_Byte_Transmit(uint8_t byte);

// function for sending an array of data to UART
void UART_Data_Transmit(const void *data, uint16_t data_size);

// function for sending a C-type string to UART
void UART_String_Transmit(const char *string);

// function for sending a C-type string to UART followed by switching to a new line
void UART_StringLn_Transmit(const char *string);

// function for sending a C-type format string to UART
void UART_StringFmt_Transmit(const char *string_fmt, ...);

// a safe version of the "UART_String_Transmit" function with
// a limit on the number of characters sent
void UART_Safe_String_Transmit(const char *string, uint16_t max_string_len);

// a safe version of the "UART_StringLn_Transmit" function with
// a limit on the number of characters sent
void UART_Safe_StringLn_Transmit(const char *string, uint16_t max_string_len);

// macro for moving the cursor to a new line in the UART terminal
#define UART_NEW_LINE UART_String_Transmit("\r\n");

#endif

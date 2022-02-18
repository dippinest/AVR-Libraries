// ======================================================================================================
//  Header              : itoa.h                                                                        -
//  Created             : 18.02.2022                                                                    -
//  Author              : Denis Chicherov (dippinest)                                                   -
//  Description         : Declaring functions for converting integer types to a C-type string           -
// ======================================================================================================

#ifndef ITOA_H_
#define ITOA_H_

#include <stdint.h>

char *ITOA_Int8_To_String(int8_t val, int8_t num_of_chars, const char empty_character, char *string_buf);

char *ITOA_UInt8_To_String(uint8_t val, int8_t num_of_chars, const char empty_character, char *string_buf);

char *ITOA_Int16_To_String(int16_t val, int8_t num_of_chars, const char empty_character, char *string_buf);

char *ITOA_UInt16_To_String(uint16_t val, int8_t num_of_chars, const char empty_character, char *string_buf);

char *ITOA_Int32_To_String(int32_t val, int8_t num_of_chars, const char empty_character, char *string_buf);

char *ITOA_UInt32_To_String(uint32_t val, int8_t num_of_chars, const char empty_character, char *string_buf);

char *ITOA_Int64_To_String(int64_t val, int8_t num_of_chars, const char empty_character, char *string_buf);

char *ITOA_UInt64_To_String(uint64_t val, int8_t num_of_chars, const char empty_character, char *string_buf);

#endif
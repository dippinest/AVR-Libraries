
// This is a library for working with numbers with a pseudo-fixed point.
// Numbers with a pseudo-fixed point are so called because fractional digits
// are given by the lower digits of an integer decimal number, and not binary,
// as in the case of classical solutions
//
// the maximum modulo value for a 32-bit number is 2^31 - 1 (2147483647.);
// the minimum depends on the position of the fixed point
//
// the maximum modulo value for a 64-bit number is 2^63 - 1 (9223372036854775807.);
// the minimum depends on the position of the fixed point

#ifndef PFIXPOINT_H_
#define PFIXPOINT_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// ===============================================================================

void PFIXPoint_Set_String_Buffer(char* string_buffer_ptr);

char *PFIXPoint_Set_String_Buffer_To_Dynamic_Memory(const uint8_t string_buffer_size);

void PFIXPoint_Delete_String_Buffer_To_Dynamic_Memory();

// ===============================================================================

void PFIXPoint_Set_Number_Of_Decimal_Places(const uint8_t number_of_decimal_places);

void PFIXPoint_Set_Empty_Char_Symbol(const char empty_char);

void PFIXPoint_Set_Decimal_Char_Separator(const char char_separator);

char* PFIXPoint_Get_String_Buffer_Ptr();

char PFIXPoint_Get_Number_Of_Decimal_Places();

char PFIXPoint_Get_Empty_Char_Symbol();

char PFIXPoint_Get_Decimal_Char_Separator();

// ===============================================================================

char* PFIXPoint_Int32PFP_To_String(int32_t val, int8_t num_int_digits, int8_t num_fract_digits);

// use a 64-bit representation of numbers to get a large
// dynamic representation of a number with a pseudo-fixed point
char* PFIXPoint_Int64PFP_To_String(int64_t val, int8_t num_int_digits, int8_t num_fract_digits);

#endif

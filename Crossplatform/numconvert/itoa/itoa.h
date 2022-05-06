
#ifndef ITOA_H_
#define ITOA_H_

#include <stdint.h>
#include <stdlib.h>

// ===============================================================================

void ITOA_Set_String_Buffer(char *string_buffer_ptr);

int ITOA_Set_String_Buffer_To_Dynamic_Memory(const uint8_t string_buffer_size);

void ITOA_Delete_String_Buffer_To_Dynamic_Memory();

// ===============================================================================

void ITOA_Set_Empty_Char_Symbol(const char empty_char);

void ITOA_Set_Decimal_Char_Separator(const char char_separator);

void ITOA_Set_Decimal_Char_Separator(const char char_separator);

void ITOA_Set_Num_Of_Fract_Part_Chars(const uint8_t num_of_fract_part_chars);

char *ITOA_Get_String_Buffer_Ptr();

char ITOA_Get_Empty_Char_Symbol();

char ITOA_Get_Decimal_Char_Separator();

uint8_t ITOA_Get_Num_Of_Fract_Part_Chars();

// ===============================================================================

char *ITOA_Int8_To_String(int8_t val, int8_t num_of_chars);

char *ITOA_UInt8_To_String(uint8_t val, int8_t num_of_chars);

char *ITOA_Int16_To_String(int16_t val, int8_t num_of_chars);

char *ITOA_UInt16_To_String(uint16_t val, int8_t num_of_chars);

char *ITOA_Int32_To_String(int32_t val, int8_t num_of_chars);

char *ITOA_UInt32_To_String(uint32_t val, int8_t num_of_chars);

char *ITOA_Int64_To_String(int64_t val, int8_t num_of_chars);

char *ITOA_UInt64_To_String(uint64_t val, int8_t num_of_chars);

#endif

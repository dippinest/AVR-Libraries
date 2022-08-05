
#ifndef ITOBINA_H_
#define ITOBINA_H_

#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

// ===============================================================================

void ITOBINA_Set_String_Buffer(char *string_buffer_ptr);

char *ITOBINA_Set_String_Buffer_To_Dynamic_Memory(const uint8_t string_buffer_size);

void ITOBINA_Delete_String_Buffer_To_Dynamic_Memory();

// ===============================================================================

char *ITOBINA_8bitNum_To_BinString(uint8_t val);

char *ITOBINA_16bitNum_To_BinString(uint16_t val);

char *ITOBINA_32bitNum_To_BinString(uint32_t val);

char *ITOBINA_64bitNum_To_BinString(uint64_t val);

#endif
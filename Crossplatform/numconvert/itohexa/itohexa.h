// =============================================================================================================
//  Header              : itohexa.h                                                                            -
//  Created             : 20.02.2022                                                                           -
//  Author              : Denis Chicherov (dippinest)                                                          -
//  Description         : Declaration of functions for converting integer types to a HEX format C-type string  -
// =============================================================================================================

#ifndef ITOHEXA_H_
#define ITOHEXA_H_

#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>

char *ITOHEXA_8bitNum_To_HexString(uint8_t val, bool is_lower_case, char *string_buf);

char *ITOHEXA_16bitNum_To_HexString(uint16_t val, bool is_lower_case, char *string_buf);

char *ITOHEXA_32bitNum_To_HexString(uint32_t val, bool is_lower_case, char *string_buf);

char *ITOHEXA_64bitNum_To_HexString(uint64_t val, bool is_lower_case, char *string_buf);

#endif
// ======================================================================================================
//  Header              : bcdcode.h                                                                     -
//  Created             : 30.04.2022                                                                    -
//  Author              : Denis Chicherov (dippinest)                                                   -
//  Description         : Declaring of functions for converting numbers                                 -
//                        to binary-decimal code (BCD) and back                                         -
// ======================================================================================================

#ifndef BCDCODE_H_
#define BCDCODE_H_

#include <stdint.h>

uint8_t BCDCODE_Convert_UINT8_To_UINT8_BCD(uint8_t num);

uint8_t BCDCODE_Convert_UINT8_BCD_To_UINT8(uint8_t bcd);

uint16_t BCDCODE_Convert_UINT16_To_UINT16_BCD(uint16_t num);

uint16_t BCDCODE_Convert_UINT16_BCD_To_UINT16(uint16_t bcd);

uint32_t BCDCODE_Convert_UINT32_To_UINT32_BCD(uint32_t num);

uint32_t BCDCODE_Convert_UINT32_BCD_To_UINT32(uint32_t bcd);

uint64_t BCDCODE_Convert_UINT64_To_UINT64_BCD(uint64_t num);

uint64_t BCDCODE_Convert_UINT64_BCD_To_UINT64(uint64_t bcd);

#endif
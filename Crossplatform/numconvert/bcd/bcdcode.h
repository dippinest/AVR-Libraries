
#ifndef BCDCODE_H_
#define BCDCODE_H_

#include <stdint.h>

uint8_t BCDCODE_UInt8_To_UInt8BCD(uint8_t num);

uint8_t BCDCODE_UInt8BCD_To_UInt8(uint8_t bcd_code);

uint16_t BCDCODE_UInt16_To_UInt16BCD(uint16_t num);

uint16_t BCDCODE_UInt16BCD_To_UInt16(uint16_t bcd_code);

uint32_t BCDCODE_UInt32_To_UInt32BCD(uint32_t num);

uint32_t BCDCODE_UInt32BCD_To_UInt32(uint32_t bcd_code);

uint64_t BCDCODE_UInt64_To_UInt64BCD(uint64_t num);

uint64_t BCDCODE_UInt64BCD_To_UInt64(uint64_t bcd_code);

#endif

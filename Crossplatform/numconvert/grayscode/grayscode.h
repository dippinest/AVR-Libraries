
#ifndef GRAYSCODE_H_
#define GRAYSCODE_H_

#include <stdint.h>

uint8_t GRAYSCODE_UInt8_To_UInt8Grayscode(uint8_t num);

uint8_t GRAYSCODE_UInt8Grayscode_To_UInt8(uint8_t gray_code);

uint16_t GRAYSCODE_UInt16_To_UInt16Grayscode(uint16_t num);

uint16_t GRAYSCODE_UInt16Grayscode_To_UInt16(uint16_t gray_code);

uint32_t GRAYSCODE_UInt32_To_UInt32Grayscode(uint32_t num);

uint32_t GRAYSCODE_UInt32Grayscode_To_UInt32(uint32_t gray_code);

uint64_t GRAYSCODE_UInt64_To_UInt64Grayscode(uint64_t num);

uint64_t GRAYSCODE_UInt64Grayscode_To_UInt64(uint64_t gray_code);

#endif
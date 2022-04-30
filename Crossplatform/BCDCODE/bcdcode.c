// ======================================================================================================
//  Header              : bcdcode.c                                                                     -
//  Created             : 30.04.2022                                                                    -
//  Author              : Denis Chicherov (dippinest)                                                   -
//  Description         : Defining of functions for converting numbers                                  -
//                        to binary-decimal code (BCD) and back                                         -
// ======================================================================================================

#include "bcdcode.h"

uint8_t BCDCODE_Convert_UINT8_To_UINT8_BCD(uint8_t num)
{
	return ((num / 10) << 4) | (num % 10);
}

uint8_t BCDCODE_Convert_UINT8_BCD_To_UINT8(uint8_t bcd)
{
	uint8_t num = (bcd >> 4) * 10;
	num += (bcd & 0x0F);
	return num;
}

uint16_t BCDCODE_Convert_UINT16_To_UINT16_BCD(uint16_t num)
{
	uint16_t bcd = (uint16_t)BCDCODE_Convert_UINT8_To_UINT8_BCD(num / 100) << 8;
	return bcd | (uint16_t)BCDCODE_Convert_UINT8_To_UINT8_BCD(num % 100);
}

uint16_t BCDCODE_Convert_UINT16_BCD_To_UINT16(uint16_t bcd)
{
	uint16_t num = (uint16_t)BCDCODE_Convert_UINT8_BCD_To_UINT8(bcd >> 8) * 100;
	return num + (uint16_t)BCDCODE_Convert_UINT8_BCD_To_UINT8(bcd);
}

uint32_t BCDCODE_Convert_UINT32_To_UINT32_BCD(uint32_t num)
{
	uint32_t bcd = (uint32_t)BCDCODE_Convert_UINT16_To_UINT16_BCD(num / 10000) << 16;
	return bcd | BCDCODE_Convert_UINT16_To_UINT16_BCD(num % 10000);
}

uint32_t BCDCODE_Convert_UINT32_BCD_To_UINT32(uint32_t bcd)
{
	uint32_t num = (uint32_t)BCDCODE_Convert_UINT16_BCD_To_UINT16(bcd >> 16) * 10000;
	return num + BCDCODE_Convert_UINT16_BCD_To_UINT16(bcd);
}

uint64_t BCDCODE_Convert_UINT64_To_UINT64_BCD(uint64_t num)
{
	uint64_t bcd = (uint64_t)BCDCODE_Convert_UINT32_To_UINT32_BCD(num / 100000000ULL) << 32;
	return bcd | BCDCODE_Convert_UINT32_To_UINT32_BCD(num % 100000000ULL);
}

uint64_t BCDCODE_Convert_UINT64_BCD_To_UINT64(uint64_t bcd)
{
	uint64_t num = (uint64_t)BCDCODE_Convert_UINT32_BCD_To_UINT32(bcd >> 32) * 100000000ULL;
	return num + BCDCODE_Convert_UINT32_BCD_To_UINT32(bcd);
}
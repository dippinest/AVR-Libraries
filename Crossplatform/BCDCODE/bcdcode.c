
#include "bcdcode.h"

uint8_t BCDCODE_UInt8_To_UInt8BCD(uint8_t num)
{
	return ((num / 10) << 4) | (num % 10);
}

uint8_t BCDCODE_UInt8BCD_To_UInt8(uint8_t bcd_code)
{
	uint8_t num = (bcd_code >> 4) * 10;
	num += (bcd_code & 0x0F);
	return num;
}

uint16_t BCDCODE_UInt16_To_UInt16BCD(uint16_t num)
{
	uint16_t bcd_code = (uint16_t)BCDCODE_UInt8_To_UInt8BCD(num / 100) << 8;
	return bcd_code | (uint16_t)BCDCODE_UInt8_To_UInt8BCD(num % 100);
}

uint16_t BCDCODE_UInt16BCD_To_UInt16(uint16_t bcd_code)
{
	uint16_t num = (uint16_t)BCDCODE_UInt8BCD_To_UInt8(bcd_code >> 8) * 100;
	return num + (uint16_t)BCDCODE_UInt8BCD_To_UInt8(bcd_code);
}

uint32_t BCDCODE_UInt32_To_UInt32BCD(uint32_t num)
{
	uint32_t bcd_code = (uint32_t)BCDCODE_UInt16_To_UInt16BCD(num / 10000) << 16;
	return bcd_code | BCDCODE_UInt16_To_UInt16BCD(num % 10000);
}

uint32_t BCDCODE_UInt32BCD_To_UInt32(uint32_t bcd_code)
{
	uint32_t num = (uint32_t)BCDCODE_UInt16BCD_To_UInt16(bcd_code >> 16) * 10000;
	return num + BCDCODE_UInt16BCD_To_UInt16(bcd_code);
}

uint64_t BCDCODE_UInt64_To_UInt64BCD(uint64_t num)
{
	uint64_t bcd_code = (uint64_t)BCDCODE_UInt32_To_UInt32BCD(num / 100000000ULL) << 32;
	return bcd_code | BCDCODE_UInt32_To_UInt32BCD(num % 100000000ULL);
}

uint64_t BCDCODE_UInt64BCD_To_UInt64(uint64_t bcd_code)
{
	uint64_t num = (uint64_t)BCDCODE_UInt32BCD_To_UInt32(bcd_code >> 32) * 100000000ULL;
	return num + BCDCODE_UInt32BCD_To_UInt32(bcd_code);
}


#include "grayscode.h"

uint8_t GRAYSCODE_UInt8_To_UInt8Grayscode(uint8_t num)
{
	return num ^ (num >> 1);
}

uint8_t GRAYSCODE_UInt8Grayscode_To_UInt8(uint8_t gray_code)
{
	uint8_t n = 0;

	for (; gray_code; gray_code >>= 1)
	{
		n ^= gray_code;
	}

	return n;
}

uint16_t GRAYSCODE_UInt16_To_UInt16Grayscode(uint16_t num)
{
	return num ^ (num >> 1);
}

uint16_t GRAYSCODE_UInt16Grayscode_To_UInt16(uint16_t gray_code)
{
	uint16_t n = 0;

	for (; gray_code; gray_code >>= 1)
	{
		n ^= gray_code;
	}

	return n;
}

uint32_t GRAYSCODE_UInt32_To_UInt32Grayscode(uint32_t num)
{
	return num ^ (num >> 1);
}

uint32_t GRAYSCODE_UInt32Grayscode_To_UInt32(uint32_t gray_code)
{
	uint32_t n = 0;

	for (; gray_code; gray_code >>= 1)
	{
		n ^= gray_code;
	}

	return n;
}

uint64_t GRAYSCODE_UInt64_To_UInt64Grayscode(uint64_t num)
{
	return num ^ (num >> 1);
}

uint64_t GRAYSCODE_UInt64Grayscode_To_UInt64(uint64_t gray_code)
{
	uint64_t n = 0;

	for (; gray_code; gray_code >>= 1)
	{
		n ^= gray_code;
	}

	return n;
}
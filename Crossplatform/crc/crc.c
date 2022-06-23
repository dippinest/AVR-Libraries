
#include "crc.h"

uint8_t CRC8_Get(void *data, uint16_t data_size, uint8_t polynomial, uint8_t initial, bool refin, bool refout, uint8_t xor_out)
{
	register uint8_t i;
	register uint8_t* byte_ptr = (uint8_t*)data;

	while (data_size--)
	{
		initial ^= *byte_ptr;
		++byte_ptr;

		for (i = 0; i < 8; ++i)
		{
			if (refin)
			{
				if (initial & 0x01)
				{
					initial >>= 1;
					initial ^= polynomial;
				}
				else
				{
					initial >>= 1;
				}
			}
			else
			{
				if (initial & 0x80)
				{
					initial <<= 1;
					initial ^= polynomial;
				}
				else
				{
					initial <<= 1;
				}
			}
		}
	}

	if (refout)
	{
		uint16_t crc8_inv = 0;

		for (i = 0; i < 8; ++i)
		{
			crc8_inv <<= 1;
			crc8_inv += initial & 1;
			initial >>= 1;
		}

		initial = crc8_inv;
	}

	return initial ^ xor_out;
}

uint16_t CRC16_Get(void *data, uint16_t data_size, uint16_t polynomial, uint16_t initial, bool refin, bool refout, uint16_t xor_out)
{
	register uint8_t i;
	register uint8_t* byte_ptr = (uint8_t*)data;

	while (data_size--)
	{
		initial ^= *byte_ptr;
		++byte_ptr;

		for (i = 0; i < 8; ++i)
		{
			if (refin)
			{
				if (initial & 0x0001)
				{
					initial >>= 1;
					initial ^= polynomial;
				}
				else
				{
					initial >>= 1;
				}
			}
			else
			{
				if (initial & 0x8000)
				{
					initial <<= 1;
					initial ^= polynomial;
				}
				else
				{
					initial <<= 1;
				}
			}
		}
	}

	if (refout)
	{
		uint16_t crc16_inv = 0;

		for (i = 0; i < 16; ++i)
		{
			crc16_inv <<= 1;
			crc16_inv += initial & 1;
			initial >>= 1;
		}

		initial = crc16_inv;
	}

	return initial ^ xor_out;
}

uint32_t CRC32_Get(void *data, uint16_t data_size, uint32_t polynomial, uint32_t initial, bool refin, bool refout, uint32_t xor_out)
{
	register uint8_t i;
	register uint8_t* byte_ptr = (uint8_t*)data;

	while (data_size--)
	{
		initial ^= *byte_ptr;
		++byte_ptr;

		for (i = 0; i < 8; ++i)
		{
			if (refin)
			{
				if (initial & 0x00000001)
				{
					initial >>= 1;
					initial ^= polynomial;
				}
				else
				{
					initial >>= 1;
				}
			}
			else
			{
				if (initial & 0x80000000)
				{
					initial <<= 1;
					initial ^= polynomial;
				}
				else
				{
					initial <<= 1;
				}
			}
		}
	}

	if (refout)
	{
		uint32_t crc32_inv = 0;

		for (i = 0; i < 32; ++i)
		{
			crc32_inv <<= 1;
			crc32_inv += initial & 1;
			initial >>= 1;
		}

		initial = crc32_inv;
	}

	return initial ^ xor_out;
}

uint64_t CRC64_Get(void* data, uint16_t data_size, uint64_t polynomial, uint64_t initial, bool refin, bool refout, uint64_t xor_out)
{
	register uint8_t i;
	register uint8_t* byte_ptr = (uint8_t*)data;

	while (data_size--)
	{
		initial ^= *byte_ptr;
		++byte_ptr;

		for (i = 0; i < 8; ++i)
		{
			if (refin)
			{
				if (initial & 0x0000000000000001)
				{
					initial >>= 1;
					initial ^= polynomial;
				}
				else
				{
					initial >>= 1;
				}
			}
			else
			{
				if (initial & 0x8000000000000000)
				{
					initial <<= 1;
					initial ^= polynomial;
				}
				else
				{
					initial <<= 1;
				}
			}
		}
	}

	if (refout)
	{
		uint64_t crc64_inv = 0;

		for (i = 0; i < 32; ++i)
		{
			crc64_inv <<= 1;
			crc64_inv += initial & 1;
			initial >>= 1;
		}

		initial = crc64_inv;
	}

	return initial ^ xor_out;
}

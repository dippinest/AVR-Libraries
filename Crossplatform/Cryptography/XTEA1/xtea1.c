#include "xtea1.h"

static uint32_t _rol(uint32_t base, uint8_t shift)
{
	shift &= 0x1F;
	return (base << shift) | (base >> (32 - shift));
}

static void _XTEA1_64bit_Block_Encrypt(void *_64bit_block, const void *key_128bit, uint8_t num_of_rounds)
{
	uint32_t v0 = ((uint32_t*)_64bit_block)[0] + ((uint32_t*)key_128bit)[0];
	uint32_t v1 = ((uint32_t*)_64bit_block)[1] + ((uint32_t*)key_128bit)[1];
	
	uint32_t sum = 0;

	for (uint8_t i = 0; i < num_of_rounds; ++i)
	{
		v0  += ((v1 << 4) ^ (v1 >> 5)) + (v1 ^ sum) + _rol(((uint32_t*)key_128bit)[sum & 3], v1);
		sum += 0x9E3779B9;
		v1  += ((v0 << 4) ^ (v0 >> 5)) + (v0 ^ sum) + _rol(((uint32_t*)key_128bit)[(sum >> 11) & 3], v0);
	}

	((uint32_t*)_64bit_block)[0] = v0 ^ ((uint32_t*)key_128bit)[2];
	((uint32_t*)_64bit_block)[1] = v1 ^ ((uint32_t*)key_128bit)[3];
}

static void _XTEA1_64bit_Block_Decrypt(void *_64bit_block, const void *key_128bit, uint8_t num_of_rounds)
{
	uint32_t v0 = ((uint32_t*)_64bit_block)[1] ^ ((uint32_t*)key_128bit)[3];
	uint32_t v1 = ((uint32_t*)_64bit_block)[0] ^ ((uint32_t*)key_128bit)[2];
	
	uint32_t sum = 0x9E3779B9 * num_of_rounds;

	for (uint8_t i = 0; i < num_of_rounds; ++i)
	{
		v0  -= ((v1 << 4) ^ (v1 >> 5)) + (v1 ^ sum) + _rol(((uint32_t*)key_128bit)[(sum >> 11) & 3], v1);
		sum -= 0x9E3779B9;
		v1  -= ((v0 << 4) ^ (v0 >> 5)) + (v0 ^ sum) + _rol(((uint32_t*)key_128bit)[sum & 3], v0);
	}

	((uint32_t*)_64bit_block)[1] = v0 - ((uint32_t*)key_128bit)[1];
	((uint32_t*)_64bit_block)[0] = v1 - ((uint32_t*)key_128bit)[0];
}

uint32_t XTEA1_Encrypt_ECB(void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds)
{
	uint32_t num_of_encrypted_bytes = 0;

	for (; num_of_encrypted_bytes < data_size; num_of_encrypted_bytes += 8)
	{
		_XTEA1_64bit_Block_Encrypt(data + num_of_encrypted_bytes, key_128bit, num_of_rounds);
	}

	return num_of_encrypted_bytes;
}

uint32_t XTEA1_Decrypt_ECB(void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds)
{
	uint32_t num_of_decrypted_bytes = 0;

	for (; num_of_decrypted_bytes < data_size; num_of_decrypted_bytes += 8)
	{
		_XTEA1_64bit_Block_Decrypt(data + num_of_decrypted_bytes, key_128bit, num_of_rounds);
	}

	return num_of_decrypted_bytes;
}

uint32_t XTEA1_Encrypt_CBC(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds)
{
	uint8_t vector[8];

	for (uint8_t i = 0; i < 8; ++i)
	{
		vector[i] = ((uint8_t*)init_vector_64bit)[i];
	}

	uint32_t num_of_encrypted_bytes = 0;

	for (; num_of_encrypted_bytes < data_size; num_of_encrypted_bytes += 8)
	{
		for (uint8_t i = 0; i < 8; ++i)
		{
			(((uint8_t*)data) + num_of_encrypted_bytes)[i] ^= vector[i];
		}

		_XTEA1_64bit_Block_Encrypt(data + num_of_encrypted_bytes, key_128bit, num_of_rounds);

		for (uint8_t i = 0; i < 8; ++i)
		{
			vector[i] = (((uint8_t*)data) + num_of_encrypted_bytes)[i];
		}
	}

	return num_of_encrypted_bytes;
}

uint32_t XTEA1_Decrypt_CBC(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds)
{
	uint8_t vector_1[8];
	uint8_t vector_2[8];

	uint32_t num_of_decrypted_bytes = 0;

	for (uint8_t i = 0; i < 8; ++i)
	{
		vector_1[i] = ((uint8_t*)init_vector_64bit)[i];
	}

	for (; num_of_decrypted_bytes < data_size; num_of_decrypted_bytes += 8)
	{
		for (uint8_t i = 0; i < 8; ++i)
		{
			vector_2[i] = (((uint8_t*)data) + num_of_decrypted_bytes)[i];
		}

		_XTEA1_64bit_Block_Decrypt(data + num_of_decrypted_bytes, key_128bit, num_of_rounds);

		for (uint8_t i = 0; i < 8; ++i)
		{
			(((uint8_t*)data) + num_of_decrypted_bytes)[i] ^= vector_1[i];

			vector_1[i] ^= vector_2[i];
			vector_2[i] ^= vector_1[i];
			vector_1[i] ^= vector_2[i];
		}
	}

	return num_of_decrypted_bytes;
}

uint32_t XTEA1_Encrypt_PCBC(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds)
{
	uint8_t vector_1[8];
	uint8_t vector_2[8];

	for (uint8_t i = 0; i < 8; ++i)
	{
		vector_1[i] = ((uint8_t*)init_vector_64bit)[i];
	}

	uint32_t num_of_encrypted_bytes = 0;

	for (; num_of_encrypted_bytes < data_size; num_of_encrypted_bytes += 8)
	{
		for (uint8_t i = 0; i < 8; ++i)
		{
			vector_2[i] = (((uint8_t*)data) + num_of_encrypted_bytes)[i];
			(((uint8_t*)data) + num_of_encrypted_bytes)[i] ^= vector_1[i];
		}

		_XTEA1_64bit_Block_Encrypt(data + num_of_encrypted_bytes, key_128bit, num_of_rounds);

		for (uint8_t i = 0; i < 8; ++i)
		{
			vector_1[i] = (((uint8_t*)data) + num_of_encrypted_bytes)[i] ^ vector_2[i];
		}
	}

	return num_of_encrypted_bytes;
}

uint32_t XTEA1_Decrypt_PCBC(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds)
{
	uint8_t vector_1[8];
	uint8_t vector_2[8];

	for (uint8_t i = 0; i < 8; ++i)
	{
		vector_1[i] = ((uint8_t*)init_vector_64bit)[i];
	}

	uint32_t num_of_decrypted_bytes = 0;

	for (; num_of_decrypted_bytes < data_size; num_of_decrypted_bytes += 8)
	{
		for (uint8_t i = 0; i < 8; ++i)
		{
			vector_2[i] = (((uint8_t*)data) + num_of_decrypted_bytes)[i];
		}

		_XTEA1_64bit_Block_Decrypt(data + num_of_decrypted_bytes, key_128bit, num_of_rounds);

		for (uint8_t i = 0; i < 8; ++i)
		{
			(((uint8_t*)data) + num_of_decrypted_bytes)[i] ^= vector_1[i];
			vector_1[i] = (((uint8_t*)data) + num_of_decrypted_bytes)[i] ^ vector_2[i];
		}
	}

	return num_of_decrypted_bytes;
}

uint32_t XTEA1_Encrypt_CFB(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds)
{
	uint8_t vector[8];

	for (uint8_t i = 0; i < 8; ++i)
	{
		vector[i] = ((uint8_t*)init_vector_64bit)[i];
	}

	uint32_t num_of_encrypted_bytes = 0;

	for (; num_of_encrypted_bytes < data_size; num_of_encrypted_bytes += 8)
	{
		_XTEA1_64bit_Block_Encrypt(vector, key_128bit, num_of_rounds);

		for (uint8_t i = 0; i < 8; ++i)
		{
			(((uint8_t*)data) + num_of_encrypted_bytes)[i] ^= vector[i];
			vector[i] = (((uint8_t*)data) + num_of_encrypted_bytes)[i];
		}
	}

	return num_of_encrypted_bytes;
}

uint32_t XTEA1_Decrypt_CFB(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds)
{
	uint8_t vector_1[8];
	uint8_t vector_2[8];

	uint32_t num_of_decrypted_bytes = 0;

	for (uint8_t i = 0; i < 8; ++i)
	{
		vector_1[i] = ((uint8_t*)init_vector_64bit)[i];
	}

	for (; num_of_decrypted_bytes < data_size; num_of_decrypted_bytes += 8)
	{
		for (uint8_t i = 0; i < 8; ++i)
		{
			vector_2[i] = (((uint8_t*)data) + num_of_decrypted_bytes)[i];
		}

		_XTEA1_64bit_Block_Encrypt(vector_1, key_128bit, num_of_rounds);

		for (uint8_t i = 0; i < 8; ++i)
		{
			(((uint8_t*)data) + num_of_decrypted_bytes)[i] ^= vector_1[i];

			vector_1[i] ^= vector_2[i];
			vector_2[i] ^= vector_1[i];
			vector_1[i] ^= vector_2[i];
		}
	}

	return num_of_decrypted_bytes;
}

uint32_t XTEA1_Encrypt_OFB(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds)
{
	uint8_t vector[8];

	for (uint8_t i = 0; i < 8; ++i)
	{
		vector[i] = ((uint8_t*)init_vector_64bit)[i];
	}

	uint32_t num_of_encrypted_bytes = 0;

	for (; num_of_encrypted_bytes < data_size; num_of_encrypted_bytes += 8)
	{
		_XTEA1_64bit_Block_Encrypt(vector, key_128bit, num_of_rounds);

		for (uint8_t i = 0; i < 8; ++i)
		{
			(((uint8_t*)data) + num_of_encrypted_bytes)[i] ^= vector[i];
		}
	}

	return num_of_encrypted_bytes;
}

uint32_t XTEA1_Decrypt_OFB(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds)
{
	return XTEA1_Encrypt_OFB(init_vector_64bit, data, data_size, key_128bit, num_of_rounds);
}
#include "tea.h"

static void _TEA_64bit_Block_Encrypt(void *_64bit_block, const void *key_128bit)
{
	uint32_t v0 = ((uint32_t*)_64bit_block)[0];
	uint32_t v1 = ((uint32_t*)_64bit_block)[1];
	uint32_t sum = 0;

	uint32_t k0 = ((uint32_t*)key_128bit)[0];
	uint32_t k1 = ((uint32_t*)key_128bit)[1];
	uint32_t k2 = ((uint32_t*)key_128bit)[2];
	uint32_t k3 = ((uint32_t*)key_128bit)[3];

	for (uint8_t i = 0; i < 32; ++i)
	{
		sum += 0x9E3779B9;

		v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
		v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
	}

	((uint32_t*)_64bit_block)[0] = v0;
	((uint32_t*)_64bit_block)[1] = v1;
}

static void _TEA_64bit_Block_Decrypt(void *_64bit_block, const void *key_128bit)
{
	uint32_t v0 = ((uint32_t*)_64bit_block)[0];
	uint32_t v1 = ((uint32_t*)_64bit_block)[1];
	uint32_t sum = 0xC6EF3720;

	uint32_t k0 = ((uint32_t*)key_128bit)[0];
	uint32_t k1 = ((uint32_t*)key_128bit)[1];
	uint32_t k2 = ((uint32_t*)key_128bit)[2];
	uint32_t k3 = ((uint32_t*)key_128bit)[3];

	for (uint32_t i = 0; i < 32; ++i)
	{
		v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
		v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);

		sum -= 0x9E3779B9;
	}

	((uint32_t*)_64bit_block)[0] = v0;
	((uint32_t*)_64bit_block)[1] = v1;
}

uint32_t TEA_Encrypt_ECB(void *data, const uint32_t data_size, const void *key_128bit)
{
	uint32_t num_of_encrypted_bytes = 0;

	for (; num_of_encrypted_bytes < data_size; num_of_encrypted_bytes += 8)
	{
		_TEA_64bit_Block_Encrypt(data + num_of_encrypted_bytes, key_128bit);
	}

	return num_of_encrypted_bytes;
}

uint32_t TEA_Decrypt_ECB(void *data, const uint32_t data_size, const void *key_128bit)
{
	uint32_t num_of_decrypted_bytes = 0;

	for (; num_of_decrypted_bytes < data_size; num_of_decrypted_bytes += 8)
	{
		_TEA_64bit_Block_Decrypt(data + num_of_decrypted_bytes, key_128bit);
	}

	return num_of_decrypted_bytes;
}

uint32_t TEA_Encrypt_CBC(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit)
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

		_TEA_64bit_Block_Encrypt(data + num_of_encrypted_bytes, key_128bit);

		for (uint8_t i = 0; i < 8; ++i)
		{
			vector[i] = (((uint8_t*)data) + num_of_encrypted_bytes)[i];
		}
	}

	return num_of_encrypted_bytes;
}

uint32_t TEA_Decrypt_CBC(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit)
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

		_TEA_64bit_Block_Decrypt(data + num_of_decrypted_bytes, key_128bit);

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

uint32_t TEA_Encrypt_PCBC(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit)
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

		_TEA_64bit_Block_Encrypt(data + num_of_encrypted_bytes, key_128bit);

		for (uint8_t i = 0; i < 8; ++i)
		{
			vector_1[i] = (((uint8_t*)data) + num_of_encrypted_bytes)[i] ^ vector_2[i];
		}
	}

	return num_of_encrypted_bytes;
}

uint32_t TEA_Decrypt_PCBC(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit)
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

		_TEA_64bit_Block_Decrypt(data + num_of_decrypted_bytes, key_128bit);

		for (uint8_t i = 0; i < 8; ++i)
		{
			(((uint8_t*)data) + num_of_decrypted_bytes)[i] ^= vector_1[i];
			vector_1[i] = (((uint8_t*)data) + num_of_decrypted_bytes)[i] ^ vector_2[i];
		}
	}

	return num_of_decrypted_bytes;
}

uint32_t TEA_Encrypt_CFB(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit)
{
	uint8_t vector[8];

	for (uint8_t i = 0; i < 8; ++i)
	{
		vector[i] = ((uint8_t*)init_vector_64bit)[i];
	}

	uint32_t num_of_encrypted_bytes = 0;

	for (; num_of_encrypted_bytes < data_size; num_of_encrypted_bytes += 8)
	{
		_TEA_64bit_Block_Encrypt(vector, key_128bit);

		for (uint8_t i = 0; i < 8; ++i)
		{
			(((uint8_t*)data) + num_of_encrypted_bytes)[i] ^= vector[i];
			vector[i] = (((uint8_t*)data) + num_of_encrypted_bytes)[i];
		}
	}

	return num_of_encrypted_bytes;
}

uint32_t TEA_Decrypt_CFB(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit)
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

		_TEA_64bit_Block_Encrypt(vector_1, key_128bit);

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

uint32_t TEA_Encrypt_OFB(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit)
{
	uint8_t vector[8];

	for (uint8_t i = 0; i < 8; ++i)
	{
		vector[i] = ((uint8_t*)init_vector_64bit)[i];
	}

	uint32_t num_of_encrypted_bytes = 0;

	for (; num_of_encrypted_bytes < data_size; num_of_encrypted_bytes += 8)
	{
		_TEA_64bit_Block_Encrypt(vector, key_128bit);

		for (uint8_t i = 0; i < 8; ++i)
		{
			(((uint8_t*)data) + num_of_encrypted_bytes)[i] ^= vector[i];
		}
	}

	return num_of_encrypted_bytes;
}

uint32_t TEA_Decrypt_OFB(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit)
{
	return TEA_Encrypt_OFB(init_vector_64bit, data, data_size, key_128bit);
}
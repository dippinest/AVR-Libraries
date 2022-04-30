#ifndef XTEA1_H_
#define XTEA1_H_

#include <stdint.h>

uint32_t XTEA1_Encrypt_ECB(void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds);

uint32_t XTEA1_Decrypt_ECB(void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds);

uint32_t XTEA1_Encrypt_CBC(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds);

uint32_t XTEA1_Decrypt_CBC(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds);

uint32_t XTEA1_Encrypt_PCBC(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds);

uint32_t XTEA1_Decrypt_PCBC(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds);

uint32_t XTEA1_Encrypt_CFB(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds);

uint32_t XTEA1_Decrypt_CFB(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds);

uint32_t XTEA1_Encrypt_OFB(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds);

uint32_t XTEA1_Decrypt_OFB(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds);

#endif
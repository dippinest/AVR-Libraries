#ifndef TEA_H_
#define TEA_H_

#include <stdint.h>

uint32_t TEA_Encrypt_ECB(void *data, const uint32_t data_size, const void *key_128bit);

uint32_t TEA_Decrypt_ECB(void *data, const uint32_t data_size, const void *key_128bit);

uint32_t TEA_Encrypt_CBC(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit);

uint32_t TEA_Decrypt_CBC(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit);

uint32_t TEA_Encrypt_PCBC(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit);

uint32_t TEA_Decrypt_PCBC(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit);

uint32_t TEA_Encrypt_CFB(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit);

uint32_t TEA_Decrypt_CFB(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit);

uint32_t TEA_Encrypt_OFB(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit);

uint32_t TEA_Decrypt_OFB(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit);

#endif
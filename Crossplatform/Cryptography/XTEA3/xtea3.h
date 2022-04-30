#ifndef XTEA3_H_
#define XTEA3_H_

#include <stdint.h>

uint32_t XTEA3_Encrypt_ECB(void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds);

uint32_t XTEA3_Decrypt_ECB(void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds);

uint32_t XTEA3_Encrypt_CBC(const void *init_vector_128bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds);

uint32_t XTEA3_Decrypt_CBC(const void *init_vector_128bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds);

uint32_t XTEA3_Encrypt_PCBC(const void *init_vector_128bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds);

uint32_t XTEA3_Decrypt_PCBC(const void *init_vector_128bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds);

uint32_t XTEA3_Encrypt_CFB(const void *init_vector_128bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds);

uint32_t XTEA3_Decrypt_CFB(const void *init_vector_128bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds);

uint32_t XTEA3_Encrypt_OFB(const void *init_vector_128bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds);

uint32_t XTEA3_Decrypt_OFB(const void *init_vector_128bit, void *data, const uint32_t data_size, const void *key_128bit, uint8_t num_of_rounds);

#endif
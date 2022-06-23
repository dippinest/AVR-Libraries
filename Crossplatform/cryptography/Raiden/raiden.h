#ifndef RAIDEN_H_
#define RAIDEN_H_

#include <stdint.h>

uint32_t RAIDEN_Encrypt_ECB(void *data, const uint32_t data_size, const void *key_128bit);

uint32_t RAIDEN_Decrypt_ECB(void *data, const uint32_t data_size, const void *key_128bit);

uint32_t RAIDEN_Encrypt_CBC(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit);

uint32_t RAIDEN_Decrypt_CBC(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit);

uint32_t RAIDEN_Encrypt_PCBC(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit);

uint32_t RAIDEN_Decrypt_PCBC(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit);

uint32_t RAIDEN_Encrypt_CFB(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit);

uint32_t RAIDEN_Decrypt_CFB(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit);

uint32_t RAIDEN_Encrypt_OFB(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit);

uint32_t RAIDEN_Decrypt_OFB(const void *init_vector_64bit, void *data, const uint32_t data_size, const void *key_128bit);

#endif /* RAIDEN_H_ */
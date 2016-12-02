#include <stdint.h>

void encrypt(const uint8_t* key, const uint8_t* plaintext, uint8_t *ciphertext);
void decrypt(const uint8_t* key, const uint8_t* ciphertext, uint8_t *plaintext);

// aes aes baby
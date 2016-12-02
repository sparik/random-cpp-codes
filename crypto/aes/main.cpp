#include <stdio.h>
#include <string.h>
#include "aes.h"

char* lastError;

void setLastError(const char* errmsg) {
	lastError = strdup(errmsg);
}

char* getLastError() {
	return lastError;
}

int readKey(uint8_t* key) {
	printf("Input the 16-byte key as hexadecimal string: ");

	for (int i = 0; i < 16; ++i) {
		key[i] = 0;
	}

	char buf[32];

	scanf(" %s", buf);

	int buflen = strlen(buf);

	for (int i = 0; i < buflen; ++i) {
		bool dig = false, af = false;
		dig = (buf[i] >= '0' && buf[i] <= '9');
		af = (buf[i] >= 'a' && buf[i] <= 'f');
		if (!(dig || af)) {
			setLastError("invalid key");
			return 1;
		}

		uint8_t val;
		if (dig) {
			val = (uint8_t)(buf[i] - '0');
			if (i % 2 == 0) {
				val <<= 4;
			}
		}
		else {
			val = (uint8_t)(buf[i] - 'a') + 10;
			if (i % 2 == 0) {
				val <<= 4;
			}
		}

		key[i >> 1] += val;
	}

	return 0;
}

int readPlaintext(uint8_t* plaintext) {
	printf("Input the 16-byte plaintext as hexadecimal string: ");

	for (int i = 0; i < 16; ++i) {
		plaintext[i] = 0;
	}

	char buf[32];

	scanf(" %s", buf);

	int buflen = strlen(buf);

	for (int i = 0; i < buflen; ++i) {
		bool dig = false, af = false;
		dig = (buf[i] >= '0' && buf[i] <= '9');
		af = (buf[i] >= 'a' && buf[i] <= 'f');
		if (!(dig || af)) {
			setLastError("invalid plaintext");
			return 1;
		}

		uint8_t val;
		if (dig) {
			val = (uint8_t)(buf[i] - '0');
			if (i % 2 == 0) {
				val <<= 4;
			}
		}
		else {
			val = (uint8_t)(buf[i] - 'a') + 10;
			if (i % 2 == 0) {
				val <<= 4;
			}
		}

		plaintext[i >> 1] += val;
	}

	return 0;
}

int readCiphertext(uint8_t* ciphertext) {
	printf("Input the 16-byte ciphertext as hexadecimal string: ");

	for (int i = 0; i < 16; ++i) {
		ciphertext[i] = 0;
	}

	char buf[32];

	scanf(" %s", buf);

	int buflen = strlen(buf);

	for (int i = 0; i < buflen; ++i) {
		bool dig = false, af = false;
		dig = (buf[i] >= '0' && buf[i] <= '9');
		af = (buf[i] >= 'a' && buf[i] <= 'f');
		if (!(dig || af)) {
			setLastError("invalid ciphertext");
			return 1;
		}

		uint8_t val;
		if (dig) {
			val = (uint8_t)(buf[i] - '0');
			if (i % 2 == 0) {
				val <<= 4;
			}
		}
		else {
			val = (uint8_t)(buf[i] - 'a') + 10;
			if (i % 2 == 0) {
				val <<= 4;
			}
		}

		ciphertext[i >> 1] += val;
	}

	return 0;
}




int main() {

	int eord;

	printf("If you want to encrypt, insert 1, otherwise insert 0: ");

	scanf("%d", &eord);

	if (eord == 1) {
		// encryption example
		uint8_t key[16];
		uint8_t plaintext[16];
		uint8_t ciphertext[16];

		if (readKey(key)) {
			printf("%s", getLastError());
			return 0;
		}

		if (readPlaintext(plaintext)) {
			printf("%s", getLastError());
			return 0;
		}

		encrypt(key, plaintext, ciphertext);

		printf("Result ciphertext: ");
		for (int i = 0; i < 16; ++i) {
			printf("%hx", ciphertext[i]);
		}
		printf("\n");
	}
	else {
		// decryption example
		uint8_t key[16];
		uint8_t plaintext[16];
		uint8_t ciphertext[16];

		if (readKey(key)) {
			printf("%s", getLastError());
			return 0;
		}

		if (readCiphertext(ciphertext)) {
			printf("%s", getLastError());
			return 0;
		}

		decrypt(key, ciphertext, plaintext);

		printf("Result plaintext: ");
		for (int i = 0; i < 16; ++i) {
			printf("%hx", plaintext[i]);
		}
		printf("\n");
	}
	
	return 0;
}

/*

key = a7bc3bd0eabd9eba981e23e6ffc9c9c2
plaintext = 877b88a77aef04f05546539e17259f53
ciphertext = 3f373962401b81dac563e98d37713f9c


*/
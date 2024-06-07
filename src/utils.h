#ifndef UTILS_H
#define UTILS_H

char* base64_encode(const char *input);

char* base64_decode(const char* input);

char* hex_encode(const char *input);

char* hex_decode(const char* input);

char* base64_to_hex(const char *base64_string);

char* hex_to_base64(const char *hex_string);

char* xor_bit_a_bit(const char* str, const char* key);

void xorHexStrings(const char *plainText, const char *key, char *cypherText);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int base64_char_index(char c) {
    if (c >= 'A' && c <= 'Z')
        return c - 'A';
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 26;
    if (c >= '0' && c <= '9')
        return c - '0' + 52;
    if (c == '+')
        return 62;
    if (c == '/')
        return 63;
    return -1;
}

char* base64_encode(const char *input) {
    const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    char *output, *p;
    int i, remainder, enc_len;

    int length = strlen(input);

    remainder = length % 3;
    enc_len = (length / 3) * 4 + (remainder ? 4 : 0);

    output = (char *)malloc(enc_len + 1);
    if (!output) return NULL;

    p = output;

    for (i = 0; i < length - 2; i += 3) {
        *p++ = base64_chars[input[i] >> 2];
        *p++ = base64_chars[((input[i] & 0x03) << 4) | (input[i + 1] >> 4)];
        *p++ = base64_chars[((input[i + 1] & 0x0f) << 2) | (input[i + 2] >> 6)];
        *p++ = base64_chars[input[i + 2] & 0x3f];
    }

    if (remainder == 1) {
        *p++ = base64_chars[input[i] >> 2];
        *p++ = base64_chars[(input[i] & 0x03) << 4];
        *p++ = '=';
        *p++ = '=';
    } else if (remainder == 2) {
        *p++ = base64_chars[input[i] >> 2];
        *p++ = base64_chars[((input[i] & 0x03) << 4) | (input[i + 1] >> 4)];
        *p++ = base64_chars[(input[i + 1] & 0x0f) << 2];
        *p++ = '=';
    }

    *p = '\0';
    return output;
}

char* base64_decode(const char* input) {
    int input_length = strlen(input);
    int output_length = (input_length / 4) * 3;
    
    char *output = (char *)malloc(output_length + 1);
    
    if (input[input_length - 1] == '=') output_length--;
    if (input[input_length - 2] == '=') output_length--;

    int i, j;
    for (i = 0, j = 0; i < input_length;) {
        int sextet_a = input[i] == '=' ? 0 & i++ : base64_char_index(input[i++]);
        int sextet_b = input[i] == '=' ? 0 & i++ : base64_char_index(input[i++]);
        int sextet_c = input[i] == '=' ? 0 & i++ : base64_char_index(input[i++]);
        int sextet_d = input[i] == '=' ? 0 & i++ : base64_char_index(input[i++]);

        int triple = (sextet_a << 3 * 6) + (sextet_b << 2 * 6) + (sextet_c << 1 * 6) + (sextet_d << 0 * 6);

        if (j < output_length) output[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < output_length) output[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < output_length) output[j++] = (triple >> 0 * 8) & 0xFF;
    }
    output[output_length] = '\0';
    return output;
}

char* hex_encode(const char *input) {
    int length = strlen(input);
    char *output, *p;
    int i;

    output = (char *)malloc(length * 2 + 1);
    if (!output) return NULL;

    p = output;

    for (i = 0; i < length; ++i) {
        sprintf(p, "%02x", input[i]);
        p += 2;
    }

    *p = '\0';
    return output;
}

char* hex_decode(const char* input) {
    int length = strlen(input);

    if (length % 2 != 0) {
        printf("Erro: A entrada hex deve ter um número par de caracteres.\n");
        return NULL;
    }

    int output_length = length / 2;

    char *output = (char *)malloc(output_length);
    if (!output) return NULL;

    for (int i = 0; i < length; i += 2) {
        sscanf(input + i, "%2hhx", &output[i / 2]);
    }

    return output;
}

char* base64_to_hex(const char *base64_string) {
    char* decoded_bytes = base64_decode(base64_string);

    if (!decoded_bytes) {
        printf("Erro ao decodificar a string Base64.\n");
        return NULL;
    }

    printf("Decoded: %s\n", decoded_bytes);

    char *hex_string = hex_encode(decoded_bytes);

    free(decoded_bytes);
    return hex_string;
}

char* hex_to_base64(const char *hex_string) {
    char* decoded_bytes = hex_decode(hex_string);

    if (!decoded_bytes) {
        printf("Erro ao decodificar a string Base64.\n");
        return NULL;
    }

    printf("Decoded: %s\n", decoded_bytes);

    char *base64_string = base64_encode(decoded_bytes);

    free(decoded_bytes);
    return base64_string;
}

char* xor_bit_a_bit(const char* str, const char* key) {
    size_t len_str = strlen(str);
    size_t len_key = strlen(key);

    if (len_str != len_key)
    {
        printf("Erro! Entrada e Chave de tamanhos diferentes.");
        return NULL;
    }

    char* result = malloc(sizeof(char) * len_str +1);

    char* hex_str = hex_encode(str);
    char* hex_key = hex_encode(key);

    for (size_t i = 0; i < strlen(hex_str); i++)
    {
        result[i] = (hex_str[i] ^ hex_key[i]);
        printf("%x XOR %x = %c\n", hex_str[i], hex_key[i], result[i]);
    }

    result[len_str] = '\0';

    char* final_result = hex_decode(result);

    return final_result;
}

// Função para converter uma string hexadecimal para um array de bytes
void hexStringToByteArray(const char *hexString, unsigned char *byteArray) {
    size_t len = strlen(hexString);
    for (size_t i = 0; i < len; i += 2) {
        sscanf(hexString + i, "%2hhx", &byteArray[i / 2]);
    }
}

// Função para converter um array de bytes para uma string hexadecimal
void byteArrayToHexString(const unsigned char *byteArray, size_t len, char *hexString) {
    for (size_t i = 0; i < len; i++) {
        sprintf(hexString + (i * 2), "%02X", byteArray[i]);
    }
}

// Função para aplicar XOR em duas strings hexadecimais de mesmo tamanho
void xorHexStrings(const char *plainText, const char *key, char *cypherText) {
    size_t len = strlen(plainText) / 2;
    unsigned char *plainTextBytes = (unsigned char *)malloc(len);
    unsigned char *keyBytes = (unsigned char *)malloc(len);
    unsigned char *cypherTextBytes = (unsigned char *)malloc(len);

    if (plainTextBytes == NULL || keyBytes == NULL || cypherTextBytes == NULL) {
        fprintf(stderr, "Falha na alocação de memória\n");
        return;
    }

    // Converte as strings hexadecimais para arrays de bytes
    hexStringToByteArray(plainText, plainTextBytes);
    hexStringToByteArray(key, keyBytes);

    // Aplica XOR byte a byte
    for (size_t i = 0; i < len; i++) {
        cypherTextBytes[i] = plainTextBytes[i] ^ keyBytes[i];
    }

    // Converte o resultado de volta para uma string hexadecimal
    byteArrayToHexString(cypherTextBytes, len, cypherText);

    // Libera a memória alocada
    free(plainTextBytes);
    free(keyBytes);
    free(cypherTextBytes);
}

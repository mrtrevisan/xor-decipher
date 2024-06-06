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

char* base64_encode(const char *input, int length) {
    const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    char *output, *p;
    int i, remainder, enc_len;

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


char* base64_decode(const char* input, int length, int* output_length) {
    char *output, *p;
    int i, j;

    *output_length = (length / 4) * 3;

    if (input[length - 1] == '=') (*output_length)--;
    if (input[length - 2] == '=') (*output_length)--;

    output = (char *)malloc(*output_length + 1);
    if (!output) return NULL;

    p = output;

    for (i = 0; i < length; i += 4) {
        int sextet_a = (input[i] == '=') ? 0 & i++ : base64_char_index(input[i]);
        int sextet_b = (input[i + 1] == '=') ? 0 & i++ : base64_char_index(input[i + 1]);
        int sextet_c = (input[i + 2] == '=') ? 0 & i++ : base64_char_index(input[i + 2]);
        int sextet_d = (input[i + 3] == '=') ? 0 & i++ : base64_char_index(input[i + 3]);

        int triple = (sextet_a << 18) + (sextet_b << 12) + (sextet_c << 6) + (sextet_d);

        for (j = 0; j < 3; j++) {
            if (p < output + *output_length) *p++ = (triple >> (8 * (2 - j))) & 0xFF;
        }
    }

    *p = '\0';

    return output;
}

char* hex_encode(const char *input, int length) {
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

char* hex_decode(const char* input, int length, int* output_length) {
    if (length % 2 != 0) {
        printf("Erro: A entrada hex deve ter um número par de caracteres.\n");
        return NULL;
    }

    *output_length = length / 2;

    char *output = (char *)malloc(*output_length);
    if (!output) return NULL;

    for (int i = 0; i < length; i += 2) {
        sscanf(input + i, "%2hhx", &output[i / 2]);
    }

    return output;
}

char* base64_to_hex(const char *base64_string) {
    int decoded_length;
    char *decoded_bytes = base64_decode(base64_string, strlen(base64_string), &decoded_length);

    if (!decoded_bytes) {
        printf("Erro ao decodificar a string Base64.\n");
        return NULL;
    }

    char *hex_string = hex_encode(decoded_bytes, decoded_length);

    free(decoded_bytes);
    return hex_string;
}

char* hex_to_base64(const char *hex_string) {
    int decoded_length;
    char *decoded_bytes = hex_decode(hex_string, strlen(hex_string), &decoded_length);

    if (!decoded_bytes) {
        printf("Erro ao decodificar a string Base64.\n");
        return NULL;
    }

    char *base64_string = base64_encode(decoded_bytes, decoded_length);

    free(decoded_bytes);
    return base64_string;
}
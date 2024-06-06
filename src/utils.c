#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


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

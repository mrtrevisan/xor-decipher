#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int main() {
    const char* str = "HELLO WORLD";

    char* base64_encoded_string = base64_encode(str, strlen(str));

    char* hex_encoded_string = hex_encode(str, strlen(str));

    printf("Original: %s\n", str);
    printf("Base64: %s\n", base64_encoded_string);
    printf("Hexadecimal: %s\n", hex_encoded_string);

    free(base64_encoded_string);
    free(hex_encoded_string);
    
    return 0;
}

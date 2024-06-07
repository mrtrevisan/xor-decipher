#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void string_convert(int mode) {
    if (mode == 1)
    {
        const char *base64_string = "QWNvcmRhUGVkcmluaG9RdWVob2pldGVtY2FtcGVvbmF0bw=="; 
        char *hex_string = base64_to_hex(base64_string);

        if (hex_string) {
            printf("Base64: %s\n", base64_string);
            printf("Hexadecimal: %s\n", hex_string);
            free(hex_string);
        }
    } 
    else 
    {
        const char* hex_string = "41636f72646150656472696e686f517565686f6a6574656d63616d70656f6e61746f";        
        char* base64_string = hex_to_base64(hex_string);

        if (base64_string) {
            printf("Hexadecimal: %s\n", hex_string);
            printf("Base64: %s\n", base64_string);
            free(base64_string);
        }
    }

    return;
}

int main() {
    char* str = "41636f72646150656472696e686f517565686f6a6574656d63616d70656f6e61746f";
    char* key = "0b021e0701003e0a0d060c0807063d1a0b0f0e060a1a020c0f0e03170403010f130e";
    char* res = malloc(strlen(str) * sizeof(char));
    
    xorHexStrings(str, key, res);
    //4a61717565616e6f697465666f696c6f6e67616c6f6e67616c6f6e67616c6f6e6761
    //4A61717565616E6F697465666F696C6F6E67616C6F6E67616C6F6E67616C6F6E6761

    if (res) {
        printf("Ciphertext: %s", res);
        printf("\n");
    }
}

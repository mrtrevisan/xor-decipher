#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int main() {
    const char *base64_string = "QWNvcmRhUGVkcmluaG9RdWVob2pldGVtY2FtcGVvbmF0bw=="; 
    // const char* hex_string = "41636f72646150656472696e686f517565686f6a6574656d63616d70656f6e61746f";
    
    char *hex_string = base64_to_hex(base64_string);
    // char* base64_string = hex_to_base64(hex_string);

    if (hex_string) {
        printf("Hexadecimal: %s\n", hex_string);
        printf("Base64: %s\n", base64_string);

        free(hex_string);
    }

    return 0;
}

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



void createArray(char* array, char c, int size){
    for(int i=0; i<size; i++){
        array[i] = c;
    }
    array[size] ='\0';
}

char** createKeys(int size){
    char** keys = (char**)malloc(26 * sizeof(char*));

    for(int i = 0; i < 26; i++ )
    {
        keys[i] = (char*)malloc(size * sizeof(char) + 1);
        createArray(keys[i], (char)(i+'A'), size);
    }

    return keys;
}

//digraph
int analyzeRawText(char* rawText){
    int len = strlen(rawText);
    int count = 0;

    char* vowels = "AEIOUaeiou";
    char* consonants = "BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz";

    for(int i=0; i < len-1; i++){
        if(strchr(consonants, rawText[i]) != NULL && strchr(vowels, rawText[i+1]) != NULL){
            count++;
        }
    }
    return count;
}

void decipher(char* cipherText) {
    int len = strlen(cipherText);
    
    char** keys = createKeys(len);

    char* bestRawText = (char*)malloc(len * sizeof(char) + 1);
    char bestKey = 'a';
    int bestCount = -1;

    for(int i=0; i<26; i++){
        char* key = hex_encode(keys[i]);
        char* res = xorHexStrings(cipherText, key);
        
        if (res) {
            char* rawText = hex_decode(res);
            int count = analyzeRawText(rawText);

            if (count > bestCount) {
                bestCount = count;
                strcpy(bestRawText, rawText);
                bestKey = keys[i][0];
            }

            free(rawText);
            free(res);
            free(key);
        }
    }

    for(int i = 0; i < 26; i++){
        free(keys[i]);
    }
    free(keys);

    if (bestRawText) {
        printf("Key: %c\n", bestKey);
        printf("Raw Text: %s\n", bestRawText);
        free(bestRawText);
    }
}



int main() {
    string_convert(1);

    string_convert(2);
    char* str = "41636f72646150656472696e686f517565686f6a6574656d63616d70656f6e61746f";
    char* key = "0b021e0701003e0a0d060c0807063d1a0b0f0e060a1a020c0f0e03170403010f130e";
    char* res = xorHexStrings(str, key);

    if (res) {
        printf("Ciphertext: %s", res);
        free(res);
        printf("\n");
    }

    char *cipherText = "072c232c223d2c3e3e2c2328232538202e2c3f3f223d223f2c3c3824072c232c223d2c3e3e2c2328232538202b24212028232c191b1b222e283c382828233f22212c2238393f222e242a2c3f3f223d223f2c2408232c22292c2f22212c3d3f223c38283b2c242c2e222339282e283f002c243e38203d22382e2228202c243e38203e282e38212239283f2024232c002c3e38202122382e223d222928393f222e22232c283e3c3824232c19382922243e3e22272c2b2c373d2c3f3928292c3f223924232c082c3f223924232c272c2b2c373d2c3f392829283b222e281c3828392820242928242c3e392c22202229283f232c3e082220283e202225222028203c38283b243b242c232c3e2e2c3b283f232c3e";
    decipher(cipherText);

    return 0;
}

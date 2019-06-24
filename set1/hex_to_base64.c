#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/*
    Convert a hex string to a base64 string
    A pair of hex characters contains 8 bits (00-FF)
    base64 characters are made up of 6 bits (2^6 = 64, hence base64)

    Hex to binary
    49 27 6d
    0100 1001 | 0010 0111 | 0110 1101

    binary to base64
    010010 | 010010 | 011101 | 101101
    18 (S)   18 (S)   29 (d)    45(t)

    49 27 6d => SSdt

    the bit strings are the exact same, the only difference is that they are divided up differently
    hex characters are divided every 8 bits, base64 characters are divided every 6 bits

    I will go about this by converting every 3 hex digit into two base64 digits
    492 => SS
    76d => dt
    ....
    If the hex string is not divisible by 3, I will pad with '='

    4927
    010010 010010  011100

 */

char getBase64Char(int num){
    if(num < 26) {
        return num+65;
    }
    else if(num > 25 && num < 52){
        return num+71;
    }
    else if(num > 51 && num < 62){
        return num-4;
    }
    return '=';
}

char *getBase64String(int num1, int num2){
    int char1 = getBase64Char(num1);
    int char2 = getBase64Char(num2);
    char *temp = (char *) malloc(2);
    temp[0] = char1;
    temp[1] = char2;
    return temp;
}

int binaryToInt(char *binary){
    int i;
    int temp = 0;
    for(i = strlen(binary)-1; i >= 0; i--){
        if(binary[i] == '1'){
            temp += (int) pow(2.0, (double) (strlen(binary) -i -1));
        }
    }
    return temp;
}   

char *padWithZero(char *str){
    const char *zero = "0";
    int i;
    int len = 12-strlen(str);
    for(i = 0; i < len; i++){
        strcat(str, zero);
    }
    return str;
}

char *toBase64(char *binary) {
    int padded = 0;
    char *bin = (char *) malloc(12);
    if(strlen(binary) < 6){
        bin = padWithZero(binary);
        padded = 1;
    }
    else{
        bin = binary;
    }
    char *substr1 = (char *) malloc(6);
    int i;
    for(i = 6; i < strlen(bin); i++){
        substr1[i-6]=bin[i];
    }
    int num1 = binaryToInt(substr1);

    char *substr2 = (char *) malloc(6);
    for(i = 0; i < 6; i++){
        substr2[i]=bin[i];
    }
    int num2 = binaryToInt(substr2);

    if(padded){
        return getBase64String(num1, 63);
    }
    return getBase64String(num2, num1);
}

char *hexToBinary(char *hex) {
    char bitString[13];
    int i;
    for(i = 0; i < 3; i++){
        switch (hex[i]) {
        case '0':
            strcat(bitString, "0000");
            break;
        case '1':
            strcat(bitString, "0001");
            break;
        case '2':
            strcat(bitString, "0010");
            break;
        case '3':
            strcat(bitString, "0011");
            break;
        case '4':
            strcat(bitString, "0100");
            break;
        case '5':
            strcat(bitString, "0101");
            break;
        case '6':
            strcat(bitString, "0110");
            break;
        case '7':
            strcat(bitString, "0111");
            break;
        case '8':
            strcat(bitString, "1000");
            break;
        case '9':
            strcat(bitString, "1001");
            break;
        case 'a':
        case 'A':
            strcat(bitString, "1010");
            break;
        case 'b':
        case 'B':
            strcat(bitString, "1011");
            break;
        case 'c':
        case 'C':
            strcat(bitString, "1100");
            break;
        case 'd': 
        case 'D':
            strcat(bitString, "1101");
            break;
        case 'e':
        case 'E':
            strcat(bitString, "1110");
            break;
        case 'f':
        case 'F':
            strcat(bitString, "1111");
            break;
        };
    }
    return (char *) toBase64(bitString);
}

char *init(char *hex){
    if(strlen(hex) < 1){
        return "Please enter a valid string\n";
    }
    const char *equals = "=";
    int len = strlen(hex);
    int i = 0;
    int offset = 0;
    char *str = (char *) malloc(3);
    char *temp = (char *) malloc(len);
    while(len - offset > 0){
        str = (char *) malloc(3);
        strncpy(str, hex + offset, 3);
        char *bin = hexToBinary(str);
        strcat(temp, bin);
        offset+=3;
    }
    while(strlen(temp) % 4 != 0) {
        strcat(temp, equals);
    }
    return temp;
}

int main(int argc, char **argv){
    if(argc < 2){
        printf("\n****************************\n");
        printf("Usage: ./hex_to_base64 <-t | hex>\n");
        printf("******************************\n\n");
        exit(0);
    }

    if(!strcmp(argv[1], "-d")){
        printf("%s\n", init("4927"));
        exit(0);
    }

    if(!strcmp(argv[1], "-t")){
        //tests
        char *out = NULL;

        printf("Test 1: running...\n");
        out = init("");
        assert(strcmp(out, "Please enter a valid string\n") == 0);
        printf("Test 1: Passed\n\n");

        printf("Test 2: running...\n");
        out = init("00");
        assert(strcmp(out, "AA==") == 0);
        printf("Test 2: Passed\n\n");

        printf("Test 3: running...\n");
        out = init("0000");
        assert(strcmp(out, "AAA=") == 0);
        printf("Test 3: Passed\n\n");

        printf("Test 4: running...\n");
        out = init("666f6f626172");
        assert(strcmp(out, "Zm9vYmFy") == 0);
        printf("Test 4: Passed\n\n");

        printf("Test 5: running...\n");
        out = init("666f6f");
        assert(strcmp(out, "Zm9v") == 0);
        printf("Test 5: Passed\n\n");

        printf("Test 6: running...\n");
        out = init("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d");
        assert(strcmp(out, "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t") == 0);
        printf("Test 6: Passed\n\n");

        exit(0);
    }
    char *hex = argv[1];
    printf("%s\n", init(hex));
}

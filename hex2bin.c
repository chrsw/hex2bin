// hex2bin  convert 2 digit hex number to 8 digit binary number
//
// Two digit hex number is passed on command line, hex2bin prints 8 
// digit binary representation of the input to standard output.
//
// Example run:
// $ ./hex2bin hh
// bbbbbbbb
//
// Building:
// $ gcc -o hex2bin hex2bin.c
// $ gcc -DDEBUG -o hex2bin hex2bin.c
// - or -
// $ make hex2bin
// $ make test
//
// Use 'make help' for help menu.
//
///////////////////////////////////////////////////////////////////////////// 

// TODO:
// Find better ways of cleaning lint warnings, .e.g. no casting.
// Implement better error handling.
// What to do on bad input?
//
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static unsigned char htoi(char *s);
static void dec2bin(unsigned char c, unsigned char bin[]);
static void str2upper(char *s);

// hex2bin:  convert a 2 digit hex string into an 8 digit binary string
int main(int argc, char *argv[]) {

    unsigned char res;
    unsigned char bin[9];
    size_t len = 0;
    char hex[8];
    char *pin = NULL;

    if (argc != 2) exit(EXIT_FAILURE);

    len = strlen(argv[1]);
        pin = argv[1];
    if ((len > 4) || (len < 2)) exit(EXIT_FAILURE);
    if (len == 4) pin += 2;

    strncpy(hex, pin, 2);
    str2upper(hex);
    memset(bin, 0, 9);
    res = htoi(hex);
#if DEBUG
    printf("main: \tfirst char: %c\n", argv[1][0]);
    printf("main: \tfirst char: %c\n", hex);
    printf("main: \tinput = %u\n", (unsigned int)res);
#endif
    dec2bin(res, bin);
    printf("%s\n", (char *)bin);
    return(EXIT_SUCCESS);
}


// htoi:  convert a 2 digit hex string of capital letters to 8-bit positive
//        integer
static unsigned char htoi(char *s) {

    char i = (char)EOF;

    // convert low nibble
    if ((s[1] >= 'A') && (s[1] <= 'F'))
        i = s[1] - (char)55;
    else if ((s[1] >= '0') && s[1] <= '9')
        i = s[1] - (char)48;
    else {
        return (unsigned char)i;
    }

    // convert high nibble
    if ((s[0] >= 'A') && (s[0] <= 'F'))
        i = i + ((s[0] - (char)55) * (char)16);
    else if ((char)toupper(s[0]) >= '0' && (char)toupper(s[0]) <= '9')
        i = i + ((s[0] - (char)48) * (char)16);
    else {
        return (unsigned char)i;
    }

    return (unsigned char)i;
}


// dec2bin:  convert an unsigned integer to string of binary digits
static void dec2bin(unsigned char c, unsigned char bin[]) {

    int i = 0;
    unsigned char lc = c;
#ifdef DEBUG
    printf("dec2bin: c = %d\n", c);
#endif
    for (i = 7; i >= 0; i--)  {
        if ((lc % 2) == (unsigned char)0)
            bin[i] = '0';
        else
            bin[i] = '1';
        lc >>= 1;
#if DEBUG
        printf("dec2bin: bin[%d] = %d, lc = %u\n", i, bin[i], lc);
#endif
    }
    bin[8] = '\0';
}


// str2upper: convert a string to upper case
static void str2upper(char *s) {

    int i = 0;
    while (*s != '\0') {
        *s = toupper(*s);
        s++;
        i++;
    }
#if DEBUG
    printf("str2upper: %d\n", i);
#endif
}

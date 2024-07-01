// hex2bin  convert 2 digit hex number to 8 digit binary number
//
// Two digit hex number is to be passed on command line, program returns 8 
// digit binary representation of the input word onto standard output
//
// $ ./hex2bin hh
// bbbbbbbb
//
// $ gcc -o hex2bin hex2bin.c
// $ gcc -DDEBUG -o hex2bin hex2bin.c
// $ make hex2bin
// $ make test
//
///////////////////////////////////////////////////////////////////////////// 

// TODO:
// Accept 0xHH, 0xhh, HH or hh
// Accept xxh or xxH
// Split functions to separate files
// Find better ways of cleaning lint warings, .e.g. no casting.
//
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned char htoi(char *s);
static void dec2bin(unsigned char c, unsigned char bin[]);


int main(int argc, char *argv[]) {

	unsigned char ucRes;
	unsigned char bin[9];

	if (argc != 2) exit(EXIT_SUCCESS);

	memset(bin, 0, 9);
	ucRes = htoi(argv[1]);
#if DEBUG
	printf("main: \tfirst char: %c\n", argv[1][0]);
	printf("main: \tinput = %u\n", (unsigned int)ucRes);
#endif
	dec2bin(ucRes, bin);
	printf("%s\n", (char *)bin);
	return(EXIT_SUCCESS);
}


// htoi:  convert a 2 digit hex string of capital letters to a positive integer
static unsigned char htoi(char *s) {
	unsigned int i;

	// convert low nibble
	if ((s[1] >= 'A') && (s[1] <= 'F'))
		i = (unsigned int)s[1] - 55;
	else if ((s[1] >= '0') && (s[1] <= '9'))
		i = (unsigned int)s[1] - 48;
	else {
		return (unsigned char)0;
	}

	// convert high nibble
	if (s[0] >= 'A' && s[0] <= 'F')
		i = i + (((unsigned int)s[0] - 55) * 16);
	else if (s[0] >= '0' && s[0] <= '9')
		i = i + (((unsigned int)s[0] - 48) * 16);
	else {
		return (unsigned char)0;
	}

	return (unsigned char)i;
}


// dec2bin:  convert an unsigned integer to string of binary digits
static void dec2bin(unsigned char c, unsigned char bin[]) {

	int i = 0;
	unsigned char lc = c;
	//printf("dec2bin: c = %d\n", c);
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

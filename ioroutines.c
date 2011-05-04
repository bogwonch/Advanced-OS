#include "ioroutines.h"
#include <stdio.h>

void print_string(unsigned char *str)
{
	printf("%s", str);
}
void print_dec(int n)
{
	printf("%d\n", n);
}

void print_hex(unsigned int n)
{
	printf("0x%08X\n", n);
}
void print_char(unsigned char c)
{
	putchar(c);
}

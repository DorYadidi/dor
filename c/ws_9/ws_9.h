#include <stdio.h>
#include <stdlib.h> /*__WORDSIZE*/
#include <string.h> 


void *Memcpy(void *dest, const void *src, size_t n);

void *Memmove(void *dest, const void *src, size_t n);

void *Memset(void *str, int c, size_t n);

int IsLittleEndian();

char *Itoa36(int value, char *str, int base);

int Atoi36(const char *str,int base);

void OnlyTwice(char *a, int a_size, char *b, int b_size, char *c, int c_size);

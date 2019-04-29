#include "ws_9.h"
#include <stdio.h>
#include <stdlib.h> /*__WORDSIZE*/
#include <string.h> /*strlen*/


#define BITINBYTE 8
#define WORDSIZE ( __WORDSIZE / BITINBYTE )
#define ASCII0 48
#define ASCIIA 65
#define ASCII_TABLE 256

#define LE (*(short*)"a" < 256)

void reverse(char str[], int len);
/******************************************************************************
 * A utility function to reverse a string                                     *
 ******************************************************************************/



void *Memset(void *str, int c, size_t n)
{
    int i = 0;
    unsigned char *tmp_str = str;
    char *word_size = (char *)malloc(sizeof(char)*WORDSIZE);

    for(i=0; i < WORDSIZE; ++i)
    {
       word_size[i] = c;
    }

    while((*(size_t *)&tmp_str % WORDSIZE) != 0 && n)
    {
        *tmp_str = (unsigned char)c;
        ++tmp_str;
        --n;
    }

    while (n > WORDSIZE)
    {
      *(size_t*)tmp_str = *(size_t*)word_size;
      tmp_str += WORDSIZE;
      n -= WORDSIZE;

    }

    while(n)
    {
        *tmp_str = (unsigned char)c;
        ++tmp_str;
        --n;
    }
    free(word_size);
    return str;

}


void *Memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *tmp_dest = dest;
    char *csrc = (char *)src;

    while((*(size_t *)&tmp_dest % WORDSIZE) != 0 && (*(size_t *)&csrc % WORDSIZE) != 0 && n)
    {
        *tmp_dest = *csrc;
        ++tmp_dest;
        ++csrc;
        --n;
    }

    while (n > WORDSIZE)
    {
      *(size_t*)tmp_dest = *(size_t*)csrc;
      tmp_dest += WORDSIZE;
      csrc += WORDSIZE;
      n -= WORDSIZE;

    }

    while(n)
    {
        *tmp_dest = *csrc;
        ++tmp_dest;
        ++csrc;
        --n;
    }

    return dest;
}


void *Memmove(void *dest, const void *src, size_t n)
{
    unsigned char *pd = dest;
    const unsigned char *ps = src;

    if(ps < pd && pd < ps + n)
    {
        pd += n;
        ps += n;

        while((*(size_t *)&pd % WORDSIZE) != 0 && (*(size_t *)&ps % WORDSIZE) != 0 && n)
        {
            --pd;
            --ps;
            *pd = *ps;
            --n;
        }

        while (n > WORDSIZE)
        {
          pd -= WORDSIZE;
          ps -= WORDSIZE;
          *(size_t*)pd = *(size_t*)ps;
          n -= WORDSIZE;

        }
        while (n != 0)
        {
            --ps;
            --pd;
            *pd = *ps;
            --n;
        }
    }

    else
    {
       Memcpy(pd, src, n);
    }

    return dest;
}


void reverse(char str[], int len)
{
    int start, end;
    char temp;
    for(start=0, end=len-1; start < end; ++start , --end)
    {
        temp = *(str+start);
        *(str+start) = *(str+end);
        *(str+end) = temp;
    }
}

char *Itoa36(int value, char *str, int base)
{
    int i = 0;
    int is_negative = 0;
    int rem = 0;

    if ( 0 == value )
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }


    if (value < 0 && 10 == base)
    {
        is_negative = 1;
        value = -value;
    }

    while (value != 0)
    {
        rem = value % base;
        if (rem > 9)
        {
            str[i++] =(rem-10) + ASCIIA;
        }
        else
        {
            str[i++] = rem + ASCII0;
        }
        value = value/base;
    }

    if (1 == is_negative)
    {
        str[i++] = '-';
    }

    str[i] = '\0';
    reverse(str, i);

    return str;
}



int Atoi36(const char *str, int base)
{
    int i = 0;
    int res = 0;
    int tmp_res = 0;
    int len = strlen(str) - 1;
    int power = 1;

    for (i=len; i >= 0; --i, power *= base)
    {
       if (str[i] >= '0' && str[i] <= '9')
       {
            tmp_res =  str[i] - ASCII0;
       }
       else if (str[i] >= 'A' && str[i] <= 'Z')
       {
            tmp_res =  str[i] - 'A' + 10;

       }

       res = res + (power *  tmp_res);
    }

    return res;
}


void OnlyTwice(char *a, int a_size, char *b, int b_size, char *c, int c_size)
{

    int i=0;
    char *p_a = calloc(ASCII_TABLE , sizeof(char));
    char *p_b = calloc(ASCII_TABLE , sizeof(char));
    if (NULL == p_a)
	{
		printf("malloc failed!\n");
		exit(0);
	}


    if (NULL == p_b)
	{
		printf("malloc failed!\n");
		exit(0);
	}

    for (i=0; i < a_size; ++i)
    {
        p_a[(unsigned)a[i]] = a[i];
    }

    for (i=0; i < b_size; ++i)
    {
        p_b[(unsigned)b[i]] = b[i];
    }

    for (i=0; i < ASCII_TABLE; ++i)
    {
        if(p_a[i] != p_b[i])
        {
            p_a[i] = 0;
        }
    }

    for(i=0; i < c_size; ++i)
    {
        if(p_a[(unsigned)c[i]] == c[i])
        {
            p_a[(unsigned)c[i]] = 0;
        }
    }
    for(i=0; i < ASCII_TABLE; ++i)
    {
        printf("%c", p_a[i]);
    }

    printf("\n");
    free(p_a);
    free(p_b);

}



int IsLittleEndian()
{
	int i = 1;
	char *p_i = (char *)&i;

	if (*p_i != 0)
	{
		printf("System is a Little Endian\n");
		return 1;
	}
	else
	{
		printf("System is a Big Endian\n");
		return 0;
	}
}

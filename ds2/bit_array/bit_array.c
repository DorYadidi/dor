/*******************************************************************************
* NAME: Bit Array                                                              *
*                                                                              *
* PURPOSE: bit array manipulation functions                                    *
*                                                                              *
* AUTHOR: dor yadidi                                                           *
* DATE UPDATED:  04.11.18                                                      *
*******************************************************************************/

#include <stdlib.h>
#include "../include/bit_array.h"

#define BITS_IN_LONG 64
#define BYTES_IN_LONG 8

static const unsigned char mirror_lut[256] = {0x00, 0x80, 0x40, 0xc0, 0x20,
	0xa0, 0x60, 0xe0, 0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0, 0x08,
	0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8, 0x18, 0x98, 0x58, 0xd8, 0x38,
	0xb8, 0x78, 0xf8, 0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4, 0x14,
	0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4, 0x0c, 0x8c, 0x4c, 0xcc, 0x2c,
	0xac, 0x6c, 0xec, 0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc, 0x02,
	0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2, 0x12, 0x92, 0x52, 0xd2, 0x32,
	0xb2, 0x72, 0xf2, 0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea, 0x1a,
	0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa, 0x06, 0x86, 0x46, 0xc6, 0x26,
	0xa6, 0x66, 0xe6, 0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6, 0x0e,
	0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee, 0x1e, 0x9e, 0x5e, 0xde, 0x3e,
	0xbe, 0x7e, 0xfe, 0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1, 0x11,
	0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1, 0x09, 0x89, 0x49, 0xc9, 0x29,
	0xa9, 0x69, 0xe9, 0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9, 0x05,
	0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5, 0x15, 0x95, 0x55, 0xd5, 0x35,
	0xb5, 0x75, 0xf5, 0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed, 0x1d,
	0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd, 0x03, 0x83, 0x43, 0xc3, 0x23,
	0xa3, 0x63, 0xe3, 0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3, 0x0b,
	0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb, 0x1b, 0x9b, 0x5b, 0xdb, 0x3b,
	0xbb, 0x7b, 0xfb, 0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7, 0x17,
	0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7, 0x0f, 0x8f, 0x4f, 0xcf, 0x2f,
	0xaf, 0x6f, 0xef, 0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff};

static const unsigned char count_lut[256] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3,
	2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2,
	3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5,
	5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4,
	5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2,
	3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3,
	3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5,
	6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5,
	4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5,
	6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8};

int BitArrayIsOn(unsigned long bit_array, size_t bit)
{
	return ((bit_array >> bit) & 1);
}

int BitArrayIsOff(unsigned long bit_array, size_t bit)
{
	return !((bit_array >> bit) & 1);
}

unsigned long BitArraySetOn(unsigned long bit_array, size_t bit)
{
	return (bit_array | (unsigned long)1 << bit);
}

unsigned long BitArraySetOff(unsigned long bit_array, size_t bit)
{
	return (bit_array & ~((unsigned long)1 << bit));
}

unsigned long BitArrayFlip(unsigned long bit_array, size_t bit)
{
	return (bit_array ^ (unsigned long)1 << bit);
}

unsigned long BitArrayRotateRight(unsigned long bit_array, unsigned int n)
{
	unsigned int i = 0;

	for ( ; i < n; ++i)
	{
		bit_array = (bit_array >> 1) | (bit_array << 63);
	}

	return (bit_array);
}

unsigned long BitArrayRotateLeft(unsigned long bit_array, unsigned int n)
{
	unsigned int i = 0;

	for ( ; i < n; ++i)
	{
		bit_array = (bit_array << 1) | (bit_array >> 63);
	}

	return (bit_array);
}

unsigned long BitArrayMirror(unsigned long bit_array)
{
	bit_array = (((bit_array & 0xaaaaaaaaaaaaaaaa) >> 1) |
		((bit_array & 0x5555555555555555) << 1));
	bit_array = (((bit_array & 0xcccccccccccccccc) >> 2) |
		((bit_array & 0x3333333333333333) << 2));
	bit_array = (((bit_array & 0xf0f0f0f0f0f0f0f0) >> 4) |
		((bit_array & 0x0f0f0f0f0f0f0f0f) << 4));
	bit_array = (((bit_array & 0xff00ff00ff00ff00) >> 8) |
		((bit_array & 0x00ff00ff00ff00ff) << 8));
	bit_array = (((bit_array & 0xffff0000ffff0000) >> 16) |
		((bit_array & 0x0000ffff0000ffff) << 16));
	bit_array = (((bit_array & 0xffffffff00000000) >> 32) |
		((bit_array & 0x00000000ffffffff) << 32));

	return (bit_array);
}

size_t BitArrayCountOn(unsigned long bit_array)
{
	bit_array = bit_array - ((bit_array >> 1) & 0x5555555555555555);
	bit_array = (bit_array & 0x3333333333333333) +
		((bit_array >> 2) & 0x3333333333333333);
	bit_array = (bit_array + (bit_array >> 4)) & 0x0f0f0f0f0f0f0f0f;
	bit_array = bit_array + (bit_array >> 8);
	bit_array = bit_array + (bit_array >> 16);
	bit_array = bit_array + (bit_array >> 32);

	return (bit_array & 0x7f);
}

size_t BitArrayCountOff(unsigned long bit_array)
{
	return (BITS_IN_LONG - BitArrayCountOn(bit_array));
}

unsigned long BitArrayMirrorLUT(unsigned long bit_array)
{
	int i = 0;

	union
	{
		unsigned long ul;
		unsigned char uch[8];
	}un1,un2;

	un1.ul = bit_array;

	for ( ; i < BYTES_IN_LONG; ++i)
	{
		un2.uch[i] = mirror_lut[un1.uch[7 - i]];
	}

	return (un2.ul);
}

size_t BitArrayCountOnLUT(unsigned long bit_array)
{
	size_t on_bits = 0;
	int i = 0;

	union
	{
		unsigned long ul;
		unsigned char uch[8];
	}un;

	un.ul = bit_array;

	for ( ; i < 8; ++i)
	{
		on_bits += count_lut[un.uch[i]];
	}

	return (on_bits);
}

size_t BitArrayCountOffLUT(unsigned long bit_array)
{
	return (BITS_IN_LONG - BitArrayCountOnLUT(bit_array));
}

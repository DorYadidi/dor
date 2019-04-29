/*******************************************************************************
* NAME: Bit Array                                                              *
*                                                                              *
* PURPOSE: bit array manipulation functions                                    *
*                                                                              *
* AUTHOR: dor yadidi                                                           *
* DATE UPDATED:  04.11.18                                                      *
*******************************************************************************/
#include <stdio.h>

#ifndef __DS_BIT_ARRAY_H__
#define __DS_BIT_ARRAY_H__

int BitArrayIsOn(unsigned long bit_array, size_t bit);
int BitArrayIsOff(unsigned long bit_array, size_t bit);
/*******************************************************************************
* Checks if a given bit is set (BitArrayIsOn) or not set (BitArrayIsOff)       *
*                                                                              *
* Parameters:                                                                  *
*   bit_array - unsigned long int representing a bit array                     *
*   bit - bit to be checked                                                    *
* Return:                                                                      *
*   0 - test result is FALSE                                                   *
*   1 - test result is TRUE                                                    *
*******************************************************************************/

unsigned long BitArraySetOn(unsigned long bit_array, size_t bit);
unsigned long BitArraySetOff(unsigned long bit_array, size_t bit);
/*******************************************************************************
* Set (BitArraySetOn) or unset (BitArraySetOff) bit at location bit            *
*                                                                              *
* Parameters:                                                                  *
*   bit_array - unsigned long int representing a bit array                     *
*   bit - bit to be set/unset                                                  *
*                                                                              *
* Return:                                                                      *
*   unsigned long int representing bit array after manipulation                *
*******************************************************************************/

unsigned long BitArrayFlip(unsigned long bit_array, size_t bit);
/*******************************************************************************
* Set/unset bit depending on current state                                     *
*                                                                              *
* Parameters:                                                                  *
*   bit_array - unsigned long int representing a bit array                     *
*   bit - bit to be flipped                                                    *
*									       *
* Return:                                                                      *
*   unsigned long int representing bit array after manipulation                *
*******************************************************************************/

unsigned long BitArrayRotateRight(unsigned long bit_array, unsigned int n);
unsigned long BitArrayRotateLeft(unsigned long bit_array, unsigned int n);
/*******************************************************************************
* Rotate bit array right/left n bit positions                                  *
*                                                                              *
* Parameters:                                                                  *
*   bit_array - unsigned long int representing a bit array                     *
*   n - number of bit positions to rotate bit array                            *
*									       *
* Return:                                                                      *
*   unsigned long int representing bit array after manipulation                *
*******************************************************************************/

unsigned long BitArrayMirror(unsigned long bit_array);
/*******************************************************************************
* Return mirror image of bit array                                             *
*                                                                              *
* Parameters:                                                                  *
*   bit_array - unsigned long int representing a bit array                     *
*                                                                              *
* Return:                                                                      *
*   unsigned long int representing bit array after manipulation                *
*******************************************************************************/

size_t BitArrayCountOn(unsigned long bit_array);
size_t BitArrayCountOff(unsigned long bit_array);
/*******************************************************************************
* Counts number of bits are on/off in a bit array                              *
*                                                                              *
* Parameters:                                                                  *
*   bit_array - unsigned long int representing a bit array                     *
*                                                                              *
* Return:                                                                      *
*   number of bits on/off as size_t                                            *
*******************************************************************************/

unsigned long BitArrayMirrorLUT(unsigned long bit_array);
size_t BitArrayCountOnLUT(unsigned long bit_array);
size_t BitArrayCountOffLUT(unsigned long bit_array);

#endif

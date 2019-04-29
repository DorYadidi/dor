/*******************************************************************************
*                                                                              *
*                             File name   : ws_8_1.h                           *
*                             Author      : Etay Pennner                       *
*                             Created     : 28/10/2018                         *
*                             Last updated: 28/10/2018                         *
*                                                                              *
*******************************************************************************/

#ifndef __WS8_1_H__
#define __WS8_1_H__

typedef struct s_polymorphism poly_type;
/*******************************************************************************
* Struct that demonstrates polymorphism.                                       *
*******************************************************************************/

int AddIntToInt(poly_type *pt, int n);
/*******************************************************************************
* Adds an intiger value to the data of type int of the struct.                 *
*******************************************************************************/

int AddIntToFloat(poly_type *pt, int n);
/*******************************************************************************
* Adds an intiger value to the data of type float of the struct.               *
*******************************************************************************/

int AddIntToString(poly_type *pt, int n);
/*******************************************************************************
* Adds an intiger value to the data of type String of the struct.              *
*******************************************************************************/

void PrintInt(poly_type pt);
/*******************************************************************************
* Prints an intiger value to the data of the struct.                           *
*******************************************************************************/

void PrintFloat(poly_type pt);
/*******************************************************************************
* Prints a float value to the data of the struct.                              *
*******************************************************************************/

void PrintString(poly_type pt);
/*******************************************************************************
* Prints a string from the struct.                                             *
*******************************************************************************/

void FreeIntFloat(poly_type pt);
/*******************************************************************************
* Does nothing.                                                                *
*******************************************************************************/

void FreeString(poly_type pt);
/*******************************************************************************
* Free the string pointer of the struct.                                       *
*******************************************************************************/

typedef int (*add_type)(poly_type *pt, int n);
/*******************************************************************************
* Function pointer for the struct.                                             *
*******************************************************************************/

typedef void (*print_type)(poly_type pt);
/*******************************************************************************
* Function pointer for the struct.                                             *
*******************************************************************************/

typedef void (*free_type)(poly_type pt);
/*******************************************************************************
* Function pointer for the struct.                                             *
*******************************************************************************/

#endif
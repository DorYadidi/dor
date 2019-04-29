/*******************************************************************************
 * file name: ws_8_1.h							       *
 * author : Dor yadidi.                                                        *	
 * date: 28.10.18				                               *
 ******************************************************************************/
 
#ifndef __WS8_1_H__
#define __WS8_1_H__

typedef struct s_polymorphism poly_type; /*forward declaration*/

int Test_Poly(int data_user);
int AddIntToInt(poly_type *pt , int n);
int AddIntToFloat(poly_type *pt, int n);	
int AddIntToString(poly_type *pt, int n);
void PrintInt(poly_type pt);
void PrintFloat(poly_type pt);
void PrintString(poly_type pt);
void FreeIntFloat(poly_type pt);
void FreeString(poly_type pt);

typedef int (*add_type) (poly_type *pt, int n);
typedef void (*print_type) (poly_type pt);
typedef void (*free_type) (poly_type pt);



#endif

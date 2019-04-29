/*******************************************************************************
* NAME: Calculator                                                             *
*                                                                              *
* AUTHOR: Yaakov Sidikman                                                      *
* DATE UPDATED:  16.12.18                                                      *
*******************************************************************************/
#include "enum_rd58.h"

#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

double CalculateExpression(char *expression, status *stat);
/*******************************************************************************
* Receives mathematical expression represented as a string, calculates and     *
* returns result of the expression                                             *
*                                                                              *
* Parameters:                                                                  *
*  expression - valid mathematical expression in the form of a string          *
*                                                                              *
* Returns:                                                                     *
*  calculated result of the expression (double)                                *
*  on ERROR returns -1 and prints error message                                *
*******************************************************************************/

#endif

/*******************************************************************************
* NAME: Stack Calculator                                                       *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  16.12.18                                                      *
*******************************************************************************/

#include <string.h> /*strtod*/
#include <assert.h> /*assert*/
#include <math.h> /*pow*/
#include <stdlib.h> /*malloc free*/
#include "calculator.h"
#include "stack.h"

#define NUM_OF_INPUTS 256
#define NUM_OF_STATE 4
#define PREC_AND_ASSOC 2
#define PREC 0
#define ASSOC 1

typedef struct stack_calculator_s stack_calculator_t;
typedef enum {
	END_OF_INPUT,
	WATING_FOR_NUMBER,
	WATING_FOR_OPERATOR,
	WORNG_INPUT
} state;

struct stack_calculator_s
{
	state current_state;
	stack_t *output;
	stack_t *operator;
};

typedef double (*math_func_lut_t)(double operand_1, double operand_2);
typedef char *(*transition_func_t)(stack_calculator_t *sc, char *character);

static int precedence_lut[NUM_OF_INPUTS][PREC_AND_ASSOC];
static math_func_lut_t math_func_lut[NUM_OF_INPUTS];
static transition_func_t transition_func_lut[NUM_OF_STATE][NUM_OF_INPUTS];

/*******************************************************************************/
static double DoCalculation(stack_calculator_t *sc);

static double StackCalculatorAdd(double operand_1, double operand_2)
{
	return (operand_1 + operand_2);
}

static double StackCalculatorSubtract(double operand_1, double operand_2)
{
	return (operand_1 - operand_2);
}

static double StackCalculatorMultiply(double operand_1, double operand_2)
{
	return (operand_1 * operand_2);
}

static double StackCalculatorDivide(double operand_1, double operand_2)
{
	return (operand_1 / operand_2);
}

static double StackCalculatorPower(double operand_1, double operand_2)
{
	return (pow(operand_1, operand_2));
}

static char *HandlerError(stack_calculator_t *sc, char *character)
{
	sc->current_state = WORNG_INPUT;

	return (character);
}

static char *HandlerNumber(stack_calculator_t *sc, char *character)
{
	char *next_input;
	double result = strtod(character ,&next_input);

	if (character == next_input)
	{
		sc->current_state = WORNG_INPUT;
		return (character);
	}

	StackPush(sc->output, &result);
	sc->current_state = WATING_FOR_OPERATOR;

	return (next_input);
}

static char *HandlerOperator(stack_calculator_t *sc, char *character)
{
	int prec_operator = precedence_lut[(int)*character][PREC];
	int prec_peek = precedence_lut[((int)*(char *)(StackPeek(sc->operator)))][PREC];
	int assoc_peek = precedence_lut[((int)*(char *)(StackPeek(sc->operator)))][ASSOC];

	double new_num = 0;

	while (prec_peek - assoc_peek >= prec_operator)
	{
		new_num = DoCalculation(sc);
		StackPush(sc->output, &new_num);
		prec_peek = precedence_lut[((int)*(char *)(StackPeek(sc->operator)))][PREC];
		assoc_peek = precedence_lut[((int)*(char *)(StackPeek(sc->operator)))][ASSOC];
	}

	StackPush(sc->operator, character);
	sc->current_state = WATING_FOR_NUMBER;

	return (++character);
}

static char *HandlerEndOfInput(stack_calculator_t *sc, char *character)
{
	double new_num = 0;
	char peek_stack_operator = *(char *)StackPeek(sc->operator);
	while ('$' != peek_stack_operator)
	{
		if ('(' == peek_stack_operator)
		{
			sc->current_state = WORNG_INPUT;
			return (character);
		}

		new_num = DoCalculation(sc);
		StackPush(sc->output, &new_num);
		peek_stack_operator = *(char *)StackPeek(sc->operator);
	}

	sc->current_state = END_OF_INPUT;

	return (character);
}

static char *HandlerSpace(stack_calculator_t *sc, char *character)
{
	(void)(sc);

	return (++character);
}

static char *HandlerOpenParenthes(stack_calculator_t *sc, char *character)
{
	StackPush(sc->operator, character);


	return (++character);
}

static char *HandlerCloseParenthes(stack_calculator_t *sc, char *character)
{
	double new_num = 0;
	char peek_stack = *(char *)StackPeek(sc->operator);

	while ('(' != peek_stack)
	{
		if ('$' == peek_stack)
		{
			sc->current_state = WORNG_INPUT;
			return (character);
		}

		new_num = DoCalculation(sc);
		StackPush(sc->output, &new_num);
		peek_stack = *(char *)StackPeek(sc->operator);
	}

	StackPop(sc->operator);

	return (++character);
}

static double DoCalculation(stack_calculator_t *sc)
{
	double result = 0;
	double temp_double2 = 0;
	double temp_double = 0;
	char operator = *(char *)StackPeek(sc->operator);

	StackPop(sc->operator);
	temp_double2 = *(double*)StackPeek(sc->output);
	StackPop(sc->output);
	temp_double = *(double*)StackPeek(sc->output);
	StackPop(sc->output);
	result = math_func_lut[(int)operator](temp_double, temp_double2);

	return (result);
}

static void StackCalculatorGenerateLUT()
{
	int i = 0, j = 0;
	for ( ; i < NUM_OF_STATE; ++i)
	{
		for (j=0; j < NUM_OF_INPUTS; ++j)
		{
			transition_func_lut[i][j] = HandlerError;
		}
	}

	transition_func_lut[WATING_FOR_OPERATOR]['\0'] = HandlerEndOfInput;

	transition_func_lut[WATING_FOR_NUMBER]['0'] = HandlerNumber;
	transition_func_lut[WATING_FOR_NUMBER]['1'] = HandlerNumber;
	transition_func_lut[WATING_FOR_NUMBER]['2'] = HandlerNumber;
	transition_func_lut[WATING_FOR_NUMBER]['3'] = HandlerNumber;
	transition_func_lut[WATING_FOR_NUMBER]['4'] = HandlerNumber;
	transition_func_lut[WATING_FOR_NUMBER]['5'] = HandlerNumber;
	transition_func_lut[WATING_FOR_NUMBER]['6'] = HandlerNumber;
	transition_func_lut[WATING_FOR_NUMBER]['7'] = HandlerNumber;
	transition_func_lut[WATING_FOR_NUMBER]['8'] = HandlerNumber;
	transition_func_lut[WATING_FOR_NUMBER]['9'] = HandlerNumber;
	transition_func_lut[WATING_FOR_NUMBER]['.'] = HandlerNumber;

	precedence_lut['+'][PREC] = 4;
	transition_func_lut[WATING_FOR_NUMBER]['+'] = HandlerNumber;
	transition_func_lut[WATING_FOR_OPERATOR]['+'] = HandlerOperator;
	math_func_lut['+'] = StackCalculatorAdd;

	precedence_lut['-'][PREC] = 4;
	transition_func_lut[WATING_FOR_NUMBER]['-'] = HandlerNumber;
	transition_func_lut[WATING_FOR_OPERATOR]['-'] = HandlerOperator;
	math_func_lut['-'] = StackCalculatorSubtract;

	precedence_lut['*'][PREC] = 6;
	transition_func_lut[WATING_FOR_OPERATOR]['*'] = HandlerOperator;
	math_func_lut['*'] = StackCalculatorMultiply;

	precedence_lut['/'][PREC] = 6;
	transition_func_lut[WATING_FOR_OPERATOR]['/'] = HandlerOperator;
	math_func_lut['/'] = StackCalculatorDivide;

	precedence_lut['^'][PREC] = 8;
	precedence_lut['^'][ASSOC] = 1;
	transition_func_lut[WATING_FOR_OPERATOR]['^'] = HandlerOperator;
	math_func_lut['^'] = StackCalculatorPower;

	transition_func_lut[WATING_FOR_NUMBER][' '] = HandlerSpace;
	transition_func_lut[WATING_FOR_OPERATOR][' '] = HandlerSpace;

	precedence_lut['('][PREC] = 2;
	transition_func_lut[WATING_FOR_NUMBER]['('] = HandlerOpenParenthes;
	math_func_lut['('] = NULL;

	transition_func_lut[WATING_FOR_OPERATOR][')'] = HandlerCloseParenthes;
	math_func_lut[')'] = NULL;

	precedence_lut['$'][PREC] = 0;
	math_func_lut['$'] = NULL;
}

static stack_calculator_t *StackCalculatorCreate(size_t number_of_inputs)
{
	char dummy_head = '$';
	stack_calculator_t *sc = (stack_calculator_t *)malloc(sizeof(stack_calculator_t));

	if (NULL == sc)
	{
		return (NULL);
	}

	sc->output = StackCreate(number_of_inputs, sizeof(double));
	if (NULL == sc->output)
	{
		free (sc);
		return (NULL);
	}
	sc->operator = StackCreate(number_of_inputs, sizeof(char));
 	if (NULL == sc->operator)
  	{
	  free (sc->output);
	  free (sc);
	  return (NULL);
	}

	sc->current_state = WATING_FOR_NUMBER;
	StackPush(sc->operator, &dummy_head);
	StackCalculatorGenerateLUT();

	return (sc);
}

static void StackCalculatorDestroy(stack_calculator_t *sc)
{
	assert(sc != NULL);
	StackDestroy(&(sc->output));
	StackDestroy(&(sc->operator));
	free(sc);
}

/*******************************************************************************/

double CalculateExpression(char *expression, status *stat)
{
	size_t len_expression = strlen(expression);
	double result = 0;
	stack_calculator_t *sc = StackCalculatorCreate(len_expression);
	if (NULL == sc)
	{
		*stat = MEMORY_ALLOCATION_FAIL;
		return (result);
	}

	while (sc->current_state != END_OF_INPUT)
	{
		expression = transition_func_lut[sc->current_state][(int)*expression]
		(sc, expression);

		if (WORNG_INPUT == sc->current_state)
		{
			*stat = FAIL;
			StackCalculatorDestroy(sc);
			sc = NULL;
			return (result);
		}
	}

	*stat = SUCCESS;
	result = *(double *)StackPeek(sc->output);
	StackCalculatorDestroy(sc);
	sc = NULL;

	return (result);
}

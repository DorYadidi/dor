/*******************************************************************************
* NAME: Knight's Tour                                                          *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  02.01.19                                                      *
*******************************************************************************/

#include <stdlib.h> /* malloc, free */
#include <stdio.h> /* printf */
#include <time.h> /*time_t */
#include "enum_rd58.h"
#include "bit_array.h"

#define N 8
#define M 8
#define VALID_MOVE 8
#define COMPLETE (N * M)
#define INVALID_STEP -1
#define MAX_TIME 5 * 60
#define POSITION(n,m) ((n + 1 + (m * N)) - 1)

/************************** Types, Structs, LUTs ******************************/

typedef enum {SUCCESS_KNIGHT, MOVE_FAILED, TIMEOUT} move_status_t;

typedef struct step_s
{
	int position;
	int move_count;
} step_t;

static int valid_move_lut[N*M][VALID_MOVE];

/************************** Print Functions ***********************************/

static void PrintTable(int *array_moves)
{
	int i = 0, j = 0;

	printf("     ");
	for (i = 0; i < N; ++i)
	{
		printf("%d   ", i);
	}
	printf("\n");

	for (j = 0; j < M ; ++j)
	{
		printf("%d | ", j);
		for (i = j * N; i < (j + 1) * N; ++i)
		{
			if (10 > array_moves[i])
			{
				printf("%d  | ", array_moves[i]);
			}
			else
			{
				printf("%d | ", array_moves[i]);
			}
		}
		printf("\n");
	}
}

/************************** Generate LUT  *******************************/

static void GenerateLegalMoves()
{
	int i = 0, j = 0;
	int lut_index = 0;

	for (j = 0; j < M ; ++j)
	{
		for (i = 0; i < N; ++i)
		{
			lut_index = POSITION(i, j);

			if (((i - 1) >= 0) && ((j - 2) >= 0))
			{
				valid_move_lut[lut_index][0] = POSITION((i - 1),(j - 2));
			}
			else
			{
				valid_move_lut[lut_index][0] = INVALID_STEP;
			}
			if (((i + 1) < N) && ((j - 2) >= 0))
			{
				valid_move_lut[lut_index][1] = POSITION((i + 1),(j - 2));
			}
			else
			{
				valid_move_lut[lut_index][1] = INVALID_STEP;
			}
			if (((i + 2) < N) && ((j - 1) >= 0))
			{
				valid_move_lut[lut_index][2] = POSITION((i + 2),(j - 1));
			}
			else
			{
				valid_move_lut[lut_index][2] = INVALID_STEP;
			}
			if (((i + 2) < N) && ((j + 1) < M))
			{
				valid_move_lut[lut_index][3] = POSITION((i + 2),(j + 1));
			}
			else
			{
				valid_move_lut[lut_index][3] = INVALID_STEP;
			}
			if (((i + 1) < N) && ((j + 2) < M))
			{
				valid_move_lut[lut_index][4] = POSITION((i + 1),(j + 2));
			}
			else
			{
				valid_move_lut[lut_index][4] = INVALID_STEP;
			}
			if (((i - 1) >= 0) && ((j + 2) < M))
			{
				valid_move_lut[lut_index][5] = POSITION((i - 1),(j + 2));
			}
			else
			{
				valid_move_lut[lut_index][5] = INVALID_STEP;
			}
			if (((i - 2) >= 0) && ((j + 1) < M))
			{
				valid_move_lut[lut_index][6] = POSITION((i - 2),(j + 1));
			}
			else
			{
				valid_move_lut[lut_index][6] = INVALID_STEP;
			}
			if (((i - 2) >= 0) && ((j - 1) >= 0))
			{
				valid_move_lut[lut_index][7] = POSITION((i - 2),(j - 1));
			}
			else
			{
				valid_move_lut[lut_index][7] = INVALID_STEP;
			}
		}
	}
}
/************************** Get Next Square ***********************************/

static int GetNextMove(int move_index, size_t visit_table,
						step_t *prioritized_moves)
{
	int next_step = prioritized_moves[move_index].position;

	if (TRUE == BitArrayIsOn(visit_table, next_step))
	{
		next_step = INVALID_STEP;
	}

	return (next_step);
}

static int MinToMax(const void *data1, const void *data2)
{

	return(((step_t *)data1)->move_count - ((step_t *)data2)->move_count);
}

static void Warendorf(step_t *prioritized_moves,
								int current_step, size_t visit_table)
{
	int next_step = 0;
	int possible_move = 0;
	int i = 0, j = 0;

	for (i = 0; i < VALID_MOVE; ++i)
	{
		int count = 0;
		next_step = valid_move_lut[current_step][i];

		if (INVALID_STEP != next_step)
		{
			for (j = 0; j < VALID_MOVE; ++j)
			{
				possible_move = valid_move_lut[next_step][j];

				if ((INVALID_STEP != possible_move) &&
					(FALSE == BitArrayIsOn(visit_table, possible_move)))
				{
					++count;
				}
			}
		}

		prioritized_moves[i].move_count = count;
		prioritized_moves[i].position = valid_move_lut[current_step][i];
	}

	qsort(prioritized_moves, VALID_MOVE, sizeof(step_t), MinToMax);
}

/************************** Make Move *****************************************/

static move_status_t KnigthTour(size_t visit_table, int current_step,
							time_t start_time, int *moves_made, int move_index,
							step_t *prioritized_moves)
{
	int next_step = INVALID_STEP;
	move_status_t current_status = MOVE_FAILED;
	int i = 0;

	visit_table = BitArraySetOn(visit_table, current_step);
	moves_made[current_step] = move_index;

	if (COMPLETE == BitArrayCountOn(visit_table))
	{
		return (SUCCESS_KNIGHT);
	}

	if (MAX_TIME <= (time(NULL) - start_time))
	{
		return (TIMEOUT);
	}

	for (i = 0; i < VALID_MOVE; ++i)
	{
		Warendorf(prioritized_moves, current_step, visit_table);
		next_step = GetNextMove(i, visit_table, prioritized_moves);

		if (INVALID_STEP != next_step)
		{
			current_status = KnigthTour(visit_table, next_step,
									  start_time, moves_made, move_index + 1,
								  	  prioritized_moves);
			if (MOVE_FAILED != current_status)
			{
				return (current_status);
			}
		}
	}

	return (MOVE_FAILED);
}

/************************** MAIN **********************************************/

int main()
{
	size_t visit_table = 0;
	time_t start_time = 0;
	int start_step = 0;
	move_status_t end_status;
	int *array_moves = NULL;
	step_t *prioritized_moves = malloc(VALID_MOVE * sizeof(step_t));

	if (NULL == prioritized_moves)
	{
		return (1);
	}

	array_moves = malloc((N * M) * sizeof(int));
	if (NULL == array_moves)
	{
		free(prioritized_moves);
		prioritized_moves = NULL;
		return (1);
	}

	GenerateLegalMoves();

	srand(time(NULL));
	start_step = rand() % (N * M);

	start_time = time(NULL);
	end_status = KnigthTour(visit_table, start_step,
						  start_time, array_moves, 0, prioritized_moves);

	if (TIMEOUT == end_status)
	{
		printf("END STATUS: Program timed-out\n");
	}
	else if (SUCCESS_KNIGHT == end_status)
	{
		printf("END STATUS: SUCCESS\n");
		PrintTable(array_moves);
	}
	else
	{
		printf("END STATUS: Solution Not Found\n");
	}

	free(prioritized_moves);
	prioritized_moves = NULL;
	free(array_moves);
	array_moves = NULL;

	return (0);
}

////////////////////////////////////////////////////////////////////////////////
// jakobi.c
// Jakobi algorithm implementation
// Jakobi algorithm lib executable file
// (c) Jan Horacek
// jan.horacek@seznam.cz
// 20.11.2014
// v1.0
////////////////////////////////////////////////////////////////////////////////

#include "jakobi.h"
#include "main.h"
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#ifdef DEBUG
	#include <stdio.h>
#endif

// function headers:
void jinitsol(MATRIX_TYPE* data, unsigned int len, MATRIX_TYPE value);
void jinitmat(matrix mat);

////////////////////////////////////////////////////////////////////////////////

void jinitsol(MATRIX_TYPE* data, unsigned int len, MATRIX_TYPE value)
{
	for (int i = 0; i < len; i++)
		data[i] = value;
}

////////////////////////////////////////////////////////////////////////////////

void jinitmat(matrix mat)
{
	int row, col;

	for (row = 0; row < mat.height; row++)
	{
		for (col = 0; (col < mat.width); col++)
			if (col != row)
				mat.data[row][col] /= mat.data[row][row];
		mat.data[row][row] = 0;
	}
}

////////////////////////////////////////////////////////////////////////////////

// Jakobi algorithm execution
//  return codes:
//	0 : ok
//	1 : iteration overflow
int jsolve(matrix mat, MATRIX_TYPE* sol, MATRIX_TYPE epsilon, unsigned int maxiter)
{
	MATRIX_TYPE* last = malloc(sizeof(MATRIX_TYPE) * mat.height);
	MATRIX_TYPE* tmp;
	bool solved = false;
	int row, col, iter;
	MATRIX_TYPE new;

	jinitmat(mat);
	jinitsol(sol, mat.height, 0);	// init value : zero

	#ifdef DEBUG
		printf("Vstupni matice:\n");
		print_matrix(mat);
	#endif

	for (iter = 0; !solved; iter++)
	{
		tmp  = last;
		last = sol;
		sol  = tmp;

		solved = true;
		for (row = 0; row < mat.height; row++)
		{
			new = mat.data[row][mat.width-1];
			for (col = 0; col < mat.width-1; col++)
				new -= mat.data[row][col] * last[col];

			if ((solved) && (fabs(new-last[row]) > epsilon))
				solved = false;

			sol[row] = new;

			#ifdef DEBUG
				printf("Row : %d\nSols:", row);
				print_solutions(sol, mat.height);
			#endif
		}

		if (iter > maxiter)
		{
			free(last);
			return 1;
		}
	}

	free(last);
	return 0;
}

////////////////////////////////////////////////////////////////////////////////


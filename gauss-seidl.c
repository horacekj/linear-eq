////////////////////////////////////////////////////////////////////////////////
// gauss-seild.c
// Gauss-seidl algorithm implementation
// Gauss-seidl algorithm lib executable file
// (c) Jan Horacek
// jan.horacek@seznam.cz
// 4.12.2014
// v1.0
////////////////////////////////////////////////////////////////////////////////

#include "gauss-seidl.h"
#include "main.h"
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#ifdef DEBUG
	#include <stdio.h>
	void gsprintsols(MATRIX_TYPE* sol, unsigned int len);
#endif

// function headers:
void gsinitsol(MATRIX_TYPE* data, unsigned int len, MATRIX_TYPE value);
void gsinitmat(matrix mat);
void gsprint(matrix mat);

////////////////////////////////////////////////////////////////////////////////

void gsinitsol(MATRIX_TYPE* data, unsigned int len, MATRIX_TYPE value)
{
	for (int i = 0; i < len; i++)
		data[i] = value;
}

////////////////////////////////////////////////////////////////////////////////

void gsinitmat(matrix mat)
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

// Gauss-seidl: algorithm execution
//  return codes:
//	0 : ok
//	1 : iteration overflow
int gssolve(matrix mat, MATRIX_TYPE* sol, MATRIX_TYPE epsilon, unsigned int maxiter)
{
	bool solved = false;
	int row, col, iter;
	MATRIX_TYPE new;

	gsinitmat(mat);
	gsinitsol(sol, mat.height, 0);	// init value : zero

	#ifdef DEBUG
		printf("Vstupni matice:\n");
		print_matrix(mat);
	#endif

	for (iter = 0; !solved; iter++)
	{
		solved = true;
		for (row = 0; row < mat.height; row++)
		{
			new = mat.data[row][mat.width-1];
			for (col = 0; (col < mat.width-1); col++)
				new -= mat.data[row][col] * sol[col];

			if ((solved) && (fabs(new-sol[row]) > epsilon))
				solved = false;

			sol[row] = new;

			#ifdef DEBUG
				printf("Row : %d\nSols:", row);
				print_solutions(sol, mat.height);
			#endif
		}

		if (iter > maxiter)
			return 1;
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////


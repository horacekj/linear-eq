////////////////////////////////////////////////////////////////////////////////
// main.c
// Gauss algorithm implementation
// main executable file
// (c) Jan Horacek
// jan.horacek@seznam.cz
// 4.12.2014
// v1.1
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "main.h"

// include lib according to the preprocessor definition (defined in Makefile)
#ifdef _USE_GS_
	#include "gauss-seidl.h"
#elif _USE_JAKOBI_
	#include "jakobi.h"
#else
	#include "gauss.h"
#endif

////////////////////////////////////////////////////////////////////////////////

#define EPSILON		0.0001
#define MAX_ITER	10000

////////////////////////////////////////////////////////////////////////////////

matrix mat;

////////////////////////////////////////////////////////////////////////////////
// malloc matrix

void init_matrix()
{
	int row;
	mat.data = malloc(sizeof(long*) * mat.height);
	for (row = 0; row < mat.height; row++)
		mat.data[row] = malloc(sizeof(long) * mat.width);
}

////////////////////////////////////////////////////////////////////////////////
// destroy matrix

void free_matrix()
{
	int row;
	for (row=0; row < mat.height; row++)
		free(mat.data[row]);
	free(mat.data);
}

////////////////////////////////////////////////////////////////////////////////
// debug:

#ifdef DEBUG
void print_matrix(matrix mat)
{
	int row, col;
	printf("Matrix:\n");

	for (row = 0; row < mat.height; row++)
	{
		for (col = 0; col < mat.width; col++)
			printf("%5.2lf, ", mat.data[row][col]);
		printf("\n");
	}
}

void print_solutions(MATRIX_TYPE* sol, unsigned int len)
{
	for (int i = 0; i < len; i++)
		printf("%5.2lf ", sol[i]);
	printf("\n");
}

#endif

////////////////////////////////////////////////////////////////////////////////
// load matrix from stdin
// input format: width height row0col0 row0col1 row0col2 ... row1col0 ...
//  all blank characters are separators

void load_matrix()
{
	int row, col;

	scanf("%d", &mat.width);
	scanf("%d", &mat.height);

	init_matrix();

	for (row = 0; row < mat.height; row++)
		for (col = 0; col < mat.width; col++)
			scanf("%lf", &mat.data[row][col]);
}

////////////////////////////////////////////////////////////////////////////////
// main function:

int main(int argc, char* argv[])
{
	double *solutions;
	int ret, i;

	printf("Enter matrix according to specification:\n");

	// load matrix from stdin
	load_matrix();
	solutions = malloc(sizeof(double) * mat.height);

	// debug print
	#ifdef DEBUG
	print_matrix(mat);
	#endif

	// run method according to macro
	#ifdef _USE_GS_
		ret = gssolve(mat, solutions, EPSILON, MAX_ITER);
	#elif _USE_JAKOBI_
		ret = jsolve(mat, solutions, EPSILON, MAX_ITER);
	#else
		ret = gsolve(mat, solutions);
	#endif

	// result of method
	if (ret == 0)
	{
		printf("Solved: %d\n", ret);
		for (i = 0; i < mat.height; i++)
			printf("x%d = %5.2lf\n", i+1, solutions[i]);
	} else
		printf("Solved with error: %d\n", ret);

	// destroy objects:
	free_matrix();
	free(solutions);

	return 0;
}

////////////////////////////////////////////////////////////////////////////////


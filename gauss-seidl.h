////////////////////////////////////////////////////////////////////////////////
// gauss-seidl.h
// Gauss-seidl algorithm implementation
// Gauss-seidl algorithm lib header file
// (c) Jan Horacek
// jan.horacek@seznam.cz
// 4.12.2014
// v1.0
////////////////////////////////////////////////////////////////////////////////

#ifndef _LIB_GS_
#define _LIB_GS_

#include "main.h"

int gssolve(matrix mat, MATRIX_TYPE* sol, MATRIX_TYPE epsilon, unsigned int maxiter);

#endif

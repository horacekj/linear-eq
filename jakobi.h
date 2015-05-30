////////////////////////////////////////////////////////////////////////////////
// jakobi.h
// Jakobi algorithm implementation
// Jakobi algorithm lib header file
// (c) Jan Horacek
// jan.horacek@seznam.cz
// 13.11.2014
// v1.0
////////////////////////////////////////////////////////////////////////////////

#ifndef _LIB_JAKOBI_
#define _LIB_JAKOBI_

#include "main.h"

int jsolve(matrix mat, MATRIX_TYPE* sol, MATRIX_TYPE epsilon, unsigned int maxiter);

#endif

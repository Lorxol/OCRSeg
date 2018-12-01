#include <stdlib.h>

#ifndef SCALE
#define SCALE

void scale(const int dim1, const int dim2, const int *matrix, int *sm);

//int scaleup(int matrix, const int dim1, const int dim2);

void scaledown(const int dim1, const int dim2,const int *matrix, int *sm);

void printmat(int dim1,int dim2, const int *mat);

#endif

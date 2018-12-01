#include <stdlib.h>
#include <stdio.h>
#include "scaling.h"




int main()
{
	int dim1 = 60,dim2 = 30;
	int *mat = calloc((dim1+1)*(dim1+1),sizeof(int));
	int *mat2 = calloc((dim2+1)*(dim2+1),sizeof(int));
	for(int i=0;i<dim1;i++)
	{
		*(mat+i*dim1) = 0;
		*(mat+i*dim1+1)=0;
		*(mat+i*dim1+2)=0;

		for(int j=3;j<8;j++)
				*(mat+i*dim1+j) = 1;
		for(int j=8;j<dim1;j++)
				*(mat+i*dim1+j) = 0;
	}
	for(int j=0;j<dim1;j++)
	{
			*(mat+9*dim1+j) = 1;
			*(mat+10*dim1+j) = 1;
			*(mat+11*dim1+j) = 1;


	}


	scale(dim1,dim2,mat,mat2);
	printmat(dim1,dim1,mat);
	printf("\n\n");
	printmat(dim2,dim2,mat2);
	free(mat);
	free(mat2);
	return 0;
}

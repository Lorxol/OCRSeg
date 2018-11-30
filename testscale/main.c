#include <stdlib.h>
#include <stdio.h>
#include "scaling.h"


void printmat(int dim,int *mat)
{
	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
				printf("%d ",*(mat+i*dim+j));
		printf("\n");
	}
}

int main()
{
	int *mat = calloc(36,sizeof(int));
	int *mat2 = calloc(16,sizeof(int));
	for(int i=0;i<6;i++)
	{
		*(mat+i*6) = 0;
		*(mat+i*6+1)=0;
		for(int j=2;j<4;j++)
				*(mat+i*6+j) = 1;
		for(int j=4;j<6;j++)
				*(mat+i*6+j) = 0;
	}

	scale(6,4,mat,mat2);
	printmat(6,mat);
	printf("\n\n");
	printmat(4,mat2);
	return 0;
}

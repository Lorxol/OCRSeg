#include <stdio.h>
#include "scaling.h"

void printmat(int dim1, int dim2, const int *mat)
{
	for(int i=0;i<dim1;i++)
	{
		for(int j=0;j<dim2;j++)
				printf("%d ",*(mat+i*dim1+j));
		printf("\n");
	}
}




void scale(const int dim1, const int dim2, const int *matrix, int *sm)
{
	//Scale a squared matrix from dim1 to dim2
	if(dim1 > dim2)
			return scaledown(dim1,dim2,matrix,sm);
	/*else if(dim1 < dim2)
			return scaleup(dim1,dim2,matrix);*/
}

/*int scaleup(int matrix, const int dim1, const int dim2)
{
	//dim1 < dim2
}*/

void scaledown(const int dim1, const int dim2, const int *matrix, int *sm)
{
	// dim1 > dim2
	int spacement = dim1/((dim1-dim2));
	if(spacement == 1)
			spacement++;
	int *temp = calloc((dim1+1)*(dim2+1),sizeof(int));
	// sm means scaledmat which is the resultant matrix
	
	//Merging cols
	for(int i=0;i<dim1;i++)
	{
		for(int j=0,jscaled=0;j<dim1 && jscaled<dim2;j++,jscaled++)
		{

			if((j+1)%spacement != 0)
			{
				*(temp+i*dim1+jscaled) = *(matrix+i*dim1+j);
			}
			else
			{
				j++;
				*(temp+i*dim1+jscaled) = *(matrix+i*dim1+j);
			}

		}
	}	


	//Merging rows
	for(int j=0;j<dim2;j++)
	{
		for(int i=0,iscaled=0;iscaled<dim2 && i<dim1;i++,iscaled++)	
		{
			if(i%spacement!=0)// Proceeding fusion
			{
				*(sm+iscaled*dim2+j)  = *(temp+i*dim1+j);

			}
			else
			{
				i++;
				*(sm+iscaled*dim2+j)  = *(temp+i*dim1+j);
			}
		}
	}
	free(temp);

}











/*void scaledown(const int dim1, const int dim2, int *matrix, int *sm)
{
	// dim1 > dim2
	int spacement = dim1/((dim1-dim2)+1);
	printf("spacement:%d\n",spacement);
	// Means scaledmat which is the resultant matrix
	
	//Merging cols
	for(int i=0,iscaled=0;i<dim1 && iscaled<dim2;i++,iscaled++)
	{
		for(int j=0,jscaled=0;j<dim1-1 && jscaled<dim2;j++,jscaled++)
		{
			if((j+1)%spacement==0)
			{
				//If an adjacent pixel is black
				if(*(matrix+i*dim1+j)== 1 || *(matrix+i*dim1+j+1)== 1)
						*(sm+iscaled*dim2+jscaled) = 1;
				else
						*(sm+iscaled*dim2+jscaled) = 0;
				j++;
			}
			else
				*(sm+iscaled*dim2+jscaled) = 0;
		}
	}

	//Merging rows
	for(int j=0,jscaled=0;j<dim1 && jscaled<dim2;j++,jscaled++)
	{
		for(int i=0,iscaled=0;i<dim1-1 && iscaled<dim2;i++,iscaled++)	
		{
			if((i+1)%spacement==0 && (j+1)%spacement != 0)// Proceeding fusion
			{

				//printf("i: %d  j: %d  isc: %d  jsc: %d\n",i,j,iscaled,jscaled);
				//If an adjacent pixel is black
				if(*(matrix+i*dim1+j)== 1 || *(matrix+(i+1)*dim1+j) == 1)
				{
						printf("i: %d j: %d val1: %d  val2: %d\n",i,j,*(matrix+i*dim1+j), *(matrix+(i+1)*dim1+j));
						*(sm+iscaled*dim2+jscaled)  = 1;
				}
				else
						*(sm+iscaled*dim2+jscaled)  = 0;
				i++;
			}
			else if((j+1)%spacement == 0)
					j++;
		}
	}
}*/

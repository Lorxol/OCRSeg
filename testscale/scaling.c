#include <stdio.h>
#include "scaling.h"

void scale(const int dim1, const int dim2, int *matrix, int *sm)
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

void scaledown(const int dim1, const int dim2, int *matrix, int *sm)
{
	// dim1 > dim2
	int spacement = dim1/((dim1-dim2)+1);
	printf("spacement:%d\n",spacement);
	// Means scaledmat which is the resultant matrix
	
	/*//Merging rows
	for(int i=0,iscaled=0;i<dim1 && iscaled<dim2;i++,iscaled++)
	{
		for(int j=0,jscaled=0;j<dim1 && jscaled<dim2;j++,jscaled++)
		{
			if(j%spacement==0)
			{
				//If an adjacent pixel is black
				if(*(matrix+i*dim1+j)!=0 || *(matrix+i*dim1+j+1)!=0)
						*(sm+iscaled*dim2+jscaled) = 1;
				else
						*(sm+iscaled*dim2+jscaled) = 0;
				j++;
			}
			else
				*(sm+iscaled*dim2+jscaled) = 0;
		}
	}*/

	//Merging cols
	for(int j=0,jscaled=0;j<dim1 && jscaled<dim2;j++,jscaled++)
	{
		for(int i=0,iscaled=0;i<dim1 && iscaled<dim2;i++,iscaled++)	
		{
			if((i+1)%spacement==0)
			{
				//If an adjacent pixel is black
				if(*(matrix+i*dim1+j)!=0 || *(matrix+(i+1)*dim1+j)!=0)
						*(sm+iscaled*dim2+jscaled)  = 1;
				else
						*(sm+iscaled*dim2+jscaled)  = 0;
				i++;
			}
			else
				*(sm+iscaled*dim2+jscaled)  = 0;
		}
	}
}

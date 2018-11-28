#include "my_math_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <err.h>

/*--------------------Matrice function--------------------*/

/*----------creator----------*/

Matrice new_null_mat(int i, int j)
{
	Matrice m;
	m.dim1 = i;
	m.dim2 = j;
	m.mat = malloc(i * j * sizeof(double));
	for (int l = 0; l < i * j; l++)
	{
		m.mat[l] = 0;
	}
	return m;
}
Matrice new_order_mat(int i, int j)
{
	Matrice m;
	m.dim1 = i;
	m.dim2 = j;
	m.mat = malloc(i * j * sizeof(double));
	for(int l = 0; l < i * j; l++)
	{
		m.mat[l] = (double) l;
	}
	return m;
}

Matrice new_ID_mat(int i)
{
	Matrice m = new_null_mat(i, i);
	for (int j = 0; j < i; j++)
	{
		mat_new_val(&m, j, j, 1);
	}
	return m;
}

Matrice new_rand_mat(int i, int j)
{
	Matrice m;
	m.dim1 = i;
	m.dim2 = j;
	m.mat = malloc(i * j * sizeof(double));
	for (int l = 0; l < i * j; l++)
	{
		m.mat[l] = (double) rand()/RAND_MAX*2.0-1.0;
	}
	return m;
}

/*---------------------------*/

/*----------printor----------*/

void print_mat(Matrice m)
{
	int dim1 = m.dim1;
	int dim2 = m.dim2;
	printf("dim1 = %i : dim2 = %i\n", dim1, dim2);
	for(int i = 0; i < dim2; i++)
	{
		for(int j = 0; j < dim1; j++)
		{
			printf("%lf ", m.mat[i*dim1 + j]);
		}
		printf("\n");
	}
}

/*---------------------------*/

/*----------operation----------*/

void mat_new_val(Matrice* m, int i, int j, double x)
{
	if (i >= 0 && i < m->dim1 && j >= 0 && j < m->dim2)
	{
		m->mat[j*m->dim1 + i] = x;
	}
	else
	{
		errx(1, "Mat_new_val : Invalid position");
	}
}

void mat_add(Matrice add, Matrice* result)
{
	if (add.dim1 != result->dim1 || add.dim2 != result->dim2)
	{
		errx(1, "Mat_Add : Matrice size not valid");
	}
	for(int l = 0; l < add.dim1 * add.dim2; l++)
	{
		result->mat[l] += add.mat[l];
	}
}

void mat_scal_mult(double scal, Matrice* result)
{
	for(int l = 0; l < result->dim1 * result->dim2; l++)
	{
		result->mat[l] *= scal;
	}
}

Matrice mat_mult(Matrice m1, Matrice m2)
{
	if (m1.dim1 != m2.dim2) errx(1, "Mat_mult : Matrice size not valid");
	Matrice result;
	result.dim1 = m2.dim1;
	result.dim2 = m1.dim2;
	double z = 0;
	result.mat = malloc(result.dim1 * result.dim2 * sizeof(double));
	for(int j = 0; j < result.dim2; j++)
	{
		for(int i = 0; i < result.dim1; i++)
		{
			z = 0;
			for(int k = 0; k < m1.dim1; k++)
			{
				z  += m1.mat[k + j * m1.dim1] * m2.mat[i + k * m2.dim1];
			}
		result.mat[i + j * result.dim1] = z;
		}
	}

	return result;
}

/*-----------------------------*/

/*--------------------------------------------------------*/




/*--------------------Vector function--------------------*/

/*----------creator----------*/

Vector new_null_vec(int i)
{
	Vector v;
	v.len = i;
	v.vec = malloc(i * sizeof(double));
	for (int l = 0; l < i; l++)
	{
		v.vec[l] = 0;
	}
	return v;
}

Vector new_order_vec(int i)
{
	Vector v;
	v.len = i;
	v.vec = malloc(i * sizeof(double));
	for (int l = 0; l < i; l++)
	{
		v.vec[l] = (double) l;
	}
	return v;
}

Vector new_rand_vec(int i)
{
	Vector v;
	v.len = i;
	v.vec = malloc(i * sizeof(double));
	for (int l = 0; l < i; l++)
	{
		v.vec[l] = (double) rand() / RAND_MAX*2.0 -1.0;
	}
	return v;
}

/*---------------------------*/

/*----------print----------*/

void print_vec(Vector v)
{
	printf("len = %i\n", v.len);
	for(int l = 0; l < v.len; l++)
	{
		printf("%lf\n", v.vec[l]);
	}
}

/*-------------------------*/

/*----------operation----------*/

void vec_new_val(Vector* v, int i, double x)
{
	if (i < 0 || i >= v->len) errx(1, "Vec_new_val : Invalid index");
	v->vec[i] = x;
}

void vec_add(Vector add, Vector* result)
{
	if(add.len != result->len) errx(1, "Vec_add : Vector size not valid");
	for(int l = 0; l < result->len; l++)
	{
		result->vec[l] += add.vec[l];
	}
}

void vec_scal_mult(double scal, Vector* result)
{
	for(int l = 0; l < result->len; l++)
	{
		result->vec[l] *= scal;
	}
}

double scalaire_product(Vector u, Vector v)
{
	if (u.len != v.len) errx(1, "Scal_product : Invalid size");
	double scal = 0;
	for(int l = 0; l < u.len; l++)
	{
		scal += u.vec[l] * v.vec[l];
	}
	return scal;
}

double vec_modul(Vector v)
{
	double result = 0;
	for(int i = 0; i < v.len; i++)
	{
		result += v.vec[i];
	}
	return result;
}

Vector vec_mult(Vector v1, Vector v2)
{
	if(v1.len != v2.len) errx(1, "Vec_mult : Invalid size");
	Vector v = new_null_vec(v1.len);
	for(int i = 0; i < v1.len; i++)
	{
		v.vec[i] = v1.vec[i] * v2.vec[i];
	}
	return v;
}

Vector vec_2(Vector v)
{
	return vec_mult(v, v);
}


/*-----------------------------*/

/*-------------------------------------------------------*/






/*--------------------links--------------------*/

Vector colon_vec(Matrice m, int i)
{
	if(i < 0 || i >=  m.dim1) errx(1, "Colon_vec : Invalid index");
	Vector v;
	v.len = m.dim2;
	v.vec = malloc(v.len * sizeof(double));
	for(int l = 0; l < v.len; l++)
	{
		v.vec[l] = m.mat[l * m.dim1 + i];
	}
	return v;
}

Vector line_vec(Matrice m, int i)
{
	if(i < 0 || i >= m.dim2) errx(1, "Line_vec : Invalid index");
	Vector v;
	v.len = m.dim1;
	v.vec = malloc(v.len * sizeof(double));
	for(int l = 0; l < v.len; l++)
	{
		v.vec[l] = m.mat[i * m.dim1 + l];
	}
	return v;
}

Matrice mat_colon(Vector v)
{
	Matrice m;
	m.dim1 = 1;
	m.dim2 = v.len;
	m.mat = malloc(v.len * sizeof(double));
	for(int l = 0; l < v.len; l++)
	{
		m.mat[l] = v.vec[l];
	}
	return m;
}

Matrice mat_line(Vector v)
{
	Matrice m = mat_colon(v);
	m.dim1 = m.dim2;
	m.dim2 = 1;
	return m;
}

Vector linear_vec(Matrice m, Vector v)
{
	if(m.dim1 != v.len) errx(1, "Linear_vec : Size error");
	Matrice n = mat_colon(v);
	n = mat_mult(m, n);
	return colon_vec(n, 0);
}

Vector anti_linear_vec(Vector v, Matrice m)
{
	if(m.dim2 != v.len) errx(1, "Anti_linear_vec : Size error");
	Matrice n = mat_line(v);
	n = mat_mult(n, m);
	return line_vec(n, 0);
}

Matrice creat_by_vec(Vector u, Vector v)
{
	return mat_mult(mat_colon(u), mat_line(v));
}

/*---------------------------------------------*/

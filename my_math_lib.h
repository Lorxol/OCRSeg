#ifndef MY_MATH_LIB_H
#define MY_MATH_LIB_H

/*---matrices---*/

/*----------*/

typedef struct Matrice Matrice;
struct Matrice
{
	double *mat;
	int dim1;
	int dim2;
};

/*----------*/

Matrice new_null_mat(int i, int j);

Matrice new_order_mat(int i, int j);

Matrice new_ID_mat(int i);

Matrice new_rand_mat(int i, int j);

/*----------*/

void print_mat(Matrice m);

/*----------*/

void mat_new_val(Matrice* m, int i, int j, double x);

void mat_add(Matrice add, Matrice* result);

void mat_scal_mult(double scal, Matrice* result);

Matrice mat_mult(Matrice m1, Matrice m2);


/*---vectors---*/

/*----------*/

typedef struct Vector Vector;
struct Vector
{
	double *vec;
	int len;
};

/*----------*/

Vector new_null_vec(int i);

Vector new_order_vec(int i);

Vector new_rand_vec(int i);

/*----------*/

void print_vec(Vector v);

/*----------*/

void vec_new_val(Vector* v, int i, double x);

void vec_add(Vector add, Vector* result);

void vec_scal_mult(double scal, Vector* result);

double scalaire_product(Vector u, Vector v);

double vec_modul(Vector v);

Vector vec_mult(Vector v1, Vector v2);

Vector vec_2(Vector v);

/*---links---*/


Vector colon_vec(Matrice m, int i);

Vector line_vec(Matrice m, int i);

Matrice mat_colon(Vector v);

Matrice mat_line(Vector v);

Vector linear_vec(Matrice m, Vector v);

Vector anti_linear_vec(Vector v, Matrice m);

Matrice creat_by_vec(Vector u, Vector v);

/*-----------*/

#endif

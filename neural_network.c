#include "my_math_lib.h"
#include "neural_network.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <math.h>

/*--------------------Layer function--------------------*/

/*----------creator----------*/

Layer new_layer(int p_num, int num,/* Type t*/ double lam)
{
	Layer l;
	l.weights = new_rand_mat(p_num, num);
	l.biais = new_rand_vec(num);
//	l.type = t;
	l.data_size = p_num;
	l.layer_size = num;
	l.lambda = lam;
	return l;
}

Layer new_null_layer(int p_num, int num,/* Type t*/ double lam)
{
	Layer l;
	l.weights = new_null_mat(p_num, num);
	l.biais = new_null_vec(num);
//	l.type = t;
	l.data_size = p_num;
	l.layer_size = num;
	l.lambda = lam;
	return l;
}

/*---------------------------*/

/*----------printor----------*/

void print_layer(Layer l)
{
	printf("input : %d\n", l.data_size);
	for(int i = 0; i < l.layer_size; i++)
	{
		for(int j = 0; j < l.data_size; j++)
		{
			printf("%lf ", l.weights.mat[i * l.data_size + j]);
		}
		printf(" %lf\n",l.biais.vec[i]);
	}
}

/*---------------------------*/

/*----------foreward----------*/

double sig(double val)
{
	return 1/(1 + exp(-val));
}
/*
double bin(double val)
{
	if(val > 0) return 1;
	return 0;
}

double lin(double val)
{
	if(val > 1) return 1;
	if(val < -1) return 0;
	return val/2 + 0.5;
}
*/
void sigmoid(Vector *v)
{
	for(int i = 0; i < v->len; i++)
	{
		v->vec[i] = sig(v->vec[i]);
	}	
}
/*
void binary(Vector *v)
{
	for(int i = 0; i < v->len; i++)
	{
		v->vec[i] = bin(v->vec[i]);
	}
}

void linear(Vector *v)
{
	for(int i = 0; i < v->len; i++)
	{
		v->vec[i] = lin(v->vec[i]);
	}
}
*/
Vector forward_step(Layer l, Vector data)
{
	if(data.len != l.data_size) errx(1, "Wrong size");
	Vector v = linear_vec(l.weights, data);
	vec_add(l.biais, &v);
/*	if(l.type == Sigmoid)
	{
*/	sigmoid(&v);
	return v;
/*	}
	if(l.type == Binary)
	{
		binary(&v);
		return v;
	}
	linear(&v);
	return v;
*/
}

/*----------------------------*/

/*----------backward----------*/

double sig_prim(double y)
{
	y = sig(y);
	return y * (1 - y);
}

void sigmoid_prim(Vector *v)
{
	for(int i = 0; i < v->len; i++)
	{
		v->vec[i] = sig_prim(v->vec[i]);
	}
}

Vector backward(Layer *l, Vector correct, Vector input)
{
	Vector prev_correct = anti_linear_vec(correct, l->weights);
	sigmoid_prim(&prev_correct);
	mat_add(creat_by_vec(correct, input), &(l->weights));
	vec_add(correct, &(l->biais));
	return prev_correct;
}

/*----------------------------*/

/*------------------------------------------------------*/



/*--------------------Network function--------------------*/

/*----------creator----------*/

Network new_network(int l_num, int l_size[],/* Type t*/ double lam)
{
	Network n;
//	n.type = t;
	n.lambda = lam;
	n.data_size = l_size[0];
	n.layer_num = l_num;
	n.layers = malloc(l_num * sizeof(Layer));
	for(int i = 0; i < l_num; i++)
	{
		n.layers[i] = new_layer(l_size[i], l_size[i + 1],/* t*/ lam);
	}
	return n;
}

Network new_null_network(int l_num, int l_size[],/* Type t*/ double lam)
{
	Network n;
//	n.type = t;
	n.lambda = lam;
	n.data_size = l_size[0];
	n.layer_num = l_num;
	n.layers = malloc(l_num * sizeof(Layer));
	for(int i = 0; i < l_num; i++)
	{
		n.layers[i] = new_null_layer(l_size[i], l_size[i + 1],/* t*/ lam);
	}
	return n;
}


/*---------------------------*/

/*----------printor----------*/

void print_network(Network n)
{
	printf("input : %d\n\n", n.data_size);
	for(int i = 0; i < n.layer_num; i++)
	{
		printf("layer :%d\n", i);
		print_layer(n.layers[i]);
	}
}

/*---------------------------*/

/*----------foreward----------*/

Vector forward(Network n, Vector data)
{
	if(data.len != n.data_size) errx(1, "Size error");
	for(int i = 0; i < n.layer_num; i++)
	{
		data = forward_step(n.layers[i], data);
	}
	return data;
}

/*----------------------------*/

/*----------backward----------*/

void train_exemple(Network *n, Vector error, Vector *input)
{
	int k = n->layer_num;
	for(int i = 1; i < k; i++)
	{
		error = backward(&(n->layers[k - i]), error, input[k - i - 1]);
	}
	mat_add(creat_by_vec(error, input[0]), &(n->layers->weights));
	vec_add(error, &(n->layers->biais));
}

void cost(Vector expected, Vector *NW_result)
{
	vec_scal_mult(-1, NW_result);
	vec_add(expected, NW_result);
//	vec_2(NW_result);
}

Vector* exemple_comput(Network n, Vector data)
{
	if(data.len != n.data_size) errx(1, "Size error");
	Vector *allout = malloc((n.layer_num + 1) * sizeof(Vector));
	allout[0] = data;
	for(int i = 0; i < n.layer_num; i++)
	{
		allout[i + 1] = forward_step(n.layers[i], allout[i]);
	}
	return allout;
}

double exemple_train(Network *n, Vector data, Vector expected)
{
	Vector *NW_answer = exemple_comput(*n, data);
	cost(expected, &(NW_answer[n->layer_num]));

	double coste = vec_modul(vec_2(NW_answer[n->layer_num]));
	train_exemple(n, NW_answer[n->layer_num], NW_answer);
	return coste;
}

void train(Network *n, Vector *exemples, double diff, int exemple_num)
{
	double x = 0;
	int turn = 0;
	do
	{
		x = 0;
		for(int i = 0; i < exemple_num; i++)
		{
			x += exemple_train(n, exemples[2 * i], exemples[2 * i + 1]);	
//			print_network(*n);
		}
		x = x / (double) exemple_num;
		printf("%lf", x);
		turn ++;
	} while(x > diff && turn < 13000);
}

/*----------------------------*/

/*--------------------------------------------------------*/

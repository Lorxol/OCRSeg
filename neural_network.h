#ifndef NETWORK_H
#define NETWORK_H
#include "my_math_lib.h"

/*-----type-----*/
/*
typedef enum Type Type;
enum Type
{
	Sigmoid = 0,
	Binary = 1,
	Linear = 2,
};
*/
/*--------------*/



/*-----layer-----*/

/*----------*/

typedef struct Layer Layer;
struct Layer
{
	Matrice weights;
	Vector biais;
//	Type type;
	int data_size;
	int layer_size;
	double lambda;
};

/*----------*/

Layer new_layer(int p_num, int num,/* Type t*/ double lam);

Layer new_null_layer(int p_num, int num, /*Type t*/ double lam);

/*----------*/

void print_layer(Layer l);

/*----------*/
double sig(double val);
/*
double bin(double val);

double lin(double val);
*/
void sigmoid(Vector *v);
/*
void binary(Vector v);

void linear(Vector v);
*/
Vector forward_step(Layer l, Vector data);

/*----------*/

double sig_prim(double y);

void sigmoid_prim(Vector *v);

Vector backward(Layer *l,Vector correct, Vector input);

/*----------*/

/*---------------*/



/*-----network-----*/

/*----------*/

typedef struct Network Network;
struct Network
{
	Layer *layers;
//	Type type;
	int data_size;
	int layer_num;
	double lambda;
};

/*----------*/

Network new_network(int l_num, int l_size[],/* Type t*/ double lam);

Network new_null_network(int l_num, int l_size[],/* Type t*/ double lam);

/*----------*/

void print_network(Network n);

/*----------*/

Vector forward(Network n, Vector data);

void train_exemple(Network *n, Vector error, Vector *input);

void cost(Vector expected, Vector *NW_result);

Vector* exemple_comput(Network n, Vector data);

double exemple_train(Network *n, Vector data, Vector expected);

void train(Network *n, Vector *exemples, double diff, int exemple_num);

/*-----------------*/






/*intern function*/

/*---------------*/

#endif

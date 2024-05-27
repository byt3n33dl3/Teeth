#ifndef SIMPLENET
#define SIMPLENET

#include "simplela.h"

struct SimpleNet;

typedef struct InputLayer {
	Vector input;
} InputLayer;

// Fully connection layer
typedef struct ConnectionLayer {
	int inputsize;
	int outputsize;
	Vector bias, biasDet;
	Mat weight, weightDet;
	Vector res, det;
} ConnectionLayer;

// Use for activation and softmax etc.
typedef struct TransformLayer {
	Vector res;
	Vector det;
} TransformLayer;

typedef struct SimpleNet
{
	int hiddenLayerNum;
	InputLayer inputLayer;
	ConnectionLayer *fls;// fully connection layers
	TransformLayer *tls;// transformation layers
	Vector *output;
} SimpleNet;

// Init the network, assign memory space to vectors and matrices
void initNetWork(SimpleNet *net, int layerNum, int *layerSize);

// Forward and compute the result as res value in Softmax/last layer
void forward(SimpleNet *net, double *input);
double l2loss(SimpleNet *net, int label);
void clear(SimpleNet *net);
// Backward, full batch
void backward(SimpleNet *net, int, void(*costFuncDet)(Vector *, Vector *, int), double sf);
void update(SimpleNet *net);

// Activation functions
double sigmoid(double num);
void acFun(Vector *act, Vector *output);
void softmax(Vector *input, Vector *output);

// Computing derivatives
double sigmoidDet(double num);
void acFunBack(Vector *input, Vector *res, Vector *det);
void softmaxBack(Vector *input, Vector *res, Vector *det);

// Determine which label it belongs to
int selectFirstBiggest(SimpleNet *net);
int selectFromOutput(SimpleNet * net);
int loss(SimpleNet *net, double *data);

// Cost Function

// Send derivative of cost function to last layer

#endif

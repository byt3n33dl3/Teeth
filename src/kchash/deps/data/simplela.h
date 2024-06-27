/*
    Simple linear algebra operation for the network
*/

#ifndef SIMPLELA
#define SIMPLELA
#include <stdbool.h>

typedef struct Vector
{
    double *data;
    int len;
} Vector;

typedef struct Mat
{
    double **data;
    int rowNum;
    int colNum;
} Mat;

double * getVecSpace(int size);
double ** getMatSpace(int inputLayerSize, int outputLayerSize);
void clearVector(Vector *vec);
void clearMat(Mat *mat);
void vplusv(Vector *vec, Vector *delta, double factor);
void vcpv(Vector *des, Vector *src);
void mplusm(Mat *m, Mat *dm, double factor);
void vmv(Vector *in_vec, Mat *mat, Vector *out_vec, bool mtrans);
void vvm(Vector *lvec, Vector *rvec, Mat *mat, double sf);
void printVector(Vector *vec);
void saveVector(Vector *v, char filename[]);
void loadVector(Vector *v, char filename[]);
void saveMat(Mat* m, char filename[]);
void loadMat(Mat *m, char filename[]);
#endif

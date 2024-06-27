#include "simplela.h"
#include <stdio.h>
#include <stdlib.h>

double * getVecSpace(int size) {
	double *vec = (double *)malloc(sizeof(double)*size);
	for (int i = 0; i < size; i++) {
		vec[i] = 0;
	}
	return vec;
}

double ** getMatSpace(int inputLayerSize, int outputLayerSize)
{
	int epsilon = 0.0012;
    double **mat = (double **)malloc(sizeof(double *)*inputLayerSize);
    int rowIndex, colIndex;
    for (rowIndex = 0; rowIndex < inputLayerSize; rowIndex++)
    {
        mat[rowIndex] = (double *)malloc(sizeof(double)*outputLayerSize);
        for (colIndex = 0; colIndex < outputLayerSize; colIndex++)
        {
			mat[rowIndex][colIndex] = 0.001*(double)rand()/(double)RAND_MAX - epsilon;
        }
    }
    return mat;
}

void clearVector(Vector *vec) {
	for (int i = 0; i < vec->len; i++) {
		vec->data[i] = 0;
	}
}

void clearMat(Mat *mat) {
	for (int i = 0; i < mat->rowNum; i++) {
		for (int j = 0; j < mat->colNum; j++) {
			mat->data[i][j] = 0;
		}
	}
}

void vplusv(Vector *vec, Vector *delta, double factor) {
	for (int i = 0; i < vec->len; i++) {
		vec->data[i] += factor*delta->data[i];
	}
}

void vcpv(Vector *des, Vector *src) {
	for (int i = 0; i < des->len; i++) {
		des->data[i] = src->data[i];
	}
}

void mplusm(Mat *m, Mat *dm, double factor) {
	for (int i = 0; i < m->rowNum; i++) {
		for (int j = 0; j < m->colNum; j++) {
			m->data[i][j] += factor*dm->data[i][j];
		}
	}
}

void vmv(Vector *in_vec, Mat *mat, Vector *out_vec, bool mtrans)
{
	// how to be execution efficient and code sufficient?
	// look at code below
    int counter1, counter2;
		if (!mtrans) {
			for (counter1 = 0; counter1 < out_vec->len; counter1++)
			{
					double tmp = 0;
					for (counter2 = 0; counter2 < in_vec->len; counter2++)
					{
							tmp += in_vec->data[counter2]*mat->data[counter2][counter1];
					}
					out_vec->data[counter1] = tmp;
			}
		}else {
			for (counter1 = 0; counter1 < out_vec->len; counter1++)
	    {
	        double tmp = 0;
	        for (counter2 = 0; counter2 < in_vec->len; counter2++)
	        {
	            tmp += in_vec->data[counter2]*mat->data[counter1][counter2];
	        }
	        out_vec->data[counter1] = tmp;
	    }
		}
}

void vvm(Vector *lvec, Vector *rvec, Mat *mat, double sf) {
	for (int i = 0; i < lvec->len; i++) {
		for (int j = 0; j < rvec->len; j++) {
			mat->data[i][j] += (sf)*lvec->data[i]*rvec->data[j];
		}
	}
}

void printVector(Vector *vec) {
	printf("Vector: ");
	for (int i = 0; i < vec->len; i++) {
		printf("%lf ", vec->data[i]);
	}
	printf("\n");
}

void saveVector(Vector *v, char filename[]) {
	FILE *f = fopen(filename, "w");//strcat(filename, ".csv")
	fprintf(f, "%d\n", v->len);
	if (v->len > 0) {
		fprintf(f, "%lf", v->data[0]);
	}
  for (int i = 1; i < v->len; i++) {
      fprintf(f, ",%lf", v->data[i]);
  }
	fprintf(f, "\n");
  fclose(f);
}

void loadVector(Vector *v, char filename[]) {
	FILE *f = fopen(filename, "r");//strcat(filename, ".csv")
	int tl;// tmp length
	fscanf(f, "%d\n", &tl);
	if (v->len > 0) {
		fscanf(f, "%lf", &v->data[0]);
	}
  for (int i = 1; i < v->len; i++) {
      fscanf(f, ",%lf", &v->data[i]);
  }
	fscanf(f, "\n");
  fclose(f);
}

void saveMat(Mat *m, char filename[]) {
  FILE *f = fopen(filename, "w");//strcat(filename, ".csv")
	fprintf(f, "%d,%d\n", m->rowNum, m->colNum);
  for (int i = 0; i < m->rowNum; i++) {
    if (m->colNum > 0) {
      fprintf(f, "%lf", m->data[i][0]);
      for (int j = 1; j < m->colNum; j++) {
        fprintf(f, ",%lf", m->data[i][j]);
      }
      fprintf(f, "\n");
    }
  }
  fclose(f);
}

void loadMat(Mat *m, char filename[]) {
	FILE *f = fopen(filename, "r");//strcat(filename, ".csv")
	int tmpRN, tmpCN;// RN: row number, CN: column number
	fscanf(f, "%d,%d\n", &tmpRN, &tmpCN);
	for (int i = 0; i < m->rowNum; i++) {
		if (m->colNum > 0) {
			fscanf(f, "%lf", &m->data[i][0]);
			for (int j = 1; j < m->colNum; j++) {
				fscanf(f, ",%lf", &m->data[i][j]);
			}
			fscanf(f, "\n");
		}
	}
	fclose(f);
}

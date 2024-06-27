#ifndef DATA_READER
#define DATA_READER
#include <stdio.h>

double **getData(char *path, int rowNum, int colNum); // Each row corresponds to a set of data like a image or something else
void readInData(double ***trainingData, double ***testData); // Load training data
void readInMiniData(double ***trainingData, int minTestPicNum); // Load first rows of trainingData for debugging
#endif

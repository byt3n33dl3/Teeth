// The data path is hard-coded in this part
#include "datareader.h"

void readInData(double ***trainingData, double ***testData)
{
    char trainingDataPath[100] = "data/train.csv";//"C:/emag/data/kaggle/minst/train.csv";
    char testDataPath[100] = "data/test.csv";//"C:/emag/data/kaggle/minst/test.csv";
    int trainingPicNum = 42000;
    int testPicNum = 28000;
    (*trainingData) = getData(trainingDataPath,trainingPicNum,785);
    (*testData) = getData(testDataPath,testPicNum,784);
}

void readInMiniData(double ***trainingData, int minTestPicNum)
{
    char trainingDataPath[100] = "data/train.csv";//"C:/emag/data/kaggle/minst/train.csv";
    int trainingPicNum = minTestPicNum;
    (*trainingData) = getData(trainingDataPath,trainingPicNum,785);
}

double ** getData(char *path, int rowNum, int colNum) //bool isTrainingData)
{
    FILE* dataFile = fopen(path, "r");
    if (dataFile == NULL) {
        printf("Check if file path is correct");
        exit(1);
    }
    char head[10000];
    fgets(head,10000,dataFile);
    double **data = (double **)malloc(sizeof(double*)*rowNum);
    int rowIndex,colIndex;
    char deliminator;
    int temp;
    for (rowIndex = 0; rowIndex < rowNum; rowIndex++)
    {
        data[rowIndex] = (double *)malloc(sizeof(double)*colNum);
        for (colIndex = 0; colIndex < colNum; colIndex++)
        {

            fscanf(dataFile,"%d%c",&temp,&deliminator);
            data[rowIndex][colIndex] = temp;
        }
    }
    fclose(dataFile);
    return data;
}

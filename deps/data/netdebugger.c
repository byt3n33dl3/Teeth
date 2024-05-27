#include "netdebugger.h"
#include "simplenet.h"
#include <stdio.h>
#include <string.h>

void printPath()
{
    char path[200];
    getcwd(path, 200);
    puts(path);
}

void printNet(SimpleNet *net) {
  for (int i = 0; i < net->hiddenLayerNum; i++) {
    printf("Fully Connection Layer %d res:\n", i);
    printVector(&net->fls[i].res);
    putchar('\n');

    printf("Fully Connection Layer %d det:\n", i);
    printVector(&net->fls[i].det);
    putchar('\n');

    printf("Translation Layer %d res:\n", i);
    printVector(&net->tls[i].res);
    putchar('\n');

    printf("Translation Layer %d det:\n", i);
    printVector(&net->tls[i].det);
    putchar('\n');
  }
}

//  void TestLongDouble()
//  {
//      /*
//     //Test if exp function works for double data type
//     double x = 0.00023;
//     printf("%lf",exp(x));
//     printf("%ld",sizeof(double));
//     */
//
//     //printf("%d %d %d %d",random(),random(), random(), random());
//     //double derivate = 0.0000001;
//  }
//
//
// void TestForwardPass(double **data, int dataRowNum, SimpleNet *net)
// {
//
//     //Test a typical forward pass of the network and get ratio of right/all on training set
//     int counter1, counter2, rightAns = 0, wrongAns = 0;//Max index = label means it's right
//
//     // In MINST, we call the data row pic stands for picture
//     for (counter1 = 0; counter1 < dataRowNum; counter1++)
//     {
//         double *pic = (double *)data[counter1];
//         pic++;
//
//         fullPass(pic, net);
//
//         /*
//         printf("Pic %6d passed the net and it's an %d answer",counter1,(maxAt == trainingData[counter1][0]));
//         getchar();
//         */
//         //printf("\a\a%d%%",(int)(100.0*counter1/42000.0));
//
//         // Select and compare result with groud truth where 0~9 corresponds to digits 0~9
//         int maxAt = selectFromOutput(net);
//
//         //printf("Selected %d\n",maxAt);
//         printf("Select %d as %d is right\n", maxAt, (int)data[counter1][0]); // Used for debugging when selectFromOutput act in wrong way
//
//         // Ground truth is noted at the head
//         if (maxAt == (int)data[counter1][0])
//             rightAns++;
//         else
//             wrongAns++;
//     }
//
//     printf("\n%d right answer among %d pics in training data, you scored %lf",rightAns, dataRowNum, (rightAns*1.0/dataRowNum));
//
// }
//
// void testDL2LD()
// {
//     double a = 3;
//     double b = 2;
//     a = b;
//     b = a;
//     double *pa = &a;
//     double *pb = &b;
// }
//
// // vMv works well, although quite tough to debug as using array failed, forced to use pointers
// void testvMv()
// {
//     double *v1 = (double *)malloc(sizeof(double)*2);
//     v1[0] = 1; v1[1] = 2;
//     double **M = (double **)malloc(sizeof(double *)*2);
//     M[0] = (double *)malloc(sizeof(double)*3);
//     M[1] = (double *)malloc(sizeof(double)*3);
//     M[0][0] = 1; M[0][1] = 0.5; M[0][2] = 0.2;M[1][0] = 0.3; M[1][1] = 0.4; M[1][2] = -2;
//     double *v2 = (double *)malloc(sizeof(double)*3);
//     vMv(v1, 2, M, v2, 3);
//     printf("%lf %lf %lf",v2[0], v2[1], v2[2]);
//     getchar();
// }
//
// void testAcfun()
// {
//     double arr[4] = {0,2,3,4};
//     actFun((double *)arr, 4);
//     if (arr[0] == 0.5)
//     {
//         printf("Activition function works fine\n");
//     }else{
//         //fprintf(stderr, "Problem with Activition function\n");
//     }
// }
//
// void printArr(double *arr, int length)
// {
//     printf("\n");
//     int ctr = 0;
//     while (ctr < length)
//     {
//         printf("%lf ", arr[ctr]);
//         ctr++;
//     }
// }

#ifndef NET_DEBUGGER
#define NET_DEBUGGER
#include "simplela.h"
#include "simplenet.h"
// Testing units to get rid of confusion when coding

// Print current path
void printPath();

// Print inner state of network
void printNet(SimpleNet *net);

// Data type test
void TestLongDouble();
void testDL2LD(); // Test if double and double is the same as I mix the use of them together

// Forward pass test
void TestForwardPass(double **data, int dataRowNum, SimpleNet *net);

// Matrix manipluation test
void testvMv();
void testAcfun();

// Part for debugging, printf collection
void printArr(double *arr, int length);

#endif

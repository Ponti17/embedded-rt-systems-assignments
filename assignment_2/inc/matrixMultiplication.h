//
// Created by alext on 03-10-2024.
//

#ifndef MATRIXMULTIPLICATION_H
#define MATRIXMULTIPLICATION_H

#include <stdio.h>
#include <xil_printf.h>

#define MATRIX_SIZE 4

typedef union {
  unsigned char comp[MATRIX_SIZE];
  unsigned int vect;
} vectorType;

typedef vectorType vectorArray[MATRIX_SIZE];

vectorArray aInst, bTInst, pInst;

void setInputMatrices(vectorArray matrixA, vectorArray matrixB);
void displayMatrix(vectorArray matrix);
void multiplyMatricesSoft(vectorArray matrixA, vectorArray matrixB, vectorArray matrixP);
void multiplyMatricesHard(vectorArray matrixA, vectorArray matrixB, vectorArray matrixP);

#endif //MATRIXMULTIPLICATION_H

#include "matrixMultiplication.h"
#include "xil_io.h"

void setInputMatrices(vectorArray matrixA, vectorArray matrixB)
{
    for (int row = 0; row < MATRIX_SIZE; row++) {
        for (int col = 0; col < MATRIX_SIZE; col++) {
          matrixA[row].comp[col] = MATRIX_SIZE * row + 1 + col;
          matrixB[row].comp[col] = row + 1;
        }
    }
}

void displayMatrix(vectorArray matrix)
{
    for (int row = 0; row < MATRIX_SIZE; row++)  {
        for (int col = 0; col < MATRIX_SIZE; col++) {
            xil_printf("%d\t", matrix[row].comp[col]);
        }
        xil_printf("\r\n");
    }
}

void multiplyMatricesSoft(vectorArray matrixA, vectorArray matrixB, vectorArray matrixP)
{
    for (int row = 0; row < MATRIX_SIZE; row++) {
        for (int col = 0; col < MATRIX_SIZE; col++) {
            matrixP[row].comp[col] = 0;
            for (int i = 0; i < MATRIX_SIZE; i++) {
                matrixP[row].comp[col] += matrixA[row].comp[i] * matrixB[col].comp[i];
            }
        }
    }
}

void multiplyMatricesHard(vectorArray matrixA, vectorArray matrixB, vectorArray matrixP)
{
	for (int row = 0; row < MATRIX_SIZE; row++) {
		for (int col = 0; col < MATRIX_SIZE; col++) {
			Xil_Out32(XPAR_MATRIX_IP_S00_AXI_BASEADDR + MATRIX_IP_S_AXI_SLV_REG0_OFFSET, matrixA[row].vect);
			Xil_Out32(XPAR_MATRIX_IP_S00_AXI_BASEADDR + MATRIX_IP_S_AXI_SLV_REG1_OFFSET, matrixB[col].vect);
			matrixP[row].comp[col] = Xil_In32(XPAR_MATRIX_IP_S00_AXI_BASEADDR + MATRIX_IP_S_AXI_SLV_REG2_OFFSET);
		}
	}
}

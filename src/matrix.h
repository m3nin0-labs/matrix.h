#ifndef MATRIX_HEADER
#define MATRIX_HEADER

#include <stdlib.h>
#include <malloc.h>

typedef struct aux {
    float** data;
    int col, row;
} Matrix;


/**
 * Function: m
 * -----------------
 * Function to create an MxN array
 * 
 * row: Number of rows
 * col: Number of cols
 * 
 * returns: An matrix
 */
Matrix * m(int row, int col) {
    float **mat;

    mat = (float **) malloc(row * sizeof(float*));
    for(int i = 0; i < row; i++) {
        mat[i] = (float *) malloc(col * sizeof(float));
    }

    // Generate a matrix
    Matrix * mm = (Matrix*) malloc(sizeof(Matrix));
    mm->data = mat;
    mm->col = col;
    mm->row = row;

    return mm;
}

/**
 * Function: magic
 * -----------------
 * Create random values in matrix
 * 
 * matrix: Matrix struct
 * 
 */
void magic(Matrix * matrix) {
    for(int i = 0; i < matrix->row; i++) {
        for(int j = 0; j < matrix->col; j++) {
            matrix->data[i][j] = rand();
        }
    }
}

/**
 * Function: zeros
 * -----------------
 * fills the inserted matrix with zero values
 * 
 * matrix: Matrix struct
 * 
 */
void zeros(Matrix * matrix) {
    for(int i = 0; i < matrix->row; i++) {
        for(int j = 0; j < matrix->col; j++) {
            matrix->data[i][j] = 0;
        }
    }
}

/**
 * Function: mprint
 * -----------------
 * display matrix elements
 * 
 * matrix: Matrix struct
 * 
 */
void mprint(Matrix * matrix) {
    for(int i = 0; i < matrix->row; i++) {
        for(int j = 0; j < matrix->col; j++) {
            printf("%f\n", matrix->data[i][j]);
        }
    }
}

/**
 * Function: matmul
 * -----------------
 * Function to element-wise matrix mul
 * 
 * m1: Matrix
 * m2: Matrix
 * 
 * returns: An matrix
 */
Matrix * matmul(Matrix * m1, Matrix * m2) {
    if (m1->col != m2->col || m1->col != m2->col) {
        perror("Matrix dimensions must be the same for matmul");
    }

    // Create the result matrix
    Matrix * resultMatrix = m(m1->row, m1->col);

    for(int i = 0; i < m1->row; i++) {
        for(int j = 0; j < m1->col; j++) {
            resultMatrix->data[i][j] = m1->data[i][j] * m2->data[i][j];
        }
    }
    return resultMatrix;
}

#endif

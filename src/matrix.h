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
            printf("%f ", matrix->data[i][j]);
        }
        printf("\n");
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
        return NULL;
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

/**
 * Function: row
 * -----------------
 * Retrieve a specific row from matrix
 * 
 * matrix: Matrix
 * row: row number
 * 
 * returns: array with row values
 */
float * row(Matrix * matrix, int row) {
    if (matrix->row < row) {
        perror("Invalid row number");
        return NULL;
    }

    return matrix->data[row];
}

/**
 * Function: col
 * -----------------
 * Retrieve a specific col from matrix
 * 
 * matrix: Matrix
 * col: col number
 * 
 * returns: array with col values
 */
float * col(Matrix * matrix, int col) {
    if (matrix->col < col) {
        perror("Invalid col number");
        return NULL;
    } 
    
    // Malloc
    float * mcol = (float *) malloc(matrix->row * sizeof(float)); 
    for(int i = 0; i < matrix->row; i++) {
        mcol[i] = matrix->data[i][col];
    }
    return mcol;
}

/**
 * Function: rowcol
 * -----------------
 * Retrieve a specific col and row from matrix
 * 
 * matrix: Matrix
 * col: col number
 * row: row number
 * 
 * returns: colrow value
 */
float rowcol(Matrix * matrix, int col, int row) {
    if (matrix->col < col || matrix->row < row) {
        perror("Invalid index number");
    }

    return matrix->data[row][col];
}

/**
 * Function: length
 * -----------------
 * retrieve full matrix dimension
 * 
 * matrix: Matrix
 * 
 * returns: matrix dimension (row * col)
 */
int length(Matrix * matrix) {
    return matrix->col * matrix->row;
}

/**
 * Function: arange
 * -----------------
 * Generate set of values ​​within a defined range
 * 
 * start: Initial value
 * end: final value
 * step: step where values ​​change
 * 
 * returns: array with generated values
 */
float * arange(int start, int end, int step) {
    if (start >= end) {
        perror("Start value must be less than end value");
        return NULL;
    }

    float * marange = (float *) malloc(((start + end) / step) * sizeof(float));
    
    size_t idx = 0;
    for (size_t i = start; i <= end; i += step) {
        marange[idx] = i;

        idx += 1;
    }
    return marange;
}

/**
 * Function: sdiagonal
 * -----------------
 * walk through the full diagonals of the matrix
 * 
 * matrix: Matrix
 * reverse: flag to indicate if the slide should be done in reverse
 * 
 * returns: Generated matrix
 */
Matrix * sdiagonal(Matrix * matrix) {
    float ** mdiagonal = (float **) malloc(sizeof(float) * (matrix->row));

    for(size_t i = 0; i < matrix->row; i++) {
        mdiagonal[i] = (float *) malloc(sizeof(float) * matrix->col - 3);
        for(size_t j = 0; j < matrix->col - 3; j++) {     
            mdiagonal[i][j] = matrix->data[i][i+j]; 
        }
    }

    Matrix * mm = (Matrix*) malloc(sizeof(Matrix));
    mm->data = mdiagonal;
    mm->col = matrix->col - 3;
    mm->row = matrix->row;

    return mm;
}

/**
 * Function: sdiagonalreverse
 * -----------------
 * walk through the full diagonals of the matrix (In reverse mode)
 * 
 * matrix: Matrix
 * reverse: flag to indicate if the slide should be done in reverse
 * 
 * returns: Generated matrix
 */
Matrix * sdiagonalreverse(Matrix * matrix) {
    // Configure the reverse
    size_t colindex;

    float ** mdiagonal = (float **) malloc(sizeof(float) * (matrix->row));

    for(size_t i = 0; i < matrix->row; i++) {
        mdiagonal[i] = (float *) malloc(sizeof(float) * matrix->col - 3);
        colindex = 0;
        for(size_t j = matrix->col; j > 3; j--) {
            mdiagonal[i][colindex] = matrix->data[i][j - (i + 1)]; 
            colindex += 1;
        }
    }

    Matrix * mm = (Matrix*) malloc(sizeof(Matrix));
    mm->data = mdiagonal;
    mm->col = matrix->col - 3;
    mm->row = matrix->row;

    return mm;
}

/**
 * Function: msum
 * -----------------
 * sum all elements of each column
 * 
 * matrix: Matrix
 * 
 * returns: vector with each column sum
 */
float * msum(Matrix * matrix) {
    float * temp;
    float * sumarray = (float *) malloc(sizeof(float) * matrix->col);

    for(size_t i = 0; i < matrix->col; i++) {
        temp = col(matrix, i);
        for(size_t j = 0; j < matrix->row; j++) {
            sumarray[i] += temp[j];
        }
    }
    return sumarray;
}

/**
 * Function: mcolcat
 * -----------------
 * concatenate to matrix columns
 * 
 * matrix: Matrix
 * 
 * returns: Generated matrix
 */
Matrix * mcolcat(Matrix * m1, Matrix * m2) {
    if (m1->col != m2->col) {
        perror("Columns must match for mcolcat");
        return NULL;
    }
    if (m1->row != m2->row)
        perror("Matrix have different row quantities. Concatenation will only be done at equivalent row positions");
    
    size_t colindex = 0;
    size_t ncolsize = m1->col + m2->col; // new column dimension

    Matrix * pmatrix = m1;
    Matrix * nmatrix = m(m1->row, ncolsize);

    for(size_t i = 0; i < ncolsize; i++){
        for(size_t j = 0; j < m1->row; j++) 
            nmatrix->data[j][i] = pmatrix->data[j][i - colindex];

        // Change matrix reference
        if (i == m1->col-1 && colindex == 0) {
            pmatrix = m2;
            colindex = i+1;
        }
    }
    return nmatrix;
}

#endif

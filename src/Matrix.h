#include <math.h>
#ifndef MATRIX_H_
#define MATRIX_H_


int zero(int *M, int m, int n);
int mult(int *M3, int *M1, int *M2);


/*
typedef struct matrix {
	int rows;
	int cols;
	double * data;
} matrix;
matrix * newMatrix(int rows, int cols);
int nRows(matrix * mtx, int * n);
int nCols(matrix * mtx, int *n);
int printMatrix(matrix * mtx);

matrix * newMatrix(int rows, int cols) ;

 Deletes a matrix.  Returns 0 if successful and -1 if mtx
 * is NULL.

int deleteMatrix(matrix * mtx);

#define ELEM(mtx, row, col) \
  mtx->data[(col-1) * mtx->rows + (row-1)]

 Copies a matrix.  Returns NULL if mtx is NULL.

matrix * copyMatrix(matrix * mtx) ;

 Sets the (row, col) element of mtx to val.  Returns 0 if
 * successful, -1 if mtx is NULL, and -2 if row or col are
 * outside of the dimensions of mtx.

int setElement(matrix * mtx, int row, int col, double val);

 Sets the reference val to the value of the (row, col)
 * element of mtx.  Returns 0 if successful, -1 if either
 * mtx or val is NULL, and -2 if row or col are outside of
 * the dimensions of mtx.

int getElement(matrix * mtx, int row, int col,
               double * val) ;


 Writes the transpose of matrix in into matrix out.
 * Returns 0 if successful, -1 if either in or out is NULL,
 * and -2 if the dimensions of in and out are incompatible.

int transpose(matrix * in, matrix * out) ;

 Writes the sum of matrices mtx1 and mtx2 into matrix
 * sum. Returns 0 if successful, -1 if any of the matrices
 * are NULL, and -2 if the dimensions of the matrices are
 * incompatible.

int sum(matrix * mtx1, matrix * mtx2, matrix * sum) ;

 Writes the product of matrices mtx1 and mtx2 into matrix
 * prod.  Returns 0 if successful, -1 if any of the
 * matrices are NULL, and -2 if the dimensions of the
 * matrices are incompatible.

int product(matrix * mtx1, matrix * mtx2, matrix * prod);
 Writes the dot product of vectors v1 and v2 into
 * reference prod.  Returns 0 if successful, -1 if any of
 * v1, v2, or prod are NULL, -2 if either matrix is not a
 * vector, and -3 if the vectors are of incompatible
 * dimensions.

int dotProduct(matrix * v1, matrix * v2, double * prod);

int identity(matrix * m) ;

int isSquare(matrix * mtx) ;

int isDiagonal(matrix * mtx);

int isUpperTriangular(matrix * mtx);

int diagonal(matrix * v, matrix * mtx);

*/





#endif /* MATRIX_H_ */

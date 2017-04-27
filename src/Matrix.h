
#ifndef MATRIX_H_
#define MATRIX_H_

typedef struct Matrix{
	int row;
	int column;
	double **elem;
} Matrix;

int zero(Matrix *M, int m, int n);

int mult(Matrix *M3, Matrix *M1, Matrix *M2);

#endif /* MATRIX_H_ */

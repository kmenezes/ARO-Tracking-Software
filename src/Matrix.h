/*
 * Matrix.h
 *
 *  Created on: Mar 4, 2017
 *      Author: james
 */


#ifndef MATRIX_H_
#define MATRIX_H_
typedef struct Matrix {
	int row;
	int column;
	double **matrix;
} Matrix;
int zero(Matrix *M,int m,int n);
int mult(Matrix *M3,Matrix *M1 ,Matrix *M2);
#endif /* MATRIX_H_ */

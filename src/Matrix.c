/*
 * Matrix.c
 *
 *  Created on: Mar 4, 2017
 *      Author: james
 */

#include "Matrix.h"
#include <Math.h>
#include <stdlib.h>
#include <stdio.h>

int zero(Matrix *M,int m,int n){
	M->matrix = (double **)calloc(m,sizeof(double));
	int count = 0;
	while(count<m){
		double *a = calloc(n,sizeof(double));
		M->matrix[count]= a;
		count = count +1;
	}
	M->row=m;
	M->column = n;
	return 0;
}
int mult(Matrix *M3,Matrix *M1 ,Matrix *M2){
	int jm = M1->row;
	int jn = M2->column;
	zero(M3, jm, jn);
	int i = 0;
	int j = 0;
	int k = 0;
	int g = 0;
	double sum1;
	double sum2;
	//double sum = 0;
	int maxi = M1->row-1;
	int maxj = M2->column-1;
	if(maxi!=maxj){
	}else{
		double sum = 0;
		if(maxi==maxj){
			while(i<=maxi){
				while (j<=maxj){
					sum1=M1->matrix[k][g];
					sum2=M2->matrix[j][i];
					sum=sum1*sum2+sum;
					j =j+1;
					g= g+1;
				}
				j=0;
				g=0;
				M3->matrix[k][i] = sum;
				sum=0;
				if(i==maxi){
					if(k==maxj){
						return 0;
					}
					k=k+1;
					i = -1;}
				i = i+1;}}}
	return 0;
}


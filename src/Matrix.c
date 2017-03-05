
#include "Matrix.h"
#include <Math.h>
#include <stdlib.h>

/*
 * initializes an mxn matrix filled with zeroes
 */
int zero(int *M, int m, int n){
	int i, j;
	int a[m][n];
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			a[i][j]=0;
		}
	}
	M=&a;
	return 0;
}

/*
 * Calculates an mxn matrix which is the product of M1 (mxp) and M2 (pxn)
 * Note: size of M1 (#columns) must match that of M2 (#rows)
 */
int mult(int *M3, int *M1, int *M2){
	int m1, p1, p2, n2;

	m1 = sizeof(M1)/sizeof(M1[0]);
	p1 = sizeof(M1[0])/sizeof(double);
	p2 = sizeof(M2)/sizeof(M2[0]);
	n2 = sizeof(M2[0])/sizeof(double);

	if(M3==NULL){
		return -1;
	}
	else if(p1!=p2){
		return -1;
	}

	int i, j, k;
	int sum=0;

	for(i=0;i<m1;i++){
		for(j=0;j<p1;j++){
			for(k=0;k<p2;k++){
				sum=sum+M1[i][j]*M2[k][j];
			}
			M3[i][j]=sum;
			sum=0;
		}
	}

	return 0;
}

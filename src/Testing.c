/*
 * Testing.h
 *
 *  Created on: Mar 4, 2017
 *      Author: keith
 */
#include "Basic.h"
#include "FileIO.h"
#include "Vector.h"
#include "DateAndTimeCalculations.h"
#include "Matrix.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	printf("-----------------------------------\n\n");
	printf("Welcome to P1 by James and Keith!\n\n");
	printf("-----------------------------------\n");
	printf("Testing of Basic Functions:\n\n");
	printf("testing of cosm1 with input 0.3:\n");
	printf("%f\n", cosm1(0.3));
	printf("\n");
	printf("testing of cosm1 with input -0.3:\n");
	printf("%f\n", cosm1(-0.3));
	printf("\n");
	printf("-----------\n");
	printf("testing of sinm1 with input 0.3:\n");
	printf("%f\n", sinm1(0.3));
	printf("testing of sinm1 with input -0.3:\n");
	printf("%f\n", sinm1(-0.3));
	printf("\n");
	printf("-----------\n");
	printf("testing of fixang with input of 10:\n");
	printf("%f\n", fixang(10));
	printf("\n");
	printf("-----------\n");
	printf("testing of frac with input of -23.77:\n");
	printf("%f\n", frac(-23.77));
	printf("testing of frac with input of 23.77:\n");
	printf("%f\n", frac(23.77));
	printf("\n");
	printf("-----------\n");
	printf("\n\nTesting of Vector Functions:\n\n");
	printf("testing of myangle:\n");
	printf("First Vector 5,5,4 with mag 8.12 \n");
	printf("Second Vector 2,3,-4 with mag 5.39 \n");
	Vector *v1;
	v1 = (Vector*)malloc(sizeof(Vector));
	v1->x = 5; v1->y = 5; v1->z = 4; v1->mag = 8.12;
	Vector *v2;
	v2 = (Vector*)malloc(sizeof(Vector));
	v2->x = 2; v2->y = 3; v2->z = -4; v2->mag = 5.39;
	printf("The angle should be 1.363683 function returns: %f\n", myangle(v1,v2));
	printf("-----------\n");
	printf("testing of magntd:\n");
	printf("Created 3rd Vector 2,3,6 with mag 7 \n");
	Vector v3; v3.x = 2; v3.y = 3; v3.z = 6; v3.mag = 7;
	printf("%f\n", magntd(v3));
	printf("-----------\n");
	printf("testing of mycross, should result in 0 return:\n");
	Vector *v4;
	v4 = (Vector*)malloc(sizeof(Vector));
	printf("%d\n",mycross(v4,v1,v2));
	printf("My cross of First and Second should be -23,28,5, with mag 42.814 and returns\n");
	printf("x=%f\n",v4->x);
	printf("y=%f\n",v4->y);
	printf("z=%f\n",v4->z);
	printf("mag=%f\n",v4->mag);
	printf("\n");
	printf("-----------\n");

	printf("testing of vecadd of Frist and Second vector should return 7,8,0 with mag 10.63:\n");
	Vector *v5;
	v5 = (Vector*)malloc(sizeof(Vector));
	vecadd(v5,v1,v2);
	printf("x=%f\n",v5->x);
	printf("y=%f\n",v5->y);
	printf("z=%f\n",v5->z);
	printf("mag=%f\n",v5->mag);
	printf("-----------\n");
	printf("\n\nTesting of Matrix Functions:\n\n");
	printf("testing of zero by initializing a 2x2 matrix:\n");
	Matrix mA;
	zero(&mA,2,2);
	printf("%f ", mA.matrix[0][0]); printf("%f\n", mA.matrix[1][0]);
	printf("%f ", mA.matrix[0][1]); printf("%f\n", mA.matrix[1][1]);
	printf("-----------\n");
	printf("testing of mult of 5,4;2,3 and 8,7;6,4 should return 54,53;38,36:\n");
	Matrix mB;
	Matrix mC;
	Matrix mD;
	zero(&mB,2,2);
	zero(&mC,2,2);
	mB.matrix[0][0] = 5; mB.matrix[1][0] = 4; mB.matrix[0][1] = 2; mB.matrix[1][1] = 3;
	mC.matrix[0][0] = 8; mC.matrix[1][0] = 7; mC.matrix[0][1] = 6; mC.matrix[1][1] = 4;
	mult(&mD,&mB,&mC);
	printf("%f ", mD.matrix[0][0]); printf("%f\n", mD.matrix[1][0]);
	printf("%f ", mD.matrix[0][1]); printf("%f\n", mD.matrix[1][1]);
	printf("-----------\n");
	printf("\n\nTesting of Fate and Time Calculations Functions:\n\n");
	printf("testing of jdaty with 2009:\n");
	printf("%f\n",jdaty(2009));
	printf("-----------\n");
	printf("testing of jdatep with 09054.71335794:\n");
	printf("%f\n",jdatep(09054.71335794));
	printf("-----------\n");
	printf("testing of doy with 2009 3 14:\n");
	printf("%f\n",doy(2009,3,14));
	printf("-----------\n");
	printf("testing of frcofd with 12,3,14.1234567890124:\n");
	printf("%f\n",frcofd(12,3,14.1234567890124));
	printf("-----------\n");
	printf("testing of dat2jd with 1997-02-24 19:11:00:\n");
	char a[] = "1997-02-24 19:11:00";
	printf("%f\n",dat2jd(a));
	printf("-----------\n");
	printf("testing of jd2dat with 2454101.1111:\n");
	printf("%s\n", jd2dat(2454101.1111));
	printf("-----------\n");
	printf("testing of curday:\n");
	printf("%s\n", curday());
	printf("-----------\n");
	printf("\n\nTesting of FileIO Functions:\n\n");
	printf("testing of Banner:\n");
	Banner();
	printf("-----------\n");
	printf("testing of ReadStationFile using station file.dat, displaying only name:\n");
	Station *stn = (Station*) malloc(sizeof(Station));
	ReadStationFile(stn, '0');
	printf("%s", stn->name);
	printf("-----------\n");
	printf("testing of ReadNoradLTE using TLE.dat, displaying only raan:\n");
	Satellite *sat = (Satellite*) malloc(sizeof(Satellite));
	ReadNoradTLE(sat, '0','1','2');
	printf("%f\n", sat->raan);
	printf("-----------\n");
	printf("testing of ERRMSG with input of \"error\":\n");
	char S[] = "error";
	ERRMSG(S);
	printf("-----------\n");
	return 0;
}

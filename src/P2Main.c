#include <stdio.h>
#include <math.h>
#include "Propagate.h"
#include "Basic.h"
#include "FileIO.h"
#include "Vector.h"
#include "DateAndTimeCalculations.h"
#include "Matrix.h"
#include "Vector.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PI 3.1415926535897932384626433832795028841971693993751058209749445923

int main(){
	printf("------------------------------------------\n");
	printf("\n Welcome to P2 by James and Keith\n\n");
	printf("------------------------------------------\n");

	double t[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		int size = 10;
		//char centralbody[] = "Earth";
		char coordinatesys[] = "J2000";
		struct Vector p[size];
		struct Vector v[size];
		for(int i=0; i<size; i++){
			p[i].x = i+100;
			p[i].y = i+100;
			p[i].z = i+100;
		}
		for(int i=0; i<size; i++){
			v[i].x = i+100;
			v[i].y = i+100;
			v[i].z = i+100;
	 	}

		STKout(t, size, coordinatesys, p, v);
/*
struct Vector position[2];
struct Vector velocity[2];

	Vector position[2] = {
			{ x: 1, y: 1, z: 0, mag: 1 },
			{ x: 1, y: 1, z: 0, mag: 1 },{ x: 1, y: 1, z: 0, mag: 1 },
	};

	Vector velocity[2] = {
			{ x: 1, y: 1, z: 0, mag: 1 },
			{ x: 1, y: 1, z: 0, mag: 1 },{ x: 1, y: 1, z: 0, mag: 1 },
	};
*/

/*
	Vector *p1;
	p1=(Vector*)malloc(2*sizeof(Vector));
	p1->x=1;
	p1->y=2;
	p1->z=3;
	Vector *p2;
	p2=(Vector*)malloc(2*sizeof(Vector));
	p2->x=3;
	p2->y=4;
	p2->z=5;
	Vector *v1;
	v1=(Vector*)malloc(2*sizeof(Vector));
	v1->x=1;
	v1->y=2;
	v1->z=3;
	Vector *v2;
	v2=(Vector*)malloc(2*sizeof(Vector));
	v2->x=3;
	v2->y=4;
	v2->z=5;
*/

	/*	Vector pos[2] = {p1, p2};
	Vector vel[2] = {v1, v2};*/
//	Matrix mB;
//	Matrix mC;
/*
	zero(&mB,1);
	zero(&mC,1);
	mB.matrix[0] = p1; mB.matrix[1] = p1;
	mC.matrix[0] = v1; mC.matrix[1] = v2;
*/
	//char Earth = "Earth";
/*
	double time[2] = {01012010, 01022010};
	STKout(*time, 1, "Earth", *position, *velocity);*/
	/*
	printf("------------Test the Station ecf----------------\n");


	Vector *s;
		s=(Vector*)malloc(2*sizeof(Vector));
		s->x=0;
		s->y=0;
		s->z=0;

		station_ECF(s, 45, 45, 45);
		printf("station_ECF:  X=%f  Y=%f  Z=%f", s->x, s->y, s->z);

		printf("------------------------------------------\n");

	printf("------------------------------------------\n");
	printf("Testing Kepler's Equation\n");
	printf("----------------------\n");
	printf("---------85.943699980374-------------\n");
	double ecc,ecc2,ecc3,ecc4;
	printf("\nTesting Circular Mean anom = 3.6029 and Ecc = 0.0\n");
	ecc = KeplerEqn(3.6029,0.0);
	printf("%f\n" ,ecc);

	printf("\nFor circular it should result in the mean anom-------\n");

	printf("\nTesting eccentric Mean anom = 3.6029 = 206.430964 degrees and Ecc = 0.37255----in radians\n");
	ecc2 = KeplerEqn(3.6029,0.37255);
	printf("%f\n" ,ecc2);

	printf("\n----------------------\n");


	double true = trueanom(0.37255, ecc2);
	printf("\n-----here come the cunt------------\n");
	printf("%f\n" ,true);
	printf("\n----------------------\n");


	printf("\nshould result in 199.35619827991917 or 3.4794220442346146527 rads\n");

	printf("\nTesting Elliptic Mean anom =1.5 and Ecc = 0.8\n");
	ecc3 = KeplerEqn(1.5,0.8);
	printf("%f\n" ,ecc3);
	printf("\n Should result in 2.1635326743829743634 or 123.96129108110373807 degrees");

	printf("Testing Parabolic orbit Mean anom = 1.5 and Ecc = 1.0\n");
	ecc4 = KeplerEqn(1.5,1.0);
	printf("%f\n" ,ecc4);

	printf("\nTesting Hyperbolic Mean anom = 40.69 and Ecc =  2.7696-------\n");
	ecc = KeplerEqn(40.69, 2.7696);
	printf("%f\n" ,ecc);
	printf("\n should return Hyperbolic eccentric anomaly = 3.46309--------------------\n");*/

	//	printf("----------------------\n");	printf("----------------------\n");	printf("----------------------\n");
	//double ans =  mean_anomaly_motion (Mt_mean_anomaly,  nt_mean_motion, time,  ts_sat_epoch, M0_mean_anomaly, n_mean_motion, n_dot_mean_motion, n_2dots_mean_motion);

	return 0;
}


#include <stdio.h>
#include <math.h>
#include "Propagate.h"
#include "Basic.h"
#include "FileIO.h"
#include "Vector.h"
#include "DateAndTimeCalculations.h"
#include "Matrix.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PI 3.1415926535897932384626433832795028841971693993751058209749445923

int main(){
	printf("----------------------\n");
	printf("\n Welcome to P2 by James and Keith\n\n");
	printf("----------------------\n");

	double Mt_mean_anomaly = 5;
	double nt_mean_motion = 120;
	double time = 500000; double ts_sat_epoch = 25000;
	double M0_mean_anomaly = 120;
	double n_mean_motion = 500;
	double n_dot_mean_motion = 500;
	double n_2dots_mean_motion = 500;
	double ans =  mean_anomaly_motion (Mt_mean_anomaly,  nt_mean_motion, time,  ts_sat_epoch, M0_mean_anomaly, n_mean_motion, n_dot_mean_motion, n_2dots_mean_motion);
	printf("\n----------------------\n");
	printf("%f\n", ans);
			printf("----------------------\n");
	printf("Testing Kepler's Equation\n");
	printf("----------------------\n");
	printf("---------85.943699980374-------------\n");
	double ecc,ecc2,ecc3,ecc4;
	printf("\nTesting Circular Mean anom = 3.6029 and Ecc = 0.0-------\n");
	ecc = KeplerEqn(3.6029,0.0);
	printf("%f\n" ,ecc);
	printf("\nFor circular it should result in the mean anom-------\n");

	printf("\nTesting eccentric Mean anom = 3.6029 = 206.430964 degrees and Ecc = 0.37255----in radians---\n");
	ecc2 = KeplerEqn(3.6029,0.37255);
	printf("%f\n" ,ecc2);
	printf("\nshould result in 199.35619827991917 or 3.4794220442346146527 rads ---\n");

	printf("\nTesting Elliptic Mean anom =1.5 and Ecc = 0.8-------\n");
	ecc3 = KeplerEqn(1.5,0.8);
	printf("%f\n" ,ecc3);
	printf("\n Should result in 2.1635326743829743634 or 123.96129108110373807 degrees");

	printf("--Testing Parabolic orbit Mean anom = 1.5 and Ecc = 1.0-------\n");
	ecc4 = KeplerEqn(1.5,1.0);
	printf("%f\n" ,ecc4);

	printf("\nTesting Hyperbolic Mean anom = 40.69 and Ecc =  2.7696-------\n");
	ecc = KeplerEqn(40.69, 2.7696);
	printf("%f\n" ,ecc);
	printf("\n should return Hyperbolic eccentric anomaly = 3.46309--------------------\n");

	return 0;
}

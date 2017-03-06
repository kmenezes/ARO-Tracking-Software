#include <stdio.h>
#include <math.h>
#include "Propagate.h"
	#define PI 3.1415926535897932384626433832795028841971693993751058209749445923

int main(){
	printf("----------------------\n");
	printf("\n Welcome to P2 by James and Keith\n\n");
	printf("----------------------\n");



	printf("----------------------\n");
	printf("Testing Kepler's Equation\n");
	printf("----------------------\n");
	printf("---------85.943699980374-------------\n");
	double ecc,ecc2,ecc3,ecc4;
	printf("--Testing Circular Mean anom = 3.6029 and Ecc = 0.0-------\n");
	ecc = KeplerEqn(3.6029,0.0);
	printf("%f\n" ,ecc);
	printf("--For circular it should result in the mean anom-------\n");

	printf("--Testing eccentric Mean anom = 3.6029 = 206.430964 degrees and Ecc = 0.37255----in radians---\n");
	ecc2 = KeplerEqn(3.6029,0.37255);
	printf("%f\n" ,ecc2);
	printf("--should result in 199.35619827991917 or 3.4794220442346146527 rads ---\n");

	printf("--Testing Elliptic Mean anom =1.5 and Ecc = 0.8-------\n");
	ecc3 = KeplerEqn(1.5,0.8);
	printf("%f\n" ,ecc3);
	printf("---- should result in 2.1635326743829743634 or 123.96129108110373807 degrees");

	printf("--Testing Parabolic orbit Mean anom = 1.5 and Ecc = 1.0-------\n");
	ecc4 = KeplerEqn(1.5,1.0);
	printf("%f\n" ,ecc4);

	printf("--Testing Hyperbolic Mean anom = 40.69 and Ecc =  2.7696-------\n");
	ecc = KeplerEqn(40.69, 2.7696);
	printf("%f\n" ,ecc);
	printf("--should return Hyperbolic eccentric anomaly = 3.46309--------------------\n");

	return 0;
}

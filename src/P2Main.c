#include <stdio.h>
#include <math.h>
#include "Propagate.h"
#include "Basic.h"
#include "FileIO.h"
#include "Vector.h"
#include "STKout.h"
#include "DateAndTimeCalculations.h"
#include "Matrix.h"
#include "Vector.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PI 3.1415926535897932384626433832795028841971693993751058209749445923

int main(){
/*
	printf("------------------------------------------\n");
	printf("\nWelcome to P2 by James and Keith\n\n");
	printf("------------------------------------------\n");

	Satellite *sat = (Satellite*) malloc(sizeof(Satellite));
	ReadNoradTLE(sat, '0','1','2');

	printf("\nTesting AnyKey() -- You must press ENTER to continue \n");
	//anykey();
	printf("\nAnykey Works!\n");

	printf("------------------------------------------\n");
	printf("\nTesting Theta - J and N \n");
	printf("------------------------------------------\n");

	printf("\nUsing the test value from the TLE Epoch: %f\n",05054.71335794);
	// 05054.71335794
	double value = 05054.71335794;
	//double THETAN = THETAN(value);
	printf("\nThe result of  %f\n", THETAN);
	printf("\nThe result should print 2.67 \n ");

	//double THETAJ(2451544.50);
	printf("------------------------------------------\n");

	//tests for keplers
	printf("------------------------------------------\n");
	printf("\nTesting Keplers Equation \n");
	printf("------------------------------------------\n");
	double ecc,ecc2,ecc3,ecc4;
	printf("\nTesting Keplers Eqn for Circular Orbit for Mean anom = 3.6029 and Ecc = 0.0\n");
	printf("------------------------------------------\n");
	ecc = KeplerEqn(3.6029,0.0);
	printf("\n %f\n" ,ecc);
	printf("\nFor circular it should result in the mean anom 3.6029 \n");
	printf("\n------------------------------------------\n");
	printf("\nTesting Kepler for eccentric Mean anom = 3.6029 = 206.430964 degrees and Ecc = 0.37255 \n");
	ecc2 = KeplerEqn(3.6029,0.37255);
	printf("\nKeplerEqn(3.6029,0.37255) returned: %f\n" ,ecc2);
	printf("\nThe result should be in 199.35619827991917 degrees or 3.4794220442346146527 rads\n");
	printf("\n------------------------------------------\n");
	printf("\nTesting Kepler Elliptic orbit for Mean anom =1.5 and Ecc = 0.8\n");
	printf("------------------------------------------\n");
	ecc3 = KeplerEqn(1.5,0.8);
	printf("\nKeplerEqn(1.5,0.8) returned: %f\n" ,ecc3);
	printf("\nShould result in 2.1635326743829743634 or 123.96129108110373807 degrees \n");
	printf("\n------------------------------------------\n");
	printf("\nTesting Parabolic orbit Mean anom = 1.5 and Ecc = 1.0\n");
	printf("------------------------------------------\n");
	ecc4 = KeplerEqn(1.5,1.0);
	printf("\nKeplerEqn(1.5,1.0) returns:  %f\n" ,ecc4);
	printf("Result should be 1.952623\n");
	printf("\n------------------------------------------\n");
	printf("\nTesting Hyperbolic Mean anom = 40.69 and Ecc =  2.7696 \n");
	printf("------------------------------------------\n");
	ecc = KeplerEqn(40.69, 2.7696);
	printf("\nKeplerEqn(40.69, 2.7696) returned: %f\n" ,ecc);
	printf("\nshould return Hyperbolic eccentric anomaly = 3.46309\n");
	printf("------------------------------------------\n");

	// testing mean anomaly motion
	// 	//double ans =  mean_anomaly_motion (Mt_mean_anomaly,  nt_mean_motion, time,  ts_sat_epoch,
	// M0_mean_anomaly, n_mean_motion, n_dot_mean_motion, n_2dots_mean_motion)
	printf("\n------------Test Mean Anomaly Motion----------------\n");
	double mean_anom, mean_motion;
	double ans =  mean_anomaly_motion(mean_anom,  mean_motion, sat->refepoch,  sat->refepoch, sat->meanan, sat->meanmo, sat->ndot, sat->nddot6);
	printf("%f %f\n", mean_anom, mean_motion);
	printf("------------------------------------------\n");

	printf("\n------------Test the Station ECF----------------\n");
	Vector *s;
	s=(Vector*)malloc(2*sizeof(Vector));
	s->x=0;
	s->y=0;
	s->z=0;

	station_ECF(s, 45, 45, 45);
	printf("\n Station_ECF with inputs of station_ECF(s, 45, 45, 45) returns:  X=%f  Y=%f  Z=%f \n", s->x, s->y, s->z);
	printf("\n The result should be ECEF from Latitude,Longitude, Height (ellipsoidal) X : 3194.442   km, Y : 3194.442   km, Z : 4487.38   km\n");
	printf("\n as confirmed with an online calculator http://www.oc.nps.edu/oc2902w/coord/llhxyz.htm \n");
	printf("\n------------------------------------------\n");


	printf("\n------------Testing range_ECF2topo----------------\n");
	Vector *vrtp;
	vrtp = (Vector*)malloc(sizeof(Vector));
	Vector *vrtv;
	vrtv = (Vector*)malloc(sizeof(Vector));
	Vector *vsbp;
	vsbp = (Vector*)malloc(sizeof(Vector));
	vsbp->x = 5; vsbp->y = 5; vsbp->z = 4; vsbp->mag = 7;
	Vector *vsep;
	vsep = (Vector*)malloc(sizeof(Vector));
	vsep->x = 5; vsep->y = 5; vsep->z = 4; vsep->mag = 7;
	Vector *vsev;
	vsev = (Vector*)malloc(sizeof(Vector));
	vsev->x = 1; vsev->y = 2; vsev->z = 3; vsev->mag = 4;
	double slong = 281.0;
	double slat = 45.0;
	printf("\n The input is V - [5,5,4,7] V2 - [5,5,4,7] v3 - [1,2,3,4]");
	range_ECF2topo(vrtp, vrtv, *vsbp, vsep, vsev, slong, slat);
	printf("The following is the range topo position vector:\n");
	printf("%f\n", vrtp->x);
	printf("%f\n", vrtp->y);
	printf("%f\n", vrtp->z);

	printf("The following is the range topo velocity vector:\n");
	printf("%f\n", vrtv->x);
	printf("%f\n", vrtv->y);
	printf("%f\n", vrtv->z);
	printf("------------------------------------------\n");


*/
		double t[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int size = 10;
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
	int a = STKout(t, size, coordinatesys, p, v);
	printf("%d",a);
	return 0;
}


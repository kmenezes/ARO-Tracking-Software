/*
 ============================================================================
 Name        : P3_Keith_James.c
 Author      : KeithMenezes
 Version     :
 Copyright   : Keith Menezes
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "Propagate.h"
#include "Basic.h"
#include "Fileio.h"
#include "Vector.h"
#include "STKout.h"
#include "DateAndTimeCalculations.h"
#include "Matrix.h"
#include "Vector.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define PI 3.1415926535897932384626433832795028841971693993751058209749445923
#define CUBE_ROOT( X)  (exp( log( X) / 3.))
int main(void){
	printf("------------------------------------------\n");
	printf("\n Mini Quiz by Keith\n\n");
	printf("------------------------------------------\n");

	//question 1
	char *file = "TLE.txt";
	Satellite sats[1];
	ReadNoradTLE(sats, file);

/*

	//1a
	char *gd=jd2dat(jdatep(sat1[1].refepoch));

	printf("\nThe Gregorian Date of the Epoch is: %s\n", gd);

	//1b
	double ma,mm, sma;

	ma=sat1[1].meanan;
	mm=sat1[1].meanmo;
	sma=pow(ma/pow(mm, 2), 1/3);

	printf("\nThe Mean Anomaly is: %f.\nThe Mean Motion is: %f.\nThe Semi-major Axis is: %f.\n", ma, mm, sma);

	//1c + 2b

	double mt, nt;
	char *date = "1995-10-16 06:23:23";
	double epoch=dat2jd(date);
	double ndot = sat1[1].ndot;
	double n2dot=sat1[1].nddot6;

	for(int j=0; j<31; j++){
		double time=j*60;

		mean_anomaly_motion(&mt, &nt, time, epoch, ma, mm, ndot, n2dot);
		double EA=KeplerEqn(mt, sat1[1].eccn);

		printf("\nTime(s):\tN(rev/day):\tM(degrees):\tEccentric Anomaly (degrees):\n");
		printf("%f\t%f\t%f\t%f\n", time, mt, nt, EA);
	}



	//question 2
	//2a

	printf("\nThe Eccentricity of the orbit is: %f.\n", sat1[1].eccn);



*/




	for(int i=0; i<1; i++){
		printf("sat[%d].name is %s\n", i, sats[i].name);
		printf("    refepoch is %f\n", sats[i].refepoch);
		printf("    incl is %f\n", sats[i].incl);
		printf("    raan is %f\n", sats[i].raan);
		printf("    Orbit eccentricity from the TLE = %f\n", sats[i].eccn);
		printf("    argper is %f\n", sats[i].argper);
		printf("    Mean Anomaly is %f\n", sats[i].meanan);
		printf("    Mean Motion is %f\n", sats[i].meanmo);
		printf("    ndot is %f\n", sats[i].ndot);
		printf("    nddot6 is %f\n", sats[i].nddot6);
		printf("    bstar is %f\n", sats[i].bstar);
		printf("    orbitnum is %f\n", sats[i].orbitnum);
	}

	double data = sats[0].refepoch;

	printf("This is the Gregorian Date: %f \n",data );
	double jd = THETAJ(data);
	char a = jd2dat(jd);
	printf("Which is: %c \n",a );

	double semimajoraxis = CUBE_ROOT(398600.4418/(4*PI*PI*0.0000232144916*0.0000232144916));
	printf("The semimajor axis is: %f \n", semimajoraxis );

    printf("Time (EpSec)    Mean Motion (Revs/Day)    Mean Anomaly (deg)\n");
/*    for(int j = 54000; j <55800.000 ; j+60){
    	double mean_motion, mean_anom;
    	mean_anomaly_motion(&mean_anom, &mean_motion, j,jd,sats[0].meanan, sats[0].meanmo,sats[0].ndot ,sats[0].nddot6);
    	printf(" %f  %f   %f", j, mean_anom, mean_motion);
    }*/
	printf("------------------------------------------\n");
	printf("\nQuestion 2 \n\n");
	printf("------------------------------------------\n");
	printf("    Orbit eccentricity from the TLE = %f\n", sats[0].eccn);
	double kepl = KeplerEqn(200.364700*(PI/180),0.011898);
/*	for(int j = 54000; j <55800.000 ; j+60){
	    	kepl = KeplerEqn(mean_anom[j],sats[0].eccn);
	    }*/
	printf("Hey the eccentric anom is: %f" ,kepl);


	return 0;
}

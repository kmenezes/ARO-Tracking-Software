/*
 * P3_Keith_James.c
 *
 *  Created on: Mar 19, 2017
 * Main.c
 *
 *  Created on: Mar 19, 2017
 *      Author: james
 */

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
#include <stdlib.h>
#include <string.h>
#define CUBE_ROOT(X) (exp(log(X)/ 3.))
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286

int main(){

	Banner();
	printf("\nImporting station data...\n\n");
	Station *stn = (Station*) malloc(sizeof(Station));
	ReadStationFile(stn, '0');
	printf("Complete\n\n");

	printf("Enter the number next to the corresponding option:\n");
	printf("1   view station file data\n");
	printf("2   continue\n\n");
	int input1;
	printf("Entry: ");
	fflush(stdout);
	scanf("%d", &input1);
	if (input1 == 1){
		printf("\nStation File Contents:\n");
		//memset(, '\0', sizeof(sat->name);
		printf("1  Name: %s\n", stn->name);
		printf("2  Station Latitude: %f\n", stn->stnlat);
		printf("3  Station Longitude: %f\n", stn->stnlong);
		printf("4  Station Altitude: %f\n", stn->stnalt);
		printf("5  UTC Offset: %f\n", stn->utc_offset);
		printf("6  Azimuth Elevation nlim: %d\n", stn->az_el_nlim);
		printf("7  Azimuth Elevation Limit Azimuth: %f\n", stn->az_el_lim.az);
		printf("8  Azimuth Elevation Limit Elevation Min: %f\n", stn->az_el_lim.elmin);
		printf("9  Azimuth Elevation Limit Elevation Max: %f\n", stn->az_el_lim.elmax);
		printf("10 Station Azimuth Speed Max: %f\n", stn->st_az_speed_max);
		printf("11 Station Elevation Speed Max: %f\n", stn->st_el_speed_max);
	}
	printf("\nImporting TLE file sats...\n\n");
	char *file = "TLE.txt";
	Satellite sats[32];
	ReadNoradTLE(sats, file);
	printf("Complete\n");
	int x;
	for(x = 0;x < 1;){
		printf("\n\nEnter the number next to the corresponding option:\n");
		printf("1   view TLE data\n");
		printf("2   continue\n\n");
		int input2;
		printf("Entry: ");
		fflush(stdout);
		scanf("%d", &input2);
		if(input2 == 1){
			printf("\nEnter the satellite number you would like to view: ");
			int num;
			fflush(stdout);
			scanf("%d", &num);

			printf("\nInformation for sat number %d\n", num);
			printf("\n    name is %s", sats[num].name);
			printf("    refepoch is %f\n", sats[num].refepoch);
			printf("    incl is %f\n", sats[num].incl);
			printf("    raan is %f\n", sats[num].raan);
			printf("    eccn is %f\n", sats[num].eccn);
			printf("    argper is %f\n", sats[num].argper);
			printf("    meanan is %f\n", sats[num].meanan);
			printf("    meanmo is %f\n", sats[num].meanmo);
			printf("    ndot is %f\n", sats[num].ndot);
			printf("    nddot6 is %f\n", sats[num].nddot6);
			printf("    bstar is %f\n", sats[num].bstar);
			printf("    orbitnum is %f\n", sats[num].orbitnum);
		}
		if(input2 == 2){x++;}
	}
	// Visibility
	printf("\nEnter a Julian Date start time for the visibility check (span is 30 minutes from start time): ");
	double input3;
	fflush(stdout);
	scanf("%lf", &input3);
	printf("\n\nThe following are in view for a 30 minute range starting from %f:\n", input3);
	int j = 1;
	for (j = 1;j < 32;j++){
		int i;
		int view = 0;
		for (i = 0; i <30;i++){

			double mA;
			double mM;
			double t = input3 + i*0.000694;
			double satEpoch = sats[j].refepoch;
			double mA0 = sats[j].meanan;
			double nMM = sats[j].meanmo;
			double ndMM = sats[j].ndot;
			double n2dMM = sats[j].nddot6;
			mean_anomaly_motion(&mA, &mM, t, satEpoch, mA0, nMM, ndMM, n2dMM);
			double eccAnom = KeplerEqn(mA, sats[j].eccn);
			Vector *eciP;
			eciP = (Vector*)malloc(sizeof(Vector));
			Vector *eciV;
			eciV = (Vector*)malloc(sizeof(Vector));
			double sMA = CUBE_ROOT(398600.4418/(4*PI*PI*mM*mM));
			sat_ECI(eciP, eciV, sats[j].eccn, eccAnom, sMA, sats[j].raan,sats[j].argper, sats[j].incl, mM);
			Vector *ecfP;
			ecfP = (Vector*)malloc(sizeof(Vector));
			Vector *ecfV;
			ecfV = (Vector*)malloc(sizeof(Vector));
			double thetat = THETAN(sats[j].refepoch);
			sat_ECF(ecfP, ecfV, thetat, eciP, eciV);
			Vector *stnP;
			stnP = (Vector*)malloc(sizeof(Vector));
			station_ECF(stnP, stn->stnlong, stn->stnlat, stn->stnalt);
			Vector *rtP;
			rtP = (Vector*)malloc(sizeof(Vector));
			Vector *rtV;
			rtV = (Vector*)malloc(sizeof(Vector));
			range_ECF2topo(rtP, rtV, *stnP, ecfP, ecfV, stn->stnlong, stn->stnlat);
			double az;
			double el;
			double azV;
			double elV;
			LookAngles *LA =(LookAngles*) malloc(sizeof(LookAngles));
			range_topo2look_angles(LA, az, el, azV, elV, rtP, rtV);

			if (LA->elevation <= stn->az_el_lim.elmax && LA->elevation >= stn->az_el_lim.elmin){
				view++;
			}
		}
		if (view > 0){
			printf("%s", sats[j].name);
		}
	}
	return 0;
}

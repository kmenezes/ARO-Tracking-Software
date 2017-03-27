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

int main(void){

	Banner();
	printf("\nImporting station data...\n\n");
	Station *stn = (Station*) malloc(sizeof(Station));
	ReadStationFile(stn, '0');
	printf("Complete\n\n");
	int sf;
	for (sf = 0; sf < 1;){
		printf("\nEnter the number next to the corresponding option:\n");
		printf("1   view station file data\n");
		printf("2   edit station file data\n");
		printf("3   continue\n\n");
		int input1;
		printf("Entry: ");
		fflush(stdout);
		scanf("%d", &input1);
		if (input1 == 1){
			printf("\nStation File Contents:\n");
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
		if(input1 == 2){

			printf("\n1    name\n");
			printf("2    stnlat\n");
			printf("3    stnlong\n");
			printf("4    stnalt\n");
			printf("5    utc_offset\n");
			printf("6    az_el_nlim\n");
			printf("7    az_el_nlim.az\n");
			printf("8    az_el_nlim.elmin\n");
			printf("9    az_el_nlim.elmax\n");
			printf("10   st_az_speed_max\n");
			printf("11   st_el_speed_max\n");

			printf("\nWhat parameter would you like to edit: ");
			int num2;
			fflush(stdout);
			scanf("%d", &num2);
			printf("\n");
			if(num2 == 1){
				printf("name entry: ");
				char *n;
				fflush(stdout);
				scanf("%c", n);
				//stn->name = n;
			}
			if(num2 == 2){
				printf("stnlat entry: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				stn->stnlat = n;
			}
			if(num2 == 3){
				printf("stnlon entry: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				stn->stnlong = n;
			}
			if(num2 == 4){
				printf("stnalt: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				stn->stnalt = n;
			}
			if(num2 == 5){
				printf("utc_offset entry: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				stn->utc_offset = n;
			}
			if(num2 == 6){
				printf("az_el_nlim entry: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				stn->az_el_nlim = n;
			}

			if(num2 == 7){
				printf("az_el_lim.az entry: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				stn->az_el_lim.az = n;
			}
			if(num2 == 8){
				printf("az_el_lim.elmin entry: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				stn->az_el_lim.elmin = n;
			}

			if(num2 == 9){
				printf("az_el_lim.elmax entry: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				stn->az_el_lim.elmax= n;
			}

			if(num2 == 10){
				printf("st_az_speed_max entry: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				stn->st_az_speed_max = n;
			}

			if(num2 == 11){
				printf("st_el_speed_max entry: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				stn->st_el_speed_max = n;
			}


		}
		if (input1 == 3){sf++;}

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
		printf("2   edit TLE data\n");
		printf("3   continue\n\n");
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
		if(input2 == 2){
			printf("\nEnter the satellite number you would like to edit: ");
			int num;
			fflush(stdout);
			scanf("%d", &num);

			printf("\n1    name\n");
			printf("2    refepoch\n");
			printf("3    incl\n");
			printf("4    raan\n");
			printf("5    eccn\n");
			printf("6    argper\n");
			printf("7    meanan\n");
			printf("8    meanmo\n");
			printf("9    ndot\n");
			printf("10   nddot6\n");
			printf("11   bstar\n");
			printf("12   orbitnum\n");

			printf("\nWhat parameter would you like to edit: ");
			int num2;
			fflush(stdout);
			scanf("%d", &num2);
			printf("\n");
			if(num2 == 1){
				printf("name entry: ");
				char *n;
				fflush(stdout);
				scanf("%c", n);
				//sats[num].name = n;
			}
			if(num2 == 2){
				printf("refepoch entry: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				sats[num].refepoch = n;
			}
			if(num2 == 3){
				printf("incl entry: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				sats[num].incl = n;
			}
			if(num2 == 4){
				printf("raan entry: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				sats[num].raan = n;
			}
			if(num2 == 5){
				printf("eccn entry: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				sats[num].eccn = n;
			}
			if(num2 == 6){
				printf("argper entry: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				sats[num].argper = n;
			}

			if(num2 == 7){
				printf("meanan entry: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				sats[num].meanan = n;
			}

			if(num2 == 8){
				printf("meanmo entry: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				sats[num].meanmo = n;
			}
			if(num2 == 9){
				printf("ndot entry: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				sats[num].ndot = n;
			}

			if(num2 == 10){
				printf("nddot6 entry: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				sats[num].nddot6 = n;
			}

			if(num2 == 11){
				printf("bstar entry: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				sats[num].bstar = n;
			}

			if(num2 == 12){
				printf("orbitnum entry: ");
				double n;
				fflush(stdout);
				scanf("%lf", &n);
				sats[num].orbitnum = n;
			}

		}
		if(input2 == 3){x++;}
	}

	//------------------------------AOS/LOS---------------------------------------------


	printf("\nOpening tracking file...\n\n");
	FILE *fp = fopen("tracking_sched.txt","r+");

	char line1[50]; //The first line in tracking_sched.txt -- Specifies the start date/time
	char line2[50]; //The second line in tracking_sched.txt -- Specifies the stop date/time
	char line3[31]; //The third line in tracking_sched.txt -- Specifies the time step
	fgets(line1, 50, fp);
	fgets(line2, 50, fp);
	fgets(line3, 31, fp);

	fclose(fp);

	//Pull out the dates from each line
	char date_start[20], date_stop[20], time_step[6];

	strncpy(date_start, line1+26, 19);
	strncpy(date_stop, line2+25, 19);
	strncpy(time_step, line3+24, 5);
	printf("Printing out the start date %s\n",date_start);
	printf("Printing out the stop date %s\n",date_stop);
	printf("Printing out the time step %s\n",time_step);

	printf("\nCalculating AOS and LOS...\n");
	//Convert each time_step to a double
	double step;
	step = atof(time_step);

	double JulianDateStart, JulianDateStop;

	JulianDateStart = dat2jd(date_start);
	JulianDateStop = dat2jd(date_stop);


	char *NAME[31];
	double AOS[31], LOS[31];
	int NUM[31];
	int num = 0;


	for(int j=1; j<32; j++){//Run through each satellite

		double currentTime;
		currentTime = JulianDateStart;
		int acquired=0; //acquired=0 if the AOS has not been obtained and =1 if it has been obtained
		int lost = 0; //lost = 0 if the sat has not been lost yet and =1 if the sat has been lost and is out of view

		for( ;currentTime<JulianDateStop; currentTime = currentTime+frcofd(0,0,step)){//Run through each time step until we reach the end of the interval
			double mA, mM;
			double satEpoch = sats[j].refepoch;
			double mA0 = sats[j].meanan;
			double nMM = sats[j].meanmo;
			double ndMM = sats[j].ndot;
			double n2dMM = sats[j].nddot6;
			mean_anomaly_motion(&mA, &mM, currentTime, satEpoch, mA0, nMM, ndMM, n2dMM);
			double mMrev=mM/(2*PI);

			double eccAnom = KeplerEqn(mA, sats[j].eccn);

			Vector *eciPos, *eciVel;
			eciPos = (Vector*)malloc(sizeof(Vector));
			eciVel = (Vector*)malloc(sizeof(Vector));

			double sMA = CUBE_ROOT(398600.4418/(4*PI*PI*mMrev*mMrev));
			sat_ECI(eciPos, eciVel, sats[j].eccn, eccAnom, sMA, sats[j].raan*PI/180,sats[j].argper*PI/180, sats[j].incl*PI/180, mM);
			Vector *ecfPos, *ecfVel;
			ecfPos = (Vector*)malloc(sizeof(Vector));
			ecfVel = (Vector*)malloc(sizeof(Vector));

			double thetat = THETAN(sats[j].refepoch);
			sat_ECF(ecfPos, ecfVel, thetat, eciPos, eciVel);
			Vector *stnPos, *rtPos, *rtVel;
			stnPos = (Vector*)malloc(sizeof(Vector));
			station_ECF(stnPos, stn->stnlong, stn->stnlat, stn->stnalt);
			rtPos = (Vector*)malloc(sizeof(Vector));
			rtVel = (Vector*)malloc(sizeof(Vector));
			range_ECF2topo(rtPos, rtVel, *stnPos, ecfPos, ecfVel, stn->stnlong, stn->stnlat);

			double az;
			double el;
			double azV;
			double elV;
			LookAngles *LA =(LookAngles*) malloc(sizeof(LookAngles));
			range_topo2look_angles(LA, az, el, azV, elV, rtPos, rtVel);
			double ss[31];
			//ss[num] = linkstrength(rtPos->mag);
			if (LA->elevation <= stn->az_el_lim.elmax && LA->elevation >= stn->az_el_lim.elmin && acquired == 0){//Go in to this loop if the satellite is acquired.
				//If the satellite has already been acquired then don't add it again
				NUM[num] = j;
				NAME[num] = sats[j].name;
				NAME[num][strlen(NAME[num])-1] = '\0'; //Just some formatting of the Name of the sat for printing.
				NAME[num][strlen(NAME[num])-2] = '\0';//Without these two lines there are two \n operators in NAME[num]
				AOS[num] = currentTime;
				acquired = 1;
			}
			if(LA->elevation >= stn->az_el_lim.elmax && LA->elevation <= stn->az_el_lim.elmin && acquired==1){// Go in to this loop if the satellite is lost.
				// You can only lose the satellite after it has been acquired
				// hence acquired==1
				LOS[num] = currentTime;
				lost = 1; //the sat is now out of view
				break;}}if(acquired==1){if(lost==0){//if the sat had been acquired but not lost then there is no LOS time.
					LOS[num] = JulianDateStop;}num++;}}
	printf("\nComplete\n\n");
	//Print the AOS/LOS table to the console and write it to a file
	FILE *filepoint;
	filepoint = fopen("AOSLOS.txt", "w+");
	printf("Sat No.		Name			AOS			LOS\n");
	fprintf(filepoint, "Sat No.			Name					AOS					LOS					Min. ExpectedLevel (dBm)\n");
	for(int i=0;i<num;i++){
		printf("%d	 %s %s 	", NUM[i], NAME[i], jd2dat(AOS[i]));
		printf("%s\n", jd2dat(LOS[i]));
		fprintf(filepoint, "%d	 	%s	%s 	", NUM[i], NAME[i], jd2dat(AOS[i]));
		fprintf(filepoint, "%s", jd2dat(LOS[i]));
	//	fprintf(filepoint,"%f\n",linkstrength(rtPos->mag));
	}
	fclose(filepoint);
	return 0;
}

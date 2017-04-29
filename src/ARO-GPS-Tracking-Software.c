
#include <stdio.h>
#include <math.h>
#include "Propagate.h"
#include "Basic.h"
#include "Fileio.h"
#include "Vector.h"
#include "Check.h"
#include "Datefun.h"
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

    printf("Enter the number next to the corresponding option:\n");
    printf("1   view station file data\n");
    printf("2   continue\n\n");
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

    //AOS/LOS

    printf("\nOpening tracking file...\n\n");
    FILE *fp = fopen("tracking_sched.txt","r+");

    char line1[50];
    char line2[50];
    char line3[31];
    fgets(line1, 50, fp);
    fgets(line2, 50, fp);
    fgets(line3, 31, fp);

    fclose(fp);


    char date_start[20], date_stop[20], time_step[6];

    strncpy(date_start, line1+26, 19);
    strncpy(date_stop, line2+25, 19);
    strncpy(time_step, line3+24, 5);
    printf("Printing out the start date %s\n",date_start);
    printf("Printing out the stop date %s\n",date_stop);
    printf("Printing out the time step %s\n",time_step);

    printf("\nCalculating AOS and LOS...\n");


    double step;
    step = atof(time_step);

    double JulianDateStart, JulianDateStop;

    JulianDateStart = dat2jd(date_start);
    JulianDateStop = dat2jd(date_stop);

    char *NAME[31];
    double AOS[31], LOS[31];
    int NUM[31];
    int num = 0;

    double ss[31], fD[31];
    for(int j=0; j<31; j++){

	double currentTime;
	currentTime = JulianDateStart;
	int acquired=0;
	int lost = 0;

	for( ;currentTime<JulianDateStop; currentTime = currentTime+frcofd(0,0,step)){
	    double mA, mM;
	    double satEpoch = sats[j].refepoch;
	    double mA0 = sats[j].meanan;
	    double nMM = sats[j].meanmo;
	    double ndMM = sats[j].ndot;
	    double n2dMM = sats[j].nddot6;
	    mean_anomaly_motion(&mA, &mM, currentTime, jdatep(satEpoch), mA0, nMM, ndMM, n2dMM);
	    double mMrev=mM/(2*PI);

	    double eccAnom = KeplerEqn(mA, sats[j].eccn);

	    Vector *eciPos, *eciVel;
	    eciPos = (Vector*)malloc(sizeof(Vector));
	    eciVel = (Vector*)malloc(sizeof(Vector));

	    double sMA = CUBE_ROOT(398600.4418/(4*PI*PI*mMrev*mMrev));
	    sat_ECI(eciPos, eciVel, sats[j].eccn, eccAnom, sMA, sats[j].raan*PI/180,
		    sats[j].argper*PI/180, sats[j].incl*PI/180, mM);
	    Vector *ecfPos, *ecfVel;
	    ecfPos = (Vector*)malloc(sizeof(Vector));
	    ecfVel = (Vector*)malloc(sizeof(Vector));

	    double thetat = THETAJ(currentTime,JulianDateStart);
	    sat_ECF(ecfPos, ecfVel, thetat, eciPos, eciVel);
	    Vector *stnPos, *rtPos, *rtVel;
	    stnPos = (Vector*)malloc(sizeof(Vector));
	    station_ECF(stnPos, stn->stnlong, stn->stnlat, stn->stnalt);
	    rtPos = (Vector*)malloc(sizeof(Vector));
	    rtVel = (Vector*)malloc(sizeof(Vector));
	    //range_ECF2topo(rtPos, rtVel, stn, ecfPos, ecfVel);
	    range_ECF2topo(rtPos, rtVel, *stnPos, ecfPos, ecfVel, stn->stnlong, stn->stnlat);

	    double az;
	    double el;
	    double azV;
	    double elV;
	    LookAngles *LA =(LookAngles*) malloc(sizeof(LookAngles));
	    range_topo2look_angles(LA, az, el, azV, elV, rtPos, rtVel);

	    ss[num] = linkstrength(rtPos->mag);
	    if (LA->elevation <= stn->az_el_lim.elmax && LA->elevation >= stn->az_el_lim.elmin && acquired == 0){//Go in to this loop if the satellite is acquired.

		NUM[num] = j;
		NAME[num] = sats[j].name;
		NAME[num][strlen(NAME[num])-1] = '\0';
		NAME[num][strlen(NAME[num])-2] = '\0';
		AOS[num] = currentTime;
		acquired = 1;
	    }
	    if(LA->elevation >= stn->az_el_lim.elmax && LA->elevation <= stn->az_el_lim.elmin && acquired==1){// Go in to this loop if the satellite is lost.
		LOS[num] = currentTime;
		lost = 1;
		break;
	    }
	}
	if(acquired==1)
	    {
	    if(lost==0)
		{
		LOS[num] = JulianDateStop;
		}num++;
	    }
    }
    printf("\nComplete\n\n");

    FILE *filepoint;
    filepoint = fopen("AOSLOS.txt", "w+");
    printf("Sat No.		Name			AOS			LOS		Min. ExpectedLevel (dBm)\n");
    fprintf(filepoint, "Sat No.			Name					AOS					LOS					Min. ExpectedLevel (dBm)\n");
    for(int i=0;i<num;i++){
	printf("%d	 %s %s 	", NUM[i], NAME[i], jd2dat(AOS[i]));
	printf("%s", jd2dat(LOS[i]));
	printf("\t%f\n",ss[i]);
	fprintf(filepoint, "%d	 	%s	%s 	", NUM[i], NAME[i], jd2dat(AOS[i]));
	fprintf(filepoint, "%s", jd2dat(LOS[i]));
	fprintf(filepoint," 	%f\n",ss[i]);
    }
    fclose(filepoint);

    //-----------------tracking Data----------------//

    printf("\n\nEnter the satellite number you would like to track from the table (values in the first column): ");
    int satNum;
    fflush(stdout);
    scanf("%d", &satNum);
    Satellite sat = sats[satNum];
    FILE *xp;
    xp = fopen("TrackingData.txt", "w+");
    printf("\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("UTC\t\t\tAZ\t\tEL\t\tAZ-vel\t\tEL-vel\t\tRange\t\tRange-Rate\t\tDoppler\t\tLevel\n");
    printf("\t\t\tdeg\t\tdeg\t\tdeg/sec\t\tdeg/sec\t\tkm\t\tkm/sec\t\t\tkHz\t\tdbm\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    fprintf(xp,"#Any comment and/or header\n");
    fprintf(xp,"# Station: %s Tracking Orbit for the %s\n", stn->name, sat.name);
    fprintf(xp,"-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(xp,"# UTC Date/Time   Azimuth and AZ_Velocity   Elevation and EL_Velocity\n");
    fprintf(xp,"YYYY.DOY.HH.MM.SS AZd AZm AZ.s AZ.Vel       ELd ELm EL.s EL.Vel\n");

    double currentTime;
    currentTime = JulianDateStart;
    int acquired=0;
    int lost = 0;

    //-----------------------------STKOUT Emphemeris------------------------------------------//
    FILE *stk;
    stk = fopen("newSTKout.e", "w+");
    fprintf(stk, "%s", "stk.v.11.0\n");
    fprintf(stk, "\nBEGIN Ephemeris\n");
    fprintf(stk,"\nNumberOfEphemerisPoints	%d\n", 30);
    char YR[5], MO[3], D[3], HR[3], MIN[3], S[3], *MONTH; //Put the year, month, day etc out of the date.
    double mon;
    char *EpochDat = jd2dat(JulianDateStart);
    //NOTE: MO is the number of the month as a character. mon is the number of the month as a double. MONTH is the month converted in to its
    // short form...Jan, Feb, Mar etc. In stk.e we actually end up printing MONTH.

    //Pull out the year, month, day etc. and put them in their arrays
    strncpy(YR, EpochDat,4);
    YR[4] = '\0';
    strncpy(MO, EpochDat+5,2);
    MO[2] = '\0';
    strncpy(D, EpochDat+8,2);
    D[2] = '\0';
    strncpy(HR, EpochDat+11,2);
    HR[2] = '\0';
    strncpy(MIN, EpochDat+14,2);
    MIN[2] = '\0';
    strncpy(S, EpochDat+17,2);
    S[2] = '\0';

    mon = atof(MO);

    if(mon==1){
	MONTH = "Jan";
    }
    if(mon==2){
	MONTH = "Feb";
    }
    if(mon==3){
	MONTH = "Mar";
    }
    if(mon==4){
	MONTH = "Apr";
    }
    if(mon==5){
	MONTH = "May";
    }
    if(mon==6){
	MONTH = "Jun";
    }
    if(mon==7){
	MONTH = "Jul";
    }
    if(mon==8){
	MONTH = "Aug";
    }
    if(mon==9){
	MONTH = "Sep";
    }
    if(mon==10){
	MONTH = "Oct";
    }
    if(mon==11){
	MONTH = "Nov";
    }
    if(mon==12){
	MONTH = "Dec";
    }


    fprintf(stk, "\nScenarioEpoch	%s %s %s %s:%s:%s\n", D, MONTH, YR, HR, MIN, S);
    fprintf(stk,"\nInterpolationMethod            Lagrange\n" );
    fprintf(stk,"\nInterpolationOrder            7\n");
    fprintf(stk, "\nCentralBody            Earth\n");
    fprintf(stk,"\nCoordinateSystem            Fixed");
    fprintf(stk, "\n");fprintf(stk, "\n");fprintf(stk, "\n");
    fprintf(stk,"%s", "EphemerisTimePosVel\n\n");
    double timey = 0;
    //-----------------------------STKOUT Emphemeris------------------------------------------//
    for( ;currentTime<JulianDateStop; currentTime = currentTime+frcofd(0,0,step)){
	double mA, mM;
	double satEpoch = sat.refepoch;
	double mA0 = sat.meanan;
	double nMM = sat.meanmo;
	double ndMM = sat.ndot;
	double n2dMM = sat.nddot6;
	mean_anomaly_motion(&mA, &mM, currentTime, jdatep(satEpoch), mA0, nMM, ndMM, n2dMM);
	double mMrev=mM/(2*PI);

	double eccAnom = KeplerEqn(mA, sat.eccn);

	Vector *eciPos, *eciVel;
	eciPos = (Vector*)malloc(sizeof(Vector));
	eciVel = (Vector*)malloc(sizeof(Vector));

	double sMA = CUBE_ROOT(398600.4418/(4*PI*PI*mMrev*mMrev));
	sat_ECI(eciPos, eciVel, sat.eccn, eccAnom, sMA, sat.raan*PI/180,sat.argper*PI/180, sat.incl*PI/180, mM);
	Vector *ecfPos, *ecfVel;
	ecfPos = (Vector*)malloc(sizeof(Vector));
	ecfVel = (Vector*)malloc(sizeof(Vector));

	double thetat = THETAJ(currentTime, JulianDateStart);
	sat_ECF(ecfPos, ecfVel, thetat, eciPos, eciVel);
	Vector *stnPos, *rtPos, *rtVel;
	stnPos = (Vector*)malloc(sizeof(Vector));
	station_ECF(stnPos, stn->stnlong, stn->stnlat, stn->stnalt);
	rtPos = (Vector*)malloc(sizeof(Vector));
	rtVel = (Vector*)malloc(sizeof(Vector));
	range_ECF2topo(rtPos, rtVel, *stnPos, ecfPos, ecfVel, stn->stnlong, stn->stnlat);
	fprintf(stk,"%+.14e %+.14e %+.14e %+.14e %+.14e %+.14e %+.14e\n",
		timey, 1000*ecfPos->x, 1000*ecfPos->y,1000*ecfPos->z,
		1000*ecfVel->x, 1000*ecfVel->y, 1000*ecfVel->z);
	timey = timey +step;
	double az;
	double el;
	double azV;
	double elV;
	LookAngles *LA =(LookAngles*) malloc(sizeof(LookAngles));
	range_topo2look_angles(LA, az, el, azV, elV, rtPos, rtVel);

	//Doppler
	double R, v, c;

	R=magntd(*rtPos);
	v=(rtVel->x*rtPos->x+rtVel->y*rtPos->y+rtVel->z*rtPos->z)/R;
	c=299792.458; //in km/s

	ss[num] = linkstrength(rtPos->mag);

	fD[num]=(-v/c)*ss[num];///c);//*ss[num];

	printf("%s\t%f\t%f\t%f\t%f\t%f\t%f\t\t%f\t%f\n", jd2dat(currentTime),fixangdeg(LA->azimuth),fixangdeg(LA->elevation),LA->azimuth_velocity,LA->elevation_velocity,sqrt(rtPos->x*rtPos->x+rtPos->y*rtPos->y+rtPos->z*rtPos->z),sqrt(rtVel->x*rtVel->x+rtVel->y*rtVel->y+rtVel->z*rtVel->z), fD[num], linkstrength(rtPos->mag));

	//Tracking Data
	double AZfix, ELfix;
	double AZms, AZmin, AZs, ELms,ELmin, ELs;
	double AZd, AZm, ELd, ELm;
	AZfix=fixangdeg(LA->azimuth);
	AZms=frac(AZfix);
	AZd=AZfix-AZms;
	AZmin=AZms*60;
	AZs=frac(AZmin);
	AZm=AZmin-AZs;

	ELfix=fixangdeg(LA->elevation);
	ELms=frac(ELfix);
	ELd=ELfix-ELms;
	ELmin=ELms*60;
	ELs=frac(ELmin);
	ELm=ELmin-ELs;

	double year, mon, day, hh, mm, se;
	double DOY;
	char YR[5], MO[3], D[3], HR[3], MIN[3], S[3]; //Put the year, month, day etc out of the date.

	char *currentTimeChar, currentTimeCharArray[20];
	currentTimeChar = jd2dat(currentTime);			//Convert the JD into a char date
	strncpy(currentTimeCharArray, currentTimeChar,20);

	//Pull out the year, month, day etc. and put them in their arrays
	strncpy(YR, currentTimeCharArray,4);
	YR[4] = '\0';
	strncpy(MO, currentTimeCharArray+5,2);
	MO[2] = '\0';
	strncpy(D, currentTimeCharArray+8,2);
	D[2] = '\0';
	strncpy(HR, currentTimeCharArray+11,2);
	HR[2] = '\0';
	strncpy(MIN, currentTimeCharArray+14,2);
	MIN[2] = '\0';
	strncpy(S, currentTimeCharArray+17,2);
	S[2] = '\0';

	//Convert the chars to ints
	year = atof(YR);
	mon = atof(MO);
	day = atof(D);
	hh = atof(HR);
	mm = atof(MIN);
	se = atof(S);

	DOY = doy(year, mon, day);// Get the day of the year from the year, month and day

	fprintf(xp,"%.0f.%03.0f.%02.0f.%02.0f.%02.0f %03.0f %02.0f  %03.1f %03.6f\t\t%03.0f %02.0f  %03.1f %03.6f\n", year, DOY, hh, mm, se, AZd, AZm, AZs, LA->azimuth_velocity, ELd, ELm, ELs, LA->elevation_velocity);

    }
    fclose(fp);
    fprintf(stk, "\nEND Ephemeris\n");
    fclose(stk);
    return 0;
}

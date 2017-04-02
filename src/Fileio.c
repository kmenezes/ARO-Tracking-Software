/*
 * FileIO.c
 *
 *  Created on: Mar 3, 2017
 *      Author: james/keith
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "FileIO.h"
void Banner(){
	printf("\n -------------------- \n");
	printf("ENG4350 Team Info:\n");
	printf("Keith Menezes\n");
	printf("James Brook\n");
	printf("Team Pointer - Memory Allocation - Masters\n");
	time_t now;
	time(&now);
	struct tm* t;
	t = localtime(&now);
	char date[80];
	strftime (date, 80, "%Y-%m-%d", t);
	puts(date);
	printf("Version 5\n");
	printf("Welcome\n");
	printf("\n -------------------- \n");
}
void ERRMSG (char* STRING){
	printf("\a\n");
	printf("%s\n", STRING);
	exit(0);
}
void anykey(){
system("pause");
}
int ReadStationFile(Station *Stn, char STNFIL) {
	char name[128];
	char *name_ptr;
	char stnlat[128];
	double stnlat_struct;
	char stnlong[128];
	double stnlong_struct;
	char stnalt[128];
	double stnalt_struct;
	char utc_offset[128];
	double utc_offset_struct;
	char az_el_nlim[128];
	double az_el_nlim_struct;
	char vector[128];
	char *x, *y, *z;
	char st_az_speed_max[128];
	double st_az_speed_max_struct;
	char st_el_speed_max[128];
	double st_el_speed_max_struct;
	FILE *fp =
			fopen(".\\station_file.dat","r+");
	int switch_param = 0;
	char currChar;
	int i;
	if (fp == NULL) {
		perror("The station file does not exist.\n");
		return 1;
	} else {
		while (switch_param < 9) {
			switch (switch_param) {
			case 0:
				fgets(name, sizeof(name), fp);
				name_ptr = &name;
				switch_param++;
				break;
			case 1:
				fgets(stnlat, sizeof(stnlat), fp);
				sscanf(stnlat, "%lf", &stnlat_struct);
				switch_param++;
				break;
			case 2:
				fgets(stnlong, sizeof(stnlong), fp);
				sscanf(stnlong, "%lf", &stnlong_struct);
				switch_param++;
				break;
			case 3:
				fgets(stnalt, sizeof(stnalt), fp);
				sscanf(stnalt, "%lf", &stnalt_struct);
				switch_param++;
				break;
			case 4:
				fgets(utc_offset, sizeof(utc_offset), fp);
				sscanf(utc_offset, "%lf", &utc_offset_struct);
				switch_param++;
				break;
			case 5:
				fgets(az_el_nlim, sizeof(az_el_nlim), fp);
				sscanf(az_el_nlim, "%lf", &az_el_nlim_struct);
				switch_param++;
				break;
			case 6:
				fgets(vector, sizeof(vector), fp);
				x = strtok(vector, ",");
				y = strtok(NULL, ",");
				z = strtok(NULL, ",");
				switch_param++;
				break;
			case 7:
				fgets(st_az_speed_max, sizeof(st_az_speed_max), fp);
				sscanf(st_az_speed_max, "%lf", &st_az_speed_max_struct);
				switch_param++;
				break;
			case 8:
				fgets(st_el_speed_max, sizeof(st_el_speed_max), fp);
				sscanf(st_el_speed_max, "%lf", &st_el_speed_max_struct);
				switch_param++;
				break;
			default:
				break;
			}
		}
		Stn->name = name_ptr;
		Stn->stnlat = stnlat_struct;
		Stn->stnlong = stnlong_struct;
		Stn->stnalt = stnalt_struct;
		Stn->utc_offset = utc_offset_struct;
		Stn->az_el_nlim = az_el_nlim_struct;
		Stn->az_el_lim.az = atof(x);
		Stn->az_el_lim.elmin = atof(y);
		Stn->az_el_lim.elmax = atof(z);
		Stn->st_az_speed_max = st_az_speed_max_struct;
		Stn->st_el_speed_max = st_az_speed_max_struct;
	}
}

int ReadNoradTLE(Satellite sats[], char *file) {
	FILE *fp = fopen(file,"r+");
	for (int i = 0; i < 32; i++) {
		ReadSingleNoradTLE(&sats[i], fp);
	}
	fclose(fp);
	return 0;
}

int ReadSingleNoradTLE(Satellite *sat, FILE *fp) {

	enum params1 {
		LINE_1,
		SATELLITE_NO,
		CLASS,
		INT_DES_1,
		INT_DES_2,
		INT_DES_3,
		EPOCH,
		MEAN_DOT,
		MEAN_2_DOT,
		DRAG,
		EPHEMERIS,
		ELEMENT_NO,
		CHKSUM_1
	};

	enum params2 {
		LINE_2,
		SATELLITE_NO_2,
		INCLINE,
		RAAN,
		ECCENTRICITY,
		ARGP,
		MEAN_ANOM,
		MEAN_MOTION,
		REV_NO_EPOCH,
		CHKSUM_2,
	};

	int indices1[13][2] = {
		{  0,  1 }, //1
		{  2,  7 }, //2
		{  7,  8 }, //3
		{  9, 11 }, //4
		{ 11, 14 }, //5
		{ 14, 17 }, //6
		{ 18, 32 }, //7
		{ 33, 43 }, //8
		{ 44, 52 }, //9
		{ 54, 61 }, //10
		{ 62, 63 }, //11
		{ 64, 68 }, //12
		{ 68, 69 }, //13
	};

	int indices2[10][2] = {
		{  0,  1 },
		{  2,  7 },
		{  8, 16 },
		{ 17, 25 },
		{ 26, 33 },
		{ 34, 42 },
		{ 43, 51 },
		{ 52, 63 },
		{ 63, 68 },
		{ 68, 69 },
	};

	int i, j;
	char lines[3][128];
	char values1[13][128];
	char values2[10][128];

	for (i = 0; i < 3; i++) {
		fgets(lines[i], 128, fp);

		if (i == 0) {
			memset(sat->name, '\0', sizeof(char) * 128);
			strncpy(sat->name, lines[i], 128);
		} else if (i == 1) {
			for (j = 0; j < 13; j++) {
				memset(values1[j], '\0', sizeof(char) * 128);
				strncpy(values1[j], &(lines[i][indices1[j][0]]), indices1[j][1] - indices1[j][0]);
			}
		} else {
			for (j = 0; j < 10; j++) {
				memset(values2[j], '\0', sizeof(char) * 128);
				strncpy(values2[j], &(lines[i][indices2[j][0]]), indices2[j][1] - indices2[j][0]);
			}
		}
	}

	sat->refepoch = atof(values1[EPOCH]);
	sat->incl = atof(values2[INCLINE]);
	sat->raan = atof(values2[RAAN]);
	sat->eccn = atof(values2[ECCENTRICITY])/pow(10,7);
	sat->argper = atof(values2[ARGP]);
	sat->meanan = atof(values2[MEAN_ANOM]);
	sat->meanmo = atof(values2[MEAN_MOTION]);
	sat->ndot = atof(values1[MEAN_DOT]);
	sat->nddot6 = atof(values1[MEAN_2_DOT]);
	sat->bstar = atof(values1[DRAG]);
	sat->orbitnum = atof(values2[REV_NO_EPOCH]);

	return 0;
}

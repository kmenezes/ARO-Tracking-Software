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
	printf("ENG4350 Team Info\n");
	printf("Program Name\n");
	time_t now;
	time(&now);
	struct tm* t;
	t = localtime(&now);
	char date[80];
	strftime (date, 80, "%Y-%m-%d", t);
	puts(date);
	printf("Version 1\n");
	printf("Welcome\n");
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

/*int ReadNoradTLE(Satellite *sat, char line0, char line1, char line2) {
	char name[128];
	char *name_str;
	FILE *fp = fopen(".\\TLE.dat","r+");
	int switch_param = 0;
	char vector[128];
	char vector2[128];
	char *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m, *n, *o, *p, *q, *r;
	if (fp == NULL)
		{
			perror("The station file does not exist.\n");
			return 1;
		}
	else {
			while(switch_param < 3) {
				switch(switch_param) {
				case 0:
					 Advance position of file pointer to next line
					fgets(name,sizeof(name),fp);
					 Set the pointer
					name_str = &name;
					switch_param++;
					break;
				case 1:
					fgets(vector,sizeof(vector),fp);
					a = strtok (vector, " " );
					b = strtok (NULL, " " );
					c = strtok (NULL, " " );
					d = strtok (NULL, " ");
					e = strtok (NULL, " ");
					f = strtok (NULL, " ");
					g = strtok (NULL, " ");
					h = strtok (NULL, " ");
					i = strtok (NULL, " ");
					switch_param++;
					break;
				case 2:
					fgets(vector2,sizeof(vector2),fp);
					j = strtok (vector2, " " );
					k = strtok (NULL, " " );
					l = strtok (NULL, " " );
					m = strtok (NULL, " ");
					n = strtok (NULL, " ");
					o = strtok (NULL, " ");
					p = strtok (NULL, " ");
					q = strtok (NULL, " ");
					r = strtok (NULL, " ");
					switch_param++;
					break;
				default:
					break;
				}
			}
		}
		sat->name = name_str;
		sat->refepoch = atof(d);
		sat->incl = atof(l);
		sat->raan = atof(m);
		sat->eccn = atof(n);
		sat->argper = atof(o);
		sat->meanmo = atof(p);
		sat->ndot = atof(e);
		sat->nddot6 = atof(f);
		sat->bstar = atof(g);
		sat->orbitnum = atof(h);
}*/
/*int ReadNoradTLE(Satellite sats[], char *file) {

	char name[32][128];

	for(int j=0; j<31; j++){
		strcpy(name[j], "empty");
	}
	char *name_str;
	FILE *fp = fopen(file,"r+");
	int switch_param = 0;
	char vector[128];
	char vector2[128];
	char *TLE1, *satnumber1, *intdesignator, *refepoch, *derivMeanMo, *derivMeanMo2, *drag, *ephemeris_type, *element_number, *TLE2, *satnumber2, *incl, *RAAN, *eccn, *argper, *meanan, *column53_69;
	char  meanmo[12], rev_num_at_epoch[6];

	//int i=0;
	for(int i=0; i<31; i++)
	{
		switch_param=0;
		if (fp == NULL)
		{
			perror("The TLE file does not exist.\n");
			return 1;
		}
		else {
			while(switch_param < 3) {

				switch(switch_param) {
				case 0:
					/* Advance position of file pointer to next line *\/

					fgets(name[i],128,fp);

					/* Set the pointer *\/
					//name_str = &name;
					switch_param++;
					break;
				case 1:
					fgets(vector,sizeof(vector),fp);
					TLE1 = strtok (vector, " " );
					satnumber1 = strtok (NULL, " " );
					intdesignator = strtok (NULL, " " );
					refepoch = strtok (NULL, " ");
					derivMeanMo = strtok (NULL, " ");
					derivMeanMo2 = strtok (NULL, " ");
					drag = strtok (NULL, " ");
					ephemeris_type = strtok (NULL, " ");
					element_number = strtok (NULL, " ");
					switch_param++;
					break;
				case 2:
					fgets(vector2,sizeof(vector2),fp);
					TLE2 = strtok (vector2, " " );
					satnumber2 = strtok (NULL, " " );
					incl = strtok (NULL, " " );
					RAAN = strtok (NULL, " ");
					eccn = strtok (NULL, " ");
					argper = strtok (NULL, " ");
					meanan = strtok (NULL, " ");
					column53_69 = strtok (NULL, " ");
					switch_param++;
					break;
				default:
					break;
				}
			}
		}


		memcpy(meanmo, &column53_69[0],10);
		memcpy(rev_num_at_epoch, &column53_69[strlen(column53_69)-7], 5);

		printf("name[%d] is %s",i ,name[i]);

		sats[i].name = name[i];
		sats[i].refepoch = atof(refepoch);
		sats[i].incl = atof(incl);
		sats[i].raan = atof(RAAN);
		sats[i].eccn = atof(eccn)/pow(10,7);
		sats[i].argper = atof(argper);
		sats[i].meanan = atof(meanan);
		sats[i].meanmo = atof(meanmo);
		sats[i].ndot = atof(derivMeanMo);
		sats[i].nddot6 = atof(derivMeanMo2);
		sats[i].bstar = atof(drag);
		sats[i].orbitnum = atof(rev_num_at_epoch);
	}
	fclose(fp);
	return 0;

}*/

int ReadNoradTLE(Satellite sats[], char *file) {
	FILE *fp = fopen(file,"r+");
	for (int i = 0; i < 3; i++) {
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
		EPOCH_YEAR,
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

	int indices1[14][2] = {
		{  0,  1 },
		{  2,  7 },
		{  7,  8 },
		{  9, 11 },
		{ 11, 14 },
		{ 14, 17 },
		{ 18, 20 },
		{ 20, 32 },
		{ 33, 43 },
		{ 44, 52 },
		{ 54, 61 },
		{ 62, 63 },
		{ 64, 68 },
		{ 68, 69 }
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
	char values1[14][128];
	char values2[10][128];

	for (i = 0; i < 3; i++) {
		fgets(lines[i], 128, fp);

		if (i == 0) {
			memset(sat->name, '\0', sizeof(char) * 128);
			strncpy(sat->name, lines[i], 128);
		} else if (i == 1) {
			for (j = 0; j < 14; j++) {
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

	sat->refepoch = atof(values1[EPOCH_YEAR]);
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














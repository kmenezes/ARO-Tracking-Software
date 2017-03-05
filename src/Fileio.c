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
			fopen(".\\station file.dat","r+");
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

int ReadNoradTLE(Satellite *sat, char line0, char line1, char line2) {
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
					/* Advance position of file pointer to next line */
					fgets(name,sizeof(name),fp);
					/* Set the pointer */
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
}

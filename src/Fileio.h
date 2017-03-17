/*
 * FileIO.h

 *
 *  Created on: Mar 2, 2017
 *      Author: james
 */
#include <stdio.h>
#include <stdlib.h>
typedef struct Station {
	char *name;
	double stnlat;
	double stnlong;
	double stnalt;
	double utc_offset;
	int az_el_nlim;
	struct az_el_lim {
		double az;
		double elmin;
		double elmax;
	} az_el_lim;
	double st_az_speed_max;
	double st_el_speed_max;
} Station;
typedef struct Satellite {
	char name[128];
	double refepoch;
	double incl;
	double raan;
	double eccn;
	double argper;
	double meanan;
	double meanmo;
	double ndot;
	double nddot6;
	double bstar;
	int orbitnum;
} Satellite;
void Banner();
void ERRMSG(char* STRING);
int ReadStationFile(Station *Stn, char STNFIL);
int ReadNoradTLE(Satellite sats[], char *file);
int ReadSingleNoradTLE(Satellite *sat, FILE *fp);
void anykey();

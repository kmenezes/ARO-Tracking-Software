/*
 * FileIO.h

 *
 *  Created on: Mar 2, 2017
 *      Author: james
 */
#include <stdio.h>
#include <stdlib.h>
typedef struct Station {
/* Station File parameters */
	char *name;
	double stnlat; //latitude
	double stnlong; //longitude
	double stnalt; //altitude
	double utc_offset; //UTC offset
	int az_el_nlim;
/* Azimuth Elevation Limit */
	struct az_el_lim {
		double az;	 //azimuth
		double elmin; //min elevation limit
		double elmax; //max elevation limit
	} az_el_lim;
	double st_az_speed_max; //max azimuth speed
	double st_el_speed_max; //max elevation speed
} Station;

typedef struct Satellite {
	char name[128]; //Satellite Name
	double refepoch; //Epoch year and day fraction
	double incl; //Inclination
	double raan; //Right Ascension of the Ascending Node
	double eccn; //Eccentricity
	double argper; //Argument of Perigee
	double meanan; //Mean Anomaly
	double meanmo; //Mean Motion
	double ndot; //1st derivative of mean motion or ballistic coefficient
	double nddot6; //2nd derivative of mean motion
	double bstar; //Drag term or radiation pressure coefficient
	int orbitnum; //Orbit Number
} Satellite;
void Banner();
void ERRMSG(char* STRING);
int ReadStationFile(Station *Stn, char STNFIL);
int ReadNoradTLE(Satellite sats[], char *file);
int ReadSingleNoradTLE(Satellite *sat, FILE *fp);
void anykey();

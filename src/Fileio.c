#include "Fileio.h"

void Banner(){
	puts("Beep");
}
/*int ReadStationFile(Station *Stn, char STNFIL){
	return 0;
}*/
/*Returns a struct with the parameters defined below. This function reads the station
parameters file and returns the values in degrees and meters for geographical coordinates,
degrees for az/el limits and deg/min for maximum az/el speeds. Use for test:*/
#ifdef Gstn
#def Gstn
typedef struct Station {
	char name = 'ARO';
	double stnlat = 45.95550333333333;
	double stnlong = 281.9269597222222;
	double stnalt = 260.42;
	double utc_offset = -4.0;
	int az_el_nlim = 1;
	struct az_el_lim {
		double az = 0.;
		double elmin = 9.0;
		double elmax = 89.0;
	} az_el_lim;
	double st_az_speed_max = 24.0;
	double st_el_speed_max = 5.0;
} Station;
#endif
/*int ReadNoradTLE(Satellite *sat, char line0, char line1, char line2){
	return 0;
}*/
/*Satellite is a struct defined as below:*/
#ifdef Satdef
#def Satdef
typedef struct Satellite {
	char name;
	double refepoch;
	double incl;
	doube raan;
	double eccn;
	double argper;
	double meanan;
	double meanmo;
	double ndot;
	double nddot6;
	double bstar;
	int orbitnum;
} Satellite;
#endif

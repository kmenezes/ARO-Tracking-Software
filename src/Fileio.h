#ifndef FILEIO_H
#define FILEIO_H

void Banner();
#ifdef Gstn
#define Gstn
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




#ifdef Satdef
#define Satdef
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

/*int ReadNoradTLE(Satellite *sat, char line0, char line1, char line2);

int ReadStationFile(Station *Stn, char STNFIL);*/

#endif /* FILEIO_H_ */



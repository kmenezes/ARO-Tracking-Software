
#include <stdio.h>
#include <math.h>
#include "Propagate.h"
#include "Basic.h"
#include "FileIO.h"
#include "Vector.h"
#include "Check.h"
#include "Datefun.h"
#include "Matrix.h"
#include "Vector.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum {false,true} boolean;
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286
#define MAX_ITERATIONS 7
#define THRESH 1.e-12
#define MIN_THRESH 1.e-15
#define CUBE_ROOT( X)  (exp( log( X) / 3.))

/*
 * The function THETAN calculates the Greenwich Mean Sidereal Time for an epoch
specified in the format used in the NORAD two-line element sets. (for example
09054.71335794) It supports dates beyond the year 1999 assuming that two-digit years
in the range 00-56 correspond to 2000-2056. It is only valid for dates through 2056
December 31.
 */
double THETAN(double TLEepoch, double JDstart){
	double JD;
	JD = jdatep(TLEepoch);
	double rads = THETAJ(JD, JDstart);
	return rads;
}

/*
 * The function THETAJ returns the Greenwich Mean Sidereal Time in radians
for an epoch specified by Julian day JD. Reference: The 1992 Astronomical Almanac,
page B6.
 */
double THETAJ (double JulianDate, double JulianDateStart){
	double JDm;
	if(JulianDateStart>=floor(JulianDateStart) + 0.5){JDm = floor(JulianDateStart) + 0.5;}
	else{JDm = floor(JulianDateStart) - 0.5;}
	double Du = JDm - 2451545.0;
	double Tu = Du / 36525.0;
	double GMST = 24110.54841 + 8640184.812866*Tu + 0.093104*Tu*Tu - 0.0000062*Tu*Tu*Tu;
	for (;GMST > 86400;){
		GMST = GMST - 86400;
	}
	double ThetaMid = 2*PI*GMST/86400;
	double r = 1.002737909350795+(5.9006/100000000000)*Tu-(5.9/1000000000000000)*Tu*Tu;
	double t = JulianDate - JDm;
	double final = ThetaMid + r*2*t*PI;
	// reduce the bounds
	while(final>2*PI){final = final - 2*PI;}
	return final;
}


/*
 * Function to calculate current mean anomaly and mean motion of the satellite
 * TESTED, WORKING
 */
int mean_anomaly_motion (double *Mt_mean_anomaly, double *nt_mean_motion, double time, double ts_sat_epoch,	double M0_mean_anomaly, double n_mean_motion, double n_dot_mean_motion,	double n_2dots_mean_motion){

	double timeinterval = (time - ts_sat_epoch)*86400.0;

	double M0_mean_anomaly_rad = M0_mean_anomaly * (PI/180);

	double n_mean_motion_rad_p_s = n_mean_motion * (2*PI/86400);
	double n_dot_mean_motion_rad_p_s = n_dot_mean_motion *(2*PI/pow(86400, 2));
	double n_2dots_mean_motion_rad_p_s = n_2dots_mean_motion * (2*PI/pow(86400, 3));

	double nt=n_mean_motion_rad_p_s + 2*(n_dot_mean_motion_rad_p_s/2)*timeinterval + 3*(n_2dots_mean_motion_rad_p_s/6)*timeinterval*timeinterval;

	double M_at_t = M0_mean_anomaly_rad + nt*timeinterval + (n_dot_mean_motion_rad_p_s/2)*(timeinterval)*(timeinterval) + (n_2dots_mean_motion_rad_p_s/6)*(timeinterval)*(timeinterval)*(timeinterval);

	for (;M_at_t > PI *2;){
		M_at_t = M_at_t - PI *2;
	}

	*Mt_mean_anomaly = M_at_t;
	*nt_mean_motion = nt;
	return 0;
}

/*
 * Function to solve Kepler’s equation, returns eccentric anomaly
 * TESTED, WORKING
 */

//Helper
double near_parabolic( const double ecc_anom, const double e){
	const double anom2 = (e > 1. ? ecc_anom * ecc_anom : -ecc_anom * ecc_anom);
	double term = e * anom2 * ecc_anom / 6.;
	double rval = (1. - e) * ecc_anom - term;
	unsigned n = 4;

	while( fabs( term) > 1e-15)
	{
		term *= anom2 / (double)(n * (n + 1));
		rval -= term;
		n += 2;
	}
	return( rval);
}

double KeplerEqn(double Mt_mean_anomaly, double eccentricity){
	double ctr, err, t, offset;
	double delta=1;
	boolean neg=false;
	unsigned n=0;

	if(!Mt_mean_anomaly){
		return 0;
	}
	if(eccentricity<1){
		if(Mt_mean_anomaly<-PI||Mt_mean_anomaly>PI){
			double tmod=fmod(Mt_mean_anomaly, PI*2);
			if(tmod>PI){
				tmod-=2*PI;
			}
			else if(tmod<-PI){
				tmod +=2*PI;
			}
			offset=Mt_mean_anomaly-tmod;
			Mt_mean_anomaly=tmod;
		}
		if(eccentricity<0.99999){
			ctr=atan2(sin(Mt_mean_anomaly),cos(Mt_mean_anomaly)-eccentricity);
			do{
				err=(ctr-eccentricity*sin(ctr)-Mt_mean_anomaly)/(1-eccentricity*cos(ctr));
				ctr-=err;
			}
			while(fabs(err)>THRESH);
			return(ctr+offset);
		}
	}

	if(Mt_mean_anomaly<0){
		Mt_mean_anomaly= -Mt_mean_anomaly;
		neg=true;
	}

	ctr=Mt_mean_anomaly;
	t=THRESH*fabs(1-eccentricity);

	if(t<MIN_THRESH){
		t=MIN_THRESH;
	}

	if(t>THRESH){
		t=THRESH;
	}

	if(Mt_mean_anomaly<PI/3||eccentricity>1){
		double trial=Mt_mean_anomaly/fabs(1-eccentricity);
		if(trial*trial>6*fabs(1-eccentricity)){
			if(Mt_mean_anomaly<PI){
				trial=CUBE_ROOT(6*Mt_mean_anomaly);
			}
			else{
				trial=asinh(Mt_mean_anomaly/eccentricity);
			}
		}
		ctr=trial;
	}

	if(eccentricity<1){
		while(fabs(delta)>t){
			if(n++>MAX_ITERATIONS){
				err=near_parabolic(ctr, eccentricity)-Mt_mean_anomaly;
			}
			else{
				err=ctr-eccentricity*sin(ctr)-Mt_mean_anomaly;
			}
			delta=-err/(1-eccentricity*cos(ctr));
			ctr+=delta;
		}
	}
	else{
		while(fabs(delta)>t){
			if(n>MAX_ITERATIONS){
				err=-near_parabolic(ctr, eccentricity)-Mt_mean_anomaly;
			}
			else{
				err=eccentricity*sinh(ctr)-ctr-Mt_mean_anomaly;
			}
			delta=-err/(eccentricity*cosh(ctr)-1);
			ctr+=delta;
		}
	}
	return(neg?offset-ctr:offset+ctr);
}


/*
// a just incase helper method
double trueanom(double ecc, double Ecc_anom){
	double true = 2*atan(sqrt((1+ecc)/(1-ecc))*tan(Ecc_anom/2));
	return true;
}
*/

/*
 * Function to calculate the current satellite position and velocity in ECI coordinates.
 * TESTED, TENTITIVELY WORKING
 */
int sat_ECI(Vector *eci_position, Vector *eci_velocity, double eccentricity, double ecc_anomaly, double a_semi_major_axis, double omega_longitude_ascending_node, double omega_argument_periapsis, double inclination, double nt_mean_motion){
	double e, E, a, capital_omega, w, i, n;
	e = eccentricity;
	E = ecc_anomaly;
	a = a_semi_major_axis;
	capital_omega = omega_longitude_ascending_node;
	w = omega_argument_periapsis;
	i = inclination;
	n = nt_mean_motion;
	// Calculating True anom. concerns with using our helper function
	double true = 2*atan(sqrt((1+e)/(1-e))*tan(E/2));
	if(true<0){
		true=true+2*PI;
	}
	//printf("True Anom: %f\n", true);
	//First time derivative of True Anomaly
	double true_dot = n*sqrt((1-pow(e,2)) / pow((1-e*cos(E)),2));
	//printf("True Anom Derivative: %f\n", true_dot);
	// range distance
	double r = (a*(1-pow(e,2)) / (1+e*cos(true)));
	//printf("Range: %f\n",r);
	// First time derivative of the spacecraft range
	double v = (a*e*(1-pow(e,2))*sin(true)*true_dot) / (pow((1+e*cos(true)),2));
	//printf("Velocity: %f\n", v);

	eci_position->x = r*(cos(capital_omega)*cos(w+true)-sin(capital_omega)*cos(i)*sin(w+true));
	eci_position->y = r*(sin(capital_omega)*cos(w+true)+cos(capital_omega)*cos(i)*sin(w+true));
	eci_position->z = r*(sin(i)*sin(w+true));
	eci_velocity->x = v*(cos(capital_omega)*cos(w+true)-sin(capital_omega)*cos(i)*sin(w+true)) + r*true_dot*(-cos(capital_omega)*sin(w+true)-sin(capital_omega)*cos(i)*cos(w+true));
	eci_velocity->y = v*(sin(capital_omega)*cos(w+true)+cos(capital_omega)*cos(i)*sin(w+true)) + r*true_dot*(-sin(capital_omega)*sin(w+true)+cos(capital_omega)*cos(i)*cos(w+true));
	eci_velocity->z = v*(sin(i)*sin(w+true)) + r*true_dot*(sin(i)*cos(w+true));
	return 0;
}

/*
 * Function to calculate the current satellite position and velocity in ECF coordinates.
 */
int sat_ECF(Vector *sat_ecf_position, Vector *sat_ecf_velocity, double theta_t, Vector *eci_position, Vector *eci_velocity){
	// initialize the constant change in theta
	double theta_dot = 7.2921158553*pow(10,-5);
	//printf("\nTheta Dot: %f\n", theta_dot);
	// T1 and T2 are the two transformation matrices. that are 3x3
	// V_1 and V_2 are the two terms of the velocity vector that are 3x1
	Matrix T1, T2, V_1, V_2;
	zero(&T1, 3, 3);
	zero(&T2, 3, 3);
	// 1st part of the ecf_velocity equation
	zero(&V_1, 3, 1);
	// 2nd part of the ecf_velocity equation
	zero(&V_2, 3, 1);

	// Setting up the first transformation matrix
	T1.elem[0][0] = cos(theta_t); T1.elem[0][1] = sin(theta_t);T1.elem[0][2] = 0;
	T1.elem[1][0] = -sin(theta_t);T1.elem[1][1] = cos(theta_t);T1.elem[1][2] = 0;
	T1.elem[2][0] = 0;T1.elem[2][1] = 0;T1.elem[2][2] = 1;
	// setting up the satellite ECF Position Matrix
	sat_ecf_position->x = T1.elem[0][0]*eci_position->x + T1.elem[0][1]*eci_position->y + T1.elem[0][2]*eci_position->z;
	sat_ecf_position->y = T1.elem[1][0]*eci_position->x + T1.elem[1][1]*eci_position->y + T1.elem[1][2]*eci_position->z;
	sat_ecf_position->z = T1.elem[2][0]*eci_position->x + T1.elem[2][1]*eci_position->y + T1.elem[2][2]*eci_position->z;
	// Setting  up the second transformation elem
	T2.elem[0][0] = -sin(theta_t);T2.elem[0][1] = cos(theta_t);T2.elem[0][2] = 0;
	T2.elem[1][0] = -cos(theta_t);T2.elem[1][1] = -sin(theta_t);T2.elem[1][2] = 0;
	T2.elem[2][0] = 0;T2.elem[2][1] = 0;T2.elem[2][2] = 0;
	// Setting up the velocity elem
	V_1.elem[0][0] = T1.elem[0][0]*eci_velocity->x + T1.elem[0][1]*eci_velocity->y + T1.elem[0][2]*eci_velocity->z;
	V_1.elem[1][0] = T1.elem[1][0]*eci_velocity->x + T1.elem[1][1]*eci_velocity->y + T1.elem[1][2]*eci_velocity->z;
	V_1.elem[2][0] = T1.elem[2][0]*eci_velocity->x + T1.elem[2][1]*eci_velocity->y + T1.elem[2][2]*eci_velocity->z;
	// calculating up the position elem
	V_2.elem[0][0] = -theta_dot*(T2.elem[0][0]*eci_position->x + T2.elem[0][1]*eci_position->y + T2.elem[0][2]*eci_position->z);
	V_2.elem[1][0] = -theta_dot*(T2.elem[1][0]*eci_position->x + T2.elem[1][1]*eci_position->y + T2.elem[1][2]*eci_position->z);
	V_2.elem[2][0] = -theta_dot*(T2.elem[2][0]*eci_position->x + T2.elem[2][1]*eci_position->y + T2.elem[2][2]*eci_position->z);
	// setting the sat_ecf_velocity elem
	sat_ecf_velocity->x = V_1.elem[0][0] - V_2.elem[0][0];
	sat_ecf_velocity->y = V_1.elem[1][0] - V_2.elem[1][0];
	sat_ecf_velocity->z = V_1.elem[2][0] - V_2.elem[2][0];
	return 0;
}


/*Function to find the current satellite position and velocity in the topocentric system
coordinates.
 */

int range_ECF2topo(Vector *range_topo_position, Vector *range_topo_velocity, Vector station_body_position, Vector *sat_ecf_position, Vector *sat_ecf_velocity, double station_longitude, double station_latitude){

	double lat, lng;
	lat=station_latitude*(PI/180);
	lng=station_longitude*(PI/180);

	Matrix T;
	zero(&T, 3, 1);

	T.elem[0][0]=station_body_position.x;
	T.elem[1][0]=station_body_position.y;
	T.elem[2][0]=station_body_position.z;


	int m, n;
	m=3;n=3;
	Matrix Trans;
	// Initialize matrix of 3x3
	zero(&Trans, m, n);

	// in matrix form it looks like
	Trans.elem[0][0] = -sin(lng);
	Trans.elem[0][1] = cos(lng);
	Trans.elem[0][2] = 0;
	Trans.elem[1][0] = -cos(lng)*sin(lat);
	Trans.elem[1][1] = -sin(lng)*sin(lat);
	Trans.elem[1][2] = cos(lat);
	Trans.elem[2][0] = cos(lng)*cos(lat);
	Trans.elem[2][1] = sin(lng)*cos(lat);
	Trans.elem[2][2] = sin(lat);

	// perform position calculations
	range_topo_position->x = Trans.elem[0][0]*(sat_ecf_position->x - T.elem[0][0]) + Trans.elem[0][1]*(sat_ecf_position->y - T.elem[1][0]) + Trans.elem[0][2]*(sat_ecf_position->z - T.elem[2][0]);
	range_topo_position->y = Trans.elem[1][0]*(sat_ecf_position->x - T.elem[0][0]) + Trans.elem[1][1]*(sat_ecf_position->y - T.elem[1][0]) + Trans.elem[1][2]*(sat_ecf_position->z - T.elem[2][0]);
	range_topo_position->z = Trans.elem[2][0]*(sat_ecf_position->x - T.elem[0][0]) + Trans.elem[2][1]*(sat_ecf_position->y - T.elem[1][0]) + Trans.elem[2][2]*(sat_ecf_position->z - T.elem[2][0]);

	// perform velocity calculations
	range_topo_velocity->x = Trans.elem[0][0]*sat_ecf_velocity->x + Trans.elem[0][1]*sat_ecf_velocity->y + Trans.elem[0][2]*sat_ecf_velocity->z;
	range_topo_velocity->y = Trans.elem[1][0]*sat_ecf_velocity->x + Trans.elem[1][1]*sat_ecf_velocity->y + Trans.elem[1][2]*sat_ecf_velocity->z;
	range_topo_velocity->z = Trans.elem[2][0]*sat_ecf_velocity->x + Trans.elem[2][1]*sat_ecf_velocity->y + Trans.elem[2][2]*sat_ecf_velocity->z;
	return 0;
}


/*
 * Function to find the current satellite look-angles at the station position.
 */
void range_topo2look_angles(LookAngles *LA, double azimuth, double elevation, double azimuth_velocity, double elevation_velocity, Vector *range_topo_position, Vector *range_topo_velocity){

	//The look angles are output in degrees FYI!!

	azimuth=atan2(range_topo_position->x,range_topo_position->y);
	elevation = atan(range_topo_position->z/sqrt(pow(range_topo_position->x,2) + pow(range_topo_position->y,2)));
	azimuth=(azimuth*180)/PI;
	elevation=(elevation*180)/PI;

	Vector *rxy, *vxy;
	rxy = (Vector*)malloc(sizeof(Vector));
	vxy = (Vector*)malloc(sizeof(Vector));
	rxy->x=range_topo_position->x;
	rxy->y=range_topo_position->y;
	rxy->z=0;
	rxy->mag=magntd(*rxy);
	vxy->x=range_topo_velocity->x;
	vxy->y=range_topo_velocity->y;
	vxy->z=0;
	vxy->mag=magntd(*vxy);
	range_topo_position->mag=magntd(*range_topo_position);
	Vector *v;
	v = (Vector*)malloc(sizeof(Vector));
	mycross(v, vxy, rxy);
	azimuth_velocity=(1/pow(rxy->mag, 2)) * v->z;
	elevation_velocity=(1/pow(range_topo_position->mag, 2))*((rxy->mag*range_topo_velocity->z)-(range_topo_position->z/rxy->mag)*(rxy->mag*vxy->mag*myangle(rxy, vxy)));
	LA->azimuth = azimuth;
	LA->azimuth_velocity = azimuth_velocity;
	LA->elevation = elevation;
	LA->elevation_velocity = elevation_velocity;
}

double linkstrength(double range){
	double fre = 1575.42;
	double eff = 0.7;
	double diam = 46;//m
	double BW = 2.;
	double RCV_gain = 56.;
	double RCV_noise = 200.;
	double light = 299792458; // m/s

	double EIRP = 8.3988; //3dBW
	double La = 0.1; //dBW
	double temp = pow((light/(4*PI*fre*range*1000)),2);
	double Ls = 10*log(temp);// dB
	double Gr = 10*log((((PI*PI) * (fre*fre) * (diam*diam) *eff)/light*light));// dB
	double linksstren = EIRP - La + Gr + Ls +30;

	return linksstren;
}


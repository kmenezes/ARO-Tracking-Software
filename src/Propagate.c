/*
 * Propagate.c
 *
 *  Created on: Mar 5, 2017
 *      Author: User
 */
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum {false,true} boolean;
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286
#define MAX_ITERATIONS 7
#define THRESH 1.e-12
#define MIN_THRESH 1.e-15
#define CUBE_ROOT( X)  (exp( log( X) / 3.))


double THETAN(double TLEepoch){
	double num = TLEepoch;
	num = TLEepoch/1000;
	double year = num - frac(num);
	double day = TLEepoch - year*1000;
	double yearf = year + 2000;
	double JDy = jdaty(yearf);
	double JD = JDy + day -1;
	double rads = THETAJ(JD);
	return rads;
}

double THETAJ (double JulianDate){
	double JDm;
	if(JulianDate>=floor(JulianDate) + 0.5){JDm = floor(JulianDate) + 0.5;}
	else{JDm = floor(JulianDate) - 0.5;}
	double Du = JulianDate - 2451545.0;
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


// a just incase helper method
double trueanom(double eccentricity, double E){
	double S = sin(E);
	double C = cos(E);
	double var = sqrt(1.0 - eccentricity*eccentricity);
	double true = atan2(var*S,C - eccentricity);
	return true;
}

//nt_mean_motion at time t
//ts = start time from TLE
// Function to calculate current mean anomaly and mean motion of the satellite
int mean_anomaly_motion (double *Mt_mean_anomaly, double *nt_mean_motion,
		double time, double ts_sat_epoch,
		double M0_mean_anomaly, //ts epoch mean anom
		double n_mean_motion,
		double n_dot_mean_motion,
		double n_2dots_mean_motion){

	// assumes it inputs julian dates// needs to be julian
	double timeinterval = time - ts_sat_epoch;
	double M0_mean_anomaly_rad = M0_mean_anomaly * (PI/180);
	// Convert all from rev/day -> rad/sec
	double n_mean_motion_rad_p_s = n_mean_motion * (2*PI/86400);
	double n_dot_mean_motion_rad_p_s = n_dot_mean_motion *(2*PI/86400);
	double n_2dots_mean_motion_rad_p_s = n_2dots_mean_motion * (2*PI/86400);
	// Calculate M_at_t
	double M_at_t = M0_mean_anomaly_rad + n_mean_motion_rad_p_s*timeinterval + (n_dot_mean_motion_rad_p_s/2)*(timeinterval)*(timeinterval) + (n_2dots_mean_motion_rad_p_s/6)*(timeinterval)*(timeinterval)*(timeinterval);
	// Same code as in Fixang, but due to passing by value must be re-done inside this function
	for (;M_at_t > PI *2;){
		M_at_t = M_at_t - PI *2;}
	// Change References to Mt_mean_anomaly and nt_mean_motion
	*Mt_mean_anomaly = M_at_t;
	*nt_mean_motion = n_mean_motion_rad_p_s + 2*(n_dot_mean_motion_rad_p_s/2)*timeinterval + 3*(n_2dots_mean_motion_rad_p_s/6)*timeinterval*timeinterval;
	return 0;
}


/*
Source https://www.projectpluto.com/kepler.htm
 */
/* If the eccentricity is very close to parabolic,  and the eccentric
anomaly is quite low,  you can get an unfortunate situation where
roundoff error keeps you from converging.  Consider the just-barely-
elliptical case,  where in Kepler's equation,

M = E - e sin( E)

   E and e sin( E) can be almost identical quantities.  To
around this,  near_parabolic( ) computes E - e sin( E) by expanding
the sine function as a power series:

E - e sin( E) = E - e( E - E^3/3! + E^5/5! - ...)
= (1-e)E + e( -E^3/3! + E^5/5! - ...)

   It's a little bit expensive to do this,  and you only need do it
quite rarely.  (I only encountered the problem because I had orbits
that were supposed to be 'pure parabolic',  but due to roundoff,
they had e = 1+/- epsilon,  with epsilon _very_ small.)  So 'near_parabolic'
is only called if we've gone seven iterations without converging. */
// Helper method
double near_parabolic( const double ecc_anom, const double e)
{
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
void range_topo2look_angles(LookAngles *LA, double azimuth, double elevation, double azimuth_velocity, double elevation_velocity, Vector *range_topo_position, Vector *range_topo_velocity){
	azimuth=atan(range_topo_position->x/range_topo_position->y);
	elevation=atan(range_topo_position->z/(sqrt(pow(range_topo_position->x, 2)+pow(range_topo_position->y, 2))));
	azimuth=(azimuth*180)/3.14;
	elevation=(elevation*180)/3.14;
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

int range_ECF2topo(Vector *range_topo_position, Vector *range_topo_velocity, Vector station_body_position, Vector *sat_ecf_position,
		Vector *sat_ecf_velocity, double station_longitude, double station_latitude){
	int m, n;m=3;n=3;
	Matrix Trans;
	// Initialize matrix of 3x3
	zero(&Trans, m, n);
	// in matrix form it looks like
	Trans.matrix[0][0] = -sin(station_longitude);	Trans.matrix[0][1] = cos(station_longitude);Trans.matrix[0][2] = 0;
	Trans.matrix[1][0] = -cos(station_longitude)*sin(station_latitude);Trans.matrix[1][1] = -sin(station_longitude)*sin(station_latitude);Trans.matrix[1][2] = cos(station_latitude);
	Trans.matrix[2][0] = cos(station_longitude)*cos(station_latitude);Trans.matrix[2][1] = sin(station_longitude)*cos(station_latitude);Trans.matrix[2][2] = sin(station_latitude);
	// perform position calculations
	range_topo_position->x = Trans.matrix[0][0]*sat_ecf_position->x + Trans.matrix[0][1]*sat_ecf_position->y + Trans.matrix[0][2]*sat_ecf_position->z;
	range_topo_position->y = Trans.matrix[1][0]*sat_ecf_position->x + Trans.matrix[1][1]*sat_ecf_position->y + Trans.matrix[1][2]*sat_ecf_position->z;
	range_topo_position->z = Trans.matrix[2][0]*sat_ecf_position->x + Trans.matrix[2][1]*sat_ecf_position->y + Trans.matrix[2][2]*sat_ecf_position->z;
	// perform velocity calculations
	range_topo_velocity->x = Trans.matrix[0][0]*sat_ecf_velocity->x + Trans.matrix[0][1]*sat_ecf_velocity->y + Trans.matrix[0][2]*sat_ecf_velocity->z;
	range_topo_velocity->y = Trans.matrix[1][0]*sat_ecf_velocity->x + Trans.matrix[1][1]*sat_ecf_velocity->y + Trans.matrix[1][2]*sat_ecf_velocity->z;
	range_topo_velocity->z = Trans.matrix[2][0]*sat_ecf_velocity->x + Trans.matrix[2][1]*sat_ecf_velocity->y + Trans.matrix[2][2]*sat_ecf_velocity->z;
	return 0;
}
int sat_ECI(Vector *eci_position, Vector *eci_velocity, double eccentricity, double ecc_anomaly, double a_semi_major_axis, double omega_longitude_ascending_node, double omega_argument_periapsis, double inclination, double nt_mean_motion){
	double e, E, a, capital_omegs, w, i, n;
	e = eccentricity;
	E = ecc_anomaly;
	a = a_semi_major_axis;
	capital_omegs = omega_longitude_ascending_node;
	w = omega_argument_periapsis;
	i = inclination;
	n = nt_mean_motion;
	// Calculating True anom. concerns with using our helper function
	double true = 2*atan(sqrt((1+e)/(1-e))*tan(E/2));
	//First time derivative of True Anomaly
	double true_dot = n*sqrt((1-pow(e,2)) / pow((1-e*cos(E)),2));
	// range distance
	double r = (a*(1-pow(e,2)) / (1+e*cos(true)));
	// First time derivative of the spacecraft range
	double v = (a*e*(1-pow(e,2))*sin(true)*true_dot) / (pow((1+e*cos(true)),2));
	eci_position->x = r*(cos(capital_omegs)*cos(w+true)-sin(capital_omegs)*cos(i)*sin(w+true));
	eci_position->y = r*(sin(capital_omegs)*cos(w+true)+cos(capital_omegs)*cos(i)*sin(w+true));
	eci_position->z = r*(sin(i)*sin(w+true));
	eci_velocity->x = v*(cos(capital_omegs)*cos(w+true)-sin(capital_omegs)*cos(i)*sin(w+true)) + r*true_dot*(-cos(capital_omegs)*sin(w+true)-sin(capital_omegs)*cos(i)*cos(w+true));
	eci_velocity->y = v*(sin(capital_omegs)*cos(w+true)+cos(capital_omegs)*cos(i)*sin(w+true)) + r*true_dot*(-sin(capital_omegs)*sin(w+true)+cos(capital_omegs)*cos(i)*cos(w+true));
	eci_velocity->z = v*(sin(i)*sin(w+true)) + r*true_dot*(sin(i)*cos(w+true));
	return 0;
}
int sat_ECF(Vector *sat_ecf_position, Vector *sat_ecf_velocity, double theta_t, Vector *eci_position, Vector *eci_velocity){
	// initialize the constant change in theta
	double theta_dot = 7.2921158553*pow(10,-5);
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
	T1.matrix[0][0] = cos(theta_t); T1.matrix[0][1] = sin(theta_t);T1.matrix[0][2] = 0;
	T1.matrix[1][0] = -sin(theta_t);T1.matrix[1][1] = cos(theta_t);T1.matrix[1][2] = 0;
	T1.matrix[2][0] = 0;T1.matrix[2][1] = 0;T1.matrix[2][2] = 1;
	// setting up the satellite ECF Position Matrix
	sat_ecf_position->x = T1.matrix[0][0]*eci_position->x + T1.matrix[0][1]*eci_position->y + T1.matrix[0][2]*eci_position->z;
	sat_ecf_position->y = T1.matrix[1][0]*eci_position->x + T1.matrix[1][1]*eci_position->y + T1.matrix[1][2]*eci_position->z;
	sat_ecf_position->z = T1.matrix[2][0]*eci_position->x + T1.matrix[2][1]*eci_position->y + T1.matrix[2][2]*eci_position->z;
	// Setting  up the second transformation matrix
	T2.matrix[0][0] = -sin(theta_t);T2.matrix[0][1] = cos(theta_t);T2.matrix[0][2] = 0;
	T2.matrix[1][0] = -cos(theta_t);T2.matrix[1][1] = -sin(theta_t);T2.matrix[1][2] = 0;
	T2.matrix[2][0] = 0;T2.matrix[2][1] = 0;T2.matrix[2][2] = 0;
	// Setting up the velocity matrix
	V_1.matrix[0][0] = T1.matrix[0][0]*eci_velocity->x + T1.matrix[0][1]*eci_velocity->y + T1.matrix[0][2]*eci_velocity->z;
	V_1.matrix[1][0] = T1.matrix[1][0]*eci_velocity->x + T1.matrix[1][1]*eci_velocity->y + T1.matrix[1][2]*eci_velocity->z;
	V_1.matrix[2][0] = T1.matrix[2][0]*eci_velocity->x + T1.matrix[2][1]*eci_velocity->y + T1.matrix[2][2]*eci_velocity->z;
	// calculating up the position matrix
	V_2.matrix[0][0] = -theta_dot*(T2.matrix[0][0]*eci_position->x + T2.matrix[0][1]*eci_position->y + T2.matrix[0][2]*eci_position->z);
	V_2.matrix[1][0] = -theta_dot*(T2.matrix[1][0]*eci_position->x + T2.matrix[1][1]*eci_position->y + T2.matrix[1][2]*eci_position->z);
	V_2.matrix[2][0] = -theta_dot*(T2.matrix[2][0]*eci_position->x + T2.matrix[2][1]*eci_position->y + T2.matrix[2][2]*eci_position->z);
	// setting the sat_ecf_velocity matrix
	sat_ecf_velocity->x = V_1.matrix[0][0] - V_2.matrix[0][0];
	sat_ecf_velocity->y = V_1.matrix[1][0] - V_2.matrix[1][0];
	sat_ecf_velocity->z = V_1.matrix[2][0] - V_2.matrix[2][0];
	return 0;
}

double KeplerEqn(double Mt_mean_anomaly,const double eccentricity){
	double curr, err, thresh, offset = 0.0;
	double delta_curr = 1.0;
	boolean is_negative = false;
	unsigned n_iter = 0;
	if( !Mt_mean_anomaly)
		return( 0.);
	if( eccentricity < 1.)
	{
		if( Mt_mean_anomaly < -PI || Mt_mean_anomaly > PI)
		{
			double tmod = fmod( Mt_mean_anomaly, PI * 2.);

			if( tmod > PI)             /* bring mean anom within -pi to +pi */
				tmod -= 2. * PI;
			else if( tmod < -PI)
				tmod += 2. * PI;
			offset = Mt_mean_anomaly - tmod;
			Mt_mean_anomaly = tmod;
		}

		if( eccentricity < .99999)     /* low-eccentricity formula from Meeus,  p. 195 */
		{
			curr = atan2( sin( Mt_mean_anomaly), cos( Mt_mean_anomaly) - eccentricity);
			do
			{
				err = (curr - eccentricity * sin( curr) - Mt_mean_anomaly) / (1. - eccentricity * cos( curr));
				curr -= err;
			}
			while( fabs( err) > THRESH);
			return( curr + offset);
		}
	}

	if( Mt_mean_anomaly < 0.)
	{
		Mt_mean_anomaly = -Mt_mean_anomaly;
		is_negative = true;
	}

	curr = Mt_mean_anomaly;
	thresh = THRESH * fabs( 1. - eccentricity);
	/* Due to roundoff error,  there's no way we can hope to */
	/* get below a certain minimum threshhold anyway:        */
	if( thresh < MIN_THRESH)
		thresh = MIN_THRESH;
	if( thresh > THRESH)       /* i.e.,  ecc > 2. */
		thresh = THRESH;
	if( Mt_mean_anomaly < PI / 3. || eccentricity > 1.)    /* up to 60 degrees */
	{
		double trial = Mt_mean_anomaly / fabs( 1. - eccentricity);

		if( trial * trial > 6. * fabs(1. - eccentricity))   /* cubic term is dominant */
		{
			if( Mt_mean_anomaly < PI)
				trial = CUBE_ROOT( 6. * Mt_mean_anomaly);
			else        /* hyperbolic w/ 5th & higher-order terms predominant */
				trial = asinh( Mt_mean_anomaly / eccentricity);
		}
		curr = trial;
	}
	if( eccentricity < 1.)
		while( fabs( delta_curr) > thresh)
		{
			if( n_iter++ > MAX_ITERATIONS)
				err = near_parabolic( curr, eccentricity) - Mt_mean_anomaly;
			else
				err = curr - eccentricity * sin( curr) - Mt_mean_anomaly;
			delta_curr = -err / (1. - eccentricity * cos( curr));
			curr += delta_curr;
		}
	else
		while( fabs( delta_curr) > thresh)
		{
			if( n_iter++ > MAX_ITERATIONS)
				err = -near_parabolic( curr, eccentricity) - Mt_mean_anomaly;
			else
				err = eccentricity * sinh( curr) - curr - Mt_mean_anomaly;
			delta_curr = -err / (eccentricity * cosh( curr) - 1.);
			curr += delta_curr;
		}
	return( is_negative ? offset - curr : offset + curr);
}

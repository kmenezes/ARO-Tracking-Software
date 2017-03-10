/*
 * Propagate.c
 *
 *  Created on: Mar 5, 2017
 *      Author: User
 */
#include <stdio.h>
#include <math.h>
#include "Propagate.h"
#include "Vector.h"
#include "DateAndTimeCalculations.h"
#include "Matrix.h"
typedef enum {false,true} boolean;
#define PI 3.1415926535897932384626433832795028841971693993751058209749445923
#define MAX_ITERATIONS 7
#define THRESH 1.e-12
#define MIN_THRESH 1.e-15
#define CUBE_ROOT( X)  (exp( log( X) / 3.))


double THETAN(double TLEepoch){

	double num = TLEepoch;

	num = TLEepoch/1000;
	printf("%f\n",num);

	double year = num - frac(num);
	double day = TLEepoch - year*1000;
	double yearf = year + 2000;
	printf("%f\n",yearf);
	double JDy = jdaty(yearf);
	double JD = JDy + day -1;
	double rads = THETAJ(JD);
	printf("%f\n",JD);
	printf("%f\n",rads);
	return rads;


}

double THETAJ (double JulianDate){
	//NOT CORRECT?
	double d = JulianDate - 2451545.0;
	double T = d / 36525.0;
	double GMSTd = 24110.54841 + 8640184.812866*T + 0.093104*T*T - 0.0000062*T*T*T;
	double degrees = GMSTd;
	for (;degrees > 86400;){
			degrees = degrees - 86400;
		}
	double rads = (degrees*2*3.14159265359)/86400;
	//double r = 1.002737909350795+(5.9006/100000000000)*T-(5.9/1000000000000000)*T*T;
	double final = rads;// + r*2*3.14159265359;
	return final;
}

int range_topo2look_angles(double azimuth, double elevation, double azimuth_velocity, double elevation_velocity, Vector *range_topo_position, Vector *range_topo_velocity){
	azimuth=atan(range_topo_position->x/range_topo_position->y);
	elevation=atan(range_topo_position->z/(sqrt(pow(range_topo_position->x, 2)+pow(range_topo_position->y, 2))));
	azimuth=(azimuth*180)/PI;
	elevation=(elevation*180)/PI;
	Vector *rxy, *vxy;
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
	int l=mycross(v, vxy, rxy);

	azimuth_velocity=(1/pow(rxy->mag, 2)) * v->z;
	elevation_velocity=(1/pow(range_topo_position->mag, 2))*((rxy->mag*range_topo_velocity->z)-(range_topo_position->z/rxy->mag)*(rxy->mag*vxy->mag*myangle(rxy, vxy)));


	return 0;
}




double trueanom(double eccentricity, double E){
	double S = sin(E);
	double C = cos(E);
	double fucking = sqrt(1.0 - eccentricity*eccentricity);
	double bitch = atan2(fucking*S,C - eccentricity);
	return bitch;
}

//nt_mean_motion at time t
//ts = start time from TLE
// Function to calculate current mean anomaly and mean motion of the satellite
int mean_anomaly_motion (double Mt_mean_anomaly, double nt_mean_motion,
		double time, double ts_sat_epoch,
		double M0_mean_anomaly, //ts epoch mean anom
		double n_mean_motion,
		double n_dot_mean_motion,
		double n_2dots_mean_motion){

	//not sure what time is being input as ??? assumes it inputs julian dates
	// needs to be julian
	double timeinterval = time - ts_sat_epoch;

	double M0_mean_anomaly_rad = M0_mean_anomaly * (PI/180);

	// rev/day -> rad/sec
	double n_mean_motion_rad_p_s = n_mean_motion * (2*PI/86400);
	double n_dot_mean_motion_rad_p_s = n_dot_mean_motion *(2*PI/86400);
	double n_2dots_mean_motion_rad_p_s = n_2dots_mean_motion * (2*PI/86400);

	double M_at_t = M0_mean_anomaly_rad + n_mean_motion_rad_p_s*timeinterval + (n_dot_mean_motion_rad_p_s/2)*(timeinterval)*(timeinterval) + (n_2dots_mean_motion_rad_p_s/6)*(timeinterval)*(timeinterval)*(timeinterval);

	double newangle = fixang(M_at_t);
	printf("\n The current mean motion is %f \n", newangle);
	return 0;
}


/*
https://www.projectpluto.com/kepler.htm
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

int range_ECF2topo(Vector *range_topo_position, Vector *range_topo_velocity, Vector station_body_position, Vector *sat_ecf_position,
Vector *sat_ecf_velocity, double station_longitude, double station_latitude){

	int m, n;
	m=3;
	n=3;

	Matrix T;

	zero(&T, m, n);

	T.matrix[0][0] = -sin(station_longitude);
	T.matrix[0][1] = cos(station_longitude);
	T.matrix[0][2] = 0;
	T.matrix[1][0] = -cos(station_longitude)*sin(station_latitude);
	T.matrix[1][1] = -sin(station_longitude)*sin(station_latitude);
	T.matrix[1][2] = cos(station_latitude);
	T.matrix[2][0] = cos(station_longitude)*cos(station_latitude);
	T.matrix[2][1] = sin(station_longitude)*cos(station_latitude);
	T.matrix[2][2] = sin(station_latitude);

	range_topo_position->x = T.matrix[0][0]*sat_ecf_position->x + T.matrix[0][1]*sat_ecf_position->y + T.matrix[0][2]*sat_ecf_position->z;
	range_topo_position->y = T.matrix[1][0]*sat_ecf_position->x + T.matrix[1][1]*sat_ecf_position->y + T.matrix[1][2]*sat_ecf_position->z;
	range_topo_position->z = T.matrix[2][0]*sat_ecf_position->x + T.matrix[2][1]*sat_ecf_position->y + T.matrix[2][2]*sat_ecf_position->z;

	range_topo_velocity->x = T.matrix[0][0]*sat_ecf_velocity->x + T.matrix[0][1]*sat_ecf_velocity->y + T.matrix[0][2]*sat_ecf_velocity->z;
	range_topo_velocity->y = T.matrix[1][0]*sat_ecf_velocity->x + T.matrix[1][1]*sat_ecf_velocity->y + T.matrix[1][2]*sat_ecf_velocity->z;
	range_topo_velocity->y = T.matrix[2][0]*sat_ecf_velocity->x + T.matrix[2][1]*sat_ecf_velocity->y + T.matrix[2][2]*sat_ecf_velocity->z;

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

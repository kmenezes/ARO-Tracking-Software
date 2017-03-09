/*
 * Propagate.h
 *
 *  Created on: Mar 5, 2017
 *      Author: user
 */
#include "Vector.h"
#ifndef PROPAGATE_H_
#define PROPAGATE_H_

double trueanom(double eccentricity, double E);


/* For a full description of this function,  see KEPLER.HTM on the Guide
Web site,  http://www.projectpluto.com.  There was a long thread about
solutions to Kepler's equation on sci.astro.amateur,  and I decided to
go into excruciating detail as to how it's done below. */


double KeplerEqn(double Mt_mean_anomaly, const double eccentricity);

/*
 * Functions to write satellite time, position and velocity resolved into a particular
Coordinate system. The function outputs the data to EphemFile in STK ephemeris
format for checking purposes.
 * */
int STKout(char outfile, char EphemFile, char StartString, double time,
Vector *Coord, Vector *position, Vector *velocity);


// Function to find the current satellite look-angles at the station position.
int range_topo2look_angles(double azimuth, double elevation,
double azimuth_velocity, double elevation_velocity,
Vector *range_topo_position, Vector *range_topo_velocity);

/*
 * Function to find the current satellite position and velocity in the topocentric system
coordinates.*/
int range_ECF2topo(Vector *range_topo_position, Vector *range_topo_velocity,
Vector station_body_position, Vector *sat_ecf_position,
Vector *sat_ecf_velocity, double station_longitude,
double station_latitude);

//Function to find the current station position in ECF coordinates.
int station_ECF(Vector *stn_ECF_pos, double station_longitude, double station_latitude, double station_elevation){



// Function to calculate the current satellite position and velocity in ECF coordinates.
int sat_ECF(Vector *sat_ecf_position, Vector *sat_ecf_velocity,
double theta_t, Vector *eci_position, Vector *eci_velocity);

// Function to calculate the current satellite position and velocity in ECI coordinates.
int sat_ECI(Vector *eci_position, Vector *eci_velocity,
double eccentricity, double ecc_anomaly, double a_semi_major_axis,
double omega_longitude_ascending_node, double omega_argument_periapsis,
double inclination, double nt_mean_motion);

// Function to calculate current mean anomaly and mean motion of the satellite
int mean_anomaly_motion (double Mt_mean_anomaly, double nt_mean_motion,
double time, double ts_sat_epoch,
double M0_mean_anomaly,
double n_mean_motion,
double n_dot_mean_motion,
double n_2dots_mean_motion);

// The function THETAJ returns the Greenwich Mean Sidereal Time in radians
// or an epoch specified by Julian day JD. Reference: The 1992 Astronomical Almanac,
// page B6. [Test: 2451544.50D0]
double THETAJ(double JulianDate);

/*The function THETAN calculates the Greenwich Mean Sidereal Time for an epoch
specified in the format used in the NORAD two-line element sets. (for example
09054.71335794) It supports dates beyond the year 1999 assuming that two-digit years
in the range 00-56 correspond to 2000-2056. It is only valid for dates through 2056
December 31.*/
double THETAN(double TLEepoch);


#endif /* PROPAGATE_H_ */

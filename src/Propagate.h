
#include "Vector.h"
#ifndef PROPAGATE_H_
#define PROPAGATE_H_

typedef struct LookAngles {
	double azimuth_velocity;
	double elevation_velocity;
	double azimuth;
	double elevation;
} LookAngles;


double THETAJ(double JulianDate, double JulianDateStart);

double THETAN(double TLEepoch, double JDstart);

double trueanom(double eccentricity, double E);

int mean_anomaly_motion (double *Mt_mean_anomaly, double *nt_mean_motion, double time, double ts_sat_epoch, double M0_mean_anomaly, double n_mean_motion, double n_dot_mean_motion, double n_2dots_mean_motion);

double near_parabolic( const double ecc_anom, const double e);

double KeplerEqn(double Mt_mean_anomaly, const double eccentricity);

int sat_ECI(Vector *eci_position, Vector *eci_velocity, double eccentricity, double ecc_anomaly, double a_semi_major_axis, double omega_longitude_ascending_node, double omega_argument_periapsis, double inclination, double nt_mean_motion);

int sat_ECF(Vector *sat_ecf_position, Vector *sat_ecf_velocity, double theta_t, Vector *eci_position, Vector *eci_velocity);

int range_ECF2topo(Vector *range_topo_position, Vector *range_topo_velocity, Vector station_body_position, Vector *sat_ecf_position, Vector *sat_ecf_velocity, double station_longitude, double station_latitude);

void range_topo2look_angles(LookAngles *LA, double azimuth, double elevation, double azimuth_velocity, double elevation_velocity, Vector *range_topo_position, Vector *range_topo_velocity);

double linkstrength(double range);

#endif /* PROPAGATE_H_ */

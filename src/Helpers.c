/*
 * Helpers.c
 *
 *  Created on: Mar 18, 2017
 *      Author: User
 */

#include "Propagate.h"
#include "DateAndTimeCalculations.h"
#include <math.h>
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286

/*
 * Function to print the AOS/LOS link strength
 *Frequency band = 1227
 *Frequency Antenna efficiency = 0.70
 *Frequency Antenna diameter = 46
 *Frequency Bandwidth = 2
 *Frequency RCV Gain = 56
 *Frequency RCV noise temp = 200
 *
 * */
/*
double linkstrength(double range){
	double fre = 1227.0;
	double eff = 0.7;
	double diam = 46;//m
	double BW = 2;
	double RCV_gain = 56;
	double RCV_noise = 200;
	double light = 3*10^8; // m/s

	double EIRP = 8.3988; //3dBW
	double La = 0.1; //dBW
	double Ls = 10*log((light/(4*PI*fre*range*1000))^2);// dB
	double Gr = 10*log((((PI*PI) * (fre*fre) * (diam*diam) *eff)/light*light));// dB
	double linksstren = EIRP - La + Gr + Ls +30;

	return linksstren;
}
*/


//double a = log(10);



/*
 * Function used to compute the available satellites. AOS/LOS Tables
 *
 * Inputs from TLE -> Sat Epoch
 * Inputs from us -> propagation 'start' time (use dat2jd)
 * 				  -> propagation 'stop' time (use dat2jd)
 * Pointers to variables created in main
 * l1 - Array 1
 * l2 - Array 2
 *
 * */

/*
A function that returns the look angles as well as the position and velocity vectors
of the satellite in the topocentric coordinates

Arguments:
1. TLEFile or Satellites in the TLE
2. ST - station parameters
3. Start - Propagation start time
4. Stop - Propagation stop time

Returns:
- avSat -> list of the AOS/LOS info
- satList -> list of satellite info
 */

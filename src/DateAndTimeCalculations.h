/*
 * DateAndTimeCalculations.h
 *
 *  Created on: Mar 4, 2017
 *      Author: james
 */

#ifndef DATEANDTIMECALCULATIONS_H_
#define DATEANDTIMECALCULATIONS_H_

double jdaty(double YEAR);
double jdatep(double EPOCH);
double doy (int YR, int MO, int D);
double frcofd (int HR, int MI, int SE);
double dat2jd (char *DateString);
char* jd2dat(double JulianDate);
char* curday();

#endif /* DATEANDTIMECALCULATIONS_H_ */

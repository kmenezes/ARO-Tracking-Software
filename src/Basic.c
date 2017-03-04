#include <stdio.h>
#include "Basic.h"
#include "Vector.h"
#include "Datefun.h"
#include <math.h>


double sinm1(double ARG) {
	if(abs(ARG) <= 1){
		return asin(ARG);
	}
	if(abs(ARG) >= 1){
		return PI;
	}
}

double cosm1(double ARG){
	if(abs(ARG) <= 1){
		return acos(ARG);
	}
	if(abs(ARG) >= 1){
		return 0;
	}
}

double frac(double ARG){
	int intpart = (int)ARG;
	double decpart = ARG - intpart;
	return decpart;
}

double fixang(double ang_in){
	return ang_in - 2*PI;
}




#include "Basic.h"
#include <Math.h>
#include <stdlib.h>
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286

/*
 * Returns the arcsine of ARG when ARG<=1
 * Returns Pi/2 when ARG>=1
 */
double sinm1(double ARG){
	if(ARG>=1){
		return PI/2;
	}
	else if(ARG<=-1){
		return -1*PI/2;
	}
	return asin(ARG);
}


/*
 * Returns the arccosine of ARG when ARG<=1
 * Returns 0 when ARG>=1
 * Returns Pi when ARG<=-1
 */
double cosm1(double ARG){
	if(ARG>=1){
		return 0;
	}
	else if(ARG<=-1){
		return PI;
	}
	return acos(ARG);
}


/*
 * Returns the fractional part of ARG
 */
double frac(double ARG){
	if(ARG<0){
		while(ARG<=-1){
			ARG=ARG+1;
		}
	}
	if(ARG>0){
		while(ARG>=1){
			ARG=ARG-1;
		}
	}
	return ARG;
}

/*
 * Reduces angles greater than 2Pi
 */
double fixang(double ang_in){
	if(ang_in>0){
		while(ang_in>2*PI){
			ang_in=ang_in-2*PI;
		}
	}
	else{
		while(ang_in<-(2*PI)){
			ang_in=ang_in+2*PI;
		}
	}
	return ang_in;
}
/*
 * Reduces degree angles greater than 360
 * used only for look angles in main function
 */
double fixangdeg(double ang_in){
	if(ang_in>0){
		while(ang_in>360){
			ang_in=ang_in-360;
		}
	}
	else{
		while(ang_in<-360){
			ang_in=ang_in+360;
		}
	}
	return ang_in;
}




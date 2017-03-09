/*
 * Vector.c
 *
 *  Created on: Mar 2, 2017
 *      Author: james_keith
 */

#include <stdio.h>
#include "Vector.h"
#include <stdlib.h>
#include <math.h>

double myangle(Vector *v1, Vector *v2){
	double theta, n, d;
	n = v1->x*v2->x + v1->y*v2->y + v1->z*v2->z;
	double maga, magb;
	maga = sqrt(pow(v1->x,2) + pow(v1->y,2) + pow(v1->z,2));
	magb = sqrt(pow(v2->x,2) + pow(v2->y,2) + pow(v2->z,2));
	d = maga*magb;
	theta=acos(n/d);
	return theta;
}
double magntd(struct Vector V){
	double magnitude = 0;
	magnitude = sqrt(pow(V.x,2) + pow(V.y,2) + pow(V.z,2));
	return magnitude;
}
int mycross(Vector*v3, Vector*v1, Vector*v2){
	if (v3 == NULL){
		return -1;
	}
	v3->x = v1->y*v2->z - v1->z*v2->y;
	v3->y = v1->z*v2->x - v1->x*v2->z;
	v3->z = v1->x*v2->y - v1->y*v2->x;
	double mag1 = magntd(*v1);
	double mag2 = magntd(*v2);
	v3->mag = mag1*mag2*sin(myangle(v1, v2));
	return 0;
}
int vecadd(Vector*v3, Vector*v1, Vector*v2){
	if(v3 == NULL){
		return -1;
	}
	v3->x = v1->x + v2->x;
	v3->y = v1->y + v2->y;
	v3->z = v1->z + v2->z;
	v3->mag = magntd(*v3);
	return 0;
}
int station_ECF(Vector *stn_ECF_pos, double station_longitude, double station_latitude, double station_elevation){
	double PI=3.1415926;
	double X, Y, Z, n, a, e2, f;
	f=1/298.257223563;
	double lat_rad, long_rad;
	lat_rad=station_latitude*(PI/180);
	long_rad=station_longitude*(PI/180);
	e2=2*f-f*f;
	a=6378137;
	n=a/(sqrt(1-e2*sin(lat_rad)*sin(lat_rad)));
	X=(n+station_elevation)*cos(lat_rad)*cos(long_rad);
	Y=(n+station_elevation)*cos(lat_rad)*sin(long_rad);
	Z=(n*(1-e2)+station_elevation)*sin(lat_rad);
	stn_ECF_pos->x=X;
	stn_ECF_pos->y=Y;
	stn_ECF_pos->z=Z;
	stn_ECF_pos->mag=magntd(*stn_ECF_pos);
	return 0;
}

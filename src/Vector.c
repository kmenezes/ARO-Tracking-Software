/*
 * This module defines all the functions needed to deal with vectors – position, velocity, etc.
 * NOTE : Position and velocity vectors are to be represented by a 4 element struct called
 * Vector. The first 3 elements are the components of the vector in a particular coordinate
 * system. The 4th element is the norm or magnitude of the vector.
 * */
#include "Vector.h"
#include <Math.h>
#include <stdlib.h>
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286
/*
 * Returns the angle between vectors v1 and v2
 */
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

/*
 * Returns the scalar magnitude of a vector
 */
double magntd(struct Vector VECTR){
	double m=sqrt(pow(VECTR.x, 2) + pow(VECTR.y, 2) + pow(VECTR.z, 2));
	return m;
}

/*
 * Calculates the vector cross product of two input vectors v1, v2
 * Returns -1 if v3==NULL
 * Returns 0 otherwise
 */
int mycross(Vector *v3, Vector *v1, Vector *v2){

	double X, Y, Z;
	v3->x=v1->y*v2->z-v1->z*v2->y;
	v3->y=-(v1->x*v2->z-v1->z*v2->x);
	v3->z=v1->x*v2->y-v1->y*v2->x;
	double maga, magb;
	maga=magntd(*v1);
	magb=magntd(*v2);

	v3->mag=maga*magb*sin(myangle(v1,v2));

	if(v3==NULL){
		return -1;
	}
	return 0;
}

/*
 * Adds the vectors v1 and v2 together to produce v3
 */
int vecadd(Vector *v3, Vector *v1, Vector *v2){

	v3->x=v1->x+v2->x;
	v3->y=v1->y+v2->y;
	v3->z=v1->z+v2->z;

	v3->mag=magntd(*v3);

	if(v3==NULL){
		return -1;
	}
	return 0;

}

/*
 * Subroutine to find the station position in the earth-centred, fixed (ECF) coordinate system.
 */
int station_ECF(Vector *stn_ECF_pos, double station_longitude, double station_latitude, double station_elevation){
	double alt, lat_rad, long_rad;
	alt=station_elevation/1000;
	lat_rad=station_latitude*(PI/180);
	long_rad=station_longitude*(PI/180);

	double X, Y, Z, n, a, e2, f;
	f=1/298.25722363;
	e2=2*f-pow(f,2);
	a=6378.137; //in m
	n=a/(sqrt(1-e2*pow(sin(lat_rad),2)));

	X=(n+alt)*cos(lat_rad)*cos(long_rad);
	Y=(n+alt)*cos(lat_rad)*sin(long_rad);
	Z=(n*(1-e2)+alt)*sin(lat_rad);

	stn_ECF_pos->x=X;
	stn_ECF_pos->y=Y;
	stn_ECF_pos->z=Z;
	stn_ECF_pos->mag=magntd(*stn_ECF_pos);
	return 0;
}

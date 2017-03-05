#include "Vector.h"
#include <stdio.h>
#include <math.h>
/*
 * This module defines all the functions needed to deal with vectors – position, velocity, etc.
 * NOTE : Position and velocity vectors are to be represented by a 4 element struct calledVector.
 *  The first 3 elements are the components of the vector in a particular coordinate system.
 *  The 4th element is the norm or magnitude of the vector.
 */



/* returns the angle between vectors v1 and v2 */
double myangle(Vector * v1, Vector *v2){
	double v1dotv2 = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z ;
	return acos(v1dotv2/(v1->mag*v2->mag));
}

/*returns the scalar magnitude of a vector */
double magntd(struct Vector VECTR){
	return sqrt(pow((VECTR.x),2) + pow((VECTR.y),2) + pow((VECTR.z),2));;
}

/*Calculates the vector cross product of two input vectors v1, v2.
 * returns -1 if v3==NULL, 0 otherwise */
int mycross(Vector *v3, Vector *v1, Vector *v2){
	if(v3 == NULL)
	{
		puts("v3 is null");
		return NULL;
	}
	else{
		v3->x = v1->y * v2->z - v1->z * v2->y;
		v3->y = v1->z * v2->x - v1->x * v2->z;
		v3->z = v1->x * v2->y - v1->y * v2->x;
	}
	return 0;
}

/*Subroutine to find the station position in the earth-centred, fixed (ECF) coordinate
system. */
/*int station_ECF(Vector *stn_ECF_pos, double station_longitude, double station_latitude, double station_elevation){
return 0;
}*/

/*
 * Vector.c
 *
 *  Created on: Mar 2, 2017
 *      Author: james_keith
 */

#include <math.h>
#include "Vector.h"

double myangle(Vector *v1, Vector *v2){
		return acos(((v1->x)*(v2->x)+(v1->y)*(v2->y)+(v1->z)*(v2->z))/(v1->mag*v2->mag));
}
double magntd(struct Vector V){
	double magnitude = 0;
	magnitude = sqrt(pow(V.x,2) + pow(V.y,2) + pow(V.z,2));
	return magnitude;
}
int mycross(Vector*v3, Vector*v1, Vector*v2){
	v3->x = v1->y*v2->z - v1->z*v2->y;
	v3->y = v1->z*v2->x - v1->x*v2->z;
	v3->z = v1->x*v2->y - v1->y*v2->x;
	double mag1 = magntd(*v1);
	double mag2 = magntd(*v2);
	v3->mag = mag1*mag2*sin(myangle(v1, v2));
	if (!v3){
	return -1;}
	else{
	return 0;}
}
int vecadd(Vector*v3, Vector*v1, Vector*v2){
	v3->x = v1->x + v2->x;
	v3->y = v1->y + v2->y;
	v3->z = v1->z + v2->z;
	v3->mag = magntd(*v3);
	return v3;
}

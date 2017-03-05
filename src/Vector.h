/*
 * Vector.c
 *
 *  Created on: Mar 2, 2017
 *      Author: james
 */
#ifndef vec
#define vec
typedef struct Vector {
double x;
double y;
double z;
double mag;
} Vector;
double myangle(Vector*v1, Vector*v2);
double magntd(struct Vector VECTR);
int mycross(Vector*v3,Vector*v1,Vector*v2);
int vecadd(Vector*v3,Vector*v1,Vector*v2);
#endif

/*This module defines all the functions needed to deal with vectors – position, velocity, etc.
NOTE : Position and velocity vectors are to be represented by a 4 element struct called
Vector. The first 3 elements are the components of the vector in a particular coordinate
system. The 4th element is the norm or magnitude of the vector. */

#define VECTOR_H


#ifndef vec
#define vec

typedef struct Vector {
double x;
double y;
double z;
double mag;
} Vector;

double myangle(Vector *v1, Vector *v2);

double magntd(struct Vector VECTR);

int mycross(Vector *v3, Vector *v1, Vector *v2);

int station_ECF(Vector *stn_ECF_pos, double station_longitude, double station_latitude, double station_elevation);
#endif

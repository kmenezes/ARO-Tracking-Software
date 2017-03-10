/*
 * STKout.c
 *
 *  Created on: Mar 9, 2017
 *      Author: User
 */
#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>

int STKout(double *time, int size_time_array, char Coordinatesystem, Vector *position, Vector *velocity){

	FILE * fp;
	fp = fopen ("STKout.e", "w+");
	fprintf(fp, "%s", "stk.v.11\n");
	fprintf(fp, "\n BEGIN Ephemeris\n");
	fprintf(fp,"\n NumberOfEphemerisPoints	%d\n", size_time_array);
	// get number of rows in time matrix
	fprintf(fp,"\n ScenarioEpoch	%f\n", time[0]);
	fprintf(fp,"InterpolationMethod	Lagrange\n" );
	fprintf(fp, "CentralBody	Earth\n");
	fprintf(fp,"CoordinateSystem	%s\n", Coordinatesystem);
	fprintf(fp, "\n");
	fprintf(fp,"%s", "EphemerisTimePosVel\n\n");
	//time array // each of the times the position. velocity
	for(int i = 0 ; i < size_time_array ; i++){
		fprintf(fp,"%f %f %f %f %f %f %f\n", time[i], position[i].x, position[i].y, position[i].z, velocity[i].x, velocity[i].y, velocity[i].z);
	}
	fclose(fp);

	return(0);
}

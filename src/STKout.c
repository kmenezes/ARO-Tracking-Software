/*
 * STKout.c
 *
 *  Created on: Mar 9, 2017
 *      Author: User
 */
#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>

int STKout(char outfile, char EphemFile, char StartString, double time,
Vector *Coord, Vector *position, Vector *velocity){
	   FILE * fp;

	   fp = fopen ("STKout.e", "w+");
	   fprintf(fp, "%s", "stk.v.11\n");
	   fprintf(fp, "%s","%d\n", "NumberOfEphemerisPoints", 570);
	   fprintf(fp, "%s", "%d\n", "ScenarioEpoch	", time);
	   fprintf(fp,"%s", "%s", "InterpolationMethod	", "Lagrange\n" );
	   fprintf(fp,"%s", "%s", "CentralBody	", "Earth\n" );
	   fprintf(fp,"%s", "%s", "CoordinateSystem	", "J2000\n" );
	   fprintf(fp, "\n");
	   fprintf(fp,"%s", "EphemerisTimePosVel");



	   fclose(fp);

	   return(0);
}


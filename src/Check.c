
#include "Check.h"
#include "Vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int STKout(double *time, int size_time_array, char *filename,
	char CoordinateSystem[], Vector *position, Vector *velocity){

	FILE * fp;
	fp = fopen (filename, "w+");
	fprintf(fp, "%s", "stk.v.11\n");
	fprintf(fp, "\nBEGIN Ephemeris\n");
	fprintf(fp,"\nNumberOfEphemerisPoints	%d\n", size_time_array);
	// get number of rows in time matrix
	fprintf(fp,"\nScenarioEpoch            28 Apr 2017 17:00:00.000000\n");
	fprintf(fp,"InterpolationMethod	Lagrange\n" );
	fprintf(fp,"InterpolationOrder 7\n");
	fprintf(fp, "CentralBody	Earth\n");
	fprintf(fp,"CoordinateSystem	");
	for(int i=0; i<strlen(CoordinateSystem); i++){
		fprintf(fp, "%c", CoordinateSystem[i]);
	}
	fprintf(fp, "\n");fprintf(fp, "\n");fprintf(fp, "\n");
	fprintf(fp,"%s", "EphemerisTimePosVel\n\n");
	//time array | px | py |pz | vx | vy | vz
	for(int i = 0 ; i < size_time_array ; i++){
		fprintf(fp,"%f %f %f %f %f %f %f\n", time[i], position[i].x, position[i].y, position[i].z, velocity[i].x, velocity[i].y, velocity[i].z);
	}
	fprintf(fp, "\nEND Ephemeris\n");
	fclose(fp);

	return 0;
}

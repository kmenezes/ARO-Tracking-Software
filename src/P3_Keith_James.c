#include "Propagate.h"
#include "Basic.h"
#include "Fileio.h"
#include "Vector.h"
#include "STKout.h"
#include "DateAndTimeCalculations.h"
#include "Matrix.h"
#include "Vector.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define PI 3.1415926535897932384626433832795028841971693993751058209749445923

int main(void){
	printf("------------------------------------------\n");
	printf("\nWelcome to P2 by James and Keith\n\n");
	printf("------------------------------------------\n");


	printf("\nTesting Theta - J and N \n");
	printf("------------------------------------------\n");

	printf("\nUsing the test value from the TLE Epoch: %f\n",05054.71335794);
	// 05054.71335794
	double value = 05054.71335794;
	double THET = THETAN(value);
	printf("\nThe result of  %f\n", THET);
	printf("\nThe result should print 0.893608 \n ");

	//tests for keplers
	printf("\n------------------------------------------\n");
	printf("\nTesting Keplers Equation for the various types of orbits \n");
	printf("------------------------------------------\n");
	double ecc,ecc2,ecc3,ecc4;
	printf("\nTesting Keplers Eqn for Circular Orbit for Mean anom = 3.6029 and Ecc = 0.0\n");
	printf("------------------------------------------\n");
	ecc = KeplerEqn(3.6029,0.0);
	printf("\n The result is: %f\n" ,ecc);
	printf("\nFor circular it should result in the mean anom 3.6029 \n");
	printf("\n------------------------------------------\n");
	printf("\nTesting Kepler for eccentric Mean anom = 3.6029 = 206.430964 degrees and Ecc = 0.37255 \n");
	ecc2 = KeplerEqn(3.6029,0.37255);
	printf("\nKeplerEqn(3.6029,0.37255) returned: %f\n" ,ecc2);
	printf("\nThe result should be in 199.35619827991917 degrees or 3.4794220442346146527 rads\n");
	printf("\n------------------------------------------\n");
	printf("\nTesting Kepler Elliptic orbit for Mean anom =1.5 and Ecc = 0.8\n");
	printf("------------------------------------------\n");
	ecc3 = KeplerEqn(1.5,0.8);
	printf("\nKeplerEqn(1.5,0.8) returned: %f\n" ,ecc3);
	printf("\nShould result in 2.1635326743829743634 or 123.96129108110373807 degrees \n");
	printf("\n------------------------------------------\n");
	printf("\nTesting Parabolic orbit Mean anom = 1.5 and Ecc = 1.0\n");
	printf("------------------------------------------\n");
	ecc4 = KeplerEqn(1.5,1.0);
	printf("\nKeplerEqn(1.5,1.0) returns:  %f\n" ,ecc4);
	printf("Result should be 1.952623\n");
	printf("\n------------------------------------------\n");
	printf("\nTesting Hyperbolic Mean anom = 40.69 and Ecc =  2.7696 \n");
	printf("------------------------------------------\n");
	ecc = KeplerEqn(40.69, 2.7696);
	printf("\nKeplerEqn(40.69, 2.7696) returned: %f\n" ,ecc);
	printf("\nshould return Hyperbolic eccentric anomaly = 3.46309\n");
	printf("------------------------------------------\n");

	// testing mean anomaly motion
	printf("\n------------Test Mean Anomaly Motion----------------------------------------------------------------------------------------------------------------------\n");
	Satellite *sat = (Satellite*) malloc(sizeof(Satellite));
	ReadNoradTLE(sat, '0','1','2');
	double mean_anom;double mean_motion;
	// sample time interval is 25 julian days
	mean_anomaly_motion(&mean_anom, &mean_motion, 50, 25, sat->meanan, sat->meanmo, 0.5, 100);
	printf("\n Testing mean-anom-motion with time interval of 25 julian date, imported sat meananom and mean motion, 0.5 n-dot-meanmotion, and 100 ndotdotmeanmotion\n");
	printf("Heres the Mean anomaly: %f and the mean motion: %f\n", mean_anom, mean_motion);
	printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	printf("\n------------Test the Station ECF------------------------------------------------------------------------------------------------\n");
	Vector *s;
	s=(Vector*)malloc(2*sizeof(Vector));
	s->x=0;
	s->y=0;
	s->z=0;
	station_ECF(s, 45, 45, 45);
	printf("\n Station_ECF with inputs of station_ECF(s, 45, 45, 45) returns:  X=%f  Y=%f  Z=%f \n", s->x, s->y, s->z);
	printf("\n The result should be ECEF from Latitude,Longitude, Height (ellipsoidal) X : 3194.442   km, Y : 3194.442   km, Z : 4487.38   km\n");
	printf("\n as confirmed with an online calculator http://www.oc.nps.edu/oc2902w/coord/llhxyz.htm \n");
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");

	printf("\n--------------------------Testing range_topo2look_angles:------------------------\n");
	Vector *vec1;
	vec1 = (Vector*)malloc(sizeof(Vector));
	vec1->x = 7; vec1->y = 2; vec1->z = 4; vec1->mag = 17;
	Vector *vec2;
	vec2 = (Vector*)malloc(sizeof(Vector));
	vec2->x = 5; vec2->y = 5; vec2->z = 4; vec2->mag = 7;
	double a1, b1, c1, d1;
	LookAngles *LA =(LookAngles*) malloc(sizeof(LookAngles));
	range_topo2look_angles(LA, a1, b1, c1, d1, vec1, vec2);
	printf("azimuth: %f\n", LA->azimuth);
	printf("elevation: %f\n", LA->elevation);
	printf("azimuth velocity: %f\n", LA->azimuth_velocity);
	printf("elevation velocity: %f\n", LA->elevation_velocity);
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");


	printf("\n------------Testing range_ECF2topo----------------\n");
	Vector *vrtp;vrtp = (Vector*)malloc(sizeof(Vector));
	Vector *vrtv;vrtv = (Vector*)malloc(sizeof(Vector));
	Vector *vsbp;vsbp = (Vector*)malloc(sizeof(Vector));
	vsbp->x = 5; vsbp->y = 5; vsbp->z = 4; vsbp->mag = sqrt(66);
	Vector *vsep;vsep = (Vector*)malloc(sizeof(Vector));
	vsep->x = 5; vsep->y = 5; vsep->z = 4; vsep->mag = sqrt(66);
	Vector *vsev;vsev = (Vector*)malloc(sizeof(Vector));
	vsev->x = 1; vsev->y = 2; vsev->z = 3; vsev->mag = sqrt(14);
	double slong = 281.0;
	double slat = 45.0;
	printf("\n The input is V - [5,5,4,sqrt(66)] V2 - [5,5,4,sqrt(66)] v3 - [1,2,3,sqrt(14]\n");
	printf("\n The input longitude is 281 degrees and latitude of 45 degrees\n");
	range_ECF2topo(vrtp, vrtv, *vsbp, vsep, vsev, slong, slat);
	printf("------------------------------------------\n");
	printf("The range topo position vector is: \n");
	printf("Px is: %f\n", vrtp->x);
	printf("Py is: %f\n", vrtp->y);
	printf("Pz is: %f\n", vrtp->z);
	printf("------------------------------------------\n");
	printf("The range topo velocity vector is: \n");
	printf("Vx is: %f\n", vrtv->x);
	printf("Vy is: %f\n", vrtv->y);
	printf("Vz is: %f\n", vrtv->z);
	printf("------------------------------------------\n");


	printf("\n-----------------------------Testing sat_ECI-----------------------------------------------------\n");
	// Create Position and Vel vectors
	struct Vector Pos, Vel;
	Pos.x = 0;Pos.y = 0;Pos.z = 0;Pos.mag = magntd(Pos);
	Vel.x = 0;Vel.y = 0;Vel.z = 0;Vel.mag = magntd(Vel);
	// Use orbital parameters from GPS satellite TLE
	double e, ecc_anomaly, semi, long_asc_node, w, i, nt, RAAN;
	e = 0.0163836;
	ecc_anomaly = 70.8137; // radians = 70.8137 deg
	//semimajor axis in km
	semi = 26562;long_asc_node = 112.038;RAAN = 81.653;
	//w and inclination in degrees
	w = 93.0850;i = 51.5649;
	// revs/sec
	nt = 0.000023213;
	printf("Currently using orbital Parameters of: \n");
	printf("e = 0.0163836, ecc_anomaly = 70.8137  semi-major-axis = 26562, long_asc_node = 112.038, RAAN = 81.653\n");
	printf("w = 93.0850;i = 51.5649; nt = 0.000023213 in rev/sec\n");
	printf("Note that angles were converted to radians\n");
	sat_ECI(&Pos, &Vel, e, ecc_anomaly*PI/180, semi, RAAN*PI/180, w*PI/180, i*PI/180, nt);
	printf("The current position and velocity in ECI is: \n");
	printf("Px is: %f\n", Pos.x);
	printf("Py is: %f\n", Pos.y);
	printf("Pz is: %f\n", Pos.z);
	printf("The predicted STK values for position are -7896.982740km, -24633.763428km, 5353.505305km \n");
	printf("Vx is: %f\n", Vel.x);
	printf("Vy is: %f\n", Vel.y);
	printf("Vz is: %f\n", Vel.z);
	printf("The predicted STK values for velocity are 2.145720km/s, -1.392020km/s, -2.937639km/s \n");

	printf("\n-------------------------------------------------------------------------------------------------\n");

	printf("\n-----------------------------Testing sat_ECF-----------------------------------------------------\n");
	struct Vector PosECI, VelECI, POSECF, VELECF;
	//initializing new pos/vel ECF vectors
	POSECF.x = 0;POSECF.y = 0;POSECF.z = 0;POSECF.mag = magntd(POSECF);
	VELECF.x = 0;VELECF.y = 0;VELECF.z = 0;VELECF.mag = magntd(VELECF);

	// Setting the expected values for ECI velocity and positions i.e. what we should've got before
	printf("This function uses the STK calculated values from the above test sat_ECI\n");
	PosECI.x = -7896.982740;PosECI.y = -24633.763428;PosECI.z = 5353.505305;PosECI.mag = magntd(PosECI);
	VelECI.x = 2.145720;VelECI.y = -1.392020;VelECI.z = -2.937639;VelECI.mag = magntd(VelECI);

	double frac, day, epoch, Du, Tu, GMST00, theta_mid, r, theta_t;

	// Calculating the Difference in JD between the start and J2000
	frac = frcofd(24, 0, 0);day = doy(2017, 3, 11);epoch = 17000+day+frac;Du = jdatep(epoch) - jdatep(00001.5);	Tu = Du/36525;
	GMST00 = 24110.54841 + 8640184.812866*Tu + 0.093104*pow(Tu,2) - 6.2*pow(10,-6)*pow(Tu,3);
	GMST00 = fmod(GMST00, 86400);theta_mid = 2*3.14159*GMST00/86400;
	r = 1.002737909350795+5.9006*pow(10,-11)*Tu - 5.9*pow(10, -15)*pow(Tu,2);
	theta_t = theta_mid + 2*3.14159*r*(16*3600);

	sat_ECF(&POSECF, &VELECF, theta_t, &PosECI, &VelECI);
	printf("The position in ECF is: \n");
	printf("Px is: %f\n", POSECF.x);
	printf("Py is: %f\n", POSECF.y);
	printf("Pz is: %f\n", POSECF.z);
	printf("The predicted STK values for position are -23997.9889km, -9664.9km, 5341.405075km \n");

	printf("The velocity in ECF is: \n");
	printf("Vx is: %f\n", VELECF.x);
	printf("Vy is: %f\n", VELECF.y);
	printf("Vz is: %f\n", VELECF.z);
	printf("The predicted STK values for velocity are -0.4km/s, -0.793789km/s, -2.934026km/s \n");

	printf("theta_t is %f\n", theta_t);

	printf("\n-------------------------------------------------------------------------------------------------\n");

	//STK out tester
	printf("---------------Testing STKout------------------\n");
	double t[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int size = 10;
	char coordinatesys[] = "J2000";
	struct Vector p[size];
	struct Vector v[size];
	for(int i=0; i<size; i++){
		p[i].x = i+69;
		p[i].y = i+59;
		p[i].z = i+49;
	}
	for(int i=0; i<size; i++){
		v[i].x = i+69;
		v[i].y = i+59;
		v[i].z = i+49;
	}
	int a = STKout(t, size, coordinatesys, p, v);
	printf("Success Check of STK out should Return 0 and file will be in top directory: STkout returns: %d\n",a);
	printf("\n------------------------------------------\n");

	printf("------------------------------------------\n");
	printf("\nTesting AnyKey() -- You must press ENTER to continue -- Comment out other code and test separately for robust test \n");
	anykey();
	printf("\nAnykey Works!\n");
	printf("------------------------------------------\n");


	return 0;
}

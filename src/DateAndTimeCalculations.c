/*
 * DateAndTimeCalculations.c
 *
 *  Created on: Mar 4, 2017
 *      Author: james/keith
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

double jdaty(double YEAR){
	double JD, t1, t2, t3, t4, t5, t6, year, mon, day, hr, min, sec;
	year = YEAR;
	mon = 01;
	day = 01;
	hr = 00;
	min = 00;
	sec = 00;
	t1 = 367*(year);
	t2 = -floor(7*((year)+floor((mon+9)/12))/4);
	t3 = floor(275*mon/9);
	t4 = day;
	t5 = 1721013.5;
	t6 = (hr+(min+(sec)/60)/60)/24;
	JD = t1 + t2 + t3 + t4 + t5 + t6;
	return JD;
}

double jdatep(double EPOCH){
	double year, day, frac, JD;
	char epoch[15];
	snprintf(epoch, 15, "%014.8f", EPOCH);
	year = 10*(epoch[0] - '0') + (epoch[1] - '0');
	day = 100*(epoch[2]-'0') + 10*(epoch[3] - '0') + (epoch[4] - '0');
	int i;
	int j = 7;
	frac = 0;
	for(i=6;i<=13; i++){
		frac = frac + (pow(10,j))*(epoch[i] - '0');
		j--;
	}
	if(year <= 56){	year = 2000 + year;}
	else{year = 1900 + year;}
	JD = jdaty(year) + day + frac/100000000;
	return JD;
}
double doy (int YR, int MO, int D){
	if(YR % 4 != 0){ int i;
		double day = 0;
		for (i=1; i<MO; i=i+1){
			if(i==2){ day = day+28;
			}
			else if(i%2 == 0){
				day = day+30;
			}
			else{
				day = day+31;
			}
		}
		day = day+D;
		return day;
	}
	else{
		int i;
		double day = 0;
		for (i=1; i<MO; i=i+1){
			if(i==2){
				day = day+29;
			}
			else if(i%2 == 0){
				day = day+30;
			}
			else{
				day = day+31;
			}
		}
		day = day+D;
		return day;
	}
}
double frcofd (int HR, int MI, int SE){
	double frac, h, m, s;
	h = HR;
	m = MI;
	s = SE;
	frac = ((((s/60)+m)/60)+h)/24;
	return frac;
}
double dat2jd (char *DateString){
	double year, mon, day, hr, min, sec;
	year = 0;
	int i;
	int j = 3;
	for(i=0; i<=3; i++){
		year = year + (DateString[i]-'0')*pow(10,j);
		j--;
	}
	mon = 0;
	j = 1;
	for(i=5; i<=6; i++){
		mon = mon + (DateString[i]-'0')*pow(10,j);
		j--;
	}
	day = 0;
	j = 1;
	for(i=8; i<=9; i++){
		day = day + (DateString[i]-'0')*pow(10,j);
		j--;
	}
	hr = 0;
	j = 1;
	for(i=11; i<=12; i++){
		hr = hr + (DateString[i]-'0')*pow(10,j);
		j--;
	}
	min = 0;
	j = 1;
	for(i=14; i<=15; i++){
		min = min + (DateString[i]-'0')*pow(10,j);
		j--;
	}
	sec = 0;
	j = 1;
	for(i=17; i<=18; i++){
		sec = sec + (DateString[i]-'0')*pow(10,j);
		j--;
	}
	double JD, t1, t2, t3, t4, t5, t6;
	t1 = 367*(year);
	t2 = -floor(7*((year)+floor((mon+9)/12))/4);
	t3 = floor(275*mon/9);
	t4 = day;
	t5 = 1721013.5;
	t6 = (hr+(min+(sec)/60)/60)/24;
	JD = t1 + t2 + t3 + t4 +t5 +t6;
	return JD;
}

char* jd2dat(double JulianDate){
	double JD = 2450006.18291;
	double Z, F, A, alpha, B, C, D, E, dd, mm, yyyy, hr, min, sec;
	Z = floor(JD+0.5);
	F = (JD+0.5)-Z;
	if(Z < 2299161){
		A = Z;
	}
	else{
		alpha = floor((Z-1867216.25)/36524.25);
		A = Z + 1 + alpha - floor(alpha/4);
	}
	B = A + 1524;
	C = floor((B-122.1)/365.25);
	D = floor(365.25*C);
	E = floor((B-D)/30.6001);
	dd = B - D - floor(30.6001*E) + F;
	hr = (dd - floor(dd))*24;
	min = (hr - floor(hr))*60;
	sec = (min-floor(min))*60;
	dd = floor(dd);
	hr = floor(hr);
	min = floor(min);
	sec = floor(sec);
	if(E < 13.5){
		mm = E-1;
	}
	else{
		mm = E-13;
	}
	if(mm > 2.5){
		yyyy = C-4716;
	}
	else{
		yyyy = C - 4715;
	}
	static char Cal[20], M[3], Day[3], H[3], Min[3], S[3];
	snprintf(Cal, 5, "%5f", yyyy);
	snprintf(M, 3, "%2f", mm);
	snprintf(Day, 3, "%2f", dd);
	snprintf(H, 3, "%2f", hr);
	snprintf(Min, 3, "%2f", min);
	snprintf(S, 3, "%2f", sec);
	strcat(Cal, "-");
	strcat(Cal, M);
	strcat(Cal, "-");
	strcat(Cal, Day);
	strcat(Cal, " ");
	strcat(Cal, H);
	strcat(Cal, ":");
	strcat(Cal, Min);
	strcat(Cal, ":");
	strcat(Cal, S);
	return Cal;
}

char* curday(){
	{
	 	time_t rt;
	 	char *d = malloc(19);
	    struct tm * ti;
	    time ( &rt );
	    ti = localtime ( &rt );
	    char Y[5];
	    sprintf(Y, "%.2d-", ti->tm_year + 1900);
	    char M[3];
	    sprintf(M, "%.d-", ti->tm_mon + 1);
	    char D[3];
	    sprintf(D, "%.d ", ti->tm_mday);
	    char H[3];
	    sprintf(H, "%.d:", ti->tm_hour);
	    char MIN[3];
	    sprintf(MIN, "%.d:", ti->tm_min);
	    char SEC[3];
	    sprintf(SEC, "%.d", ti->tm_sec);
	    strcpy(d, Y);
	    strcat(d, M);
	    strcat(d, D);
	    strcat(d, H);
	    strcat(d, MIN);
	    strcat(d, SEC);
	    return d;
	}


}




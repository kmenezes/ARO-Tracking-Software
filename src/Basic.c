/*
 * Basic.c
 *
 *  Created on: Mar 3, 2017
 *      Author: james
 */
#include <stdio.h>
#include <math.h>



double cosm1(double ARG)
{
 if (ARG >= 1)
  return 3.141592653589793238462643383279502884197169399375105820974944592307816406286 /2;
  else if (ARG <= -1)
  return -1*3.141592653589793238462643383279502884197169399375105820974944592307816406286 /2;
  else
  return acos(ARG);
}
double fixang(double ARG)
{
 for (;ARG > 3.141592653589793238462643383279502884197169399375105820974944592307816406286 *2;){
	 ARG = ARG - 3.141592653589793238462643383279502884197169399375105820974944592307816406286 *2;
 }
 return ARG;
}
double sinm1(double ARG)
{
 if (ARG >= 1)
  return 3.141592653589793238462643383279502884197169399375105820974944592307816406286 /2;
  else if (ARG <= -1)
  return -1*3.141592653589793238462643383279502884197169399375105820974944592307816406286 /2;
  else
  return asin(ARG);
}
double frac (double ARG)
{
 if (ARG > 0) {
	for (;ARG >= 1;)
	{ARG = ARG - 1;}
 	return ARG;}
 else{
 	for (;ARG <= -1;)
 	{ARG = ARG + 1;}
 	return ARG;}
}

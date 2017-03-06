/*
 * Propagate.c
 *
 *  Created on: Mar 5, 2017
 *      Author: User
 */
#include <stdio.h>
#include <math.h>
typedef enum {false,true} boolean;


/*
https://www.projectpluto.com/kepler.htm
 */
/* If the eccentricity is very close to parabolic,  and the eccentric
anomaly is quite low,  you can get an unfortunate situation where
roundoff error keeps you from converging.  Consider the just-barely-
elliptical case,  where in Kepler's equation,

M = E - e sin( E)

   E and e sin( E) can be almost identical quantities.  To
around this,  near_parabolic( ) computes E - e sin( E) by expanding
the sine function as a power series:

E - e sin( E) = E - e( E - E^3/3! + E^5/5! - ...)
= (1-e)E + e( -E^3/3! + E^5/5! - ...)

   It's a little bit expensive to do this,  and you only need do it
quite rarely.  (I only encountered the problem because I had orbits
that were supposed to be 'pure parabolic',  but due to roundoff,
they had e = 1+/- epsilon,  with epsilon _very_ small.)  So 'near_parabolic'
is only called if we've gone seven iterations without converging. */

// Helper method
	double near_parabolic( const double ecc_anom, const double e)
	{
	   const double anom2 = (e > 1. ? ecc_anom * ecc_anom : -ecc_anom * ecc_anom);
	   double term = e * anom2 * ecc_anom / 6.;
	   double rval = (1. - e) * ecc_anom - term;
	   unsigned n = 4;

	   while( fabs( term) > 1e-15)
	      {
	      term *= anom2 / (double)(n * (n + 1));
	      rval -= term;
	      n += 2;
	      }
	   return( rval);
	}

	#define MAX_ITERATIONS 7
	#define THRESH 1.e-12
	#define MIN_THRESH 1.e-15
	#define CUBE_ROOT( X)  (exp( log( X) / 3.))
	#define PI 3.1415926535897932384626433832795028841971693993751058209749445923

	double KeplerEqn(double Mt_mean_anomaly,const double eccentricity){
	   double curr, err, thresh, offset = 0.0;
	   double delta_curr = 1.0;
	   boolean is_negative = false;
	   unsigned n_iter = 0;

	   if( !Mt_mean_anomaly)
	      return( 0.);

	   if( eccentricity < 1.)
	      {
	      if( Mt_mean_anomaly < -PI || Mt_mean_anomaly > PI)
	         {
	         double tmod = fmod( Mt_mean_anomaly, PI * 2.);

	         if( tmod > PI)             /* bring mean anom within -pi to +pi */
	            tmod -= 2. * PI;
	         else if( tmod < -PI)
	            tmod += 2. * PI;
	         offset = Mt_mean_anomaly - tmod;
	         Mt_mean_anomaly = tmod;
	         }

	      if( eccentricity < .99999)     /* low-eccentricity formula from Meeus,  p. 195 */
	         {
	         curr = atan2( sin( Mt_mean_anomaly), cos( Mt_mean_anomaly) - eccentricity);
	         do
	            {
	            err = (curr - eccentricity * sin( curr) - Mt_mean_anomaly) / (1. - eccentricity * cos( curr));
	            curr -= err;
	            }
	            while( fabs( err) > THRESH);
	         return( curr + offset);
	         }
	      }


	   if( Mt_mean_anomaly < 0.)
	      {
	      Mt_mean_anomaly = -Mt_mean_anomaly;
	      is_negative = true;
	      }

	   curr = Mt_mean_anomaly;
	   thresh = THRESH * fabs( 1. - eccentricity);
	               /* Due to roundoff error,  there's no way we can hope to */
	               /* get below a certain minimum threshhold anyway:        */
	   if( thresh < MIN_THRESH)
	      thresh = MIN_THRESH;
	   if( thresh > THRESH)       /* i.e.,  ecc > 2. */
	      thresh = THRESH;
	   if( Mt_mean_anomaly < PI / 3. || eccentricity > 1.)    /* up to 60 degrees */
	      {
	      double trial = Mt_mean_anomaly / fabs( 1. - eccentricity);

	      if( trial * trial > 6. * fabs(1. - eccentricity))   /* cubic term is dominant */
	         {
	         if( Mt_mean_anomaly < PI)
	            trial = CUBE_ROOT( 6. * Mt_mean_anomaly);
	         else        /* hyperbolic w/ 5th & higher-order terms predominant */
	            trial = asinh( Mt_mean_anomaly / eccentricity);
	         }
	      curr = trial;
	      }
	   if( eccentricity < 1.)
	      while( fabs( delta_curr) > thresh)
	         {
	         if( n_iter++ > MAX_ITERATIONS)
	            err = near_parabolic( curr, eccentricity) - Mt_mean_anomaly;
	         else
	            err = curr - eccentricity * sin( curr) - Mt_mean_anomaly;
	         delta_curr = -err / (1. - eccentricity * cos( curr));
	         curr += delta_curr;
	         }
	   else
	      while( fabs( delta_curr) > thresh)
	         {
	         if( n_iter++ > MAX_ITERATIONS)
	            err = -near_parabolic( curr, eccentricity) - Mt_mean_anomaly;
	         else
	            err = eccentricity * sinh( curr) - curr - Mt_mean_anomaly;
	         delta_curr = -err / (eccentricity * cosh( curr) - 1.);
	         curr += delta_curr;
	         }
	   return( is_negative ? offset - curr : offset + curr);
	}

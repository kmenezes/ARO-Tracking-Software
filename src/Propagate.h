/*
 * Propagate.h
 *
 *  Created on: Mar 5, 2017
 *      Author: user
 */

#ifndef PROPAGATE_H_
#define PROPAGATE_H_

/* For a full description of this function,  see KEPLER.HTM on the Guide
Web site,  http://www.projectpluto.com.  There was a long thread about
solutions to Kepler's equation on sci.astro.amateur,  and I decided to
go into excruciating detail as to how it's done below. */


double KeplerEqn(double Mt_mean_anomaly, double eccentricity);

#endif /* PROPAGATE_H_ */

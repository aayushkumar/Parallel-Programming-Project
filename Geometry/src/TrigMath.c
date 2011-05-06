/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
**
** Copyright (C), 2003, Victorian Partnership for Advanced Computing (VPAC) Ltd, 110 Victoria Street, Melbourne, 3053, Australia.
**
** Authors:
**	Stevan M. Quenette, Senior Software Engineer, VPAC. (steve@vpac.org)
**	Patrick D. Sunter, Software Engineer, VPAC. (pds@vpac.org)
**	Luke J. Hodkinson, Computational Engineer, VPAC. (lhodkins@vpac.org)
**	Siew-Ching Tan, Software Engineer, VPAC. (siew@vpac.org)
**	Alan H. Lo, Computational Engineer, VPAC. (alan@vpac.org)
**	Raquibul Hassan, Computational Engineer, VPAC. (raq@vpac.org)
**	Robert B. Turnbull, Monash Cluster Computing. (Robert.Turnbull@sci.monash.edu.au)
**
**  This library is free software; you can redistribute it and/or
**  modify it under the terms of the GNU Lesser General Public
**  License as published by the Free Software Foundation; either
**  version 2.1 of the License, or (at your option) any later version.
**
**  This library is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**  Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public
**  License along with this library; if not, write to the Free Software
**  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
**
**
**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <mpi.h>
#include "StGermain/StGermain.h"

#include <math.h>

#include "units.h"
#include "types.h"
#include "TrigMath.h"

#include <assert.h>

#define RADIUS sphericalCoords[0]
#define THETA  sphericalCoords[1]
#define PHI    sphericalCoords[2]
#define X      rectangularCoords[0]
#define Y      rectangularCoords[1]
#define Z      rectangularCoords[2]

/** StGermain_RectangularToSpherical - Converts a from rectanglar coordinates to spherical coordinates */
/* Macros (X, Y, Z) and (RADIUS, THETA, PHI) are used for clarity - See macros defined above */
void StGermain_RectangularToSpherical(double* sphericalCoords, double* rectangularCoords, Index dim) {
	double theta_sin_solution1, theta_sin_solution2;
	double theta_cos_solution1, theta_cos_solution2;
	
	if (dim == 2) {
		RADIUS = sqrt(X*X + Y*Y);

		/* Get first solution for arcos */
		theta_cos_solution1 = acos(X/RADIUS);		
		
		/* Get first solution for arcsin */
		theta_sin_solution1 = asin(Y/RADIUS);		
	}
	else if (dim == 3) { 
		RADIUS = sqrt(X*X + Y*Y + Z*Z);
		PHI = acos(Z/RADIUS);

		/* Get first solution for arcos */
		theta_cos_solution1 = acos( X/ (RADIUS*sin(PHI)) );		/* Solution is between 0 and PI i.e. quadrant 1 and 2 */
		
		/* Get first solution for arcsin */
		theta_sin_solution1 = asin( Y/(RADIUS*sin(PHI)) );		/* Solution is between -PI/2 and PI/2 i.e. quadrant 1 and 4 */
	}
	else {
		Stream* error = Journal_Register( Error_Type , (Name)__FILE__  );
		Journal_Printf( error, "Func %s does not work with dimension %u\n", __func__, dim );
		exit(EXIT_FAILURE);
	}

	/* Get second solution for arcos */
	theta_cos_solution2 = 2.0 * M_PI - theta_cos_solution1;			/* Solution is between PI and 2 PI - i.e. quadrant 3 and 4 */

	/* Get second solution for arcsin */
	theta_sin_solution2 = M_PI - theta_sin_solution1;			/* Solution is between PI/2 and 3PI/2 - i.e. quadrant 2 and 3 */
	
	/* Find sine and cosine solutions that match up */
	if ( StGermain_TrigQuadrant( theta_cos_solution1 ) ==  StGermain_TrigQuadrant(theta_sin_solution1) 
		||  StGermain_TrigQuadrant( theta_cos_solution1 ) ==  StGermain_TrigQuadrant( theta_sin_solution2 ) ) { 
		THETA = theta_cos_solution1;
	}
	else { 
		THETA = theta_cos_solution2;
	}
}


/** StGermain_SphericalToRectangular - Converts a from spherical coordinates to rectanglar coordinates */
/* Macros (X, Y, Z) and (RADIUS, THETA, PHI) are used for clarity - See macros defined above */
void StGermain_SphericalToRectangular(double* rectangularCoords, double* sphericalCoords, Index dim) {
	X = RADIUS * cos(THETA);
	Y = RADIUS * sin(THETA);
	
	if (dim == 3) {
		X = X * sin(PHI);
		Y = Y * sin(PHI);
		Z = RADIUS * cos(PHI);
	}
}

/** StGermain_TrigDomain - Gets angle into domain between 0 and 2\pi */
double StGermain_TrigDomain(double angle) {
	if (angle > 0)
		return fmod( angle, 2.0 * M_PI );
	else 
		return (2.0 * M_PI - fmod( fabs(angle), 2.0 * M_PI ));
}

/** StGermain_TrigQuadrant - Returns 0 (UPPER_RIGHT_QUADRANT), 1 (UPPER_LEFT_QUADRANT), 
2 (LOWER_RIGHT_QUADRANT), or 3 (LOWER_RIGHT_QUADRANT) depending on what quadrant the angle is in */
char StGermain_TrigQuadrant(double angle) {
	/* Gets radian into correct domain */
	angle = StGermain_TrigDomain(angle);
	
	/* return angle * \frac{2}{\pi} */
	return (char) (angle * M_2_PI);
}



/* Author: Glen MacLachlan, bindatype@gmail.com
 * 
 *  Copyright (C) 2010 Glen Alan MacLachlan
 *
 *     This file is part of Fast Wavelet Transform (fwt).
 *
 *   Fast Wavelet Transform is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Fast Wavelet Transform is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Fast Wavelet Transform.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __MATH_HELPER_H__
#define __MATH_HELPER_H__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define G_PI 3.14159265

double 
inner_prod(int N, double vec1[],double vec2[]);

int 
getNumOctaves(int N);

double 
*dn_sample (double **a, int N);

double 
*up_sample (double **a, int N);

double
*unirand(double *a,int N);

double 
*poisson(double *lambda,int LENGTH);

double 
*box_muller(double *sigma, int LENGTH);


#endif

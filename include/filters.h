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

#ifndef __FILTERS_H__
#define __FILTERS_H__

#include <math.h>

void (*filter)(double **c, double **d,int *support);
void initD2(double **c, double **d,int *support);
void initD4(double **c, double **d,int *support);
void initC6(double **c, double **d,int *support);
void initD6(double **c, double **d,int *support);
void initC12(double **c, double **d,int *support);
void initC18(double **c, double **d,int *support);

void initD2inv(double **c, double **d,int *support);
void initD4inv(double **c, double **d,int *support);
void initC6inv(double **c, double **d,int *support);
void initD6inv(double **c, double **d,int *support);
void initC12inv(double **c, double **d,int *support);
void initC18inv(double **c, double **d,int *support);


double sqrt2;
double sqrt3;
static double D2c[2],D2d[2];
static double D4c[4],D4d[4];
static double D6c[6],D6d[6];

static double C6c[6],C6d[6];
static double C12c[12],C12d[12];
static double C18c[18],C18d[18];

void initD2(double **c, double **d, int *support)
{
	sqrt2 = sqrt(2.);

	D2c[0] =(1.)/sqrt2;
	D2c[1] = (1.)/sqrt2;

	D2d[0] =  D2c[1];
	D2d[1] = -D2c[0];

	*c = D2c;
	*d = D2d;
	*support = 2;
}

void initD2inv(double **c, double **d, int *support)
{
	sqrt2 = sqrt(2.);
	sqrt2 =  sqrt2;

	D2c[0] =(1.)/sqrt2;
	D2c[1] = (1.)/sqrt2;

	D2d[0] =  D2c[1];
	D2d[1] = -D2c[0];

	*c = D2c;
	*d = D2d;
	*support = 2;
}

void initD4(double **c, double **d, int *support)
{
	sqrt3 = sqrt(3.);
	sqrt2 = 4. * sqrt(2);

	D4c[0] = (1. + sqrt3)/sqrt2;
	D4c[1] = (3. + sqrt3)/sqrt2;
	D4c[2] = (3. - sqrt3)/sqrt2;
	D4c[3] = (1. - sqrt3)/sqrt2;

	D4d[0] =  D4c[3];
	D4d[1] = -D4c[2];
	D4d[2] =  D4c[1];
	D4d[3] = -D4c[0];


	*c = D4c;
	*d = D4d;
	*support = 4;

}

void initD4inv(double **c, double **d, int *support)
{
	sqrt3 = sqrt(3.);
	sqrt2 = 4. * sqrt(2);

	D4c[2] = (1. + sqrt3)/sqrt2;
	D4c[1] = (3. + sqrt3)/sqrt2;
	D4c[0] = (3. - sqrt3)/sqrt2;
	D4c[3] = (1. - sqrt3)/sqrt2;

	D4d[0] =  D4c[3];
	D4d[1] = -D4c[2];
	D4d[2] =  D4c[1];
	D4d[3] = -D4c[0];


	*c = D4c;
	*d = D4d;
	*support = 4;

}

void initD6(double **c, double **d, int * support)
{
	sqrt2 = sqrt(2.);

	D6c[0] =  0.235233603892705*sqrt2;
	D6c[1] =  0.570558457917308*sqrt2;
	D6c[2] =  0.325182500263710*sqrt2;
	D6c[3] = -0.095467207784260*sqrt2;
	D6c[4] = -0.060416104155354*sqrt2;
	D6c[5] =  0.024908749865891*sqrt2;

	D6d[0] =  D6c[5];
	D6d[1] = -D6c[4];
	D6d[2] =  D6c[3];
	D6d[3] = -D6c[2];
	D6d[4] =  D6c[1];
	D6d[5] = -D6c[0];

	*c = D6c;
	*d = D6d;
	*support = 6;
}

void initD6inv(double **c, double **d, int * support)
{
	sqrt2 = sqrt(2.);


	D6c[4] =  0.235233603892705*sqrt2;
	D6c[1] =  0.570558457917308*sqrt2;
	D6c[2] =  0.325182500263710*sqrt2;
	D6c[3] = -0.095467207784260*sqrt2;
	D6c[0] = -0.060416104155354*sqrt2;
	D6c[5] =  0.024908749865891*sqrt2;

	D6d[0] =  D6c[5];
	D6d[1] = -D6c[4];
	D6d[2] =  D6c[3];
	D6d[3] = -D6c[2];
	D6d[4] =  D6c[1];
	D6d[5] = -D6c[0];

	*c = D6c;
	*d = D6d;
	*support = 6;
}


void initC6(double **c, double **d, int *support)
{	

	sqrt2 = sqrt(2.);
	sqrt2 =  sqrt2;

	C6c[0] = -0.1028594569415370/sqrt2;
	C6c[1] = 0.4778594569415370/sqrt2;
	C6c[2] = 1.2057189138830700/sqrt2;
	C6c[3] = 0.5442810861169260/sqrt2;
	C6c[4] = -0.1028594569415370/sqrt2;
	C6c[5] = -0.0221405430584631/sqrt2;

	C6d[0] = C6c[5];
	C6d[1] = -C6c[4];
	C6d[2] = C6c[3];
	C6d[3] = -C6c[2];
	C6d[4] = C6c[1];
	C6d[5] = -C6c[0];

	*c = C6c;
	*d = C6d;
	*support = 6;

}

void initC6inv(double **c, double **d, int *support)
{
	sqrt2 = sqrt(2.);
	sqrt2 =  sqrt2;


	C6c[4] = -0.1028594569415370/sqrt2;
	C6c[1] = 0.4778594569415370/sqrt2;
	C6c[2] = 1.2057189138830700/sqrt2;
	C6c[3] = 0.5442810861169260/sqrt2;
	C6c[0] = -0.1028594569415370/sqrt2;
	C6c[5] = -0.0221405430584631/sqrt2;

	C6d[0] = C6c[5];
	C6d[1] = -C6c[4];
	C6d[2] = C6c[3];
	C6d[3] = -C6c[2];
	C6d[4] = C6c[1];
	C6d[5] = -C6c[0];

	*c = C6c;
	*d = C6d;
	*support = 6;

}

void initC12(double **c, double **d, int *support)
{
	sqrt2 = sqrt(2.);

	C12c[0] = 0.0231751934774337/sqrt2;
	C12c[1] = -0.0586402759669371/sqrt2;
	C12c[2] = -0.0952791806220162/sqrt2;
	C12c[3] = 0.5460420930695330/sqrt2;
	C12c[4] = 1.1493647877137300/sqrt2;
	C12c[5] = 0.5897343873912380/sqrt2;
	C12c[6] = -0.1081712141834230/sqrt2;
	C12c[7] = -0.0840529609215432/sqrt2;
	C12c[8] = 0.0334888203265590/sqrt2;
	C12c[9] = 0.0079357672259240/sqrt2;
	C12c[10] = -0.0025784067122813/sqrt2;
	C12c[11] = -0.0010190107982153/sqrt2;

	C12d[0] = C12c[11];
	C12d[1] = -C12c[10];
	C12d[2] = C12c[9];
	C12d[3] = -C12c[8];
	C12d[4] = C12c[7];
	C12d[5] = -C12c[6];
	C12d[6] = C12c[5];
	C12d[7] = -C12c[4];
	C12d[8] = C12c[3];
	C12d[9] = -C12c[2];
	C12d[10] = C12c[1];
	C12d[11] = -C12c[0];

	*c = C12c;
	*d = C12d;
	*support = 12;
}

void initC12inv(double **c, double **d, int *support)
{
	sqrt2 = sqrt(2.);

	C12c[10] = 0.0231751934774337/sqrt2;
	C12c[1] = -0.0586402759669371/sqrt2;
	C12c[8] = -0.0952791806220162/sqrt2;
	C12c[3] = 0.5460420930695330/sqrt2;
	C12c[6] = 1.1493647877137300/sqrt2;
	C12c[5] = 0.5897343873912380/sqrt2;
	C12c[4] = -0.1081712141834230/sqrt2;
	C12c[7] = -0.0840529609215432/sqrt2;
	C12c[2] = 0.0334888203265590/sqrt2;
	C12c[9] = 0.0079357672259240/sqrt2;
	C12c[0] = -0.0025784067122813/sqrt2;
	C12c[11] = -0.0010190107982153/sqrt2;

	C12d[0] = C12c[11];
	C12d[1] = -C12c[10];
	C12d[2] = C12c[9];
	C12d[3] = -C12c[8];
	C12d[4] = C12c[7];
	C12d[5] = -C12c[6];
	C12d[6] = C12c[5];
	C12d[7] = -C12c[4];
	C12d[8] = C12c[3];
	C12d[9] = -C12c[2];
	C12d[10] = C12c[1];
	C12d[11] = -C12c[0];

	*c = C12c;
	*d = C12d;
	*support = 12;
}

void initC18(double **c, double **d, int *support)
{
	sqrt2 = sqrt(2.);

	C18c[0] = -0.00268241867100*sqrt2;
	C18c[1] = 0.005503126709000*sqrt2;
	C18c[2] = 0.016583560479000*sqrt2;
	C18c[3] = -0.046507764479000*sqrt2;
	C18c[4] = -0.043220763560000*sqrt2;
	C18c[5] = 0.286503335274000*sqrt2;
	C18c[6] = 0.561285256870000*sqrt2;
	C18c[7] = 0.302983571773000*sqrt2;
	C18c[8] = -0.050770140755000*sqrt2;
	C18c[9] = -0.058196250762000*sqrt2;
	C18c[10] = 0.024434094321000 *sqrt2;
	C18c[11] = 0.011229240962000*sqrt2;
	C18c[12] = -0.006369601011000*sqrt2;
	C18c[13] = -0.001820458916000*sqrt2;
	C18c[14] = 0.000790205101000*sqrt2;
	C18c[15] = 0.000329665174000*sqrt2;
	C18c[16] = -0.000050192775000*sqrt2;
	C18c[17] = -0.000024465734000*sqrt2;

	C18d[0] = C18c[17];
	C18d[1] = -C18c[16];
	C18d[2] = C18c[15];
	C18d[3] = -C18c[14];
	C18d[4] = C18c[13];
	C18d[5] = -C18c[12];
	C18d[6] = C18c[11];
	C18d[7] = -C18c[10];
	C18d[8] = C18c[9];
	C18d[9] = -C18c[8];
	C18d[10] = C18c[7];
	C18d[11] = -C18c[6];
	C18d[12] = C18c[5];
	C18d[13] = -C18c[4];
	C18d[14] = C18c[3];
	C18d[15] = -C18c[2];
	C18d[16] = C18c[1];
	C18d[17] = -C18c[0];

	*c = C18c;
	*d = C18d;
	*support = 18;
}

void initC18inv(double **c, double **d, int *support)
{
	sqrt2 = sqrt(2.);

	C18c[16] = -0.00268241867100*sqrt2;
	C18c[1] = 0.005503126709000*sqrt2;
	C18c[14] = 0.016583560479000*sqrt2;
	C18c[3] = -0.046507764479000*sqrt2;
	C18c[12] = -0.043220763560000*sqrt2;
	C18c[5] = 0.286503335274000*sqrt2;
	C18c[10] = 0.561285256870000*sqrt2;
	C18c[7] = 0.302983571773000*sqrt2;
	C18c[8] = -0.050770140755000*sqrt2;
	C18c[9] = -0.058196250762000*sqrt2;
	C18c[6] = 0.024434094321000 *sqrt2;
	C18c[11] = 0.011229240962000*sqrt2;
	C18c[4] = -0.006369601011000*sqrt2;
	C18c[13] = -0.001820458916000*sqrt2;
	C18c[2] = 0.000790205101000*sqrt2;
	C18c[15] = 0.000329665174000*sqrt2;
	C18c[0] = -0.000050192775000*sqrt2;
	C18c[17] = -0.000024465734000*sqrt2;

	C18d[0] = C18c[17];
	C18d[1] = -C18c[16];
	C18d[2] = C18c[15];
	C18d[3] = -C18c[14];
	C18d[4] = C18c[13];
	C18d[5] = -C18c[12];
	C18d[6] = C18c[11];
	C18d[7] = -C18c[10];
	C18d[8] = C18c[9];
	C18d[9] = -C18c[8];
	C18d[10] = C18c[7];
	C18d[11] = -C18c[6];
	C18d[12] = C18c[5];
	C18d[13] = -C18c[4];
	C18d[14] = C18c[3];
	C18d[15] = -C18c[2];
	C18d[16] = C18c[1];
	C18d[17] = -C18c[0];

	*c = C18c;
	*d = C18d;
	*support = 18;
}

#endif

/* Author: Glen MacLachlan, bindatype@gmail.com
 * 
 *     This file is part of fwt.
 *
 *   make_scalogram is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Foobar is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with FWT.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "get_data.h"
#include "math_helper.h"

int main (int argc, char **argv)
{

	double *index,*signal,*uncert;
	double dx_sqd;
	double var,log_var;
	int octaves;
	int i,j,k;

	struct data ts;
	ts = get_data(stdin,ts);
	octaves = getNumOctaves(ts.ROWS);


	index = malloc(ts.ROWS*sizeof(double));
	signal = malloc(ts.ROWS*sizeof(double));
	uncert = malloc(ts.ROWS*sizeof(double));
	stack_columns(index,signal,uncert,ts);
	if ( 1 != ts.COLS && 2 != ts.COLS && 3 != ts.COLS ) {
		puts(" ");
		puts("WRONG NUMBER OF COLUMNS!");
		puts("Acceptable formats for input files are 1, 2 or 3 columns."); 
		puts("Try awk if necessary.");
		//      puts("For usage use -h or --help.");
		free( index );
		free( signal );  
		free( uncert );  
		free( ts.value ); 
		exit(EXIT_FAILURE);
	}


	for ( k = 1; k <= octaves; k++)
	{ 
		dx_sqd = 0.;
		for ( i = pow(2,k-1); i < (pow(2,k)); i++)
		{
			dx_sqd += signal[i]*signal[i];
		}
		var = dx_sqd/pow(2,k-1);
		j = octaves - k + 1;
		log_var = log( var )/log(2.);
		printf("%d %f \n", j, log_var );
	}


	free( index );
	free( signal );  
	free( uncert );
	free( ts.value );
	return 0;
}



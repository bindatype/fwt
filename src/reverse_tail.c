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
 *   along with fwt.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/* Wrap main code into this */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "get_data.h"
#include "math_helper.h"

int main (int argc, char **argv)
{

	double *index;
	double *signal;
	double *uncert;

	int i;
	int j;

	struct data ts;
	ts = get_data(stdin,ts);

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



	if ( 3 == ts.COLS ) {
		for ( i = 0; i < ts.ROWS ; i++)
		{
			printf("%d %20.16f %20.16f\n", i , signal[i], uncert[i]);
		}
		j = 0;
		for ( i = ts.ROWS-1; i >= 0 ; i--)
		{
			printf("%d %20.16f %20.16f\n", ts.ROWS+j++, signal[i], uncert[i]);
		}
	} else {
		for ( i = 0; i < ts.ROWS ; i++)
		{
			printf("%d %20.16f\n", i , signal[i]);
		}
		j = 0;
		for ( i = ts.ROWS-1; i >= 0 ; i--)
		{
			printf("%d %20.16f\n", ts.ROWS+j++, signal[i]);
		}
	} 


	free( ts.value );
	free( index );
	free( signal );  
	free( uncert );
	return 0;
}

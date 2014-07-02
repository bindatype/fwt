/* Author: Glen MacLachlan, bindatype@gmail.com
 * 
 * Copyright 2010 Glen Alan MacLachlan
 * 
 *     This file is part of wavelet.
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
 *   along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
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
  double meanY = 0.;
  double variance = 0.;

  double *index=NULL,*signal=NULL,*uncert=NULL;
 
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


  for ( int i = 0; i < ts.ROWS ; i++)
  {
    meanY +=signal[i];
  }
  meanY/=(double)ts.ROWS;
  
  for ( int i = 0; i < ts.ROWS ; i++)
  {
    variance += (signal[i]-meanY)*(signal[i]-meanY);
  }
  variance/=(double)(ts.ROWS-1);
  printf(" %g \n", variance);


 
  free( index );
  free( signal );  
  free( uncert );  
  free( ts.value );  

  return 0;
}

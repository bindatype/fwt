/* Author: Glen MacLachlan, bindatype@gmail.com
 *
 * Copyright (C) 2010 Glen Alan MacLachlan
 * 
 *   This file is part of Fast Wavelet Transform (fwt).
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



#include <stdio.h>
#include "usage.h"

void
usage()
{
printf("NAME\n \
        fwt - decomposes an array of numbers into wavelet coefficients.\n"); 
printf("\n \
\n \
SYNOPSIS\n \
        fwt [OPTION]... < [file]...\n ");
printf(" \
DESCRIPTION\n \
        This software expects input in the form of ascii numbers with one, two, or three columns.\n \
        If one column then that column must be the series to to transform. If two columns then\n \
        the first column is the index (such as time) and the second is the series (signal) to be transformed.\n \
        If three columns are supplied then the first column is the index, the second is the series (signal)\n \
        to be transformed, and the third column is the uncertainty. If only one or two columns are given\n \
        then the uncertainty is assumed to be the square root of the signal.\n \
        columns must be of length 2^m where m is a positive integer. The maximum size\n \
        of m depends on the machine running the code. It is the user's responsibility\n \
        to guarantee the length of the data. In any case the signal is assumed to be uniformly sampled.\n\n ");
printf(" \n \
        Input is supplied in the form of pipes or redirection. This can be accomplished via:\n \
          cat INPUTFILE | fwt\n \
        or \n \
          fwt < INPUTFILE\n \
\n \
        Different wavelet filters can be chosen via command line options.\n \
\n \
          cat INPUTFILE | fwt -d2\n \
        or\n \
          cat INPUTFILE | fwt -c12 --offset 3\n ");

printf("\n \
        If no wavelet filter is specified the default, -d2 (aka the Haar basis), is assumed.\n  \
\n \
        A positive offset to the signal may be specified by the --offset option or -o.\n  \
        For example, if there were an array 1,2,3...7,8 and an offset of one were given\n \
        then the signal would be processed as 8,1,2...6,7. This is useful when adjusting\n \
        the appearance of a scalogram. Any statistical measure which sums over position\n \
        values in an octave will be insensitive to offset.\n \
\n ");
printf("\n \
        The output of the code is also two column ascii data. The first column is \n \
        index information and the second column holds the transformed signal. \n ");
printf("\n \
OPTIONS\n \
        -d NUM, --daub=NUM Daubechies family of wavelet filters. NUM=2 gives the Haar filter. \n \
                           NUM determines wavelet support and can be 2, 4, 6.\n \
\n \
        -c NUM, --coif=NUM Coiflet family of wavelet filters. NUM determines wavelet support and \n \
                           can be 6, 12, or 18.\n \
\n ");
printf("\n \
        -i, --inverse Does inverse of fwt. \n \
\n \
        -o NUM, --order=NUM Specifies offset of the signal. If offset is not specified a \n \
                            default value of zero is assumed. \n \
\n \
	-g, --gaussian Bootstrap based on a gaussian probability distribution. The mean is zero and the width (sigma) \n \
	               is taken from the third column. If a third column isn't given then the width is assumed \n \
		       to be the square root of the number of counts.\n \
	 	       This option is incompatible with poisson bootstrap. \n \
\n \
	-p, --poisson Bootstrap based on a poisson probability distribution (Knuth's The Art of Computer Programming, Vol. 2.)\n \
		       The parameter lamda is taken from the third column. If a third column isn't given then the width \n \
		       is assumed to be the square root of the number of counts.\n \
	 	       This option is incompatible with gaussian bootstrap. \n \
\n \
AUTHOR\n \
        Written by Glen Alan MacLachlan.\n ");
printf("\n \
REPORTING BUGS\n \
        Report bugs to <bindatype@gmail.com>\n \
\n \
COPYRIGHT\n \
       Copyright © 2010 Glen Alan MacLachlan.  License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n \
       This is free software: you are free to change and redistribute it.  There is NO WARRANTY, to the extent permitted by law.\n \
\n \
REQUIREMENTS\n \
         gcc\n \
         make\n \
\n ");
printf("\n \
COMPILING\n \
        To make the project type:\n \
          make\n \
\n \
        To clean the project, i.e., remove the objects and executable:\n \
          make clean\n ");
}

void
version()
{
puts ("Fast Wavelet Transform, 2.0.04-10");
puts ("Copyright (C) 2010, Glen Alan MacLachlan, <bindatype@gmail.com>");
puts ("License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.");
puts ("This is free software; see the source for copying conditions.  There is NO");
puts ("warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.");
}

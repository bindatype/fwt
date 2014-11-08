#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <math.h>
#include "math_helper.h"
#include "filters.h"
#include "usage.h"
#include "get_data.h"



int main(int argc, char **argv)
{

	
	double *index;
	double *signal;
	double *uncert;
	double *short_signal;
	double *c,*d;
	double *temp;

	int octaves;
	int c_opts;
	short gaus=0; 
	short pois=0; 
	short denoise_octave = 0;
	int support = 2;
	int offset = 0;
	int inverse = 0;
	char *file = NULL;
	char filter_type[]="daub";
	double* (*boot_strap)(double *, int );

	while (1)
	{
		static struct option long_options[] =
		{
			{"coif",    required_argument, 0, 'c'},
			{"daub",    required_argument, 0, 'd'},
			{"file",    required_argument, 0, 'f'},
			{"gaussian",    no_argument,       0, 'g'},
			{"help",    no_argument,       0, 'h'},
			{"inverse", no_argument,       0, 'i'},
			{"offset",  required_argument, 0, 'o'},
			{"poisson", no_argument,       0, 'p'},
			{"version", no_argument,       0, 'v'},
			{0, 0, 0, 0}
		};
		int option_index = 0;

		c_opts = getopt_long (argc, argv, "c:d:f:ghio:pv",
				long_options, &option_index);

		if (c_opts == -1)
			break;

		switch (c_opts)
		{
			case 0:
				if (long_options[option_index].flag != 0)
					break;
				printf ("option %s", long_options[option_index].name);
				if (optarg)
					printf (" with arg %s", optarg);
				printf ("\n");
				break;

			case 'c':
				support = atoi(optarg);
				strcpy(filter_type,"coif");
				break;

			case 'd':
				support = atoi(optarg);
				strcpy(filter_type,"daub");
				break;

			case 'f':
				file = optarg;	
				break;

			case 'g':
				if (pois) {
					puts("Invalid options. User may set gaussian or poisson bootstrap but not both."); 
					puts("use -h or --help for usage."); 
					exit(EXIT_FAILURE);
				}
				gaus = 1;
				break;

			case 'h':
				usage();
				exit(EXIT_SUCCESS);

			case 'i':
				inverse = 1;
				break;

			case 'o':
				offset = atoi(optarg);
				break; 	

			case 'p':
				if (gaus) {
					puts("Invalid options. User may set gaussian or poisson bootstrap but not both."); 
					puts("use -h or --help for usage."); 
					exit(EXIT_FAILURE);
				}
				pois = 1;
				break;

			case 'v':
				version();
				exit(EXIT_SUCCESS);

			default:
				puts("Option not recognized. Try --help or -h");
				exit (2);
		}
	}

	if (optind < argc)
	{
		printf ("non-option ARGV-elements: ");
		while (optind < argc)
			printf ("%s ", argv[optind++]);
		putchar ('\n');
		exit (EXIT_SUCCESS);
	}



	short_signal = malloc(support *sizeof(double));


	/*************READ IN DATA ************************/


	FILE *fp;
//	fp = fopen("testfile.dat","r");
	struct data ts;
//	ts = get_data(fp,ts);
	ts = get_data(stdin,ts);
	octaves = getNumOctaves(ts.ROWS);
	//  printf("NumCols: %d\n",ts.COLS);  
	if (denoise_octave > octaves){
		free(ts.value);
		exit(EXIT_FAILURE);
	}

	temp = malloc(ts.ROWS*sizeof(double));
	index = malloc(ts.ROWS*sizeof(double));
	signal = malloc(ts.ROWS*sizeof(double));
	uncert = malloc(ts.ROWS*sizeof(double));
	stack_columns(index,signal,uncert,ts);

	if ( 1 != ts.COLS && 2 != ts.COLS && 3 != ts.COLS ) {
		puts(" ");
		puts("WRONG NUMBER OF COLUMNS!");
		puts("Acceptable formats for input files are 1, 2 or 3 columns."); 
		puts("Try awk if necessary.");
		puts("For usage use -h or --help.");
		free( index );
		free( signal );  
		free( uncert );  
		free( ts.value );
		free( temp ); 
		exit(EXIT_FAILURE);
	}
	//    for (int i = 0; i < ts.ROWS; i++)
	//      printf ("# %20.16f\n",signal[i]);


		if ( ts.ROWS < support)  
		{ 
			puts("Signal length should be at least as long as the filter used.");
			free( short_signal );
			free( index );
			free( signal );
			free( uncert );
			free( temp );
			free(ts.value);
			exit(2);
		}

	/*********** PREPARE BOOTSTRAP NOISE *************************/


	double *boot_noise;
	if ( gaus ) {
		boot_strap = box_muller;
	}
	if ( pois ) {
		boot_strap = poisson;
	}
	if ( gaus || pois ) {
		boot_noise = boot_strap (uncert,ts.ROWS);
		for ( int i = 0; i <ts.ROWS; i++ ) {
			signal[i] += boot_noise[i];
		}
	}



	/*********** PREPARE WAVELET FILTERS *************************/



	if ( 0 == strcmp (filter_type,"daub") )
		{
			switch (support)
			{
				case 2:
					if (!inverse){
					    filter = initD2;
					 } else {
					    filter = initD2inv;
                                         }
					break;  
				case 4:
					if (!inverse){
					    filter = initD4;
					 } else {
					    filter = initD4inv;
                                         }
					break;
				case 6:
					if (!inverse){
					    filter = initD6;
					 } else {
					    filter = initD6inv;
                                         }
					break;
				default:
					puts("Filter not supported.");
					free( short_signal );
					free( index );
					free( signal );
					free( uncert );
					free( temp );
					free(ts.value);
					if (gaus || pois)
						free (boot_noise);
					exit(2);
			}
		} 
		else if ( 0 == strcmp (filter_type,"coif") )
		{
			switch (support)
			{
				case 6:
					if (!inverse){
					    filter = initC6;
					 } else {
					    filter = initC6inv;
                                         }
					break;
				case 12:
					if (!inverse){
					    filter = initC12;
					 } else {
					    filter = initC12inv;
                                         }
					break;
				case 18:
					if (!inverse){
					    filter = initC18;
					 } else {
					    filter = initC18inv;
                                         }
					break;

				default:
					puts("Filter not supported.");
					free( short_signal );
					free( index );
					free( signal );
					free( uncert );
					free( temp );
					free(ts.value);
					if (gaus || pois)
						free (boot_noise);
					exit(2);
			}   
		}
		else
		{
			// If no basis specified default to D4  
			filter = initD4;
		}

	filter(&c,&d,&support);





	/**************** Do Forward Transform ********************/
	if (!inverse)
	{
		for ( int i = 0; i < ts.ROWS; i++)
			temp[(i+offset)%(ts.ROWS)]  = signal[i]; //Back wrap to front or vice versa 

		for ( int i = 0; i < ts.ROWS; i++)
			signal[i] = temp[i]; // Back wrap to front or vice versa 

		for( int k = 1; k <= ts.ROWS/2; k <<= 1 ){

			// Make copy of signal at each octave and do offset if necessary 
			for ( int i = 0; i < ts.ROWS/k; i++){
				temp[(i+0*offset)%(ts.ROWS/k)]  = signal[i]; // Back wrap to front or vice versa 
				// temp[(i+offset)%(ts.ROWS/k)]  = signal[i]; // Back wrap to front or vice versa 
			}
			// Take inner product with wavelet filter, doing loop round each octave. 
			for ( int i = 0; i < ts.ROWS/2/k; i++){
				for ( int j = 0; j < support; j++){
					short_signal[j] = temp[(2*i+j)%(ts.ROWS/k)];
				}
				signal[2*i]   = inner_prod(support,c,short_signal);
				signal[2*i+1] = inner_prod(support,d,short_signal);
			}

			// Do Mallat down sampling to group approx and detail coefficients in resulting array. 
			dn_sample(&signal,ts.ROWS/k);

			// Repeat until signal is decimated. 
		}
	}



	/**************** Do Backward Transform ********************/
	else // We are doing inverse of FWT 
	{
		for( int k = ts.ROWS/2; k >= 1; k >>= 1){
			/* Fan out and reshuffle approx and detail coefficients according to Mallat scheme. */
			up_sample (&signal,ts.ROWS/k);
			/* Take inner product with wavelet filter, doing loop round each octave. */
			for ( int i = 0; i < ts.ROWS/2/k; i++)
			{
				for ( int j = 0; j < support; j++)
					short_signal[j] = signal[(ts.ROWS+2-support+ 2*i+j)%(ts.ROWS/k)];

				temp[2*i]=inner_prod(support,c,short_signal);
				temp[2*i+1]=inner_prod(support,d,short_signal);
			}

			/* Make copy of signal at each octave and do offset if necessary */
			for ( int i = 0; i < ts.ROWS/k; i++)
				signal[i] = temp[(i+0*offset)%(ts.ROWS/k)]; 
				/*signal[i] = temp[(i+offset)%(ts.ROWS/k)]; */

			/* Repeat until signal is decimated. */
		}
		for ( int i = 0; i < ts.ROWS; i++)
			temp[i]=signal[i];

		for ( int i = 0; i < ts.ROWS; i++)
			signal[i] = temp[(i+offset)%(ts.ROWS)];

	}

/* Print results */

	for ( int i = 0; i < ts.ROWS; i++)
			printf("%d %20.16f\n",i+1,signal[i]);
	free( short_signal );
	free( index );
	free( signal );
	free( uncert );  
	free( temp );
	free(ts.value);

	//fclose(fp);

	if (gaus || pois)
		free (boot_noise);
	return 0;
}

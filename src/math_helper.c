#include "math_helper.h"


double inner_prod(int N,double vec1[],double vec2[]){
	double inner_prod = 0.;
	int i;

	for ( i = 0; i < N; i++)
	{
		inner_prod += vec1[i]*vec2[i];
	}
	return  inner_prod;
}

int getNumOctaves(int N)
{
	int n;
	int octaves = 0;
	n=N;
	while (n > 1)
	{
		n>>=1;
		octaves++;
	}
	return octaves;
}


double *dn_sample(double **a, int N)
{
	/* Does forwared Mallat scheme swapping */

	double *p = *a;
	double *temp;
	int i;

	temp = malloc ( N * sizeof (double) );

	for ( i = 0; i < N; i++)
	{
		if ( 0 == i%2 )
		{
			temp[i/2] = p[i]; 
		}
		else if ( 1 == i%2 )
		{
			temp[(i-1)/2+N/2] = p[i]; 
		}
	}

	for ( i = 0; i < N; i++)
	{
		p[i] = temp[i];
	}  


	free( temp );
	return p;
}
double *up_sample (double **a, int N)
{
	/* does backward Mallat scheme swapping. */
	double *p = *a;
	double *temp;
	int i;

	temp = malloc ( N * sizeof (double) );


	for ( i = 0; i < N/2; i++)
	{
		temp[2*i] = p[i];
		temp[2*i+1] = p[i+N/2];
	}

	for ( i = 0; i < N; i++)
	{
		p[i] = temp[i];
	} 


	free( temp );
	return p;
}

double* unirand(double *array, int N)
{
	double *local;
	local = malloc ( N * sizeof (double) );
	long int random;
	double drandom,max;

	srand((unsigned)time(NULL));

	for (int i=0; i<N; i++){
		random = rand();
		drandom = (double)random;
		max = (double) RAND_MAX;
		printf("Number %d, %lu, %u %le\n",i,random,RAND_MAX,drandom/max);
	}

	return local;
}

double* poisson(double *lambda,int LENGTH)
{ //Knuth's algorithm
	double *local;
	local = malloc ( LENGTH * sizeof (double) );
	long int random;
	double drandom,max,u;
	double L,p;
	int k ;
	srand((unsigned)time(NULL));

	for (int i=0; i<LENGTH; i++){
		L = exp(-lambda[i]);
		p = 1;
		k = 0;


		do {
			random = rand();
			drandom = (double)random;
			max = (double) RAND_MAX;
			u = drandom/max;
			p = p*u;
			k++; 
		} while ( p >= L);

		local[i] = k - 1 ;
	}
	return local;  
}

double* box_muller(double *sigma, int LENGTH)
{ 
	double *local;
	local = malloc ( LENGTH * sizeof (double) );
	long int random;
	double drandom,max,r1,r2;

	srand((unsigned)time(NULL)); 

	for (int i=0; i<LENGTH; i++){
		random = rand();
		drandom = (double)random;
		max = (double) RAND_MAX;
		r1 = drandom/max;
		random = rand();
		drandom = (double)random;
		max = (double) RAND_MAX;
		r2 = drandom/max;

		local[i] = sigma[i] * sqrt(-2*log( r1 ) )*cos(2*G_PI*r2 );  
	}

	return local;
}


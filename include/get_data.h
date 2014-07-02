#ifndef __GET_DATA_H__
#define __GET_DATA_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 100


struct data {
	int COLS,ROWS,SIZE;
	double *value;
};

struct data get_data(FILE * stream,struct data this_struct);
void stack_columns(double *index, double *signal, double *uncert, struct data ts);
void remove_trailing_blanks(char *buf);

#endif

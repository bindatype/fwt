# Copyright (C) 2010 Glen Alan MacLachlan

CC=gcc
CFLAGS=  -Wall -g -ansi -std=c99 -O3 -fopenmp -lgomp
LDFLAGS= #-lgomp
CMATH= -lm 
INCLUDE=-I ./include
SRC=src
OBJECTS= usage.o get_data.o math_helper.o 
EXE=fwt


all: get_data math_helper usage fwt wavelet_variance heatmap reverse_tail get_mean get_variance get_min get_max agg get_sum dagg

fwt: 
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDE) $(OBJECTS) $(SRC)/$(EXE).c -o $(EXE) $(CMATH) 

math_helper:
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDE) $(SRC)/math_helper.c -c $(CMATH)

get_data:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)/get_data.c -c

get_mean:
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJECTS) $(SRC)/get_mean.c -o get_mean $(CMATH)
 
get_variance:
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJECTS) $(SRC)/get_variance.c -o get_variance $(CMATH) 

get_min:
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJECTS) $(SRC)/get_min.c -o get_min $(CMATH) 

get_max:
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJECTS) $(SRC)/get_max.c -o get_max $(CMATH) 

get_sum:
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJECTS) $(SRC)/get_sum.c -o get_sum $(CMATH)
	
agg:
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJECTS) $(SRC)/agg.c -o agg $(CMATH) 

dagg:
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJECTS) $(SRC)/dagg.c -o dagg $(CMATH) 

wavelet_variance: 
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJECTS) $(SRC)/wavelet_variance.c -o wavelet_variance $(CMATH)

heatmap: 
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJECTS) $(SRC)/heatmap.c -o heatmap $(CMATH)

reverse_tail: 
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJECTS) $(SRC)/reverse_tail.c -o reverse_tail $(CMATH)

usage: 
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)/usage.c -c

install: 
	install -c fwt /usr/local/bin
	install -c wavelet_variance /usr/local/bin
	install -c heatmap /usr/local/bin
	install -c reverse_tail /usr/local/bin
	install -c dagg /usr/local/bin
	install -c agg /usr/local/bin
	install -c get_mean /usr/local/bin
	install -c get_sum /usr/local/bin
	install -c get_min /usr/local/bin
	install -c get_max /usr/local/bin
	install -c get_variance /usr/local/bin
	

clean:
	rm $(OBJECTS) $(EXE) wavelet_variance heatmap reverse_tail agg dagg get_mean get_min get_max get_sum get_variance 

clean_objects:
	rm $(OBJECTS)

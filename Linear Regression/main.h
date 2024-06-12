#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

const double training_data[][2] = {
    {0,0},
    {1,2},
    {2,4},
    {3,6},
    {4,8},
    {5,10},
    {6,12}
};


// data seems to follow mathematical model: y = mx where y is output, x is input, and m is some parameter to be determined by training the model (the ai)

double rand_double(void);

double scorer(double m, double b);

#endif

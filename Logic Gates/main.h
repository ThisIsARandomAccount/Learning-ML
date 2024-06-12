#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// OR-Gate model
const double or_training_data[][3] = {
    {0,0,0},
    {0,1,1},
    {1,0,1},
    {1,1,1}
};

double sigmoid(double x);
double scorer(double w1, double w2, double b);
double rand_double(void);

#endif

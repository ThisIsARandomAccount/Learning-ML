#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// OR-Gate model
const double or_training_data[][3] = {
    {72,99,27},
    {27,45,18},
    {18,39,21},
    {13,21,7}
};

double sigmoid(double x);
double scorer(double w1, double w2, double b);
double rand_double(void);

#endif

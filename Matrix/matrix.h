#ifndef matrix_h
#define matrix_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "file_reader.h"
#include <string.h>
#include <time.h>
#include <errno.h>

#define file_path "/Users/nandan/Documents/matrix.txt"


typedef struct Matrix{
    double** data;
    int rows;
    int cols;
} Matrix;

#endif

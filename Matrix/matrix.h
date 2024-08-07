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



Matrix* create(int rows, int cols); // SUCCESS
void fill(Matrix* matrix, double num); // SUCCESS
void copy(Matrix* matrix, double** data); // SUCCESS
void free_matrix(Matrix* matrix); // SUCCESS
void print_matrix(Matrix* matrix); // SUCCESS
Matrix* full_copy(Matrix* to_copy); // SUCCESS
void save(Matrix* to_save, char* path); // SUCCESS
Matrix* load(char* path); // SUCCESS
double rand_double(double min, double max); // SUCCESS
void randomize(Matrix* to_randomize, double min, double max); // SUCCESS
Matrix* flatten(Matrix* to_flatten, int row_col_bool); // SUCCESS
int argmax(Matrix* input, int col); // SUCCESS
Matrix* dot(Matrix* m1, Matrix* m2); // SUCCESS
Matrix* add(Matrix* m1, Matrix* m2); // SUCCESS
Matrix* subtract(Matrix* m1, Matrix* m2); // SUCCESS
Matrix* apply(Matrix* m, double(*func)(double)); // SUCCESS
Matrix* scale(Matrix* m, double num); // SUCCESS
Matrix* transpose(Matrix* m); // SUCCESS
Matrix* row_echelon(Matrix* m); // SUCCESS
double determinant(Matrix* m); // SUCCESS
double r_determinant(Matrix* simple); // SUCCESS



#endif

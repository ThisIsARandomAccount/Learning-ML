// basic ai demo
#include "main.h"
#define training_size sizeof(training_data)/sizeof(training_data[0])

double rand_double(void){
    srand((unsigned int)time(NULL));
    double number = (double)rand();
    number = (double)rand(); // need to do another one because apparently the logic to get a random number from a seed makes all similar seeds have similar first random numbers. the second is more random, so the second will be used.
    return(number/RAND_MAX);
}

double scorer(double m, double b){
    double score = 0;
    for(int i = 0; i < training_size; i++){
        double predicted = m*training_data[i][0] + b;
        double err = predicted - training_data[i][1];
        score += pow(err,2.0);
    }
    score /= training_size;
    return score;
}

int main(void) {
    double m = rand_double() * 10; // weight of parameter
    double b = rand_double() * 10; // bias
    double h = 1e-3;
    double dscore = 1e-3; // what we call learning rate
    double score = scorer(m, b);
    double in_m = m;
    double in_b = b;
    for(int i = 0; i < 800; i++){
        double dscoredm = (scorer(m+h, b)-scorer(m, b))/h;
        double dscoredb = (scorer(m,b+h)-scorer(m,b))/h;
        m -= dscore*dscoredm;
        b -= dscore*dscoredb;
    }
    printf("Initial Score: %lf\n",score);
    printf("Final Score: %lf\n", scorer(m, b));
    printf("Initial Model: y=%lfx+%lf\n",in_m,in_b);
    printf("Final Model: y=%lfx+%lf\n",m,b);
    return 0;
}

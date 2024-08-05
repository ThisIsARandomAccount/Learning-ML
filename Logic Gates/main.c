#include "main.h"
#define or_training_size sizeof(or_training_data)/sizeof(or_training_data[0])

// basic ai demo
double rand_double(void){
    srand((unsigned int)time(NULL));
    double number = (double)rand();
    number = (double)rand(); // need to do another one because apparently the logic to get a random number from a seed makes all similar seeds have similar first random numbers. the second is more random, so the second will be used.
    return(number/RAND_MAX);
}

double scorer(double w1, double w2, double b){
    double score = 0;
    for(int i = 0; i < or_training_size; i++){
        double predicted = w1*or_training_data[i][0] + w2*or_training_data[i][1] + b;
        //predicted = sigmoid(predicted);
        double err = predicted - or_training_data[i][2];
        score += pow(err,2.0);
    }
    score /= or_training_size;
    return score;
}

double sigmoid(double x){
    return(1.0/(1.0+exp(-x)));
}

int main(void) {
    double w1 = rand_double() - 0.5; // weight of parameter 1
    double w2 = rand_double() - 0.5; // weight of parameter 2
    double b = rand_double() - 0.5; // bias
    double h = 1e-3;
    double dscore = 1e-1; // what we call learning rate
    double score = scorer(w1, w2, b);
    for(int i = 0; i < 1000000; i++){
        double dscoredw1 = (scorer(w1+h, w2, b)-scorer(w1,w2,b))/h;
        double dscoredw2 = (scorer(w1,w2+h, b)-scorer(w1,w2,b))/h;
        double dscoredb = (scorer(w1,w2,b+h)-scorer(w1,w2,b))/h;
        w1 -= dscore*dscoredw1;
        w2 -= dscore*dscoredw2;
        b -= dscore*dscoredb;
    }
    printf("Initial Score: %lf\n",score);
    printf("Final Score: %lf\n", scorer(w1, w2, b));
    /*printf("Prediction of 1||1: %lf\n", sigmoid(w1*1+w2*1+b));
    printf("Prediction of 1||0: %lf\n",sigmoid(w1*1+w2*0+b));
    printf("Prediction of 0||1: %lf\n", sigmoid(w1*0+w2*1+b));
    printf("Prediction of 0||0: %lf\n", sigmoid(w1*0+w2*0+b));*/
    printf("21 & 36: %lf\n",w1*21+w2*36+b);
    return 0;
}

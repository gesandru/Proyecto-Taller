#include <cstdio>
#include "../include/EccAnom.h"
#include "../include/const.h"

using namespace std;

double static eccAnom (double M, double e){

int maxit = 15;
int i = 1;
double E;

//Starting value
M = fmod(M, Const::pi2);

if (e<0.8){
    E = M; 
}else{
    E = Const::pi;
}

double f = E - e*sin(E) - M;
E = E - f / ( 1.0 - e*cos(E) );

//Iteration
while (abs(f) > 1e2*nextafter(1.0, pow(2, -52))){
    f = E - e*sin(E) - M;
    E = E - f / ( 1.0 - e*cos(E) );
    i = i+1;
    if (i==maxit){
        printf(" convergence problems in EccAnom");
        exit(EXIT_FAILURE);
    }
}
return E;
}

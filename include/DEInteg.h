#ifndef _DEINTEG_
#define _DEINTEG_

#include "../include/Matrix.h"
#include "../include/sign_.h"
#include <cmath>

class DEInteg
{
public:
    Matrix static deinteg(Matrix (*func)(double, double),double t,double tout,double relerr,
                          double abserr,int n_eqn,Matrix y);
};

#endif
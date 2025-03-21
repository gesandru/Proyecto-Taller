#ifndef _CHEB3D_
#define _CHEB3D_

#include "../include/Matrix.h"
#include <cmath>

class Cheb3D
{
    public:
        Matrix static cheb3D(double t,int N,double Ta,double Tb,Matrix& Cx,Matrix& Cy,Matrix& Cz);
};

#endif
#ifndef _LEGENDRE_
#define _LEGENDRE_

#include "../include/Matrix.h"
#include <cmath>

class Legendre
{
    public:
        void static legendre(int n,int m,double fi, Matrix& pnm, Matrix& dpnm);
};

#endif
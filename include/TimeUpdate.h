#ifndef _TIMEUPDATE_
#define _TIMEUPDATE_

#include "../include/Matrix.h"
#include <cmath>

class TimeUpdate
{
    public:
        void static timeUpdate(Matrix& P, Matrix Phi, double Qdt);
        void static timeUpdate(Matrix& P, Matrix Phi);
};

#endif
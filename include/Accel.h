#ifndef _ACCEL_
#define _ACCEL_

#include "../include/Matrix.h"
#include <cmath>

class Accel
{
    public:
        Matrix static accel(double x, Matrix& Y);
};

#endif
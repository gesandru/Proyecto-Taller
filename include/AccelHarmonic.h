#ifndef _ACCELHARMONIC_
#define _ACCELHARMONIC_

#include "../include/Matrix.h"
#include "../include/Legendre.h"
#include "../include/globals.h"
#include <cmath>

class AccelHarmonic
{
    public:
        Matrix static accelHarmonic(Matrix r, Matrix E, int n_max, int m_max);
};

#endif
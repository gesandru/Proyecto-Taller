#ifndef _ACCELPOINTMASS_
#define _ACCELPOINTMASS_

#include "../include/Matrix.h"
#include <cmath>

class AccelPointMass
{
    public:
        Matrix static accelPointMass(Matrix& r, Matrix& s, double GM);
};

#endif
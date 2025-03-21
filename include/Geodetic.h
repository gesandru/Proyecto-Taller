#ifndef _GEODETIC_
#define _GEODETIC_

#include "../include/Matrix.h"
#include <cmath>

class Geodetic
{
    public:
        void static geodetic(Matrix r, double& lon, double& lat, double& h);
};

#endif
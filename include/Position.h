#ifndef _POSITION_
#define _POSITION_

#include "../include/Matrix.h"
#include "../include/const.h"
#include <cmath>

class Position
{
    public:
        Matrix static position(double lon, double lat, double h);
};

#endif
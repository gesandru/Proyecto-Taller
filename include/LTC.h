#ifndef _LTC_
#define _LTC_

#include "../include/Matrix.h"
#include "../include/R_y.h"
#include "../include/R_z.h"
#include <cmath>

class LTC
{
    public:
        Matrix static ltc(double lon,double lat);
};

#endif
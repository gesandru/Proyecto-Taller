#ifndef _IERS_
#define _IERS_

#include "../include/Matrix.h"
#include "../include/const.h"
#include <cmath>

class IERS
{
    public:
    void static iers(Matrix eop, double Mjd_UTC,char interp, double &x_pole, double &y_pole, double &UT1_UTC,
                     double &LOD, double &dpsi, double &deps, double &dx_pole, double &dy_pole, double &TAI_UTC);
    void static iers(Matrix eop, double Mjd_UTC, double &x_pole, double &y_pole, double &UT1_UTC,
                     double &LOD, double &dpsi, double &deps, double &dx_pole, double &dy_pole, double &TAI_UTC);
};

#endif
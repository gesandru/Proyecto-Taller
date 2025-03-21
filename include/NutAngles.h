#ifndef _NUTANGLES_
#define _NUTANGLES_

#include "../include/Matrix.h"
#include <cmath>

class NutAngles
{
    public:
        void static nutAngles(double Mjd_TT, double& dpsi, double& deps);
};

#endif
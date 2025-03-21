#ifndef _AZELPA_
#define _AZELPA_

#include "../include/Matrix.h"
#include <cmath>

class AzElPa
{
    public:
        void static azElPa(Matrix& s, double& Az, double& El, Matrix& dAds, Matrix& dEds);
};

#endif
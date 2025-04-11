#ifndef _AZELPA_
#define _AZELPA_

#include "../include/Matrix.h"
#include <cmath>

class AzElPa
{
    public:
        tuple<double, double, Matrix, Matrix> static azElPa(Matrix& s);
};

#endif
#ifndef _POLEMATRIX_
#define _POLEMATRIX_

#include "../include/Matrix.h"
#include "../include/R_x.h"
#include "../include/R_y.h"
#include <cmath>

class PoleMatrix
{
    public:
        Matrix static poleMatrix (double xp, double yp);
};

#endif
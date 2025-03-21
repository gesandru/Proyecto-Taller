#ifndef _NUTMATRIX_
#define _NUTMATRIX_

#include "../include/Matrix.h"
#include "../include/MeanObliquity.h"
#include "../include/NutAngles.h"
#include "../include/R_x.h"
#include "../include/R_z.h"
#include <cmath>

class NutMatrix
{
    public:
        Matrix static nutMatrix (double Mjd_TT);
};

#endif
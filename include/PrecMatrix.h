#ifndef _PRECMATRIX_
#define _PRECMATRIX_

#include "../include/Matrix.h"
#include "../include/R_y.h"
#include "../include/R_z.h"
#include <cmath>

class PrecMatrix
{
    public:
        Matrix static precMatrix (double Mjd_1, double Mjd_2);
};

#endif
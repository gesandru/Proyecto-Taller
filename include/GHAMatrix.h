#ifndef _GHAMATRIX_
#define _GHAMATRIX_

#include "../include/Matrix.h"
#include "../include/gast.h"
#include "../include/R_z.h"
#include <cmath>

class GHAMatrix
{
    public:
        Matrix static ghaMatrix (double Mjd_UT1);
};

#endif
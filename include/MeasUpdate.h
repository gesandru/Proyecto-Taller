#ifndef _MEASUPDATE_
#define _MEASUPDATE_

#include "../include/Matrix.h"
#include <cmath>

class MeasUpdate
{
    public:
        void static measUpdate( Matrix& x, double z, double g, double s, Matrix G, Matrix& P, double n, Matrix& K);
};

#endif
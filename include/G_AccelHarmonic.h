#ifndef _GACCELHARMONIC_
#define _GACCELHARMONIC_

#include "../include/Matrix.h"
#include "../include/AccelHarmonic.h"
#include <cmath>

class G_AccelHarmonic
{
    public:
        Matrix static g_AccelHarmonic(Matrix r, Matrix U, double  n_max, double m_max );
};

#endif
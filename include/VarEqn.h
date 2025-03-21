#ifndef _VAREQN_
#define _VAREQN_

#include "../include/Matrix.h"
#include "../include/timediff.h"
#include "../include/PrecMatrix.h"
#include "../include/NutMatrix.h"
#include "../include/PoleMatrix.h"
#include "../include/GHAMatrix.h"
#include "../include/AccelHarmonic.h"
#include "../include/G_AccelHarmonic.h"
#include <cmath>

class VarEqn
{
    public:
        Matrix static varEqn(double x, Matrix yPhi);
};

#endif
#ifndef _GIBBS_
#define _GIBBS_

#include "../include/Matrix.h"
#include "../include/const.h"
#include "../include/angl.h"
#include "../include/unit.h"
#include <cmath>
#include <string>

class Gibbs
{
    public:
        void static gibbs( Matrix r1, Matrix r2, Matrix r3, Matrix& v2, double& theta, double& theta1,
                    double& copa, std::string& error);
};

#endif
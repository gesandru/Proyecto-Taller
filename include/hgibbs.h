#ifndef _HGIBBS_
#define _HBIGGS_

#include "../include/Matrix.h"
#include "../include/const.h"
#include "../include/unit.h"
#include "../include/angl.h"
#include <cmath>
#include <string>

class Hbiggs
{
    public:
        void hgibbs ( Matrix r1, Matrix r2, Matrix r3, double Mjd1, double Mjd2, double Mjd3,
                      Matrix& v2, double& theta, double& theta1, double& copa, std::string& error);
};

#endif
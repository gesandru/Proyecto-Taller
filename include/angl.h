#ifndef _ANGL_
#define _ANGL_

#include "../include/Matrix.h"
#include "../include/sign_.h"
#include <cmath>

class Angl
{
    public:
        double static angl (Matrix& vec1, Matrix& vec2);
};

#endif
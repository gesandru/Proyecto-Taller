#ifndef _ELEMENTS_
#define _ELEMENTS_

#include "../include/Matrix.h"
#include <cmath>

class Elements
{
    public:
        static tuple<double, double, double, double, double, double, double,> elements (Matrix& y);
};

#endif
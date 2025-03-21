#ifndef _MJDAY_
#define _MJDAY_

#include "../include/Matrix.h"
#include <cmath>

class Mjday
{
    public:
        double static mjday(double yr, double mon, double day, double hr, double min, double sec);
        double static mjday(double yr, double mon, double day);
};

#endif
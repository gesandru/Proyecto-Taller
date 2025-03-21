#ifndef _EKF_
#define _EKF_

#include "../include/Matrix.h"
#include "../include/const.h"
#include "../include/globals.h"
#include "../include/Position.h"
#include "../include/Mjday.h"
#include "../include/LTC.h"
#include "../include/IERS.h"
#include "../include/timediff.h"
#include "../include/gmst.h"
#include "../include/TimeUpdate.h"
#include "../include/AzElPa.h"
#include "../include/MeasUpdate.h"
#include <cmath>
#include <cstdio>

class EKF_GEOS3
{
public:
    void static ekf_geos();
};

#endif
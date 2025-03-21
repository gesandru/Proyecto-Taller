#include "../include/AccelPointMass.h"

Matrix static accelPointMass(Matrix& r,Matrix& s, double GM){

Matrix d = r - s;


return ( (d/pow(d.norm(), 3) + s/pow(d.norm(), 3)) * -GM);
}
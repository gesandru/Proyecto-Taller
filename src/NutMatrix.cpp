#include "../include/NutMatrix.h"

Matrix static nutMatrix (double Mjd_TT){

//Mean obliquity of the ecliptic
double eps = MeanObliquity::meanObliquity(Mjd_TT);

//Nutation in longitude and obliquity
double dpsi = 0.0;
double deps = 0.0;
NutAngles::nutAngles(Mjd_TT, dpsi, deps);

//Transformation from mean to true equator and equinox
return (Rx::R_x(-eps-deps)*Rz::R_z(-dpsi)*Rx::R_x(+eps));
}
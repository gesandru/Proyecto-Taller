#include "../include/EqnEquinox.h"

double static eqnEquinox(double Mjd_TT){

//Nutation in longitude and obliquity
double dpsi=0;
double deps=0;
NutAngles::nutAngles(Mjd_TT, dpsi, deps);

//Equation of the equinoxes
return (dpsi * cos ( MeanObliquity::meanObliquity(Mjd_TT) ));
}
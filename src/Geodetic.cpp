#include <cstdio>
#include "../include/Geodetic.h"
#include "../include/const.h"

void static geodetic(Matrix r, double& lon, double& lat, double& h){


double R_equ = Const::R_Earth;
double f     = Const::f_Earth;

double epsRequ = nextafter(1.0, pow(2, -52))*R_equ;        //Convergence criterion
double e2      = f*(2.0-f);        //Square of eccentricity

double X = r(1);                   //Cartesian coordinates
double Y = r(2);
double Z = r(3);
double rho2 = X*X + Y*Y;           //Square of distance from z-axis

//Check validity of input data
if (r.norm()==0.0){
    lon = 0.0;
    lat = 0.0;
    h   = -Const::R_Earth;
    printf( " invalid input in Geodetic constructor\n" );
    exit(EXIT_FAILURE);
}

//Iteration 
double dZ = e2*Z;
double ZdZ = 0.0;
double Nh = 0.0;
double N = 0.0;

while(true){
    ZdZ    =  Z + dZ;
    Nh     =  sqrt ( rho2 + ZdZ*ZdZ );
    double SinPhi =  ZdZ / Nh;                    //Sine of geodetic latitude
    N      =  R_equ / sqrt(1.0-e2*SinPhi*SinPhi);
    double dZ_new =  N*e2*SinPhi;
    if ( abs(dZ-dZ_new) < epsRequ ){
        break;
    }
    dZ = dZ_new;
}

//Longitude, latitude, altitude
lon = atan2 ( Y, X );
lat = atan2 ( ZdZ, sqrt(rho2) );
h   = Nh - N;

}
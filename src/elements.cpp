#include "../include/Elements.h"
#include "../include/const.h"

static tuple<double, double, double, double, double, double, double> elements (Matrix& y){

    Matrix r = Matrix(3);
    Matrix v = Matrix(3);

for(i = 0; i<=2;i++){
    r(i) = y(i);
}

int j=0;
 for(i = 3; i<=5;i++){
    v(j) = y(i);
    j++;
}

 Matrix h = r*v;                                    // Areal velocity
 double magh = h.norm();
 double p = magh*magh/Const::GM_Earth;
 double H = h.norm();
 
 double Omega = atan2 ( h(1), -h(2) );                     // Long. ascend. node 
 double Omega = fmod(Omega,Const::pi2);
 double i     = atan2 ( sqrt(h(1)*h(1)+h(2)*h(2)), h(3) ); // Inclination        
 double u     = atan2 ( r(3)*H, -r(1)*h(2)+r(2)*h(1) );    // Arg. of latitude   
 
 double R  = r.norm();                                      // Distance
 
 double a = 1/(2/R-v.dot(v)/Const::GM_Earth);               // Semi-major axis
 
 double eCosE = 1-R/a;                                     // e*cos(E)           
 double eSinE = r.dot(v)/sqrt(Const::GM_Earth*a);           // e*sin(E)
 
 double e2 = eCosE*eCosE +eSinE*eSinE;
 double e  = sqrt(e2);                                     // Eccentricity
 double E  = atan2(eSinE,eCosE);                           // Eccentric anomaly  
 
 double M  = fmod(E-eSinE,Const::pi2);                             // Mean anomaly
 
 double nu = atan2(sqrt(1.0-e2)*eSinE, eCosE-e2);          // True anomaly
 
 double omega = fmod(u-nu,Const::pi2);                             // Arg. of perihelion
 
 return new tuple<double, double, double, double, double, double, double>(p, a, e, i, Omega, omega, M)
 }
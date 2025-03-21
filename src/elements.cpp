#include "../include/Elements.h"
#include "../include/const.h"

void static elements (Matrix& y, double& p, double& a, double& e, double& i, double& Omega, double& omega, double& M){

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
 p = magh*magh/Const::GM_Earth;
 double H = h.norm();
 
 Omega = atan2 ( h(1), -h(2) );                     // Long. ascend. node 
 Omega = fmod(Omega,Const::pi2);
 i     = atan2 ( sqrt(h(1)*h(1)+h(2)*h(2)), h(3) ); // Inclination        
 double u     = atan2 ( r(3)*H, -r(1)*h(2)+r(2)*h(1) );    // Arg. of latitude   
 
 double R  = r.norm();                                      // Distance
 
 a = 1/(2/R-v.dot(v)/Const::GM_Earth);               // Semi-major axis
 
 double eCosE = 1-R/a;                                     // e*cos(E)           
 double eSinE = r.dot(v)/sqrt(Const::GM_Earth*a);           // e*sin(E)
 
 double e2 = eCosE*eCosE +eSinE*eSinE;
 e  = sqrt(e2);                                     // Eccentricity
 double E  = atan2(eSinE,eCosE);                           // Eccentric anomaly  
 
 M  = fmod(E-eSinE,Const::pi2);                             // Mean anomaly
 
 double nu = atan2(sqrt(1.0-e2)*eSinE, eCosE-e2);          // True anomaly
 
 omega = fmod(u-nu,Const::pi2);                             // Arg. of perihelion
 
 }
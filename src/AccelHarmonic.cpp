#include "../include/AccelHarmonic.h"
#include "../include/const.h"

Matrix static accelHarmonic( Matrix r, Matrix E, int n_max, int m_max){

Matrix Cnm = reinterpret_cast<const Matrix &>(Global::Cnm);
Matrix Snm = reinterpret_cast<const Matrix &>(Global::Snm);

double r_ref = 6378.1363e3;   // Earth's radius [m]; GGM03S
double gm    = 398600.4415e9; // [m^3/s^2]; GGM03S

// Body-fixed position 
Matrix r_bf = E * r;

// Auxiliary quantities
double d = r_bf.norm();                     // distance
double latgc = asin(r_bf(3)/d);
double lon = atan2(r_bf(2),r_bf(1));

Matrix pnm = Matrix(n_max+1,m_max+1);
Matrix dpnm = Matrix(n_max+1,m_max+1);

Legendre::legendre( n_max, m_max, latgc, pnm, dpnm);

double dUdr = 0.0;
double dUdlatgc = 0.0;
double dUdlon = 0.0;
double q3 = 0.0; 
double q2 = q3; 
double q1 = q2;
for (int n = 0; n<=n_max;n++){
    double b1 = (-gm/pow(d,2))*pow((r_ref/d),n)*(n+1);
    double b2 =  (gm/d)*pow((r_ref/d),n);
    double b3 =  (gm/d)*pow((r_ref/d),n);
    for (int m = 0; m<=m_max;m++){
        q1 = q1 + pnm(n+1,m+1)*(Cnm(n+1,m+1)*cos(m*lon)+Snm(n+1,m+1)*sin(m*lon));
        q2 = q2 + dpnm(n+1,m+1)*(Cnm(n+1,m+1)*cos(m*lon)+Snm(n+1,m+1)*sin(m*lon));
        q3 = q3 + m*pnm(n+1,m+1)*(Snm(n+1,m+1)*cos(m*lon)-Cnm(n+1,m+1)*sin(m*lon));
    }
    dUdr     = dUdr     + q1*b1;
    dUdlatgc = dUdlatgc + q2*b2;
    dUdlon   = dUdlon   + q3*b3;
    q3 = 0; q2 = q3; q1 = q2;
}

// Body-fixed acceleration
double r2xy = pow(r_bf(1),2)+pow(r_bf(2),2);

double ax = (1/d*dUdr-r_bf(3)/(pow(d,2)*sqrt(r2xy))*dUdlatgc)*r_bf(1)-(1/r2xy*dUdlon)*r_bf(2);
double ay = (1/d*dUdr-r_bf(3)/(pow(d,2)*sqrt(r2xy))*dUdlatgc)*r_bf(2)+(1/r2xy*dUdlon)*r_bf(1);
double az =  1/d*dUdr*r_bf(3)+sqrt(r2xy)/pow(d,2)*dUdlatgc;

double arr[] = {ax, ay, az};

Matrix a_bf = Matrix(3, arr, 3) ;

// Inertial acceleration 
return (E.transpose()*a_bf);

}
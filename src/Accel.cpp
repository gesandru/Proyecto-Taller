#include "../include/Accel.h"
#include "../include/const.h"
#include "../include/globals.h"

Matrix static accel(double x, Matrix& Y){

    //no estoy seguro si es (3) o (3, 3)
//Matrix a = Matrix(3, 3);

Matrix P, N, T, E;
//cambiar estos por los parámetros de las funciones
[x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC] = 
IERS(eopdata,Const.AuxParam.Mjd_UTC + x/86400,'l');
[UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC] = timediff(UT1_UTC,TAI_UTC);
Mjd_UT1 = Const.AuxParam.Mjd_UTC + x/86400.0 + UT1_UTC/86400.0;
Mjd_TT = Const.AuxParam.Mjd_UTC + x/86400.0 + TT_UTC/86400.0;

P = PrecMatrix(Const.MJD_J2000,Mjd_TT);
N = NutMatrix(Mjd_TT);
T = N * P;
E = PoleMatrix(x_pole,y_pole) * GHAMatrix(Mjd_UT1) * T;

double MJD_TDB = Mjday_TDB(Mjd_TT);
//Aquí también
[r_Mercury,r_Venus,r_Earth,r_Mars,r_Jupiter,r_Saturn,r_Uranus, 
 r_Neptune,r_Pluto,r_Moon,r_Sun] = JPL_Eph_DE430(MJD_TDB);

double[3] Y1 = {Y(1), Y(2), Y(3)};
Matrix y1 = new Matrix(3, Y1, 3);
double[3] Y2 = {Y(4), Y(5), Y(6)};
Matrix y1 = new Matrix(3, Y2, 3);

//Acceleration due to harmonic gravity field
Matrix a = AccelHarmonic(y1, E, Const.AuxParam.n, Const.AuxParam.m);

//Luni-solar perturbations
if (Const.AuxParam.sun){
    a = a + AccelPointMass(y1,r_Sun,Const.GM_Sun);
}

if (Const.AuxParam.moon){
    a = a + AccelPointMass(y1,r_Moon,Const.GM_Moon);
}

//Planetary perturbations
if (Const.AuxParam.planets){
    a = a + AccelPointMass(y1,r_Mercury,Const.GM_Mercury);
    a = a + AccelPointMass(y1,r_Venus,Const.GM_Venus);
    a = a + AccelPointMass(y1,r_Mars,Const.GM_Mars);
    a = a + AccelPointMass(y1,r_Jupiter,Const.GM_Jupiter);
    a = a + AccelPointMass(y1,r_Saturn,Const.GM_Saturn);
    a = a + AccelPointMass(y1,r_Uranus,Const.GM_Uranus);    
    a = a + AccelPointMass(y1,r_Neptune,Const.GM_Neptune);
    a = a + AccelPointMass(y1,r_Pluto,Const.GM_Pluto);
}

dY = [y2;a];

}
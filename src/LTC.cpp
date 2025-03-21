#include "../include/LTC.h"

Matrix static ltc(double lon,double lat){

Matrix M = Ry::R_y(-1.0*lat)*Rz::R_z(lon);
double Aux;

for (int j = 1; j<=3;j++){
    Aux=M(1,j); 
    M(1,j)=M(2,j); 
    M(2,j)=M(3,j); 
    M(3,j)= Aux;
}

}

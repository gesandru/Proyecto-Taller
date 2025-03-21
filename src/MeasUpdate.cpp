#include "../include/MeasUpdate.h"

//No cuadra s con la llamada desde EKF_GEOS3
void static measUpdate( Matrix& x, double z, double g, double s, Matrix G, Matrix& P, double n, Matrix& K){

double Inv_W = s*s;

Matrix support = G*P*G.transpose();

//Kalman gain
K = P*G.transpose()*(1/(Inv_W+support(1,1)));

//State update
x = x + K*(z-g);

//Covariance update
P = (Matrix::eye(n)-K*G)*P;
}
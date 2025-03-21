#include "../include/G_AccelHarmonic.h"

Matrix static g_AccelHarmonic(Matrix r, Matrix U, double  n_max, double m_max ){

double d = 1.0;   // Position increment [m]

Matrix G = Matrix(3, 3);
Matrix dr = Matrix(3);

// Gradient
for (int i = 1; i<=3;i++){
    // Set offset in i-th component of the position vector
    for (int j = 1; j<=3;j++){
        dr(j) = 0.0;
    }
    dr(i) = d;
    // Acceleration difference
    Matrix da = AccelHarmonic::accelHarmonic( r+dr/2,U, n_max, m_max ) -
         AccelHarmonic::accelHarmonic( r-dr/2,U, n_max, m_max );
    // Derivative with respect to i-th axis
    for (int k = 1; k<=3;k++){
        G(k,i) = da(k)/d;
    }

    return G;
}
}
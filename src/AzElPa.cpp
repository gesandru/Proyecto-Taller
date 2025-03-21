#include "../include/AzElPa.h"
#include "../include/const.h"

void static  azElPa(Matrix& s, double& Az, double& El, Matrix& dAds, Matrix& dEds){



double rho = sqrt(s(1)*s(1)+s(2)*s(2));

//Angles
Az = atan2(s(1),s(2));

if (Az<0.0){
    Az = Az+Const::pi2;
}

El = atan ( s(3) / rho );

// Partials
double arr1[] = { s(2)/(rho*rho), -s(1)/(rho*rho), 0.0 };
dAds = Matrix(3, arr1, 3);
double arr2[] = { -s(1)*s(3)/rho, -s(2)*s(3)/rho , rho };
dEds = Matrix(3, arr2, 3);
dEds = dEds/(s.dot(s));
}
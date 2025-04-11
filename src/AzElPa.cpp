#include "../include/AzElPa.h"
#include "../include/const.h"

static tuple<double, double, Matrix, Matrix> azElPa(Matrix& s){



double rho = sqrt(s(1)*s(1)+s(2)*s(2));

//Angles
double Az = atan2(s(1),s(2));

if (Az<0.0){
    Az = Az+Const::pi2;
}

double El = atan ( s(3) / rho );

// Partials
double arr1[] = { s(2)/(rho*rho), -s(1)/(rho*rho), 0.0 };
Matrix dAds = Matrix(3, arr1, 3);
double arr2[] = { -s(1)*s(3)/rho, -s(2)*s(3)/rho , rho };
Matrix dEds = Matrix(3, arr2, 3);
dEds = dEds/(s.dot(s));

return new Tuple<double, double, Matrix, Matrix>(Az, El, dAds, dEds);
}
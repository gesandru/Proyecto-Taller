#include <cstdio>
#include "../include/Cheb3D.h"

Matrix static cheb3D(double t,int N,double Ta,double Tb,const Matrix& Cx,const Matrix& Cy,Matrix& Cz){

//Check validity
if ( (t<Ta) || (Tb<t) ){
    printf("ERROR: Time out of range in Cheb3D::Value\n");
    exit(EXIT_FAILURE);
}

//Clenshaw algorithm
double tau = (2*t-Ta-Tb)/(Tb-Ta);  

Matrix f1 = Matrix(1,3);
Matrix f2 = Matrix(1,3);

Matrix m1 = Matrix(1,3);

for (int i = N; i>=2;i--){
    Matrix old_f1 = f1;
    m1 = Matrix(1, 3, new double[] {Cx(i),Cy(i),Cz(i)}, 3);
    f1 = f1*(2*tau)-f2+m1;
    f2 = old_f1;
}
    m1 = Matrix(1, 3, new double[] {Cx(1),Cy(1),Cz(1)}, 3);

return (f1*tau-f2+m1);

}
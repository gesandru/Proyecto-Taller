#include "../include/angl.h"

double static angl (Matrix& vec1, Matrix& vec2){

double small     = 0.00000001;
double undefined = 999999.1;

double magv1 = vec1.norm();
double magv2 = vec2.norm();

double temp;
double theta;
double signo = 0.0;

if (magv1*magv2 > pow(small,2)){
    temp= vec1.dot(vec2) / (magv1*magv2);
    if (std::abs( temp ) > 1.0){
        if(temp>0.0){
            signo = 1.0;
        } else if(temp==0.0){
            signo = 0.0;
        } else if(temp<0.0){
            signo = -1.0;
        }
        temp= signo * 1.0;
    }
    theta= acos( temp );
}else{
    theta= undefined;
}
return theta;
}
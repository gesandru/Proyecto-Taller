#include "../include/PoleMatrix.h"

Matrix static poleMatrix (double xp,double yp){
 
return (Ry::R_y(-xp) * Rx::R_x(-yp));
}
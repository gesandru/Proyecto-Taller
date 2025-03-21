#include "../include/GHAMatrix.h"

Matrix ghaMatrix (double Mjd_UT1){

return (Rz::R_z( Gast::gast(Mjd_UT1) ));

}
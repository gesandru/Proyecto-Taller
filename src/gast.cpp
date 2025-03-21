#include "../include/gast.h"

double static gast (double Mjd_UT1){

return (fmod ( Gmst::gmst(Mjd_UT1) + EqnEquinox::eqnEquinox(Mjd_UT1), Const::pi2 ));

}
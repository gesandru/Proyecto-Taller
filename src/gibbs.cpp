#include "../include/gibbs.h"

void static gibbs( Matrix r1, Matrix r2, Matrix r3, Matrix& v2, double& theta,
            double& theta1, double& copa, std::string& error){

double small= 0.00000001;
theta= 0.0;
error = "          ok";
theta1= 0.0;

double magr1 = r1.norm();
double magr2 = r2.norm();
double magr3 = r3.norm();
for (int i = 1; i<=3;i++){
    v2(i)= 0.0;
}

Matrix p = r2*r3;
Matrix q = r3*r1;
Matrix w = r1*r2;
Matrix pn = Unit::unit( p );
Matrix r1n = Unit::unit( r1 );
copa=  asin( pn.dot( r1n ) );

if ( abs( r1n.dot(pn) ) > 0.017452406 ){
    error= "not coplanar";
}

Matrix d = p + q + w;
double magd = d.norm();
Matrix n = p*magr1 + q*magr2 + w*magr3;
double magn = n.norm();
Matrix nn = Unit::unit( n );
Matrix dn = Unit::unit( d );

// -------------------------------------------------------------
// determine if  the orbit is possible. both d and n must be in
// the same direction, and non-zero.
// -------------------------------------------------------------
if ( ( abs(magd)<small ) || ( abs(magn)<small ) || ( nn.dot(dn) < small ) ){
    error= "  impossible";
}else{
      theta  = Angl::angl( r1,r2 );
      theta1 = Angl::angl( r2,r3 );

      // ----------- perform gibbs method to find v2 -----------
      double r1mr2= magr1-magr2;
      double r3mr1= magr3-magr1;
      double r2mr3= magr2-magr3;
      Matrix s  = r3*r1mr2 + r2*r3mr1 + r1*r2mr3;
      Matrix b  = d*r2;
      double l  = sqrt(Const::GM_Earth / (magd*magn) );
      double tover2= l / magr2;
      v2 =  b*tover2 + s*l;
}

}
#include "../include/IERS.h"

void static iers(Matrix eop, double Mjd_UTC,char interp, double &x_pole, double &y_pole, double &UT1_UTC,
                 double &LOD, double &dpsi, double &deps, double &dx_pole, double &dy_pole, double &TAI_UTC){


    double mjd = (floor(Mjd_UTC));
    int j=1;
    bool found = false;
    double i;
    while(j<=eop.getCol() && !found){
        if(eop(4,j)==mjd){
            i=j;
            found = true;
        }
        j++;
    }

if (interp =='l'){
    // linear interpolation

    Matrix preeop = Matrix(13, new double[] {eop(1,i), eop(2,i), eop(3, i), eop(4,i),eop(5,i), 
                                             eop(6,i), eop(7,i), eop(8,i), eop(9,i), eop(10,i), 
                                             eop(11,i), eop(12,i), eop(13,i)}, 13);
    Matrix nexteop = Matrix(13, new double[] {eop(1,i+1), eop(2,i+1), eop(3, i+1), eop(4,i+1),eop(5,i+1),
                                       eop(6,i+1), eop(7,i+1), eop(8,i+1), eop(9,i+1), eop(10,i+1),
                                       eop(11,i+1), eop(12,i+1), eop(13,i+1)}, 13);
    double mfme = 1440.0*(Mjd_UTC-floor(Mjd_UTC));
    double fixf = mfme/1440.0;
    // Setting of IERS Earth rotation parameters
    // (UT1-UTC [s], TAI-UTC [s], x ["], y ["])
    x_pole  = preeop(5)+(nexteop(5)-preeop(5))*fixf;
    y_pole  = preeop(6)+(nexteop(6)-preeop(6))*fixf;
	UT1_UTC = preeop(7)+(nexteop(7)-preeop(7))*fixf;
    LOD     = preeop(8)+(nexteop(8)-preeop(8))*fixf;
    dpsi    = preeop(9)+(nexteop(9)-preeop(9))*fixf;
    deps    = preeop(10)+(nexteop(10)-preeop(10))*fixf;
    dx_pole = preeop(11)+(nexteop(11)-preeop(11))*fixf;
    dy_pole = preeop(12)+(nexteop(12)-preeop(12))*fixf;
    TAI_UTC = preeop(13);
	
    x_pole  = x_pole/Const::Arcs;  // Pole coordinate [rad]
    y_pole  = y_pole/Const::Arcs;  // Pole coordinate [rad]
    dpsi    = dpsi/Const::Arcs;
    deps    = deps/Const::Arcs;
    dx_pole = dx_pole/Const::Arcs; // Pole coordinate [rad]
    dy_pole = dy_pole/Const::Arcs; // Pole coordinate [rad]
}else if (interp =='n'){
    Matrix eop = Matrix(13, new double[] {eop(1,i), eop(2,i), eop(3, i), eop(4,i),eop(5,i),
                                   eop(6,i), eop(7,i), eop(8,i), eop(9,i), eop(10,i),
                                   eop(11,i), eop(12,i), eop(13,i)}, 13);
    // Setting of IERS Earth rotation parameters
    // (UT1-UTC [s], TAI-UTC [s], x ["], y ["])
    x_pole  = eop(5)/Const::Arcs;  // Pole coordinate [rad]
    y_pole  = eop(6)/Const::Arcs;  // Pole coordinate [rad]
	UT1_UTC = eop(7);             // UT1-UTC time difference [s]
    LOD     = eop(8);             // Length of day [s]
    dpsi    = eop(9)/Const::Arcs;
    deps    = eop(10)/Const::Arcs;
    dx_pole = eop(11)/Const::Arcs; // Pole coordinate [rad]
    dy_pole = eop(12)/Const::Arcs; // Pole coordinate [rad]
	TAI_UTC = eop(13);            // TAI-UTC time difference [s]
}

}

void static iers(Matrix eop, double Mjd_UTC, double &x_pole, double &y_pole, double &UT1_UTC,
                 double &LOD, double &dpsi, double &deps, double &dx_pole, double &dy_pole, double &TAI_UTC){

    char interp = 'n';

    double mjd = (floor(Mjd_UTC));
    int j=1;
    bool found = false;
    double i;
    while(j<=eop.getCol() && !found){
        if(eop(4,j)==mjd){
            i=j;
            found = true;
        }
        j++;
    }

    if (interp =='l'){
        // linear interpolation

        Matrix preeop = Matrix(13, new double[] {eop(1,i), eop(2,i), eop(3, i), eop(4,i),eop(5,i),
                                                 eop(6,i), eop(7,i), eop(8,i), eop(9,i), eop(10,i),
                                                 eop(11,i), eop(12,i), eop(13,i)}, 13);
        Matrix nexteop = Matrix(13, new double[] {eop(1,i+1), eop(2,i+1), eop(3, i+1), eop(4,i+1),eop(5,i+1),
                                                  eop(6,i+1), eop(7,i+1), eop(8,i+1), eop(9,i+1), eop(10,i+1),
                                                  eop(11,i+1), eop(12,i+1), eop(13,i+1)}, 13);
        double mfme = 1440.0*(Mjd_UTC-floor(Mjd_UTC));
        double fixf = mfme/1440.0;
        // Setting of IERS Earth rotation parameters
        // (UT1-UTC [s], TAI-UTC [s], x ["], y ["])
        x_pole  = preeop(5)+(nexteop(5)-preeop(5))*fixf;
        y_pole  = preeop(6)+(nexteop(6)-preeop(6))*fixf;
        UT1_UTC = preeop(7)+(nexteop(7)-preeop(7))*fixf;
        LOD     = preeop(8)+(nexteop(8)-preeop(8))*fixf;
        dpsi    = preeop(9)+(nexteop(9)-preeop(9))*fixf;
        deps    = preeop(10)+(nexteop(10)-preeop(10))*fixf;
        dx_pole = preeop(11)+(nexteop(11)-preeop(11))*fixf;
        dy_pole = preeop(12)+(nexteop(12)-preeop(12))*fixf;
        TAI_UTC = preeop(13);

        x_pole  = x_pole/Const::Arcs;  // Pole coordinate [rad]
        y_pole  = y_pole/Const::Arcs;  // Pole coordinate [rad]
        dpsi    = dpsi/Const::Arcs;
        deps    = deps/Const::Arcs;
        dx_pole = dx_pole/Const::Arcs; // Pole coordinate [rad]
        dy_pole = dy_pole/Const::Arcs; // Pole coordinate [rad]
    }else if (interp =='n'){
        Matrix eop = Matrix(13, new double[] {eop(1,i), eop(2,i), eop(3, i), eop(4,i),eop(5,i),
                                              eop(6,i), eop(7,i), eop(8,i), eop(9,i), eop(10,i),
                                              eop(11,i), eop(12,i), eop(13,i)}, 13);
        // Setting of IERS Earth rotation parameters
        // (UT1-UTC [s], TAI-UTC [s], x ["], y ["])
        x_pole  = eop(5)/Const::Arcs;  // Pole coordinate [rad]
        y_pole  = eop(6)/Const::Arcs;  // Pole coordinate [rad]
        UT1_UTC = eop(7);             // UT1-UTC time difference [s]
        LOD     = eop(8);             // Length of day [s]
        dpsi    = eop(9)/Const::Arcs;
        deps    = eop(10)/Const::Arcs;
        dx_pole = eop(11)/Const::Arcs; // Pole coordinate [rad]
        dy_pole = eop(12)/Const::Arcs; // Pole coordinate [rad]
        TAI_UTC = eop(13);            // TAI-UTC time difference [s]
    }

}
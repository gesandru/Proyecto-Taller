#ifndef _GLOBALS_
#define _GLOBALS_

#include "../include/Matrix.h"
#include "../include/const.h"
#include "../include/Mjday.h"

//lo mismo haremos con GEOS3 y con GGMO3S

typedef struct{
    double Mjd_UTC, Mjd_TT;
    int n, m, sun, moon, planets;
} Param;

class Global{
    public:
    static int n_eqn;
    static Param *AuxParam;
    static Matrix *eopdata;
    static Matrix *obs;
    static Matrix *GGMO3Sdata;
    static Matrix *Cnm;
    static Matrix *Snm;
    static Matrix *PC;

    static void eop19620101(int c);
    static void GEOS3();
    static void GGMO3S();
    static Param* getParam();
};

#endif
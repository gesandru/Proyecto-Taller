
#include <cstdio>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <cstring>
#include "../include/globals.h"

using namespace std;

    Matrix *Global::eopdata;

    void Global::eop19620101(int c){
        Global::eopdata = new Matrix(13, c);

        FILE* fid = fopen("../data/eop19620101.txt","r");
        if(fid==nullptr){
            printf("Error al abrir el archivo");
            exit(EXIT_FAILURE);
        }

for(int i=1; i<=c; i++){
fscanf(fid,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
&((*Global::eopdata)(1,i)),
&((*Global::eopdata)(2,i)),
&((*Global::eopdata)(3,i)),
&((*Global::eopdata)(4,i)),
&((*Global::eopdata)(5,i)),
&((*Global::eopdata)(6,i)),
&((*Global::eopdata)(7,i)),
&((*Global::eopdata)(8,i)),
&((*Global::eopdata)(9,i)),
&((*Global::eopdata)(10,i)),
&((*Global::eopdata)(11,i)),
&((*Global::eopdata)(12,i)),
&((*Global::eopdata)(13,i)));
}

fclose(fid);
    }

Matrix *Global::obs;

void Global::GEOS3(){
    Global::obs = new Matrix(46, 4);

    FILE* fid = fopen("../data/GEOS3.txt","r");
    if(fid==nullptr){
        printf("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    char* auxi;
    const char *tline;
    double Y, M, D, h, m, s, az, el, Dist;

    for (int i=0; i<=45; i++){
            fgets (auxi, 100 , fid);
        //no entiendo porqué esto no se castea a const char* aquí
            tline = reinterpret_cast<const char *>(auxi);
            Y = atof(reinterpret_cast<const char *>(tline[0, 1, 2, 3]));
            M = atof(reinterpret_cast<const char *>(tline[5, 6]));
            D = atof(reinterpret_cast<const char *>(tline[8, 9]));
            h = atof(reinterpret_cast<const char *>(tline[12, 13]));
            m = atof(reinterpret_cast<const char *>(tline[15, 16]));
            s = atof(reinterpret_cast<const char *>(tline[18, 19, 20, 21, 22, 23]));
            az = atof(reinterpret_cast<const char *>(tline[25, 26, 27, 28, 29, 30, 31, 32]));
            el = atof(reinterpret_cast<const char *>(tline[35, 36, 37, 38, 39, 40, 41]));
            Dist = atof(reinterpret_cast<const char *>(tline[44, 45, 46, 47, 48, 49, 50, 51, 52, 53]));
            Global::obs[i, 0] = Mjday::mjday(Y, M, D, h, m, s);
            Global::obs[i, 1] = Const::Rad*az;
            Global::obs[i, 2] = Const::Rad*el;
        Global::obs[i, 3] = 1e3*Dist;
    }

    fclose(fid);
}

Matrix *Global::Cnm;
Matrix *Global::Snm;

void Global::GGMO3S(){
    Global::Cnm = new Matrix(181, 181);
    Global::Snm = new Matrix(181,181);

    FILE* fid = fopen("../data/GGMO3S.txt","r");
    if(fid==nullptr){
        printf("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    double *auxi;

    for(int n=1; n<=180; n++){
        for (int m=0; m<=n; m++){
                fscanf(fid, "%lf %lf %lf %lf %lf %lf",auxi);
                Global::Cnm[n, m] = auxi[2];
                Global::Snm[n, m] = auxi[3];
        }
    }

    fclose(fid);

}

/*
void Global::GGMO3S(int c){
    Global::GGMO3Sdata = new Matrix(6, c);

    FILE* fid = fopen("../data/GGMO3S.txt","r");
    if(fid==nullptr){
        printf("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    for(int i=1; i<=c; i++){
        fscanf(fid,"%lf %lf %lf %lf %lf %lf",
               &((*Global::GGMO3Sdata)(1,i)),
               &((*Global::GGMO3Sdata)(2,i)),
               &((*Global::GGMO3Sdata)(3,i)),
               &((*Global::GGMO3Sdata)(4,i)),
               &((*Global::GGMO3Sdata)(5,i)),
               &((*Global::GGMO3Sdata)(6,i)));
    }

    fclose(fid);

}
 */

Param* Global::getParam(){
    return new Param();
}

Matrix *Global::PC;
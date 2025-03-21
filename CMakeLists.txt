cmake_minimum_required(VERSION 3.20)
project(ProyectoTaller)

set(CMAKE_CXX_STANDARD 14)

add_executable(ProyectoTaller main.cpp test.cpp test.h include/const.h include/globals.h src/globals.cpp
        include/AccelHarmonic.h src/AccelHarmonic.cpp include/AccelPointMass.h src/AccelPointMass.cpp
        include/Matrix.h src/Matrix.cpp include/angl.h src/angl.cpp include/AzElPa.h src/AzElPa.cpp
        include/Cheb3D.h src/Cheb3D.cpp include/EccAnom.h src/EccAnom.cpp include/elements.h src/elements.cpp
        include/EqnEquinox.h src/EqnEquinox.cpp include/NutAngles.h src/NutAngles.cpp
        include/MeanObliquity.h src/MeanObliquity.cpp include/Frac.h src/Frac.cpp
        include/G_AccelHarmonic.h src/G_AccelHarmonic.cpp include/gast.h src/gast.cpp include/gmst.h src/gmst.cpp
        include/Geodetic.h src/Geodetic.cpp include/GHAMatrix.h src/GHAMatrix.cpp include/R_z.h src/R_z.cpp
        include/gibbs.h src/gibbs.cpp include/unit.h src/unit.cpp include/hgibbs.h src/hgibbs.cpp
        include/Legendre.h src/Legendre.cpp include/LTC.h src/LTC.cpp include/R_y.h src/R_y.cpp
        include/MeasUpdate.h src/MeasUpdate.cpp include/Mjday.h src/Mjday.cpp include/Mjday_TDB.h src/Mjday_TDB.cpp
        include/NutMatrix.h src/NutMatrix.cpp include/R_x.h src/R_x.cpp include/PoleMatrix.h src/PoleMatrix.cpp
        include/Position.h src/Position.cpp include/PrecMatrix.h src/PrecMatrix.cpp include/sign_.h src/sign_.cpp
        include/timediff.h src/timediff.cpp include/TimeUpdate.h src/TimeUpdate.cpp include/DEInteg.h src/DEInteg.cpp
        include/EKF_GEOS3.h src/EKF_GEOS3.cpp include/IERS.h src/IERS.cpp src/main.cpp)

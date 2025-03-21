#include "../include/EKF_GEOS3.h"

void static ekf_geos() {

    Global::GEOS3();
    Global::GGMO3S();
    Global::eop19620101(21413);

    int nobs = 46;

    Matrix obs = reinterpret_cast<const Matrix &>(Global::obs);

    double sigma_range = 92.5;          // [m]
    double sigma_az = 0.0224 * Const::Rad; // [rad]
    double sigma_el = 0.0139 * Const::Rad; // [rad]

// Kaena Point station
    double lat = Const::Rad * 21.5748;     // [rad]
    double lon = Const::Rad * (-158.2706); // [rad]
    double alt = 300.20;                // [m]

    Matrix Rs = Position::position(lon, lat, alt).transpose();

    double Mjd1 = obs(1, 1);
    double Mjd2 = obs(9, 1);
    double Mjd3 = obs(18, 1);
/*
    [r2, v2] = anglesg(obs(1, 2), obs(9, 2), obs(18, 2), obs(1, 3), obs(9, 3), obs(18, 3), ...
    Mjd1, Mjd2, Mjd3, Rs, Rs, Rs);
    */

// [r2,v2] = anglesdr(obs(1,2),obs(9,2),obs(18,2),obs(1,3),obs(9,3),obs(18,3),...
//                    Mjd1,Mjd2,Mjd3,Rs,Rs,Rs);

    Matrix Y0_apr = Matrix(6, new double[]{6221397.62857869, 2867713.77965738, 3006155.98509949,
                                           4645.04725161806, -2752.21591588204, -7507.99940987031},
                           6);                           //[r2;v2];

    double Mjd0 = Mjday::mjday(1995, 1, 29, 02, 38, 0);

    double Mjd_UTC = obs(9, 1);

    Global::AuxParam->Mjd_UTC = Mjd_UTC;
    Global::AuxParam->n = 20;
    Global::AuxParam->m = 20;
    Global::AuxParam->sun = 1;
    Global::AuxParam->moon = 1;
    Global::AuxParam->planets = 1;

    Global::n_eqn = 6;


    Matrix Y = Matrix(6, new double[]{5542555.93722861, 3213514.86734920, 3990892.97587685,
                                      5394.06842166351, -2365.21337882342, -7061.84554200295}, 6);
    //DEInteg(@Accel, 0, -(obs(9, 1) - Mjd0) * 86400.0, 1e-13, 1e-6, 6, Y0_apr);

    Matrix P = Matrix(6, 6);

    for (int i = 1; i <= 3; i++) {
    P(i, i) = 1e8;
    }
    for(int i = 4; i<=6; i++) {
        P(i, i) = 1e3;
    }

    Matrix LT = LTC::ltc(lon, lat);

    Matrix yPhi = Matrix(42, 1);
    Matrix Phi = Matrix(6, 6);

// Measurement loop
    int t = 0;

    for(int i = 1; i<=nobs; i++) {
// Previous step
        int t_old = t;
        Matrix Y_old = Y;

// Time increment and propagation
        Mjd_UTC = obs(i, 1);                       // Modified Julian Date
        t = (Mjd_UTC - Mjd0) * 86400.0;         // Time since epoch [s]

        double x_pole = 0, y_pole = 0, UT1_UTC = 0, LOD = 0, dpsi = 0, deps = 0, dx_pole = 0,
                dy_pole = 0, TAI_UTC = 0, UT1_TAI = 0, UTC_GPS = 0, UT1_GPS = 0, TT_UTC = 0, GPS_UTC = 0;

        IERS::iers(*Global::eopdata, Mjd_UTC, 'l', x_pole, y_pole, UT1_UTC, LOD, dpsi,
                   deps, dx_pole, dy_pole, TAI_UTC);
        Timediff::timediff(UT1_UTC, TAI_UTC, UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC);
        double Mjd_TT = Mjd_UTC + TT_UTC / 86400.0;
        double Mjd_UT1 = Mjd_TT + (UT1_UTC - TT_UTC) / 86400.0;
        Global::AuxParam->Mjd_UTC = Mjd_UTC;
        Global::AuxParam->Mjd_TT = Mjd_TT;

        for (int ii = 1; ii <= 6; ii++) {
            yPhi(ii) = Y_old(ii);
            for (int j = 1; j <= 6; j++) {
                if (ii == j) {
                    yPhi(6 * j + ii) = 1;
                } else {
                    yPhi(6 * j + ii) = 0;
                }
            }
        }
        Matrix yPhy = Matrix(42, new double[]{5738566.57839022, 3123975.34079016, 3727114.48185792,
                                              5199.63333072017, -2474.43881538621, -7195.16750655247, 1.00041922218421,
                                              0.000599205935296332,
                                              0.000737334362715857, 2.34511597726076e-05, 3.25240005703786e-05,
                                              3.97546996084771e-05,
                                              0.000599210758004640, 0.999703770692448, 0.000418687815016773,
                                              3.25246538129495e-05,
                                              -1.61854966570168e-05, 2.23405999021430e-05, 0.000737344013183382,
                                              0.000418689926977497,
                                              0.999877413280203, 3.97560066226160e-05, 2.23408858666587e-05,
                                              -7.22167524905088e-06,
                                              37.0053480735676, 0.00742079763261262, 0.00907126696766097,
                                              1.00044810751589, 0.000604061271798779,
                                              0.000733447715473557, 0.00742082743734526, 36.9963058593911,
                                              0.00509711969510428, 0.000604066116977851,
                                              0.999697158528768, 0.000407829918517552, 0.00907132660578788,
                                              0.00509713274145821, 36.9983505101633,
                                              0.000733457411225203, 0.000407832040276950, 0.999855141838681}, 42);
        //yPhi = DEInteg(@VarEqn, 0, t - t_old, 1e-13, 1e-6, 42, yPhi);

// Extract state transition matrices
        for (int j = 1; j <= 6; j++) {
        Phi(1,j) = yPhi(6 * j + 1);
        Phi(2,j) = yPhi(6 * j + 2);
        Phi(3,j) = yPhi(6 * j + 3);
        Phi(4,j) = yPhi(6 * j + 4);
        Phi(5,j) = yPhi(6 * j + 5);
        Phi(6,j) = yPhi(6 * j + 6);
        }

        Matrix Y = Matrix(6, new double[]{5738566.57769180, 3123975.34092958, 3727114.48156063,
                                          5199.63329181125, -2474.43881044665, -7195.16752553892}, 6);
        //Y = DEInteg(@Accel, 0, t - t_old, 1e-13, 1e-6, 6, Y_old);

// Topocentric coordinates
        double theta = Gmst::gmst(Mjd_UT1);                    // Earth rotation
        Matrix U = Rz::R_z(theta);
        Matrix r = Matrix(3, new double[]{5738566.57769180, 3123975.34092958, 3727114.48156063}, 3);
        Matrix s = LT * (U * r - Rs);                          // Topocentric position [m]

// Time update
        TimeUpdate::timeUpdate(P, Phi);

// Azimuth and partials

        double Azim = 0, Elev = 0;
        Matrix dAds = Matrix(3);
        Matrix dEds = Matrix(3);
        Matrix dAdY = Matrix(6);

        AzElPa::azElPa(s, Azim, Elev, dAds, dEds); // Azimuth, Elevation
        dAdY = Matrix(1, 6, new double[]{9.59123748602946e-08, 2.16050345227544e-07, -3.27382770920699e-07,
                                         0, 0, 0}, 6);
        //dAdY = [dAds * LT * U, zeros(1, 3)];


        // Measurement update

        Matrix K = Matrix(6);

        MeasUpdate::measUpdate(Y, obs(i, 2), Azim, sigma_az, dAdY, P, 6, K);

// Elevation and partials
        r(1) = Y(1);
        r(2) = Y(2);
        r(3) = Y(3);
        s = LT * (U * r - Rs);                          // Topocentric position [m]
        AzElPa::azElPa(s, Azim, Elev, dAds, dEds); // Azimuth, Elevation
        Matrix dEdY = Matrix(1, 6, new double[]{3.75911994175456e-07, -3.52029176081630e-08, 8.64940776864810e-08,
                                                0, 0, 0}, 6);
        //dEdY = [dEds * LT * U, zeros(1, 3)];

// Measurement update
        MeasUpdate::measUpdate(Y, obs(i, 3), Elev, sigma_el, dEdY, P, 6, K);

// Range and partials
        r(1) = Y(1);
        r(2) = Y(2);
        r(3) = Y(3);
        s = LT * (U * r - Rs);                          // Topocentric position [m]
        double Dist = s.norm();
        Matrix dDds = (s / Dist).transpose();         // Range
        Matrix dDdY = Matrix(1, 6, new double[]{-0.0502491041382981, 0.838684104471026, 0.542295123010462,
                                                0, 0, 0}, 6);

// Measurement update
        MeasUpdate::measUpdate(Y, obs(i, 4), Dist, sigma_range, dDdY, P, 6, K);
    }

    double x_pole = 0, y_pole = 0, UT1_UTC = 0, LOD = 0, dpsi = 0, deps = 0, dx_pole = 0,
            dy_pole = 0, TAI_UTC = 0, UT1_TAI = 0, UTC_GPS = 0, UT1_GPS = 0, TT_UTC = 0, GPS_UTC = 0;

    IERS::iers(*Global::eopdata, obs(46, 1), 'l', x_pole, y_pole, UT1_UTC,
               LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC);
    Timediff::timediff(UT1_UTC, TAI_UTC, UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC);
    double Mjd_TT = Mjd_UTC + TT_UTC / 86400.0;
    Global::AuxParam->Mjd_UTC = Mjd_UTC;
    Global::AuxParam->Mjd_TT = Mjd_TT;

    Matrix Y0 = Matrix( 6, new double[]{5753212.04419213, 2673401.89427079, 3440289.36652239,
            4326.35119496467, -1926.72407270954, -5726.09595759172}, 6);
    //Y0 = DEInteg(@Accel, 0, -(obs(46, 1) - obs(1, 1)) * 86400.0, 1e-13, 1e-6, 6, Y);

    Matrix Y_true = Matrix( 6, new double[]{5753.173e3, 2673.361e3, 3440.304e3, 4.324207e3,
                                            -1.924299e3, -5.728216e3}, 6);

    printf("\nError of Position Estimation\n");
    printf("dX//10.1f [m]\n", Y0(1) - Y_true(1));
    printf("dY//10.1f [m]\n", Y0(2) - Y_true(2));
    printf("dZ//10.1f [m]\n", Y0(3) - Y_true(3));
    printf("\nError of Velocity Estimation\n");
    printf("dVx//8.1f [m/s]\n", Y0(4) - Y_true(4));
    printf("dVy//8.1f [m/s]\n", Y0(5) - Y_true(5));
    printf("dVz//8.1f [m/s]\n", Y0(6) - Y_true(6));

}
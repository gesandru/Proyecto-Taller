#include "../include/TimeUpdate.h"

void static timeUpdate(Matrix& P, Matrix Phi,double Qdt){



P = Phi*P*Phi.transpose() + Qdt;
}

void static TimeUpdate(Matrix& P, Matrix Phi){



P = Phi*P*Phi.transpose();
}
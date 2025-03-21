/*#include <iostream>
#include "include/EKF_GEOS3.h"

int main() {

    EKF_GEOS3::ekf_geos();

}

*/

#include "../include/Matrix.h"

int main(){
	Matrix M1(3,2);
	M1(1,1)=5.0;
	
	cout << M1 << endl;
	
	return 0;
}
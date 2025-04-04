#ifndef _MATRIX_
#define _MATRIX_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class Matrix
{
	private:
    void initMatrix();

 
    private:
        double **matrix;
	
    public:
	    int fil;
        int col;
        Matrix(const int fil, const int col);
        Matrix(int fil);
        Matrix(int fil, int col, double v[], int n);
        Matrix(int fil, double v[], int n);

        Matrix(const Matrix& m);
        ~Matrix();
 
        Matrix& operator=(const Matrix& matrix2);
        Matrix&  operator+(const Matrix& matrix2);
        Matrix  operator-(const Matrix& matrix2);
        Matrix  operator*(const Matrix& matrix2);
        Matrix  operator*(const double& d);
        Matrix  operator/(const Matrix& matrix2);
        Matrix  operator/(const double& d);
        double& operator()(const int i, const int j); //const;
        double& operator()(const int i); //const;
		friend ostream& operator << (ostream &o, Matrix&m);
 
        void print();

        double dot(Matrix m);
        double norm();
        Matrix& transpose();
        Matrix static eye(double size);
        int getFil();
        int getCol();
        double **getMatrix();

        Matrix inv(Matrix& M);
 


    double det(Matrix &M, int n);
    void getCfactor(Matrix& M, Matrix& t, int p, int q, int n);
    Matrix adj(Matrix &M);


};

#endif

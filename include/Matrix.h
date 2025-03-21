#ifndef _MATRIX_
#define _MATRIX_

class Matrix
{
    public:
        Matrix(int fil, int col);
        Matrix(int fil);
        Matrix(int fil, int col, double v[], int n);
        Matrix(int fil, double v[], int n);

        Matrix(const Matrix& m);
        ~Matrix();
 
        Matrix& operator=(const Matrix& matrix2);
        Matrix  operator+(const Matrix& matrix2);
        Matrix  operator-(const Matrix& matrix2);
        Matrix  operator*(const Matrix& matrix2);
        Matrix  operator*(const double& d);
        Matrix  operator/(const Matrix& matrix2);
        Matrix  operator/(const double& d);
        double& operator()(const int i, const int j) const;
        double& operator()(const int i) const;
 
        void print();

        double dot(Matrix m);
        double norm();
        Matrix& transpose();
        Matrix static eye(double size);
        int getFil();
        int getCol();
        double **getMatrix();

        Matrix INV(Matrix& M);
 
    private:
        void initMatrix();

 
    private:
        int fil;
        int col;
        double **matrix;

    double DET(Matrix &M, int n);
    void getCfactor(Matrix& M, Matrix& t, int p, int q, int n);
    Matrix ADJ(Matrix &M);


};

#endif

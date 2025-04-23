#include "../include/Matrix.h"

Matrix::Matrix(const int fil, const int col) : fil(fil), col(col)
{
    initMatrix();
}

Matrix::Matrix(int fil) : fil(fil), col(1)
{
    initMatrix();
}

Matrix Matrix::zeros(int n){
	
	Matrix m = Matrix(n, n);
	return m;
}
 
Matrix::Matrix(int fil, int col, double v[], int n): fil(fil), col(col)
{
    initMatrix();
 
    int k = 0;
    
    for (int i = 0; i < fil; i++)
        for (int j = 0; j < col; j++){
            if (k < n)
                data[i][j] = v[k++];
            else
                data[i][j] = 0;
        }
}

Matrix::Matrix(int fil, double v[], int n): fil(fil), col(1)
{
    initMatrix();
 
    int k = 0;
    
    for (int i = 0; i < fil; i++)
        for (int j = 0; j < 1; j++){
            if (k < n)
                data[i][j] = v[k++];
            else
                data[i][j] = 0;
        }
}
 
Matrix::Matrix(const Matrix& m)
{
    *this = m;
}
 
Matrix::~Matrix()
{
    for (int i = 0; i < fil; i++)
        delete[] data[i];
 
    delete[] data;
}
 
void Matrix::initMatrix()
{
	if(fil<=0 || col <=0){
		cout<<"Error de matriz\n";
		exit(EXIT_FAILURE);
	}
    data = (double**)malloc(fil*sizeof(double**)); //new double*[fil];
	
	if(data == NULL){
		cout<<"Error al crear la matriz initMatrix\n";
		exit(EXIT_FAILURE);
	}
	
    for (int i = 0; i < fil; i++)
        data[i] = (double*)malloc(col*sizeof(double*));//new double[col];
 
    for (int i = 0; i < fil; i++)
        for (int j = 0; j < col; j++)
            data[i][j] = 0.0;
}
 
Matrix& Matrix::operator=(const Matrix& matrix2)
{
    for (int i = 0; i < fil; i++)
        for (int j = 0; j < col; j++)
            this->data[i][j] = matrix2.data[i][j];
 
    return *this;
}
 
Matrix& Matrix::operator+(const Matrix& matrix2)
{
	
	if(this->fil!=matrix2.fil || this->col!=matrix2.col){
		cout<<"Error de matriz en operador +\n";
		exit(EXIT_FAILURE);
	}
	
    Matrix *result = new Matrix(this->fil, this->col);
    
    for (int i = 0; i < fil; i++)
        for (int j = 0; j < col; j++)
            result->data[i][j] = data[i][j] + matrix2.data[i][j];
 
    return *result;
}
 
Matrix Matrix::operator-(const Matrix& matrix2)
{
	if(this->fil!=matrix2.fil || this->col!=matrix2.col){
		cout<<"Error de matriz en operador -\n";
		exit(EXIT_FAILURE);
	}
	
    Matrix *result = new Matrix(this->fil, this->col);
    
    for (int i = 0; i < fil; i++)
        for (int j = 0; j < col; j++)
            result->data[i][j] = data[i][j] - matrix2.data[i][j];
 
    return *result;
}
 
Matrix Matrix::operator*(Matrix* matrix2)
{
    	if(this->fil!=matrix2->fil || this->col!=matrix2->col){
		cout<<"Error de matriz en operador * con otra matriz\n";
		exit(EXIT_FAILURE);
	}
	
    Matrix *result = new Matrix(this->fil, this->col);
 
    for (int i = 0; i < this->fil ; i++){
        for (int j = 0; j < matrix2->col; j++){
            result->data[i][j] = 0;
            for (int k = 0; k < this->col; k++){
                result->data[i][j] = result->data[i][j] + this->data[i][k] * matrix2->data[k][j];
            }
        }
    }
 
    return *result;
}

Matrix Matrix::operator*(const double& d)
{
    Matrix *result = new Matrix(this->fil, this->col);
 
    for (int i = 0; i < this->fil ; i++){
        for (int j = 0; j < this->col; j++){
            result->data[i][j] = 0;
            result->data[i][j] = this->data[i][j] * d;
        }
    }
 
    return *result;
}

//en nuestro código las matrices siempre van a ser cuadradas,
//se hace en Legendre
Matrix Matrix::operator/(Matrix* matrix2)
{
	if(this->fil!=matrix2->fil || this->col!=matrix2->col){
		cout<<"Error de matriz en operador /\n";
		exit(EXIT_FAILURE);
	}
	
    Matrix *result = new Matrix(this->fil, this->col);

    Matrix matrix3 = Matrix::inv(matrix2);
 
    for (int i = 0; i < this->fil ; i++){
        for (int j = 0; j < matrix2->col; j++){
            result->data[i][j] = 0;
            for (int k = 0; k < this->col; k++){
                result->data[i][j] = result->data[i][j] + this->data[i][k] * matrix2->data[k][j];
            }
        }
    }

    return *result;
}

Matrix Matrix::operator/(const double& d)
{
	if(d==0.0){
		cout<<"Error de matriz en operador / por dividir por 0\n";
		exit(EXIT_FAILURE);
	}
	
    Matrix *result = new Matrix(this->fil, this->col);
 
    for (int i = 0; i < this->fil ; i++){
        for (int j = 0; j < this->col; j++){
            result->data[i][j] = 0;
            result->data[i][j] = this->data[i][j] / d;
        }
    }
 
    return *result;
}
 
 
double& Matrix::operator()(const int i, const int j) const
{
	if(fil<=0 || col <=0 || i>fil || j>col){
		cout<<"Error de matriz operador ()\n";
		exit(EXIT_FAILURE);
	}
    return data[i-1][j-1];
}

double& Matrix::operator()(const int n) const
{
		if(n<=0 || n>fil*col){
		if(n<=0 || n>fil*col){
		cout<<"Error de matriz operador ()\n";
		exit(EXIT_FAILURE);
	}
	
    return data[(n-1)/this->col][(n-1)%this->col];
}
}


ostream& operator << (ostream &o, Matrix&m){
	for(int i = 0; i<m.fil; i++){
		for(int j=0;j<m.col; j++){
			printf("%5.20lf ", m(i,j));
		}
		o << "\n";
	}
	return o;
}

 
void Matrix::printer()
{
    for (int i = 0; i < fil; i++){
        for (int j = 0; j < col; j++){
            std::cout << std::fixed << std::setprecision(14) << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

double Matrix::dot(Matrix m) {
    double result = 0.0;

    for (int i = 0; i < this->fil ; i++){
        for (int j = 0; j < this->col; j++){
            result += (data[i][j] * m.data[i][j]);
        }
    }
    return result;
}

double Matrix::norm() {

	if(this->col>1){
		cout<<"Esto es la norma del vector, no puede haber más de una columna /\n";
		exit(EXIT_FAILURE);
	}

    double result = 0.0;

    for (int i = 0; i < this->fil ; i++){
		for(int j = 0; j < this->col ; j++){
			result += (data[i][j] * data[i][j]);
		}
    }
	result = sqrt(result)
    return result;
}

Matrix& Matrix::transpose(){
	
    Matrix *result = new Matrix(this->fil, this->col);
 
    
    for (int i = 0; i < this->getFil(); i++)
        for (int j = 0; j < this->getCol(); j++){
            result.data[i][j] = this->data[j][i];
            
        }
    return *result;
}

Matrix static eye(double size)
{
    int s = nearbyint(size);
    Matrix m = Matrix(s, s);

    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
        if (i == j)
            m.getMatrix()[i][j] = 1.0;
        else
            m.getMatrix()[i][j] = 0.0;
        }
    }
    return m;
}

int Matrix::getFil(){
    return this->fil;
}

int Matrix::getCol(){
    return this->col;
}

Matrix Matrix::getFil(Matrix m1, int n){
	Matrix m2 = new Matrix(m1->col);
	
    for (int j = 0; j < col; j++)
        m2[j][0] = m1[n][j];
	
	return m2;
}

Matrix Matrix::getCol(Matrix m1, int n){
	Matrix m2 = new Matrix(m1->fil);
	
    for (int i = 0; i < fil; i++)
        m2[i][0] = m1[i][n];
	
	return m2;
}

double** Matrix::getMatrix(){
    return this->data;
}

void getCfactor(Matrix& M, Matrix& t, int p, int q, int n) {
   int i = 0, j = 0;
   for (int r= 0; r< n; r++) {
      for (int c = 0; c< n; c++) //Copy only those elements which are not in given row r and column c: 
      {
         if (r != p && c != q) {
             j++;
              t(i+1, j+1) = M(r+1,c+1); //If row is filled increase r index and reset c index
            if (j == n - 1) {
               j = 0; i++;
            }
         }
      }
   }
}


double Matrix::det(Matrix& M, int n){ //to find determinant
   double D = 0;
   if (n == 1)
      return M(1,1);
   Matrix t(n, n); //store cofactors
   int s = 1; //store sign multiplier
   //To Iterate each element of first row
   for (int f = 0; f < n; f++) {
      //For Getting Cofactor of M[0][f] do 
      getCfactor(M, t, 0, f, n); 
      D += s * M(1, f+1) * det(t, n - 1);
      s = -s;
   }
   return D;
}

Matrix Matrix::adj(Matrix& M){
//to find adjoint matrix
    int n = M.getFil();
    Matrix adj = Matrix(n, n);
   if (n == 1) {
      adj(1, 1) = 1;
      return adj;
   }
   int s = 1;
   Matrix t = Matrix(n, n);
   for (int i=0; i<n; i++) {
      for (int j=0; j<n; j++) {
         //To get cofactor of M[i][j]
         getCfactor(M, t, i, j, n);
         s = ((i+j)%2==0)? 1: -1; //sign of adj[j][i] positive if sum of row and column indexes is even.
         adj(j+1, i+1) = (s)*(det(t, n-1)); //Interchange rows and columns to get the transpose of the cofactor matrix
      }
   }
   return adj;
}

Matrix Matrix::inv(Matrix* M) {
    Matrix inv(M.getFil(), M.getCol());
   double det = det(M, M.getFil());
   if (det == 0) {
      std::cout << "can't find its inverse";
      return Matrix(M.fil, M.col);
   }
    Matrix adj = adj(M);
   for (int i=0; i<M.getFil(); i++) for (int j=0; j<M.getFil(); j++) inv(i+1, j+1) = adj(i+1, j+1)/det;
   return inv;
}
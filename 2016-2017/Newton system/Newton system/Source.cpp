#include <math.h>
#include <iostream>
using namespace std;
const double calculationError = 0.0001;

class matrix {
public:
	double** someMatrixPtr;
	int rows;
	int cols;
	matrix() {};
	matrix(int row, int col, double* arrayOfNums) :rows(row), cols(col) {//standart constructor
		double **someMatrix = new double *[row];
		int counter = 0;
		for (int i = 0; i < row; i++) {
			someMatrix[i] = new double[col];
		};
		for (int countRow = 0; countRow < row; countRow++) {
			for (int countCol = 0; countCol < col; countCol++) {
				someMatrix[countRow][countCol] = arrayOfNums[counter];
				counter++;
			}
		};
		someMatrixPtr = someMatrix;
	}
	matrix(int row, int col) :rows(row), cols(col) {//special zero matrix constructor
		double **someMatrix = new double *[row];
		int counter = 0;
		for (int i = 0; i < row; i++) {
			someMatrix[i] = new double[col];
		};
		for (int countRow = 0; countRow < row; countRow++) {
			for (int countCol = 0; countCol < col; countCol++) {
				someMatrix[countRow][countCol] = 0;
			}
		};
		someMatrixPtr = someMatrix;
	}
	matrix(const matrix &Matrix) :rows(Matrix.rows), cols(Matrix.cols) {//copy constructor
		double **someMatrix = new double *[Matrix.rows];
		int counter = 0;
		for (int i = 0; i < Matrix.rows; i++) {
			someMatrix[i] = new double[Matrix.cols];
		};
		for (int countRow = 0; countRow < Matrix.rows; countRow++) {
			for (int countCol = 0; countCol < Matrix.cols; countCol++) {
				someMatrix[countRow][countCol] = Matrix.someMatrixPtr[countRow][countCol];
			}
		};
		someMatrixPtr = someMatrix;
	}
	//arithmetic operations with matrices and special operators for matrix class
	matrix* operator*(const matrix &rightMatrix) const {
		matrix* result = new matrix(this->rows, rightMatrix.cols);
		for (int countRow = 0; countRow < this->rows; countRow++) {
			for (int countCol = 0; countCol < rightMatrix.cols; countCol++) {
				for (int resultCount = 0; resultCount < this->cols; resultCount++) {
					result->someMatrixPtr[countRow][countCol] += someMatrixPtr[countRow][resultCount] * rightMatrix.someMatrixPtr[resultCount][countCol];
				};
			};
		};
		return result;
	};
	matrix* operator+(const matrix &rightMatrix) const {
		matrix* result = new matrix(this->rows, rightMatrix.cols);
		for (int countRow = 0; countRow < this->rows; countRow++) {
			for (int countCol = 0; countCol < rightMatrix.cols; countCol++) {
				result->someMatrixPtr[countRow][countCol] = someMatrixPtr[countRow][countCol] + rightMatrix.someMatrixPtr[countRow][countCol];
			};
		};
		return result;
	};
	matrix* operator-(const matrix &rightMatrix) const {
		matrix* result = new matrix(this->rows, rightMatrix.cols);
		for (int countRow = 0; countRow < this->rows; countRow++) {
			for (int countCol = 0; countCol < rightMatrix.cols; countCol++) {
				result->someMatrixPtr[countRow][countCol] = someMatrixPtr[countRow][countCol] - rightMatrix.someMatrixPtr[countRow][countCol];
			};
		};
		return result;
	};
	matrix* operator/(const float &right) const {
		matrix* result = new matrix(this->rows, 1);
		for (int matrixCounter = 0; matrixCounter < (this->rows); matrixCounter++) {
			result->someMatrixPtr[matrixCounter][0] = someMatrixPtr[matrixCounter][0] / right;
		};
		return result;
	};
	double* operator[] (int num) const {
		return this->someMatrixPtr[num];
	}
	friend std::ostream &operator<<(std::ostream &out, const matrix& left);
	matrix* operator=(const matrix *left) {
		if (this == left) {
			return this;
		}
		else {

			this->cols = left->cols;
			this->rows = left->rows;
			for (int i = 0; i < cols; i++) {
				for (int j = 0; j < rows; j++) {
					this->someMatrixPtr[j][i] = left->someMatrixPtr[j][i];
				};
			};
			return this;
		}
	};
	~matrix() {
		for (int count = 0; count < rows; count++)
			delete[] someMatrixPtr[count];
	}
};
std::ostream &operator<<(std::ostream &out, const matrix& left) {
	for (int countRow = 0; countRow < left.rows; countRow++) {
		for (int countCol = 0; countCol < left.cols; countCol++) {
			out << left.someMatrixPtr[countRow][countCol] << " ";
		}
		out << std::endl;
	};
	return out;
}
double norm(const matrix &Matrix) {//matrix norm (root of the sum of squares of matrix elements)
	double result = 0;
	for (int countRow = 0; countRow < Matrix.rows; countRow++) {
		for (int countCol = 0; countCol < Matrix.cols; countCol++) {
			result += pow(Matrix[countRow][countCol], 2);
		};
	};
	return sqrt(result);
}
matrix* doInverseDiag(const matrix &Matrix) {//do diagonal matrix for formula in Seidel's method
	matrix* result = new matrix(Matrix.rows, Matrix.cols);
	for (int diagCounter = 0; diagCounter < Matrix.rows; diagCounter++) {
		if (Matrix.someMatrixPtr[diagCounter][diagCounter]) {
			result->someMatrixPtr[diagCounter][diagCounter] = 1 / Matrix.someMatrixPtr[diagCounter][diagCounter];
		};
	};
	return result;
}

matrix* doU(const matrix &Matrix) {//do upper matrix for formula in Seidel's method
	matrix* result = new matrix(Matrix.rows, Matrix.cols);
	for (int countRow = 0; countRow < Matrix.rows; countRow++) {
		for (int countCol = 0; countCol < Matrix.cols; countCol++) {
			if (countCol > countRow) {
				result->someMatrixPtr[countRow][countCol] = Matrix.someMatrixPtr[countRow][countCol];
			};
		};
	};
	return result;
}
matrix* doL(const matrix &Matrix) {//do lower matrix for formula in Seidel's method
	matrix* result = new matrix(Matrix.rows, Matrix.cols);
	for (int countRow = 0; countRow < Matrix.rows; countRow++) {
		for (int countCol = 0; countCol < Matrix.cols; countCol++) {
			if (countCol < countRow) {
				result->someMatrixPtr[countRow][countCol] = Matrix.someMatrixPtr[countRow][countCol];
			};
		};
	};
	return result;
}
matrix* Seidel(const matrix* systemMatrix, const matrix* C) {//Seidel's method  (we did it more universal)
	matrix Diag = *doInverseDiag(*systemMatrix);
	const matrix U = *doU(*systemMatrix);
	const matrix L = *doL(*systemMatrix);
	matrix X = *C;
	matrix *newX = new matrix(X);
	for (int counter = 0; counter < systemMatrix->rows; counter++) {
		*newX = *(*(*(Diag**C) - *(*(Diag*U)*X)) - *(*(Diag*L)**newX));//first approach 
	};
	matrix DeltaX = *(X - *newX);
	while (norm(DeltaX) >= calculationError) {
		X = *newX;
		*newX = *(*(*(Diag**C) - *(*(Diag*U)*X)) - *(*(Diag*L)**newX));//new approach 
		DeltaX = *(X - *newX);
	};
	matrix proof(3, 1);
	proof = *(*(*systemMatrix**newX) - *C);
	return newX;
}
matrix* systemFunctions(const matrix &X) {//functions from our system
	double resultArray[2];
	resultArray[1] = -(sin(X.someMatrixPtr[0][0] - 1) + X.someMatrixPtr[1][0] - 1.3);
	resultArray[0] = -(-sin(X.someMatrixPtr[1][0] + 1) + X.someMatrixPtr[0][0] - 0.8);
	matrix* result = new matrix(2, 1, resultArray);
	return result;
}
matrix* systemFunctionsDerivatives(const matrix &X) {//Jacobian matrix
	double resultArray[4];
	resultArray[0] = 1;
	resultArray[1] = -cos(X.someMatrixPtr[1][0] + 1);
	resultArray[2] = cos(X.someMatrixPtr[0][0] - 1);
	resultArray[3] = 1;
	matrix* result = new matrix(2, 2, resultArray);
	return result;
}
int main() {
	double arrayX[2] = { 2,1 };
	matrix X(2, 1, arrayX);//first approach
	matrix newX(2, 1);
	int iterationsCounter = 0;
	while (norm(*(X - newX)) >= calculationError) {
		iterationsCounter += 1;
		X = newX;
		newX = *(*(Seidel(systemFunctionsDerivatives(X), systemFunctions(X))) + X);//formula: we solve the linear system whose coefficients are obtained by substituting the approach in the corresponding relations
	};
	cout << "answer: " << endl << newX << endl << "proof:" << endl << *systemFunctions(newX) << endl << "iterations number: " << iterationsCounter << endl;
	system("pause");
	return 0;
}
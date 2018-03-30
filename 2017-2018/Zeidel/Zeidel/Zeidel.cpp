#include <math.h>
#include <iostream>
using namespace std;

class matrix {
public:
	double** someMatrixPtr;
	int rows;
	int cols;
	matrix() {};
	matrix(int row, int col, double* arrayOfNums) :rows(row), cols(col) {
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
	matrix(int row, int col) :rows(row), cols(col) {
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
	matrix(const matrix &Matrix) :rows(Matrix.rows), cols(Matrix.cols) {
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
		for (int matrixCounter = 0; matrixCounter<(this->rows); matrixCounter++) {
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
double norm(const matrix &Matrix) {
	double result = 0;
	for (int countRow = 0; countRow < Matrix.rows; countRow++) {
		for (int countCol = 0; countCol < Matrix.cols; countCol++) {
			result += pow(Matrix[countRow][countCol], 2);
		};
	};
	return sqrt(result);
}
matrix* doDiag(const matrix &Matrix) {
	matrix* result = new matrix(Matrix.rows, Matrix.cols);
	for (int diagCounter = 0; diagCounter < Matrix.rows; diagCounter++) {
		result->someMatrixPtr[diagCounter][diagCounter] = Matrix.someMatrixPtr[diagCounter][diagCounter];
	};
	return result;
}
matrix* doInverseToDiag(matrix &Diag) {
	matrix* result = new matrix(Diag.rows, Diag.cols);
	for (int diagCounter = 0; diagCounter < Diag.rows; diagCounter++) {
		if (Diag.someMatrixPtr[diagCounter][diagCounter]) {
			result->someMatrixPtr[diagCounter][diagCounter] = 1/Diag.someMatrixPtr[diagCounter][diagCounter];
		};
	};
	return result;
}
matrix* doU(const matrix &Matrix) {
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
matrix* doL(const matrix &Matrix) {
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
int main() {
	double calculationError = 0.00001;
	//special type of matrix of our system
	double arrayOfNumsForSystemMatrix[9] =	
	{ 6.2, 2.2, 2.3,
		3.8, 6.7, -1.2,
		0.2, -0.9, -5};
	const matrix systemMatrix(3, 3, arrayOfNumsForSystemMatrix);
	double arrayOfNumsForFreeVector[3] = { -4.6,-5.2,0.8 };
	const matrix C(3, 1, arrayOfNumsForFreeVector);
	matrix Diag = *doDiag(systemMatrix);	
	matrix U = *doU(systemMatrix);
	matrix L = *doL(systemMatrix);
	matrix X = C;
	Diag = doInverseToDiag(Diag);	
	matrix newX = X;
	for (int counter = 0; counter < systemMatrix.rows; counter++) {
		newX = *(*(*(Diag*C)-*(*(Diag*U)*X))-*(*(Diag*L)*newX));
	};
	matrix DeltaX = *(X - newX);
	while (norm(DeltaX) >= calculationError) {
		X = newX;
		newX = *(*(*(Diag*C) - *(*(Diag*U)*X)) - *(*(Diag*L)*newX));
		DeltaX=*(X - newX);
	};
	matrix proof(3,1);
	proof = *(*(systemMatrix*newX)-C);
	cout << "SEIDEL'S METHOD" << endl <<"answer:" <<endl<< newX << endl <<"proof:"<<endl<< proof << endl;
	system("pause");
	return(0);
}
#include <math.h>
#include <iostream>
using namespace std;

const double calculationError = 0.000001;
const int studentNumber = 13;


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
	matrix* operator*(const double &number) const {
		matrix* result = new matrix(this->rows, this->cols);
		for (int countRow = 0; countRow < this->rows; countRow++) {
			for (int countCol = 0; countCol < this->cols; countCol++) {				
					result->someMatrixPtr[countRow][countCol] = someMatrixPtr[countRow][countCol] * number;				
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
	matrix* operator+(const int &number) const {
		matrix* result = new matrix(this->rows, this->cols);
		for (int countRow = 0; countRow < this->rows; countRow++) {
			for (int countCol = 0; countCol < this->cols; countCol++) {
				result->someMatrixPtr[countRow][countCol] = someMatrixPtr[countRow][countCol] + number;
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
matrix* transpose(matrix &Matrix) {
	matrix* result = new matrix(Matrix.cols, Matrix.rows);
	for (int countRow = 0; countRow < Matrix.cols; countRow++) {
		for (int countCol = 0; countCol < Matrix.rows; countCol++) {
			result->someMatrixPtr[countRow][countCol] = Matrix[countCol][countRow];
		};
	};
	return result;
};

double norm(const matrix &Matrix) {
	double result = 0;
	for (int countRow = 0; countRow < Matrix.rows; countRow++) {
		for (int countCol = 0; countCol < Matrix.cols; countCol++) {
			result += pow(Matrix[countRow][countCol], 2);
		};
	};
	return sqrt(result);
}
/*
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
			result->someMatrixPtr[diagCounter][diagCounter] = 1 / Diag.someMatrixPtr[diagCounter][diagCounter];
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
*/

double functionValue(matrix* x, matrix * A, matrix *b) {	
	return	(*(*(*transpose(*x) * *A) * *x) + *(*transpose(*x) * *b))->someMatrixPtr[0][0] + studentNumber;	
};

matrix* gradient(matrix* x, matrix * A, matrix *b) {
	matrix* result = new matrix();
	*result = *(*(*A * *x) + *b);
	return result;
};

void methodOut(matrix* x, matrix * A, matrix *b,int &iterationCounter) {
	cout<<  "X: " << endl << *x << endl
		<< "function value: " << functionValue(x, A, b) << endl
		<< "gradient value:" << endl << *gradient(x, A, b) << endl
		<< "number of iterations: " << iterationCounter << endl;
};

void methodOfSteepestGradientDescent(matrix* x, matrix * A, matrix *b) {
	matrix direction=*gradient(x,A,b);
	double step=-pow(norm(*gradient(x, A, b)),2)/((*(*transpose(*gradient(x, A, b)) * *A) * *gradient(x, A, b))->someMatrixPtr[0][0]);
	int iterationCounter = 1;
	matrix newX = *(*x + *(direction * step));
	while (norm(*(newX-*x))>=calculationError) {
		*x = newX;
		direction = *gradient(x, A, b);
		step = -pow(norm(*gradient(x, A, b)), 2) / ((*(*transpose(*gradient(x, A, b)) * *A) * *gradient(x, A, b))->someMatrixPtr[0][0]);
		newX = *(*x + *(direction * step));
		iterationCounter += 1;
	};
	*x = newX;
	cout << "METHOD OF STEEPEST GRADIENT DESCENT:" << endl;
	methodOut(x, A, b, iterationCounter);
};

void methodOfSteepestCoordinateDescent(matrix* x, matrix * A, matrix *b) {
	matrix direction(x->rows, x->cols);
	direction.someMatrixPtr[0][0] = 1; //(1,0,0) column
	double step = -norm(*(*transpose(direction) * *gradient(x, A, b))) / norm(*(*(*transpose(direction) * *A) * direction));
	int iterationCounter = 1;
	matrix newX = *(*x + *(direction * step));
	while (norm(*(newX - *x)) >= calculationError) {		
		*x = newX;
		direction.someMatrixPtr[(iterationCounter-1)%direction.rows][0] = 0;
		direction.someMatrixPtr[iterationCounter%direction.rows][0] = 1;
		step = -((*transpose(direction) * *gradient(x, A, b))->someMatrixPtr[0][0]) / ((*(*transpose(direction) * *A) * direction)->someMatrixPtr[0][0]);
		newX = *(*x + *(direction * step));
		iterationCounter += 1;		
	};
	*x = newX;
	cout << "METHOD OF STEEPEST COORDINATE DESCENT:" << endl;
	methodOut(x, A, b, iterationCounter);
};

int main() {
	double matrixAArray[9] = { 4,1,1,1,2 * (3 + 0.1*studentNumber),-1,1,-1,2 * (4 + 0.1*studentNumber) };
	matrix* A= new matrix(3, 3, matrixAArray);
	double vectorBArray[3] = { 1,-2,3 };
	matrix* b= new matrix(3, 1, vectorBArray);
	matrix* x = new matrix(3, 1);
	methodOfSteepestGradientDescent(x, A, b);
	methodOfSteepestCoordinateDescent(x, A, b);

	return (0);
}
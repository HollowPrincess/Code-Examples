#include <math.h>
#include <iostream>
using namespace std;
const double calculationError = 0.00001;

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

matrix * Seidel(matrix *systemMatrix, matrix *systemVector) {//Seidel's method
	
	//make special calculations for method
	matrix Diag = *doInverseDiag(*systemMatrix);
	const matrix U = *doU(*systemMatrix);
	const matrix L = *doL(*systemMatrix);
	matrix X = *systemVector;
	matrix *newX = new matrix();
	*newX=	X;
	for (int counter = 0; counter < systemMatrix->rows; counter++) {
		*newX = *(*(*(Diag**systemVector) - *(*(Diag*U)*X)) - *(*(Diag*L)**newX));//first approach 
	};
	//int iterationsCounter = 1;
	while (norm(*(X - *newX)) >= calculationError) {
		//iterationsCounter += 1;
		X = *newX;
		*newX = *(*(*(Diag**systemVector) - *(*(Diag*U)*X)) - *(*(Diag*L)**newX));//new approach 
	};
	return newX;
	//matrix proof(3, 1);
	//proof = *(*(*systemMatrix*newX) - *systemVector);
	//cout << "SEIDEL'S METHOD" << endl << "number of iterations: " << iterationsCounter << endl << "answer:" << endl << newX << endl << "proof:" << endl << proof << endl;
}

double pointX(int numOfPoint) {
	double leftEnd = -1;
	double rightEnd = 1;
	return leftEnd + numOfPoint*(rightEnd - leftEnd) / 4;
};
double taskFunc(double x) {
	return x*tan(x);
};
double xWithDegree(double point, int degree) { return pow(point, degree); };//functions for poly
double LegandersPoly(double point, int degree) {
	switch (degree) {
	case 0:
		return 1;
	case 1:
		//return point;
		return -point;
	case 2:
		//return (3 * pow(point, 2) - 1) / 2;
		return 1.5*pow(point, 2) - 0.5;
	case 3:
		//return (5 * pow(point, 3) - 3 * point) / 2;
		return 1.5*point - 2.5*pow(point, 3);
	};
};

matrix* matrixOfFuncValues(double(*funcPtr)(double,int)) {
	matrix* result = new matrix(5, 4);
	//It's Q matrix 
	for (int countRow = 0; countRow < result->rows; countRow++) {
		for (int countCol = 0; countCol < result->cols; countCol++) {
			result->someMatrixPtr[countRow][countCol] = funcPtr(pointX(countRow), countCol);
		};
	};
	return result;
};
matrix* systemMatrix(double(*funcPtr)(double, int)) {
	matrix* result = matrixOfFuncValues(funcPtr);
	*result = *(*transpose(*result) * *result);
	//do for system a=Ha+b
	/*for (int counter = 0; counter < result->cols; counter++) {
		result->someMatrixPtr[counter][counter] = result->someMatrixPtr[counter][counter] + 1;
	};	*/
	return result;//4*4
};
matrix* systemVector(double(*funcPtr)(double, int)) {
	matrix* result = transpose(*matrixOfFuncValues(funcPtr));
	matrix valueVector(5, 1);
	for (int counter = 0; counter < 5; counter++) {
		valueVector.someMatrixPtr[counter][0] = taskFunc(pointX(counter));
	};
	*result = *(*result * valueVector);//4*1
/*	for (int counter = 0; counter < result->rows; counter++) {
		result->someMatrixPtr[counter][0] = -result->someMatrixPtr[counter][0];
	};*/
	//cout << endl << *result << endl;

	return result;
};

void specialOutput(matrix* cofficients) {
	cout << "result: "<<endl;	
	for (int counter = 0; counter < 4; counter++) {
		if (cofficients->someMatrixPtr[counter][0] >= 0 ) {
			cout << "+";
		};		
		cout << cofficients->someMatrixPtr[counter][0] << "*x^" << counter ;
	};
	cout << endl;
};

int main() {
	matrix* coefficients = Seidel(systemMatrix(xWithDegree), systemVector(xWithDegree));
	specialOutput(coefficients);
	coefficients = Seidel(systemMatrix(LegandersPoly), systemVector(LegandersPoly));
	cout << *coefficients << endl;

	system("pause");
	return(0);
}
#include <cstdlib>
#include <cstdint>
#include <vector>

#ifndef _MATRIX_H_
#define _MATRIX_H_

using namespace std;
typedef struct {
	uint64_t rowindex_U64;
	uint64_t colindex_U64;
	double value_D;
}sElement;

class Matrix
{
public:
	vector<vector<double>> data_V2D;
	uint64_t row_U64;
	uint64_t col_U64;

public:
	Matrix();
	Matrix(uint64_t row_U64, uint64_t col_U64);
	void UpdateData(uint64_t rowindex_U64, uint64_t colindex_U64, double value_D);
	Matrix AddMatrix(Matrix *matrix1, Matrix *matrix2);
	Matrix AddMatrix(Matrix *matrix);
	Matrix MultipleMatrix(Matrix *matrix1, Matrix *matrix2);
	Matrix MultipleMatrix(Matrix *matrix);
	Matrix MultipleNumber(Matrix *matrix, double number);
	Matrix MultipleNumber(double number);
	Matrix SubMatrix(Matrix *matrix1, Matrix *matrix2);
	Matrix SubMatrix(Matrix *matrix);
	Matrix DevideNumber(Matrix *matrix, double number);
	Matrix DevideNumber(double number);
	Matrix Copy(uint64_t rowstart_U64, uint64_t rowend_U64, uint64_t colstart_U64, uint64_t colend_U64, Matrix *matrix);
	Matrix Copy(uint64_t rowstart_U64, uint64_t rowend_U64, uint64_t colstart_U64, uint64_t colend_U64);
	Matrix Transpose(Matrix* matrix);
	Matrix Transpose();
	void Free();
};

#endif
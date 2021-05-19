#include "stdafx.h"

#include "Matrix.h"

Matrix::Matrix()
{

}

Matrix::Matrix(uint64_t row_U64, uint64_t col_U64)
{
	this->row_U64 = row_U64;
	this->col_U64 = col_U64;
	// this->data_D=(double**)calloc(row_U64,sizeof(double*));
	this->data_V2D.resize(row_U64);
	for (uint64_t i = 0; i < row_U64; i++)
		this->data_V2D.at(i).resize(col_U64);
	// this->data_D[i]=(double*)calloc(col_U64,sizeof(double));
}

void Matrix::UpdateData(uint64_t rowindex_U64, uint64_t colindex_U64, double value_D)
{
	this->data_V2D.at(rowindex_U64).at(colindex_U64) = value_D;
}

Matrix Matrix::AddMatrix(Matrix *matrix1, Matrix *matrix2)
{
	if (matrix1->col_U64 != matrix2->col_U64 || matrix1->row_U64 != matrix2->row_U64)
		throw "Dimension mismatches!";
	else
	{
		Matrix res = Matrix(matrix1->row_U64, matrix1->col_U64);
		for (uint64_t i = 0; i < matrix1->col_U64; i++)
			for (uint64_t j = 0; j < matrix1->row_U64; j++)
				res.data_V2D.at(i).at(j) = matrix1->data_V2D.at(i).at(j) + matrix2->data_V2D.at(i).at(j);
		return res;
	}
}

Matrix Matrix::AddMatrix(Matrix *matrix)
{
	return AddMatrix(this, matrix);
}

Matrix Matrix::MultipleMatrix(Matrix *matrix1, Matrix *matrix2)
{
	if (matrix1->col_U64 != matrix2->row_U64)
		throw "Dimension mismatches!";
	else
	{
		Matrix res = Matrix(matrix1->row_U64, matrix2->col_U64);
		double tmp;
		for (uint64_t i = 0; i < matrix1->row_U64; i++)
			for (uint64_t j = 0; j < matrix2->col_U64; j++)
			{
				tmp = 0;
				for (uint64_t index = 0; index < matrix1->col_U64; index++)
					tmp += matrix1->data_V2D.at(i).at(index)*matrix2->data_V2D.at(index).at(j);
				res.data_V2D.at(i).at(j) = tmp;
			}

		return res;
	}
}

Matrix Matrix::MultipleMatrix(Matrix *matrix)
{
	return MultipleMatrix(this, matrix);
}

Matrix Matrix::MultipleNumber(Matrix *matrix, double number)
{
	Matrix res = Matrix(matrix->row_U64, matrix->col_U64);

	for (uint64_t i = 0; i < matrix->row_U64; i++)
		for (uint64_t j = 0; j < matrix->col_U64; j++)
			res.data_V2D.at(i).at(j) = matrix->data_V2D.at(i).at(j)*number;

	return res;
}

Matrix Matrix::MultipleNumber(double number)
{
	return MultipleNumber(this, number);
}

Matrix Matrix::SubMatrix(Matrix *matrix1, Matrix *matrix2)
{
	if (matrix1->col_U64 != matrix2->col_U64 || matrix1->row_U64 != matrix2->row_U64)
		throw "Dimension mismatches!";
	else
	{
		Matrix res = Matrix(matrix1->row_U64, matrix1->col_U64);

		for (uint64_t i = 0; i < matrix1->row_U64; i++)
			for (uint64_t j = 0; j < matrix1->col_U64; j++)
				res.data_V2D.at(i).at(j) = matrix1->data_V2D.at(i).at(j) - matrix2->data_V2D.at(i).at(j);

		return res;
	}
}

Matrix Matrix::SubMatrix(Matrix *matrix)
{
	return this->SubMatrix(this, matrix);
}

Matrix Matrix::DevideNumber(Matrix *matrix, double number)
{
	if (number == 0)
		throw "Can not devide to 0!";
	else
	{
		number = 1 / number;
		return MultipleNumber(matrix, number);
	}
}

Matrix Matrix::DevideNumber(double number)
{
	return DevideNumber(this, number);
}

Matrix Matrix::Copy(uint64_t rowstart_U64, uint64_t rowend_U64, uint64_t colstart_U64, uint64_t colend_U64, Matrix *matrix)
{
	if (rowstart_U64 >= matrix->row_U64 || rowend_U64 >= matrix->row_U64
		|| colstart_U64 >= matrix->col_U64 || colend_U64 >= matrix->col_U64)
		throw "Dimension mismatches!";
	else
	{
		Matrix res = Matrix(rowend_U64 - rowstart_U64 + 1, colend_U64 - colstart_U64 + 1);
		uint64_t ii = 0;
		uint64_t jj = 0;
		for (uint64_t i = rowstart_U64; i <= rowend_U64; i++)
		{
			jj = 0;
			for (uint64_t j = colstart_U64; j <= colend_U64; j++)
				res.UpdateData(ii, jj++, matrix->data_V2D.at(i).at(j));
			ii++;
		}
		return res;
	}
}

Matrix Matrix::Copy(uint64_t rowstart_U64, uint64_t rowend_U64, uint64_t colstart_U64, uint64_t colend_U64)
{
	return Copy(rowstart_U64, rowend_U64, colstart_U64, colend_U64, this);
}

Matrix Matrix::Transpose(Matrix* matrix)
{
	Matrix res = Matrix(matrix->col_U64, matrix->row_U64);
	for (uint64_t i = 0; i < matrix->col_U64; i++)
		for (uint64_t j = 0; j < matrix->row_U64; j++)
			res.UpdateData(i, j, matrix->data_V2D.at(j).at(i));

	return res;
}

Matrix Matrix::Transpose()
{
	return Transpose(this);
}

void Matrix::Free()
{

	for (uint64_t i = 0; i < this->row_U64; i++)
		this->data_V2D.at(i).clear();
	this->data_V2D.clear();

}
#include <cstdlib>
#include <cstdint>
#include "Matrix.h"
#include "Node.h"

#ifndef _SHORTENMATRIX_H_
#define _SHORTENMATRIX_H_

class ShortenMatrix
{
public:
	vector<tNODENAME> Index_PU64;
	Matrix Matrix_M;

public:
	ShortenMatrix();
	ShortenMatrix(vector<tNODENAME> index_PU64, Matrix matrix);
	ShortenMatrix ExtendAdd(ShortenMatrix matrix_M);
	void Free();

private:
	ShortenMatrix Extend(vector<tNODENAME> oldindex_PU64, uint64_t oldsize_U64, vector<tNODENAME> newindex_U64, uint64_t newsize_U64, Matrix oldmatrix_M);
};
#endif
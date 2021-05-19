#include "stdafx.h"

#include "ShortenMatrix.h"
#include <cstdlib>
#include <string>

ShortenMatrix::ShortenMatrix()
{
    
}

ShortenMatrix::ShortenMatrix(vector<tNODENAME> index_PU64, Matrix matrix)
{
    //memcpy(&this->Index_PU64,index_PU64,matrix.row_U64);
    // memcpy(&this->Matrix_M,&matrix,sizeof(Matrix));
    this->Index_PU64=index_PU64;
    this->Matrix_M=matrix;
}

ShortenMatrix ShortenMatrix::Extend(vector<tNODENAME> oldindex_PU64, uint64_t oldsize_U64, vector<tNODENAME> newindex_U64, uint64_t newsize_U64, Matrix oldmatrix_M)
{
    Matrix matrix=Matrix(newsize_U64,newsize_U64);

    uint64_t i_raw=0;
    uint64_t j_raw;
    for (uint64_t i=0; i<newsize_U64;i++)
    {
        j_raw=0;
        for (uint64_t j=0;j<newsize_U64;j++)
        {
            if (i_raw>=oldsize_U64 || j_raw>=oldsize_U64)
                matrix.UpdateData(i,j,0);
            else if (newindex_U64[j]==oldindex_PU64[j_raw] && newindex_U64[i]==oldindex_PU64[i_raw])
            {
                matrix.UpdateData(i,j,oldmatrix_M.data_V2D.at(i_raw).at(j_raw));
                j_raw++;
            }
            else
                matrix.UpdateData(i,j,0);
        }

        if (i_raw < oldsize_U64)
            if (newindex_U64[i]==oldindex_PU64[i_raw])
                i_raw++;
    }
    

    return ShortenMatrix(newindex_U64,matrix);
}

ShortenMatrix ShortenMatrix::ExtendAdd(ShortenMatrix smatrix_M)
{
    
    uint64_t i=0;
    uint64_t j=0;
    uint64_t cnt_U64=0;

    uint64_t len1=this->Matrix_M.row_U64;
    uint64_t len2=smatrix_M.Matrix_M.row_U64;

    vector<tNODENAME> newindex_PU64;
    while (i<len1 || j<len2)
    {
        cnt_U64++;
        if (j>=len2)
            newindex_PU64.push_back(this->Index_PU64.at(i++));
        else if (i>=len1)
            newindex_PU64.push_back(smatrix_M.Index_PU64.at(j++));
        else if (this->Index_PU64[i] <= smatrix_M.Index_PU64[j])
        {
            newindex_PU64.push_back(this->Index_PU64.at(i));
            if (this->Index_PU64.at(i) == smatrix_M.Index_PU64.at(j))
                j++;
            i++;
        }
        else
            newindex_PU64.push_back(smatrix_M.Index_PU64.at(j++));
    }

    //refactor matrix
    ShortenMatrix smatrix1_M=Extend(this->Index_PU64,len1,newindex_PU64,cnt_U64,this->Matrix_M);
    ShortenMatrix smatrix2_M=Extend(smatrix_M.Index_PU64,len2,newindex_PU64,cnt_U64,smatrix_M.Matrix_M);

    
    Matrix new_matrix_M;
    new_matrix_M=new_matrix_M.AddMatrix(&smatrix1_M.Matrix_M,&smatrix2_M.Matrix_M);

    return ShortenMatrix(newindex_PU64,new_matrix_M);
}

void ShortenMatrix::Free()
{
    this->Matrix_M.Free();
    // free(this);
}



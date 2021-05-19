//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// OrdinaryCholesky.cpp
//
// Code generation for function 'OrdinaryCholesky'
//

// Include files
#include "stdafx.h"

#include "OrdinaryCholesky.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
void OrdinaryCholesky(coder::array<double, 2U> &A, coder::array<double, 2U> &L)
{
  coder::array<double, 1U> L21;
  unsigned int col;
  int i;
  int loop_ub;
  int m;
  unsigned int row;
  // Function to find the Cholesky factor of a Positive Definite matrix A
  // Author Mathuranathan for https://www.gaussianwaves.com
  // Licensed under Creative Commons: CC-NC-BY-SA 3.0
  // A = positive definite matrix
  // Option can be one of the following 'Lower','Upper'
  // L = Cholesky factorizaton of A such that A=LL^T
  // If option ='Lower', then it returns the Cholesky factored matrix L in
  // lower triangular form
  // If option ='Upper', then it returns the Cholesky factored matrix L in
  // upper triangular form
  // Test for positive definiteness (symmetricity need to satisfy)
  // Check if the matrix is symmetric
  // if ~isequal(A,A'),
  //     error('Input Matrix is not Symmetric');
  // end
  // if isPositiveDefinite(A),
  m = A.size(0);
  L.set_size(A.size(0), A.size(0));
  loop_ub = A.size(0) * A.size(0);
  for (i = 0; i < loop_ub; i++) {
    L[i] = 0.0;
  }
  // Initialize to all zeros
  row = 2U;
  col = 1U;
  i = A.size(0);
  for (int b_i{0}; b_i < i; b_i++) {
    double a11;
    a11 = std::sqrt(A[0]);
    L[(static_cast<int>(row) + L.size(0) * (static_cast<int>(col) - 1)) - 2] =
        a11;
    if (m != 1) {
      int i1;
      int i2;
      // Reached the last partition
      if (2 > m) {
        i1 = 0;
        i2 = 0;
      } else {
        i1 = 1;
        i2 = m;
      }
      loop_ub = i2 - i1;
      L21.set_size(loop_ub);
      for (i2 = 0; i2 < loop_ub; i2++) {
        L21[i2] = A[i1 + i2] / a11;
      }
      if (row > static_cast<unsigned int>(L.size(1))) {
        i1 = 0;
        i2 = 0;
      } else {
        i1 = static_cast<int>(row) - 1;
        i2 = L.size(1);
      }
      loop_ub = i2 - i1;
      for (i2 = 0; i2 < loop_ub; i2++) {
        L[(static_cast<int>(col) + L.size(0) * (i1 + i2)) - 1] = L21[i2];
      }
      if (2 > m) {
        i1 = 0;
        i2 = 0;
      } else {
        i1 = 1;
        i2 = 1;
      }
      loop_ub = L21.size(0);
      for (int i3{0}; i3 < loop_ub; i3++) {
        m = L21.size(0);
        for (int i4{0}; i4 < m; i4++) {
          A[i4 + A.size(0) * i3] =
              A[(i1 + i4) + A.size(0) * (i2 + i3)] - L21[i4] * L21[i3];
        }
      }
      m = A.size(0);
      row++;
      col++;
    }
  }
  //     switch nargin
  //         case 2
  //             if strcmpi(option,'upper'),F=L';
  //             else
  //                 if strcmpi(option,'lower'),F=L;
  //                 else error('Invalid option');
  //                 end
  //             end
  //         case 1
  //             F=L;
  //         otherwise
  //             error('Not enough input arguments')
  //     end
  // else
  //         error('Given Matrix A is NOT Positive definite');
  // end
}

// End of code generation (OrdinaryCholesky.cpp)

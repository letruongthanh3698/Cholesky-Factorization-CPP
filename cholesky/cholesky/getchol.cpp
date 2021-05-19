//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// getchol.cpp
//
// Code generation for function 'getchol'
//

// Include files
#include "stdafx.h"
#include "getchol.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
void getchol(const coder::array<double, 2U> &input,
             coder::array<double, 2U> &res)
{
  int i;
  int jmax;
  int n;
  // GETCHOL Summary of this function goes here
  //    Detailed explanation goes here
  res.set_size(input.size(0), input.size(1));
  jmax = input.size(0) * input.size(1);
  for (i = 0; i < jmax; i++) {
    res[i] = input[i];
  }
  n = input.size(1);
  if (input.size(1) != 0) {
    int idxAjj;
    int info;
    int j;
    boolean_T exitg1;
    info = -1;
    j = 0;
    exitg1 = false;
    while ((!exitg1) && (j <= n - 1)) {
      double ssq;
      int idxA1j;
      int nmj;
      idxA1j = j * n;
      idxAjj = idxA1j + j;
      ssq = 0.0;
      if (j >= 1) {
        for (nmj = 0; nmj < j; nmj++) {
          jmax = idxA1j + nmj;
          ssq += res[jmax] * res[jmax];
        }
      }
      ssq = res[idxAjj] - ssq;
      if (ssq > 0.0) {
        ssq = std::sqrt(ssq);
        res[idxAjj] = ssq;
        if (j + 1 < n) {
          int ia0;
          int idxAjjp1;
          nmj = (n - j) - 2;
          ia0 = (idxA1j + n) + 1;
          idxAjjp1 = idxAjj + n;
          if ((j != 0) && (nmj + 1 != 0)) {
            jmax = idxAjjp1;
            i = ia0 + n * nmj;
            for (int iac{ia0}; n < 0 ? iac >= i : iac <= i; iac += n) {
              double c;
              c = 0.0;
              idxAjj = (iac + j) - 1;
              for (int ia{iac}; ia <= idxAjj; ia++) {
                c += res[ia - 1] * res[(idxA1j + ia) - iac];
              }
              res[jmax] = res[jmax] + -c;
              jmax += n;
            }
          }
          ssq = 1.0 / ssq;
          i = (idxAjjp1 + n * nmj) + 1;
          for (nmj = idxAjjp1 + 1; n < 0 ? nmj >= i : nmj <= i; nmj += n) {
            res[nmj - 1] = ssq * res[nmj - 1];
          }
        }
        j++;
      } else {
        res[idxAjj] = ssq;
        info = j;
        exitg1 = true;
      }
    }
    if (info + 1 == 0) {
      jmax = input.size(1);
    } else {
      jmax = info;
    }
    for (j = 0; j < jmax; j++) {
      i = j + 2;
      for (idxAjj = i; idxAjj <= jmax; idxAjj++) {
        res[(idxAjj + res.size(0) * j) - 1] = 0.0;
      }
    }
  }
}

// End of code generation (getchol.cpp)

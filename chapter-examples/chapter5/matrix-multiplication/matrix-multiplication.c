#include "matrix-multiplication.h"

void matrix_multiplication_1(double *C, double *A, double *B, int dim) {
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      int sum = 0;
      for (int k = 0; k < dim; k++) {
        sum += A[i * dim + k] * B[k * dim + j];
      }
      C[i * dim + j] = sum;
    }
  }
}

void matrix_multiplication_2(double *C, double *A, double *B, int dim) {
  for (int k = 0; k < dim; k++) {
    for (int i = 0; i < dim; i++) {
      int r = A[i * dim + k];
      for (int j = 0; j < dim; j++) {
        C[i * dim + j] += r * B[k * dim + j];
      }
    }
  }
}

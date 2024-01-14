#include <stdio.h>
void transpose_naive(int *dst, int *src, int dim) {
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      dst[dim * i + j] = src[dim * j + i];
    }
  }
}

#ifndef BLOCK_SIZE
#define BLOCK_SIZE 4
#endif

void transpose_optimized(int *dst, int *src, int dim) {
  int i = 0;
  int j = 0;
  int last;
  for (i = 0; i < dim - BLOCK_SIZE + 1; i += BLOCK_SIZE) {
    for (j = 0; j < dim - BLOCK_SIZE + 1; j += BLOCK_SIZE) {
      for (int k = 0; k < BLOCK_SIZE; k++) {
        for (int l = 0; l < BLOCK_SIZE; l++) {
          dst[(i + k) * dim + (j + l)] = src[(j + l) * dim + (i + k)];
        }
      }
    }
  }
  last = i;
  for (int i = 0; i < dim; i++) {
    for (int j = last; j < dim; j++) {
      dst[dim * i + j] = src[dim * j + i];
      dst[dim * j + i] = src[dim * i + j];
    }
  }
}

void transpose_optimized2(int *dst, int *src, int dim) {
  int i = 0;
  int j = 0;
  int last;
  for (i = 0; i < dim - BLOCK_SIZE + 1; i += BLOCK_SIZE) {
    for (j = 0; j < dim - BLOCK_SIZE + 1; j += BLOCK_SIZE) {
      for (int k = 0; k < BLOCK_SIZE; k++) {
        int l;
        for (l = 0; l < BLOCK_SIZE - 3; l += 4) {
          dst[(i + k) * dim + (j + l)] = src[(j + l) * dim + (i + k)];
          dst[(i + k) * dim + (j + l + 1)] = src[(j + l + 1) * dim + (i + k)];
          dst[(i + k) * dim + (j + l + 2)] = src[(j + l + 2) * dim + (i + k)];
          dst[(i + k) * dim + (j + l + 3)] = src[(j + l + 3) * dim + (i + k)];
        }
        for (; l < BLOCK_SIZE; l++) {
          dst[(i + k) * dim + (j + l)] = src[(j + l) * dim + (i + k)];
        }
      }
    }
  }
  last = i;
  for (int i = 0; i < dim; i++) {
    for (int j = last; j < dim; j++) {
      dst[dim * i + j] = src[dim * j + i];
      dst[dim * j + i] = src[dim * i + j];
    }
  }
}

#include "convert.h"

void convert_naive(int *G, int dim) {
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++)
      G[dim * i + j] = G[dim * i + j] || G[dim * j + i];
  }
}

#ifndef BLOCK_SIZE
#define BLOCK_SIZE 16
#endif // BLOCK_SIZE

void convert_optimized(int *G, int dim) {
  int i;
  for (i = 0; i < dim - BLOCK_SIZE + 1; i += BLOCK_SIZE) {
    for (int j = 0; j < dim - BLOCK_SIZE + 1; j += BLOCK_SIZE) {
      for (int k = 0; k < BLOCK_SIZE; k += 1) {
        int l;
        for (l = 0; l < BLOCK_SIZE - 3; l += 4) {
          G[dim * (i + k) + (j + l)] =
              G[dim * (i + k) + (j + l)] || G[dim * (j + l) + (i + k)];
          G[dim * (i + k) + (j + l + 1)] =
              G[dim * (i + k) + (j + l + 1)] || G[dim * (j + l + 1) + (i + k)];
          G[dim * (i + k) + (j + l + 2)] =
              G[dim * (i + k) + (j + l + 2)] || G[dim * (j + l + 2) + (i + k)];
          G[dim * (i + k) + (j + l + 3)] =
              G[dim * (i + k) + (j + l + 3)] || G[dim * (j + l + 3) + (i + k)];
        }
        for (; l < BLOCK_SIZE; l += 1) {
          G[dim * (i + k) + (j + l)] =
              G[dim * (i + k) + (j + l)] || G[dim * (j + l) + (i + k)];
        }
      }
    }
  }
  int last = i;
  for (int i = 0; i < dim; i++) {
    for (int j = last; j < dim; j++) {
      G[dim * i + j] = G[dim * i + j] || G[dim * j + i];
      G[dim * j + i] = G[dim * j + i] || G[dim * i + j];
    }
  }
}

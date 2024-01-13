#include "matrix-multiplication.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h>

#define START_N 100
#define END_N 1000
#define STEP_N 100
#define F_NUM 2
#define AVERAGING 1

typedef void (*matrix_multiplication_f)(double *, double *, double *, int);
matrix_multiplication_f f[F_NUM] = {&matrix_multiplication_1,
                                    &matrix_multiplication_2};
char *f_name[F_NUM] = {"matrix_multiplication_1", "matrix_multiplication_2"};
double C[END_N * END_N];
double A[END_N * END_N];
double B[END_N * END_N];

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <output file>\n", argv[0]);
    return 1;
  }

  FILE *fp;
  fp = fopen(argv[1], "w");
  fprintf(fp, "n, ");
  for (int i = 0; i < F_NUM; i++) {
    fprintf(fp, "%s, ", f_name[i]);
  }
  fprintf(fp, "\n");

  for (int n = START_N; n <= END_N; n += STEP_N) {
    fprintf(fp, "%d, ", n);

    // Initilize input
    int dim = n;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        A[i * dim + j] = random();
        B[i * dim + j] = random();
      }
    }

    // Benchmark all functions
    for (int i = 0; i < F_NUM; i++) {
      uint64_t duration_average = 0;
      for (int j = 0; j < AVERAGING; j++) {
        uint64_t begin = __rdtsc();
        f[i]((double *)C, (double *)A, (double *)B, n);
        uint64_t end = __rdtsc();
        uint64_t duration = (end - begin);
        duration_average = (duration_average * j + duration) / (j + 1);
      }
      // Write duration average to output file
      fprintf(fp, "%ld, ", duration_average / (n * n * n));
    }

    fprintf(fp, "\n");
  }

  // Close file
  fclose(fp);
  return 0;
}

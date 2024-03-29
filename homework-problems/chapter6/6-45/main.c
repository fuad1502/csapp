#include "transpose.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h>

#define START_N 100
#define END_N 1000
#define STEP_N 10
#define F_NUM 3
#define WARM_UP 10
#define AVERAGING 10

typedef void (*matrix_multiplication_f)(int *, int *, int);
matrix_multiplication_f f[F_NUM] = {&transpose_naive, &transpose_optimized,
                                    &transpose_optimized2};
char *f_name[F_NUM] = {"transpose_naive", "transpose_optimized",
                       "transpose_optimized2"};
int check_result(int *result1, int *result2, int dim);
void print_result(int *result1, int *result2, int dim);
int dst[F_NUM][END_N * END_N];
int src[END_N * END_N];

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

  // Initilize input
  for (int i = 0; i < END_N; i++) {
    for (int j = 0; j < END_N; j++) {
      src[i * END_N + j] = random() % 100;
    }
  }

  for (int n = START_N; n <= END_N; n += STEP_N) {
    int dim = n;
    fprintf(fp, "%d, ", n);

    // Benchmark all functions
    for (int i = 0; i < F_NUM; i++) {
      // Warm up cache
      for (int j = 0; j < WARM_UP; j++) {
        f[i]((int *)dst[i], (int *)src, n);
      }
      // Benchmark function
      uint64_t duration_average = 0;
      for (int j = 0; j < AVERAGING; j++) {
        uint64_t begin = __rdtsc();
        f[i]((int *)dst[i], (int *)src, n);
        uint64_t end = __rdtsc();
        uint64_t duration = (end - begin);
        duration_average = (duration_average * j + duration) / (j + 1);
      }
      // Check result
      if (i > 0) {
        if (check_result(dst[i], dst[i - 1], dim) != 0) {
          printf("Incorrect result! (%d)\n", n);
          print_result(dst[i], dst[i - 1], dim);
          exit(1);
        }
      }
      // Write duration average to output file
      fprintf(fp, "%lf, ", (double)duration_average / (n * n));
    }

    fprintf(fp, "\n");
  }

  // Close file
  fclose(fp);
  return 0;
}

int check_result(int *result1, int *result2, int dim) {
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      if (result1[i * dim + j] != result2[i * dim + j]) {
        return 1;
      }
    }
  }
  return 0;
}

void print_result(int *result1, int *result2, int dim) {
  printf("result1 = \n");
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      printf("%4d ", result1[i * dim + j]);
    }
    printf("\n");
  }
  printf("result2 = \n");
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      printf("%4d ", result2[i * dim + j]);
    }
    printf("\n");
  }
}

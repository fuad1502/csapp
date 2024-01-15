#include "convert.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h>

#define START_N 10
#define END_N 4000
#define STEP_N 100
#define F_NUM 2
#define WARM_UP 1
#define AVERAGING 10

typedef void (*convert_f)(int *, int);
convert_f f[F_NUM] = {&convert_naive, &convert_optimized};
char *f_name[F_NUM] = {"convert_naive", "convert_optimized"};
int check_result(int *result1, int *result2, int dim);
void print_result(int *result1, int *result2, int dim);
int G[F_NUM][END_N * END_N];
int G_in[END_N * END_N];

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
      int val = rand() % 2;
      for (int k = 0; k < F_NUM; k++) {
        G_in[i * END_N + j] = val;
      }
    }
  }

  for (int n = START_N; n <= END_N; n += STEP_N) {
    int dim = n;
    fprintf(fp, "%d, ", n);

    // Benchmark all functions
    for (int i = 0; i < F_NUM; i++) {
      // Warm up cache
      for (int j = 0; j < WARM_UP; j++) {
        f[i]((int *)G[i], n);
      }
      // Benchmark function
      uint64_t duration_average = 0;
      for (int j = 0; j < AVERAGING; j++) {
        uint64_t begin = __rdtsc();
        f[i]((int *)G[i], n);
        uint64_t end = __rdtsc();
        uint64_t duration = (end - begin);
        duration_average = (duration_average * j + duration) / (j + 1);
      }
      // Check result
      if (i > 0) {
        if (check_result(G[i], G[i - 1], dim) != 0) {
          printf("Incorrect result! (%d)\n", n);
          print_result(G[i], G[i - 1], dim);
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

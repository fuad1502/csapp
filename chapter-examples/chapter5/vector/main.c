#include "operation.h"
#include "vector.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h>

#define START_N 32
#define END_N 8192
#define STEP_N 64
#define F_NUM 17
#define AVERAGING 256

typedef void (*combine_f)(vec_ptr, data_t *);
combine_f f[F_NUM] = {&combine1,         &combine2,        &combine3,
                      &combine4,         &combine5_2x1,    &combine5_3x1,
                      &combine5_5x1,     &combine6_2x2,    &combine6_3x3,
                      &combine6_5x5,     &combine6_10x10,  &combine7_2x1a,
                      &combine7_3x1a,    &combine7_5x1a,   &combine7_10x1a,
                      &combine8_4x4_vec, &combine8_8x8_vec};
char *f_name[F_NUM] = {
    "combine1",           "combine2",           "combine3",
    "combine4",           "combine5 (2 x 1)",   "combine5 (3 x 1)",
    "combine5 (5 x 1)",   "combine6 (2 x 2)",   "combine6 (3 x 3)",
    "combine6 (5 x 5)",   "combine6 (10 x 10)", "combine7 (2 x 1a)",
    "combine7 (3 x 1a)",  "combine7 (5 x 1a)",  "combine7 (10 x 1a)",
    "combine8 (4 x 4 v)", "combine8 (8 x 8 v)"};

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <output file>\n", argv[0]);
    return 1;
  }

  // Open output file
  FILE *fp;
  fp = fopen(argv[1], "w");
  fprintf(fp, "n, ");
  for (int i = 0; i < F_NUM; i++) {
    fprintf(fp, "%s, ", f_name[i]);
  }
  fprintf(fp, "\n");

  // Benchmark for different vector sizes
  for (int n = START_N; n <= END_N; n += STEP_N) {
    // Write vector size to output file
    fprintf(fp, "%d, ", n);

    // Create vector
    vec_ptr v = new_vec(n);
    if (v == NULL) {
      printf("Vector NULL!\n");
      exit(1);
    }
    for (int i = 0; i < vec_length(v); i++) {
      if (set_vec_element(v, i, i + 1) == 0) {
        printf("Set Vector NULL!\n");
        exit(1);
      }
    }

    // Benchmark all functions
    for (int i = 0; i < F_NUM; i++) {
      uint64_t duration_average = 0;
      for (int j = 0; j < AVERAGING; j++) {
        data_t data;
        uint64_t begin = __rdtsc();
        f[i](v, &data);
        uint64_t end = __rdtsc();
        uint64_t duration = (end - begin);
        duration_average = (duration_average * j + duration) / (j + 1);
      }
      // Write duration average to output file
      fprintf(fp, "%ld, ", duration_average);
    }

    // Free vector
    fprintf(fp, "\n");
    free(v->data);
    free(v);
  }

  // Close file
  fclose(fp);
  return 0;
}

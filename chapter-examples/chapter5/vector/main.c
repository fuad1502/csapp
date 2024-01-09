#include "operation.h"
#include "vector.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h>

#define MAX_N 1000000
#define STEP_N 10000
#define F_NUM 15

typedef void (*combine_f)(vec_ptr, data_t *);
combine_f f[F_NUM] = {&combine1,      &combine2,       &combine3,
                      &combine4,      &combine5_2x1,   &combine5_3x1,
                      &combine5_5x1,  &combine6_2x2,   &combine6_3x3,
                      &combine6_5x5,  &combine6_10x10, &combine7_2x1a,
                      &combine7_3x1a, &combine7_5x1a,  &combine7_10x1a};
char *f_name[F_NUM] = {
    "combine1",          "combine2",           "combine3",
    "combine4",          "combine5 (2 x 1)",   "combine5 (3 x 1)",
    "combine5 (5 x 1)",  "combine6 (2 x 2)",   "combine6 (3 x 3)",
    "combine6 (5 x 5)",  "combine6 (10 x 10)", "combine7 (2 x 1a)",
    "combine7 (3 x 1a)", "combine7 (5 x 1a)",  "combine7 (10 x 1a)"};

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
  for (int n = 1; n < MAX_N; n += STEP_N) {
    // Write vector size to output file
    fprintf(fp, "%d, ", n);

    // Create vector
    vec_ptr v = new_vec(n);
    for (int i = 0; i < vec_length(v); i++) {
      set_vec_element(v, i, rand());
    }

    // Benchmark all functions
    for (int i = 0; i < F_NUM; i++) {
      data_t data;
      uint64_t begin = __rdtsc();
      f[i](v, &data);
      uint64_t end = __rdtsc();
      uint64_t duration = (end - begin);

      // Write duration to output file
      fprintf(fp, "%ld, ", duration);
    }

    // Free vector
    fprintf(fp, "\n");
    free(v);
  }

  // Close file
  fclose(fp);
  return 0;
}

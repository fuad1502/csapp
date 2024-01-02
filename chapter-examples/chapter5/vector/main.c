#include "operation.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 1000000
#define STEP_N 10000
#define F_NUM 3

typedef void (*combine_f)(vec_ptr, data_t *);
combine_f f[F_NUM] = {&combine1, &combine2, &combine3};
char *f_name[F_NUM] = {"combine1", "combine2", "combine3"};

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
      clock_t begin = clock();
      f[i](v, &data);
      clock_t end = clock();
      long duration = (end - begin);

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

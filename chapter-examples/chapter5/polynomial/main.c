#include <stdint.h>
#include <stdio.h>
#include <x86intrin.h>

#define MAX_N 1000000
#define STEP_N 10000

double poly(double a[], double x, long degree);
double polyh(double a[], double x, long degree);

uint64_t rdtsc() {
  unsigned int lo, hi;
  __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
  return ((uint64_t)hi << 32) | lo;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <output file>\n", argv[0]);
    return 1;
  }

  FILE *fp;
  fp = fopen(argv[1], "w");
  fprintf(fp, "n, ");
  fprintf(fp, "%s, ", "Normal method");
  fprintf(fp, "%s, ", "Horner's method");
  fprintf(fp, "\n");

  for (int n = 0; n < MAX_N; n += STEP_N) {
    fprintf(fp, "%d, ", n);

    double a[n];
    for (int i = 0; i < n; i++) {
      a[i] = (double)rand() / RAND_MAX;
    }
    double x = (double)rand() / RAND_MAX;

    uint64_t begin = rdtsc();
    poly(a, x, n);
    uint64_t end = rdtsc();
    uint64_t duration = (end - begin);
    fprintf(fp, "%ld, ", duration);

    begin = rdtsc();
    polyh(a, x, n);
    end = rdtsc();
    duration = (end - begin);
    fprintf(fp, "%ld, ", duration);

    fprintf(fp, "\n");
  }
  return 0;
}

double poly(double a[], double x, long degree) {
  long i;
  double result = a[0];
  double xpwr = x; /* Equals x^i at start of loop */
  for (i = 1; i <= degree; i++) {
    result += a[i] * xpwr;
    xpwr = x * xpwr;
  }
  return result;
}

double polyh(double a[], double x, long degree) {
  long i;
  double result = a[degree];
  for (i = degree - 1; i >= 0; i--)
    result = a[i] + x * result;
  return result;
}

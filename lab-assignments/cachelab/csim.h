#ifndef CSIM_H
#define CSIM_H

#include <stdio.h>

typedef struct {
  int valid;
  int tag;
} cache_line_t;

typedef struct {
  cache_line_t *cache_lines;
} cache_set_t;

typedef struct {
  cache_set_t *cache_sets;
  int b;
  int s;
} cache_t;

typedef enum { L, S, M } op_t;

typedef struct {
  op_t op;
  unsigned long addr;
} trace_line_t;

int parse_trace_file(FILE *trace_file, trace_line_t trace_lines[]);
void simulate_cache(cache_t *cache, trace_line_t trace_line, int *hits,
                    int *misses, int *evictions);

#endif // CSIM_H

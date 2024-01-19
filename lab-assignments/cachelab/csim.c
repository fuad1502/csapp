#define _GNU_SOURCE
#include "csim.h"
#include "cachelab.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_TRACE_LINES 1000000

trace_line_t trace_lines[MAX_TRACE_LINES];

int main(int argc, char *argv[]) {
  // Parse command line arguments
  unsigned long s, E, b;
  FILE *trace_file;
  int set_s = 0, set_E = 0, set_b = 0, set_t = 0;
  int opt;
  while ((opt = getopt(argc, argv, "s:E:b:t:")) != -1) {
    switch (opt) {
    case 's': {
      s = atol(optarg);
      set_s = 1;
    } break;
    case 'E':
      E = atol(optarg);
      set_E = 1;
      break;
    case 'b': {
      b = atol(optarg);
      set_b = 1;
    } break;
    case 't':
      trace_file = fopen(optarg, "r");
      set_t = 1;
      break;
    case '?':
      fprintf(stderr, "Failed to parse arguments\n");
      exit(1);
      break;
    }
  }
  b = b;
  if (!set_s || !set_E || !set_b || !set_t) {
    fprintf(stderr, "Missing required arguments\n");
    exit(1);
  }

  // Create cache
  unsigned long S = (2 << s);
  cache_set_t *cache_sets = calloc(S, sizeof(cache_set_t));
  for (int i = 0; i < S; i++) {
    cache_sets[i].cache_lines = calloc(E, sizeof(cache_line_t));
  }
  cache_t cache;
  cache.cache_sets = cache_sets;
  cache.s = s;
  cache.b = b;

  // Parse trace file
  int n_trace_lines = parse_trace_file(trace_file, trace_lines);
  n_trace_lines = n_trace_lines;

  // Simulate cache
  int hits = 0, misses = 0, evictions = 0;
  for (int i = 0; i < n_trace_lines; i++) {
    simulate_cache(&cache, trace_lines[i], &hits, &misses, &evictions);
  }

  // Print summary
  printSummary(hits, misses, evictions);

  // Free cache
  for (int i = 0; i < S; i++) {
    free(cache.cache_sets[i].cache_lines);
  }
  free(cache.cache_sets);

  // Close files
  fclose(trace_file);
  return 0;
}

int parse_trace_file(FILE *trace_file, trace_line_t trace_lines[]) {
  char *line = NULL;
  size_t n = 0;
  int i = 0;
  while (getline(&line, &n, trace_file) != -1) {
    if (i >= MAX_TRACE_LINES) {
      printf(
          "Parse trace file failed: exceeded maximum number of trace lines\n");
      exit(1);
    }
    if (line[0] == 'I') {
      continue;
    }
    switch (line[1]) {
    case 'L':
      trace_lines[i].op = L;
      break;
    case 'S':
      trace_lines[i].op = S;
      break;
    case 'M':
      trace_lines[i].op = M;
      break;
    default:
      printf("Parse trace file failed: unknown operation %c\n", line[1]);
      exit(1);
      break;
    }
    char *addr_str = line + 3;
    char *delim = strchr(addr_str, ',');
    *delim = 0;
    trace_lines[i].addr = strtoul(addr_str, NULL, 16);
    i++;
  }
  free(line);
  return i;
}

void simulate_cache(cache_t *cache, trace_line_t trace_line, int *n_hits,
                    int *n_miss, int *n_evicted) {}

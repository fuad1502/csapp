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
  unsigned long S = (1 << s);
  cache_set_t *cache_sets = calloc(S, sizeof(cache_set_t));
  for (int i = 0; i < S; i++) {
    cache_sets[i].cache_lines = calloc(E, sizeof(cache_line_t));
  }
  cache_t cache;
  cache.cache_sets = cache_sets;
  cache.s = s;
  cache.E = E;
  cache.b = b;

  // Parse trace file
  int n_trace_lines = parse_trace_file(trace_file, trace_lines);
  n_trace_lines = n_trace_lines;

  // Simulate cache
  int hits = 0, misses = 0, evictions = 0;
  for (int i = 0; i < n_trace_lines; i++) {
    simulate_cache(&cache, trace_lines[i], &hits, &misses, &evictions);
    // Perform cache simulation twice for 'Modify' operation
    if (trace_lines[i].op == M) {
      simulate_cache(&cache, trace_lines[i], &hits, &misses, &evictions);
    }
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

void simulate_cache(cache_t *cache, trace_line_t trace_line, int *hits,
                    int *misses, int *evictions) {
  // Decode set index and tag value from address
  unsigned long curr_set_idx =
      (trace_line.addr >> cache->b) & ((1 << cache->s) - 1);
  unsigned long curr_tag = (trace_line.addr >> (cache->b + cache->s));
  cache_set_t *curr_set = &cache->cache_sets[curr_set_idx];

  // Check if cache entry exist and update cache line age
  int hit = 0;
  for (int i = 0; i < cache->E; i++) {
    if (curr_set->cache_lines[i].valid &&
        curr_set->cache_lines[i].tag == curr_tag) {
      curr_set->cache_lines[i].age = 0;
      *hits += 1;
      hit = 1;
    } else if (curr_set->cache_lines[i].valid) {
      curr_set->cache_lines[i].age += 1;
    }
  }

  // Return if hit
  if (hit) {
    return;
  }
  // Miss
  *misses += 1;

  // Find LRU cache line or empty cache line
  int max_age = -1;
  int evict_line_idx = -1;
  for (int i = 0; i < cache->E; i++) {
    if (curr_set->cache_lines[i].valid == 0) {
      // Found empty cache line
      curr_set->cache_lines[i].tag = curr_tag;
      curr_set->cache_lines[i].valid = 1;
      curr_set->cache_lines[i].age = 0;
      return;
    } else if (curr_set->cache_lines[i].age > max_age) {
      max_age = curr_set->cache_lines[i].age;
      evict_line_idx = i;
    }
  }

  // Evict and update cache line
  printf("Evict line %d\n", evict_line_idx);
  *evictions += 1;
  curr_set->cache_lines[evict_line_idx].tag = curr_tag;
  curr_set->cache_lines[evict_line_idx].age = 0;
}

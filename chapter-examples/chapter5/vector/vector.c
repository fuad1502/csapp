#include "vector.h"
#include <stdlib.h>

vec_ptr new_vec(long len) {
  vec_ptr result = (vec_ptr)malloc(sizeof(vec_rec));
  if (result == NULL) {
    // Cannot allocate memory for vector
    return NULL;
  }
  // Initilize member
  result->len = len;
  result->data = NULL;
  // Allocate vector data
  if (len > 0) {
    data_t *data = (data_t *)calloc(len, sizeof(data_t));
    if (data == NULL) {
      // Cannot allocate vector data
      free(result);
      return NULL;
    }
    result->data = data;
  }
  return result;
}

int get_vec_element(vec_ptr v, long index, data_t *dest) {
  if (index < 0 || index >= v->len) {
    // Index out of bounds
    return 0;
  }
  *dest = v->data[index];
  return 1;
}

int set_vec_element(vec_ptr v, long index, data_t data) {
  if (index < 0 || index >= v->len) {
    // Index out of bounds
    return 0;
  }
  v->data[index] = data;
  return 1;
}

long vec_length(vec_ptr v) { return v->len; }

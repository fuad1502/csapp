#include "operation.h"
#include "vector.h"

void combine1(vec_ptr v, data_t *dest) {
  *dest = INDENT;
  long i;
  for (i = 0; i < vec_length(v); i++) {
    data_t val;
    get_vec_element(v, i, &val);
    *dest = *dest OP val;
  }
}

void combine2(vec_ptr v, data_t *dest) {
  *dest = INDENT;
  long i;
  long length = vec_length(v);
  for (i = 0; i < length; i++) {
    data_t val;
    get_vec_element(v, i, &val);
    *dest = *dest OP val;
  }
}
void combine3(vec_ptr v, data_t *dest) {
  *dest = INDENT;
  long i;
  long length = vec_length(v);
  for (i = 0; i < length; i++) {
    *dest = *dest OP v->data[i];
  }
}
void combine4(vec_ptr v, data_t *dest) {
  *dest = INDENT;
  long i;
  long length = vec_length(v);
  data_t result = INDENT;
  for (i = 0; i < length; i++) {
    result = result OP v->data[i];
  }
  *dest = result;
}

void combine5_2x1(vec_ptr v, data_t *dest) {
  long length = vec_length(v);
  long i;
  data_t result = INDENT;
  for (i = 0; i < length - 1; i += 2) {
    result = result OP v->data[i];
    result = result OP v->data[i + 1];
  }
  for (i = length - 1; i < length; i++) {
    result = result OP v->data[i];
  }
  *dest = result;
}

void combine5_3x1(vec_ptr v, data_t *dest) {
  long length = vec_length(v);
  long i;
  data_t result = INDENT;
  for (i = 0; i < length - 2; i += 3) {
    result = result OP v->data[i];
    result = result OP v->data[i + 1];
    result = result OP v->data[i + 2];
  }
  for (i = length - 2; i < length; i++) {
    result = result OP v->data[i];
  }
  *dest = result;
}

void combine5_5x1(vec_ptr v, data_t *dest) {
  long length = vec_length(v);
  long i;
  data_t result = INDENT;
  for (i = 0; i < length - 4; i += 5) {
    result = result OP v->data[i];
    result = result OP v->data[i + 1];
    result = result OP v->data[i + 2];
    result = result OP v->data[i + 3];
    result = result OP v->data[i + 4];
  }
  for (i = length - 4; i < length; i++) {
    result = result OP v->data[i];
  }
  *dest = result;
}

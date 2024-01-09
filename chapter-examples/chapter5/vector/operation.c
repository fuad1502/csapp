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

void combine6_2x2(vec_ptr v, data_t *dest) {
  long length = vec_length(v);
  long i;
  data_t acc1 = INDENT;
  data_t acc2 = INDENT;
  for (i = 0; i < length - 1; i += 2) {
    acc1 = acc1 OP v->data[i];
    acc2 = acc2 OP v->data[i + 1];
  }
  data_t result = acc1 OP acc2;
  for (i = length - 1; i < length; i++) {
    result = result OP v->data[i];
  }
  *dest = result;
}

void combine6_3x3(vec_ptr v, data_t *dest) {
  long length = vec_length(v);
  long i;
  data_t acc1 = INDENT;
  data_t acc2 = INDENT;
  data_t acc3 = INDENT;
  for (i = 0; i < length - 2; i += 3) {
    acc1 = acc1 OP v->data[i];
    acc2 = acc2 OP v->data[i + 1];
    acc3 = acc3 OP v->data[i + 2];
  }
  data_t result = acc1 OP acc2 OP acc3;
  for (i = length - 2; i < length; i++) {
    result = result OP v->data[i];
  }
  *dest = result;
}

void combine6_5x5(vec_ptr v, data_t *dest) {
  long length = vec_length(v);
  long i;
  data_t acc1 = INDENT;
  data_t acc2 = INDENT;
  data_t acc3 = INDENT;
  data_t acc4 = INDENT;
  data_t acc5 = INDENT;
  for (i = 0; i < length - 4; i += 5) {
    acc1 = acc1 OP v->data[i];
    acc2 = acc2 OP v->data[i + 1];
    acc3 = acc3 OP v->data[i + 2];
    acc4 = acc4 OP v->data[i + 3];
    acc5 = acc5 OP v->data[i + 4];
  }
  data_t result = acc1 OP acc2 OP acc3 OP acc4 OP acc5;
  for (i = length - 4; i < length; i++) {
    result = result OP v->data[i];
  }
  *dest = result;
}

void combine6_10x10(vec_ptr v, data_t *dest) {
  long length = vec_length(v);
  long i;
  data_t acc1 = INDENT;
  data_t acc2 = INDENT;
  data_t acc3 = INDENT;
  data_t acc4 = INDENT;
  data_t acc5 = INDENT;
  data_t acc6 = INDENT;
  data_t acc7 = INDENT;
  data_t acc8 = INDENT;
  data_t acc9 = INDENT;
  data_t acc10 = INDENT;
  for (i = 0; i < length - 9; i += 10) {
    acc1 = acc1 OP v->data[i];
    acc2 = acc2 OP v->data[i + 1];
    acc3 = acc3 OP v->data[i + 2];
    acc4 = acc4 OP v->data[i + 3];
    acc5 = acc5 OP v->data[i + 4];
    acc6 = acc6 OP v->data[i + 5];
    acc7 = acc7 OP v->data[i + 6];
    acc8 = acc8 OP v->data[i + 7];
    acc9 = acc9 OP v->data[i + 8];
    acc10 = acc10 OP v->data[i + 9];
  }
  data_t result = acc1 OP acc2 OP acc3 OP acc4 OP acc5;
  result = result OP acc6 OP acc7 OP acc8 OP acc9 OP acc10;
  for (i = length - 9; i < length; i++) {
    result = result OP v->data[i];
  }
  *dest = result;
}

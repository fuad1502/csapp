#include "operation.h"
#include "vector.h"
#include <immintrin.h>

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
  for (; i < length; i++) {
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
  for (; i < length; i++) {
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
  for (; i < length; i++) {
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
  for (; i < length; i++) {
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
  for (; i < length; i++) {
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
  for (; i < length; i++) {
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
  for (; i < length; i++) {
    result = result OP v->data[i];
  }
  *dest = result;
}

void combine7_2x1a(vec_ptr v, data_t *dest) {
  long length = vec_length(v);
  long i;
  data_t result = INDENT;
  for (i = 0; i < length - 1; i += 2) {
    data_t temp = v->data[i] OP v->data[i + 1];
    result = result OP temp;
  }
  for (; i < length; i++) {
    result = result OP v->data[i];
  }
  *dest = result;
}

void combine7_3x1a(vec_ptr v, data_t *dest) {
  long length = vec_length(v);
  long i;
  data_t result = INDENT;
  for (i = 0; i < length - 2; i += 3) {
    data_t temp = v->data[i + 1] OP v->data[i + 2];
    temp = temp OP v->data[i];
    result = result OP temp;
  }
  for (; i < length; i++) {
    result = result OP v->data[i];
  }
  *dest = result;
}

void combine7_5x1a(vec_ptr v, data_t *dest) {
  long length = vec_length(v);
  long i;
  data_t result = INDENT;
  for (i = 0; i < length - 4; i += 5) {
    data_t temp = v->data[i + 3] OP v->data[i + 4];
    temp = temp OP v->data[i + 2];
    temp = temp OP v->data[i + 1];
    temp = temp OP v->data[i];
    result = result OP temp;
  }
  for (; i < length; i++) {
    result = result OP v->data[i];
  }
  *dest = result;
}

void combine7_10x1a(vec_ptr v, data_t *dest) {
  long length = vec_length(v);
  long i;
  data_t result = INDENT;
  for (i = 0; i < length - 9; i += 10) {
    data_t temp = v->data[i + 8] OP v->data[i + 9];
    temp = temp OP v->data[i + 7];
    temp = temp OP v->data[i + 6];
    temp = temp OP v->data[i + 5];
    temp = temp OP v->data[i + 4];
    temp = temp OP v->data[i + 3];
    temp = temp OP v->data[i + 2];
    temp = temp OP v->data[i + 1];
    temp = temp OP v->data[i];
    result = result OP temp;
  }
  for (; i < length; i++) {
    result = result OP v->data[i];
  }
  *dest = result;
}

#if DATA_T == LONG

typedef __m256i __m256x;
typedef __m256i mem_ptr_t;
#define PACKING 4
#define _mm256_set1_x _mm256_set1_epi64x
#define _mm256_loadu_x _mm256_loadu_si256
#define _mm256_storeu_x _mm256_storeu_si256

#if OPSTR == ADD
#define _mm256_op_x _mm256_add_epi64
#else
#endif

#elif DATA_T == DOUBLE

typedef __m256d __m256x;
typedef double mem_ptr_t;
#define PACKING 4
#define _mm256_set1_x _mm256_set1_pd
#define _mm256_loadu_x _mm256_loadu_pd
#define _mm256_storeu_x _mm256_storeu_pd

#if OPSTR == ADD
#define _mm256_op_x _mm256_add_pd
#elif OPSTR == MUL
#define _mm256_op_x _mm256_mul_pd
#else
#endif

#elif DATA_T == INT

typedef __m256i __m256x;
typedef __m256i mem_ptr_t;
#define PACKING 8
#define _mm256_set1_x _mm256_set1_epi32
#define _mm256_loadu_x _mm256_loadu_si256
#define _mm256_storeu_x _mm256_storeu_si256

#if OPSTR == ADD
#define _mm256_op_x _mm256_add_epi32
#elif OPSTR == MUL
#define _mm256_op_x _mm256_mullo_epi32
#else
#endif

#else
#endif

#if DATA_T == LONG && OPSTR == MUL
void combine8_4x4_vec(vec_ptr v, data_t *dest) {
  long length = vec_length(v);
  long i;
  data_t acc1 = INDENT;
  data_t acc2 = INDENT;
  data_t acc3 = INDENT;
  data_t acc4 = INDENT;
  for (i = 0; i < length - 3; i += 4) {
    acc1 = acc1 OP v->data[i];
    acc2 = acc2 OP v->data[i + 1];
    acc3 = acc3 OP v->data[i + 2];
    acc4 = acc4 OP v->data[i + 3];
  }
  data_t result = acc1 OP acc2 OP acc3 OP acc4;
  for (; i < length; i++) {
    result = result OP v->data[i];
  }
  *dest = result;
}
#else
void combine8_4x4_vec(vec_ptr v, data_t *dest) {
  long length = vec_length(v);
  long i;
  __m256x acc_vec1 = _mm256_set1_x(INDENT);
  __m256x acc_vec2 = _mm256_set1_x(INDENT);
  __m256x acc_vec3 = _mm256_set1_x(INDENT);
  __m256x acc_vec4 = _mm256_set1_x(INDENT);
  for (i = 0; i < length - (PACKING * 4 - 1); i += PACKING * 4) {
    __m256x data1 = _mm256_loadu_x((mem_ptr_t *)&v->data[i]);
    __m256x data2 = _mm256_loadu_x((mem_ptr_t *)&v->data[i + PACKING]);
    __m256x data3 = _mm256_loadu_x((mem_ptr_t *)&v->data[i + PACKING * 2]);
    __m256x data4 = _mm256_loadu_x((mem_ptr_t *)&v->data[i + PACKING * 3]);
    acc_vec1 = _mm256_op_x(acc_vec1, data1);
    acc_vec2 = _mm256_op_x(acc_vec2, data2);
    acc_vec3 = _mm256_op_x(acc_vec3, data3);
    acc_vec4 = _mm256_op_x(acc_vec4, data4);
  }
  acc_vec1 = _mm256_op_x(acc_vec1, acc_vec2);
  acc_vec1 = _mm256_op_x(acc_vec1, acc_vec3);
  acc_vec1 = _mm256_op_x(acc_vec1, acc_vec4);
  data_t acc[PACKING];
  _mm256_storeu_x((mem_ptr_t *)acc, acc_vec1);
  data_t result = acc[0];
  for (int j = 1; j < PACKING; j++) {
    result = result OP acc[j];
  }
  for (; i < length; i++) {
    result = result OP v->data[i];
  }
  *dest = result;
}
#endif

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

#if OPSTR == ADD
#if DATA_T == LONG
void combine8_4x4_vec(vec_ptr v, data_t *dest) {
  long length = vec_length(v);
  long i;
  __m256i acc_vec1 = _mm256_set1_epi64x(INDENT);
  __m256i acc_vec2 = _mm256_set1_epi64x(INDENT);
  __m256i acc_vec3 = _mm256_set1_epi64x(INDENT);
  __m256i acc_vec4 = _mm256_set1_epi64x(INDENT);
  __m256i zeros = _mm256_set1_epi64x(0xFFFFFFFFFFFFFFFF);
  for (i = 0; i < length - 15; i += 16) {
    __m256i data1 =
        _mm256_maskload_epi64((const long long *)&v->data[i], zeros);
    __m256i data2 =
        _mm256_maskload_epi64((const long long *)&v->data[i + 4], zeros);
    __m256i data3 =
        _mm256_maskload_epi64((const long long *)&v->data[i + 8], zeros);
    __m256i data4 =
        _mm256_maskload_epi64((const long long *)&v->data[i + 12], zeros);
    acc_vec1 = _mm256_add_epi64(acc_vec1, data1);
    acc_vec2 = _mm256_add_epi64(acc_vec2, data2);
    acc_vec3 = _mm256_add_epi64(acc_vec3, data3);
    acc_vec4 = _mm256_add_epi64(acc_vec4, data4);
  }
  acc_vec1 = _mm256_add_epi64(acc_vec1, acc_vec2);
  acc_vec1 = _mm256_add_epi64(acc_vec1, acc_vec3);
  acc_vec1 = _mm256_add_epi64(acc_vec1, acc_vec4);
  data_t acc1 = _mm256_extract_epi64(acc_vec1, 0);
  data_t acc2 = _mm256_extract_epi64(acc_vec1, 1);
  data_t acc3 = _mm256_extract_epi64(acc_vec1, 2);
  data_t acc4 = _mm256_extract_epi64(acc_vec1, 3);
  data_t result = acc1 OP acc2 OP acc3 OP acc4;
  for (; i < length; i++) {
    result = result OP v->data[i];
  }
  *dest = result;
}
#elif DATA_T == DOUBLE
void combine8_4x4_vec(vec_ptr v, data_t *dest) {
  long length = vec_length(v);
  long i;
  __m256d acc_vec1 = _mm256_set1_pd(INDENT);
  __m256d acc_vec2 = _mm256_set1_pd(INDENT);
  __m256d acc_vec3 = _mm256_set1_pd(INDENT);
  __m256d acc_vec4 = _mm256_set1_pd(INDENT);
  __m256i zeros = _mm256_set1_epi64x(0xFFFFFFFFFFFFFFFF);
  for (i = 0; i < length - 15; i += 16) {
    __m256d data1 = _mm256_maskload_pd((const double *)&v->data[i], zeros);
    __m256d data2 = _mm256_maskload_pd((const double *)&v->data[i + 4], zeros);
    __m256d data3 = _mm256_maskload_pd((const double *)&v->data[i + 8], zeros);
    __m256d data4 = _mm256_maskload_pd((const double *)&v->data[i + 12], zeros);
    acc_vec1 = _mm256_add_pd(acc_vec1, data1);
    acc_vec2 = _mm256_add_pd(acc_vec2, data2);
    acc_vec3 = _mm256_add_pd(acc_vec3, data3);
    acc_vec4 = _mm256_add_pd(acc_vec4, data4);
  }
  acc_vec1 = _mm256_add_pd(acc_vec1, acc_vec2);
  acc_vec1 = _mm256_add_pd(acc_vec1, acc_vec3);
  acc_vec1 = _mm256_add_pd(acc_vec1, acc_vec4);
  data_t acc[4] __attribute__((aligned(32)));
  _mm256_store_pd(acc, acc_vec1);
  data_t result = acc[0] OP acc[1] OP acc[2] OP acc[3];
  for (; i < length; i++) {
    result = result OP v->data[i];
  }
  *dest = result;
}
#elif DATA_T == INT
void combine8_4x4_vec(vec_ptr v, data_t *dest) {
  long length = vec_length(v);
  long i;
  __m256i acc_vec1 = _mm256_set1_epi32(INDENT);
  __m256i acc_vec2 = _mm256_set1_epi32(INDENT);
  __m256i acc_vec3 = _mm256_set1_epi32(INDENT);
  __m256i acc_vec4 = _mm256_set1_epi32(INDENT);
  for (i = 0; i < length - 31; i += 32) {
    __m256i data1 = _mm256_loadu_si256((const __m256i *)&v->data[i]);
    __m256i data2 = _mm256_loadu_si256((const __m256i *)&v->data[i + 8]);
    __m256i data3 = _mm256_loadu_si256((const __m256i *)&v->data[i + 16]);
    __m256i data4 = _mm256_loadu_si256((const __m256i *)&v->data[i + 24]);
    acc_vec1 = _mm256_add_epi32(acc_vec1, data1);
    acc_vec2 = _mm256_add_epi32(acc_vec2, data2);
    acc_vec3 = _mm256_add_epi32(acc_vec3, data3);
    acc_vec4 = _mm256_add_epi32(acc_vec4, data4);
  }
  acc_vec1 = _mm256_add_epi32(acc_vec1, acc_vec2);
  acc_vec1 = _mm256_add_epi32(acc_vec1, acc_vec3);
  acc_vec1 = _mm256_add_epi32(acc_vec1, acc_vec4);
  data_t acc1 = _mm256_extract_epi32(acc_vec1, 0);
  data_t acc2 = _mm256_extract_epi32(acc_vec1, 1);
  data_t acc3 = _mm256_extract_epi32(acc_vec1, 2);
  data_t acc4 = _mm256_extract_epi32(acc_vec1, 3);
  data_t acc5 = _mm256_extract_epi32(acc_vec1, 4);
  data_t acc6 = _mm256_extract_epi32(acc_vec1, 5);
  data_t acc7 = _mm256_extract_epi32(acc_vec1, 6);
  data_t acc8 = _mm256_extract_epi32(acc_vec1, 7);
  data_t result = acc1 OP acc2 OP acc3 OP acc4 OP acc5 OP acc6 OP acc7 OP acc8;
  for (; i < length; i++) {
    result = result OP v->data[i];
  }
  *dest = result;
}
#endif
#elif OPSTR == MUL
#if DATA_T == LONG
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
#elif DATA_T == DOUBLE
void combine8_4x4_vec(vec_ptr v, data_t *dest) {
  long length = vec_length(v);
  long i;
  __m256d acc_vec1 = _mm256_set1_pd(INDENT);
  __m256d acc_vec2 = _mm256_set1_pd(INDENT);
  __m256d acc_vec3 = _mm256_set1_pd(INDENT);
  __m256d acc_vec4 = _mm256_set1_pd(INDENT);
  __m256i zeros = _mm256_set1_epi64x(0xFFFFFFFFFFFFFFFF);
  for (i = 0; i < length - 15; i += 16) {
    __m256d data1 = _mm256_maskload_pd((const double *)&v->data[i], zeros);
    __m256d data2 = _mm256_maskload_pd((const double *)&v->data[i + 4], zeros);
    __m256d data3 = _mm256_maskload_pd((const double *)&v->data[i + 8], zeros);
    __m256d data4 = _mm256_maskload_pd((const double *)&v->data[i + 12], zeros);
    acc_vec1 = _mm256_mul_pd(acc_vec1, data1);
    acc_vec2 = _mm256_mul_pd(acc_vec2, data2);
    acc_vec3 = _mm256_mul_pd(acc_vec3, data3);
    acc_vec4 = _mm256_mul_pd(acc_vec4, data4);
  }
  acc_vec1 = _mm256_mul_pd(acc_vec1, acc_vec2);
  acc_vec1 = _mm256_mul_pd(acc_vec1, acc_vec3);
  acc_vec1 = _mm256_mul_pd(acc_vec1, acc_vec4);
  data_t acc[4];
  _mm256_store_pd((double *)acc, acc_vec1);
  data_t result = acc[0] OP acc[1] OP acc[2] OP acc[3];
  for (; i < length; i++) {
    result = result OP v->data[i];
  }
  *dest = result;
}
#elif DATA_T == INT
void combine8_4x4_vec(vec_ptr v, data_t *dest) {
  long length = vec_length(v);
  long i;
  __m256i acc_vec1 = _mm256_set1_epi32(INDENT);
  __m256i acc_vec2 = _mm256_set1_epi32(INDENT);
  __m256i acc_vec3 = _mm256_set1_epi32(INDENT);
  __m256i acc_vec4 = _mm256_set1_epi32(INDENT);
  __m256i zeros = _mm256_set1_epi32(0xFFFFFFFF);
  for (i = 0; i < length - 31; i += 32) {
    __m256i data1 = _mm256_loadu_si256((const __m256i *)&v->data[i]);
    __m256i data2 = _mm256_loadu_si256((const __m256i *)&v->data[i + 8]);
    __m256i data3 = _mm256_loadu_si256((const __m256i *)&v->data[i + 16]);
    __m256i data4 = _mm256_loadu_si256((const __m256i *)&v->data[i + 24]);
    acc_vec1 = _mm256_mullo_epi32(acc_vec1, data1);
    acc_vec2 = _mm256_mullo_epi32(acc_vec2, data2);
    acc_vec3 = _mm256_mullo_epi32(acc_vec3, data3);
    acc_vec4 = _mm256_mullo_epi32(acc_vec4, data4);
  }
  acc_vec1 = _mm256_mullo_epi32(acc_vec1, acc_vec2);
  acc_vec1 = _mm256_mullo_epi32(acc_vec1, acc_vec3);
  acc_vec1 = _mm256_mullo_epi32(acc_vec1, acc_vec4);
  data_t acc1 = _mm256_extract_epi32(acc_vec1, 0);
  data_t acc2 = _mm256_extract_epi32(acc_vec1, 1);
  data_t acc3 = _mm256_extract_epi32(acc_vec1, 2);
  data_t acc4 = _mm256_extract_epi32(acc_vec1, 3);
  data_t acc5 = _mm256_extract_epi32(acc_vec1, 4);
  data_t acc6 = _mm256_extract_epi32(acc_vec1, 5);
  data_t acc7 = _mm256_extract_epi32(acc_vec1, 6);
  data_t acc8 = _mm256_extract_epi32(acc_vec1, 7);
  data_t result = acc1 OP acc2 OP acc3 OP acc4 OP acc5 OP acc6 OP acc7 OP acc8;
  for (; i < length; i++) {
    result = result OP v->data[i];
  }
  *dest = result;
}
#endif
#else
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
#endif

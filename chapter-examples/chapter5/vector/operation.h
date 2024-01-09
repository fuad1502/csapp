#ifndef OPERATION_H
#define OPERATION_H
#include "vector.h"

#define ADD 1
#define MUL 2

#ifndef OPSTR
#define OPSTR ADD
#endif // !OPSTR

#if OPSTR == ADD
#define OP +
#define INDENT 0
#elif OPSTR == MUL
#define OP *
#define INDENT 1
#else
#define OP +
#define INDENT 0
#endif // !OPSTR

void combine1(vec_ptr v, data_t *dest);
void combine2(vec_ptr v, data_t *dest);
void combine3(vec_ptr v, data_t *dest);
void combine4(vec_ptr v, data_t *dest);
void combine5_2x1(vec_ptr v, data_t *dest);
void combine5_3x1(vec_ptr v, data_t *dest);
void combine5_5x1(vec_ptr v, data_t *dest);
void combine6_2x2(vec_ptr v, data_t *dest);
void combine6_3x3(vec_ptr v, data_t *dest);
void combine6_5x5(vec_ptr v, data_t *dest);
void combine6_10x10(vec_ptr v, data_t *dest);
void combine7_2x1a(vec_ptr v, data_t *dest);
void combine7_3x1a(vec_ptr v, data_t *dest);
void combine7_5x1a(vec_ptr v, data_t *dest);
void combine7_10x1a(vec_ptr v, data_t *dest);
void combine8_4x4_vec(vec_ptr v, data_t *dest);

#endif // !OPERATION_H

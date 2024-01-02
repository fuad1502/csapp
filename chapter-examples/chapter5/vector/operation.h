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

#endif // !OPERATION_H

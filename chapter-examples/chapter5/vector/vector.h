#ifndef VECTOR_H
#define VECTOR_H

#define LONG 0
#define DOUBLE 1

#ifndef DATA_T
#define DATA_T LONG
#endif // !DATA_T

#if DATA_T == LONG
typedef long data_t;
#elif DATA_T == DOUBLE
typedef double data_t;
#else
typedef long data_t;
#endif

typedef struct {
  long len;
  data_t *data;
} vec_rec, *vec_ptr;

vec_ptr new_vec(long len);

int get_vec_element(vec_ptr v, long index, data_t *dest);

int set_vec_element(vec_ptr v, long index, data_t data);

long vec_length(vec_ptr v);
#endif // !VECTOR_H

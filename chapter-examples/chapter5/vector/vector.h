#ifndef VECTOR_H
#define VECTOR_H

#ifndef DATA_T
typedef long data_t;
#else
typedef DATA_T data_t;
#endif // !DATA_T

typedef struct {
  long len;
  data_t *data;
} vec_rec, *vec_ptr;

vec_ptr new_vec(long len);

int get_vec_element(vec_ptr v, long index, data_t *dest);

int set_vec_element(vec_ptr v, long index, data_t data);

long vec_length(vec_ptr v);
#endif // !VECTOR_H

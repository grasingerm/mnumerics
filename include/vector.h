#ifndef __MNMVECTOR_H__
#define __MNMVECTOR_H__

#include <stddef.h>

struct mnm_vector
{
  unsigned int n_avail;
  unsigned int n_elems;
  double* data;
};

enum mnm_codes { MNM_SUCCESS, MNM_DIM_ERROR };

struct mnm_vector* mnm_vec_alloc (const unsigned int size);

void mnm_vec_destroy (struct mnm_vector* vec);

void mnm_vec_resize (struct mnm_vector* vec, const unsigned int new_size);

double mnm_vec_mag (const struct mnm_vector* vec);

void mnm_vec_zero (struct mnm_vector* vec);

int mnm_vec_add2 (const struct mnm_vector* u, const struct mnm_vector* v, 
  struct mnm_vector* result);

int mnm_vec_add (const unsigned int n, struct mnm_vector* result, ...);

int mnm_vec_dot (const struct mnm_vector* u, const struct mnm_vector* v, 
  double* res);

bool mnm_vec_equal (const struct mnm_vector* u, const struct mnm_vector* v, 
  const double tol);

// TODO: make this work for arbitrary size mnm_vector
int mnm_vec_to_str (const struct mnm_vector* vec, char* buffer, 
  const size_t buffer_sz);

#endif

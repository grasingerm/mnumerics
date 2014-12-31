#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

//! Allocate a vector on the heap
//!
//! \param size Size of vector
//! \return Pointer to vector
struct mnm_vector* mnm_vec_alloc (const unsigned int size)
{
  struct mnm_vector* vec = (struct mnm_vector *) 
    malloc (sizeof (struct mnm_vector));
  if (vec == NULL) return NULL;

  double* new_d = (double *) malloc (sizeof (double) * size);
  if (new_d == NULL)
  {
    free (vec);
    return NULL;
  }

  vec -> data = new_d;
  vec -> n_avail = size;
  vec -> n_elems = size;

  return vec;
}

//! Deallocate vector
//!
//! \param vec Pointer to vector
void mnm_vec_destroy (struct mnm_vector* vec)
{
  free (vec -> data);
  free (vec);
}

//! Resize a vector
//!
//! \param vec Pointer to vector to resize
//! \param new_size New size of vector
void mnm_vec_resize (struct mnm_vector* vec, const unsigned int new_size)
{
  if (new_size <= vec -> n_avail)
    vec -> n_elems = new_size;
  else
  {
    free (vec -> data); // do not need to check for NULL here as C std says so
    vec -> data = (double *) malloc (sizeof (double) * new_size);
    if (vec -> data == NULL)
    {
      vec -> n_avail = 0;
      vec -> n_elems = 0;
    }
    else
    {
      vec -> n_avail = new_size;
      vec -> n_elems = new_size;
    }
  }
}

//! Magnitude of vector
//!
//! \param vec Pointer to vector
//! \return Magnitude of vector
double mnm_vec_mag (const struct mnm_vector* vec)
{
  unsigned int i;
  double sumsq = 0;

  for (i = 0; i < vec -> n_elems; i++)
    sumsq += (vec -> data [i] * vec -> data [i]);

  return sqrt (sumsq);
}

//! Set all element of a vector to zero
//!
//! \param vec Pointer to vector to zero
void mnm_vec_zero (struct mnm_vector* vec)
{
  unsigned int i;
  for (i = 0; i < vec -> n_elems; i++)
    vec -> data [i] = 0;
}

//! Add two vectors
//!
//! \param u First vector in addition
//! \param v Second vector in addition
//! \param result Pointer to where to store result
//! \return Error code indicating status of calculation
int mnm_vec_add2 (const struct mnm_vector* u, const struct mnm_vector* v, 
  struct mnm_vector* result)
{
  unsigned int i;

  if (u -> n_elems != v -> n_elems || u -> n_elems != result -> n_elems)
    return MNM_DIM_ERROR;

  mnm_vec_zero (result);

  for (i = 0; i < u -> n_elems; i++)
    result -> data [i] = u -> data [i] + v -> data [i];

  return MNM_SUCCESS;
}

//! Add an arbitrary number of vectors together
//!
//! \param n Number of vectors to add
//! \param result Pointer to where to store result
//! \param ... Pointers to vectors in which to add
//! \return Error code indicating status of calculation
int mnm_vec_add (const unsigned int n, struct mnm_vector* result, ...)
{
  va_list args;
  unsigned int i, a, dim = result -> n_elems;
  struct mnm_vector* pv;

  mnm_vec_zero (result);

  va_start (args, result);

  for (i = 0; i < n; i++)
  {
    pv = va_arg (args, struct mnm_vector*);

    if (pv -> n_elems != dim)
      return MNM_DIM_ERROR;

    for (a = 0; a < dim; a++)
      result -> data [a] += pv -> data [a];
  }

  va_end (args);

  return MNM_SUCCESS;
}

//! Calculate dot product of two vectors
//!
//! \param u Pointer to vector
//! \param v Pointer to vector
//! \param res Pointer to where to store result
//! \return Error code indicating status of calculation
int mnm_vec_dot (const struct mnm_vector* u, const struct mnm_vector* v, 
  double* res)
{
  unsigned int i;
  double sum = 0;

  if (u -> n_elems != v -> n_elems)
    return MNM_DIM_ERROR;

  for (i = 0; i < u -> n_elems; i++)
    sum += u -> data [i] * v -> data [i];

  *res = sum;
  return MNM_SUCCESS;
}

//! Test two vectors for equality
//!
//! \param u Pointer to vector
//! \param v Pointer to vector
//! \param tol Tolerance in which to test
//! \return True if equal
bool mnm_vec_equal (const struct mnm_vector* u, const struct mnm_vector* v, 
  const double tol)
{
  unsigned int i;

  if (u -> n_elems != v -> n_elems)
    return false;

  for (i = 0; i < u -> n_elems; i++)
    if (abs (u->data[i] - v->data[i]) > tol)
      return false;

  return true;
}

// TODO: make this work for arbitrary size mnm_vector
int mnm_vec_to_str (const struct mnm_vector* vec, char* buffer, 
  const size_t buffer_sz)
{
  unsigned int k = 0;
  size_t chs = 0;

  if (buffer_sz > 0)
  {
    buffer[0] = '(';
    chs++;
  }
  else return chs;

  while (buffer_sz > chs && k < vec->n_elems-1)
  {
    chs += snprintf (buffer+chs, buffer_sz-chs, "%lf, ", vec->data[k]);
    k++;
  }

  if (chs >= buffer_sz) return chs;
  chs += snprintf (buffer+chs, buffer_sz-chs, "%lf)", vec->data[k]);

  return chs;
}

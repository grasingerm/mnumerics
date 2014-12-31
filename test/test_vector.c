#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "vector.h"

#define M_PI 3.1415926535897932384626433832795028841

void vec_hex_mod (struct mnm_vector* vec, const unsigned int i)
{
  vec -> data [0] = cos (M_PI / 3. * i);
  vec -> data [1] = sin (M_PI / 3. * i);
}

#define N_VECS 6

int main ()
{
  unsigned int i;
  struct mnm_vector vecs [N_VECS] = { {0, 0, NULL} };
  char vts_buffer [128];
  char vts_buffer2 [128];
  const size_t vts_buffer_sz = sizeof (vts_buffer);

  for (i = 0; i < N_VECS; i++)
  {
    assert ( 
      vecs [i] . n_elems == vecs [i] . n_avail &&
      vecs [i] . n_elems == 0 &&
      "all mnm_vectors not initialized to size 0"
      );
    mnm_vec_resize ((vecs+i), 2);
    assert (vecs [i] . data != NULL && 
      "memory allocation failed during resize");
    assert ( 
      vecs [i] . n_elems == vecs [i] . n_avail &&
      vecs [i] . n_elems == 2 &&
      "all mnm_vectors not reinitialized to size 2"
      );
  }

  puts ("Lattice vectors:");
  for (i = 0; i < N_VECS; i++)
  {
    vec_hex_mod ((vecs+i), i+1);
    assert ( abs (mnm_vec_mag (vecs+i) - 1.0) < 0.001 && "not a unit vector" );
    mnm_vec_to_str (vecs+i, vts_buffer, vts_buffer_sz);
    printf ("%d, %s\n", i, vts_buffer);
  }
  fputc ('\n', stdout);

  double m11 = 0, m12 = 0, m22 = 0;
  puts ("Velocity moments:");
  for (i = 0; i < N_VECS; i++)
  {
    m11 += vecs [i] . data [0] * vecs [i] . data [0];
    m12 += vecs [i] . data [0] * vecs [i] . data [1];
    m22 += vecs [i] . data [1] * vecs [i] . data [1];
  }
  printf ("m11 = %.2lf, m12 = %.2lf, m22 = %.2lf\n", m11, m12, m22);
  fputc ('\n', stdout);


  double dat1[2], dat2[2];
  struct mnm_vector res1 = { 2, 2, dat1 }, res2 = { 2, 2, dat2 };
  puts ("Momentum conservation of collisions:");

  mnm_vec_add2 (vecs+2, vecs+5, &res1);
  mnm_vec_add2 (vecs+0, vecs+3, &res2);
  assert (mnm_vec_equal (&res1, &res2, 1e-3) 
    && "collision 'a1' doesn't conserve momentum");
  mnm_vec_to_str (&res1, vts_buffer, vts_buffer_sz);
  mnm_vec_to_str (&res2, vts_buffer2, vts_buffer_sz);
  printf ("a1| pre: %s, post: %s\n", vts_buffer, vts_buffer2);

  mnm_vec_add (3, &res1, vecs+0, vecs+2, vecs+4);
  mnm_vec_add (3, &res2, vecs+1, vecs+3, vecs+5);
  assert (mnm_vec_equal (&res1, &res2, 1e-3) 
    && "collision 'b' doesn't conserve momentum");
  mnm_vec_to_str (&res1, vts_buffer, vts_buffer_sz);
  mnm_vec_to_str (&res2, vts_buffer2, vts_buffer_sz);
  printf ("b| pre: %s, post: %s\n", vts_buffer, vts_buffer2);

  mnm_vec_add (4, &res1, vecs+0, vecs+1, vecs+3, vecs+4);
  mnm_vec_add (4, &res2, vecs+1, vecs+2, vecs+4, vecs+5);
  assert (mnm_vec_equal (&res1, &res2, 1e-3) 
    && "collision 'c1' doesn't conserve momentum");
  mnm_vec_to_str (&res1, vts_buffer, vts_buffer_sz);
  mnm_vec_to_str (&res2, vts_buffer2, vts_buffer_sz);
  printf ("c1| pre: %s, post: %s\n", vts_buffer, vts_buffer2);

  mnm_vec_add (3, &res1, vecs+2, vecs+3, vecs+5);
  mnm_vec_add (3, &res2, vecs+1, vecs+3, vecs+4);
  assert (mnm_vec_equal (&res1, &res2, 1e-3) 
    && "collision 'd1' doesn't conserve momentum");
  mnm_vec_to_str (&res1, vts_buffer, vts_buffer_sz);
  mnm_vec_to_str (&res2, vts_buffer2, vts_buffer_sz);
  printf ("d1| pre: %s, post: %s\n", vts_buffer, vts_buffer2);
  fputc ('\n', stdout);

  for (i = 0; i < N_VECS; i++)
    free ((vecs+i) -> data);

  puts ("All tests successful.");

  return 0;
}

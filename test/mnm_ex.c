#include <stdio.h>
#include "mnumerics.h"

#define BUFFER_SZ 512

int main ()
{
  unsigned int i;
  const unsigned int n = 5;

  char buffer1[BUFFER_SZ];
  char buffer2[BUFFER_SZ];
  char buffer3[BUFFER_SZ];
  char buffer4[BUFFER_SZ];

  struct mnm_vector* v1 = mnm_vec_alloc (n);
  struct mnm_vector* v2 = mnm_vec_alloc (n);
  struct mnm_vector* v3 = mnm_vec_alloc (n);
  struct mnm_vector* v4 = mnm_vec_alloc (n);

  for (i = 0; i < n; i++)
  {
    v1->data[i] = 1.1*i;
    v2->data[i] = -2.2*i;
  }

  if (mnm_vec_add2 (v1, v2, v3) == MNM_SUCCESS)
  {
    mnm_vec_to_str (v1, buffer1, BUFFER_SZ);
    printf ("v1: %s\n", buffer1);

    mnm_vec_to_str (v2, buffer2, BUFFER_SZ);
    printf ("v2: %s\n", buffer2);

    mnm_vec_to_str (v3, buffer3, BUFFER_SZ);
    printf ("v1 + v2 = v3: %s\n", buffer3);
  }
  else
  {
    fputs ("Vector addition should not have failed?", stderr);
    return -1;
  }

  mnm_vec_scale (v1, -1);
  mnm_vec_to_str (v1, buffer1, BUFFER_SZ);
  printf ("v1 after rescaling by -1: %s\n", buffer1);

  printf ("sum(%s) = %lf\n", buffer2, mnm_vec_sum (v2));

  if (mnm_vec_add (3, v4, v1, v2, v3) == MNM_SUCCESS)
  {
    mnm_vec_to_str (v4, buffer4, BUFFER_SZ);
    printf ("v1+v2+v3 = v4: %s\n", buffer4);
  }
  else
  {
    fputs ("Vector addition should not have failed?", stderr);
    return -1;
  }

  double res;
  if (mnm_vec_dot (v1, v3, &res) != MNM_SUCCESS) return -1;
  printf ("v1 dot v3 = %lf\n", res);

  mnm_vec_zero (v1);
  mnm_vec_to_str (v1, buffer1, BUFFER_SZ);
  printf ("v1 after zeroing: %s\n", buffer1);

  printf ("%s == %s ? = %s\n", buffer2, buffer3, 
    (mnm_vec_equal (v2, v3, 1e-4)) ? "true" : "false");

  mnm_vec_resize (v3, 10);
  if (mnm_vec_add2 (v1, v3, v4) != MNM_DIM_ERROR) 
    fputs ("Vector addition should have failed", stderr);

  mnm_vec_destroy (v1);
  mnm_vec_destroy (v2);
  mnm_vec_destroy (v3);
  mnm_vec_destroy (v4);

  return 0;
}

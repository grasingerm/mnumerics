#ifndef __MNUMERICS_H__
#define __MNUMERICS_H__

#include <stdbool.h>
#include "vector.h"

double mnm_darrsum (const double*, const unsigned int);
int mnm_iarrsum (const int*, const unsigned int);
long mnm_larrsum (const long*, const unsigned int);
int mnm_barrsum (const bool*, const unsigned int);

#define _MNM_TEMPLATE_ARRSCALE(T) \
  void mnm_##T_arrscale (T* arr, const unsigned int n, const double scale) \
  {                                                                        \
    unsigned int i;                                                        \
    for (i = 0; i < n; i++) arr[i] *= scale;                               \
  }                                                                        \

void mnm_darrscale (double*, const unsigned int, const double);
void mnm_iarrscale (int*, const unsigned int, const int);
void mnm_larrscale (long*, const unsigned int, const long);

#define _MNM_TEMPLATE_ARRAPPLY(T) \
  void mnm_##T_arrapply (T* arr, const unsigned int n, T (*f) (const T))  \
  {                                                                       \
    unsigned int i;                                                       \
    for (i = 0; i < n; i++) arr[i] = f(arr[i]);                           \
  }                                                                       \

#endif

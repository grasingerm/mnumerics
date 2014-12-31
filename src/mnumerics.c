#include "mnumerics.h"

//! Sum an array of doubles
//!
//! \param arr Array of doubles
//! \param n Number of elements in array
//! \return Sum of elements
double mnm_darrsum (const double* arr, const unsigned int n)
{
  unsigned int i;
  double sum = 0;
  for (i = 0; i < n; i++) sum += arr[i];

  return sum;
}

//! Sum an array of ints
//!
//! \param arr Array of ints
//! \param n Number of elements in array
//! \return Sum of elements
int mnm_iarrsum (const int* arr, const unsigned int n)
{
  unsigned int i;
  int sum = 0;
  for (i = 0; i < n; i++) sum += arr[i];

  return sum;
}

//! Sum an array of longs
//!
//! \param arr Array of longs
//! \param n Number of elements in array
//! \return Sum of elements
long mnm_larrsum (const long* arr, const unsigned int n)
{
  unsigned int i;
  long sum = 0;
  for (i = 0; i < n; i++) sum += arr[i];

  return sum;
}

//! Sum an array of booleans
//!
//! \param arr Array of booleans
//! \param n Number of elements in array
//! \return Sum of elements
int mnm_barrsum (const bool* arr, const unsigned int n)
{
  unsigned int i;
  int sum = 0;
  for (i = 0; i < n; i++) sum += arr[i];

  return sum;
}

//! Scale each element of an array by a constant multiple
//!
// \param arr Pointer to array
// \param n Number of elements to scale
// \param scale Multiplier
void mnm_darrscale (double* arr, const unsigned int n, const double scale)
{
    unsigned int i;
    for (i = 0; i < n; i++) arr[i] *= scale;
}

//! Scale each element of an array by a constant multiple
//!
// \param arr Pointer to array
// \param n Number of elements to scale
// \param scale Multiplier
void mnm_iarrscale (int* arr, const unsigned int n, const int scale)
{
    unsigned int i;
    for (i = 0; i < n; i++) arr[i] *= scale;
}

//! Scale each element of an array by a constant multiple
//!
// \param arr Pointer to array
// \param n Number of elements to scale
// \param scale Multiplier
void mnm_larrscale (long* arr, const unsigned int n, const long scale)
{
    unsigned int i;
    for (i = 0; i < n; i++) arr[i] *= scale;
}

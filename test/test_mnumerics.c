#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "mnumerics.h"

int main ()
{
  unsigned int k;

  const unsigned int n = 6;
  double d[] = {1.1, -1.1, 3.0, -9.3, 2.2, 9.3};
  bool b[] = {true, true, false, true, false, false};
  int i[] = {1, 2, 3, 4, 5, -6};
  long l[] = {100, 200, 300, 400, 500, 600};

  puts ("Testing mnm_darrsum, mnm_iarrsum, mnm_barrsum ...");
  assert (mnm_darrsum(d, n) == 1.1-1.1+3.0-9.3+2.2+9.3 && 
    "mnm_darrsum test failed.");
  assert (mnm_barrsum(b, n) == 3 && "mnm_barrsum test failed.");
  assert (mnm_iarrsum(i, n) == 9);
  puts ("... tests passed.");

  puts ("Testing mnm_darrscale, mnm_iarrscale, mnm_barrscale ...");

  mnm_darrscale (d, n, -2.0);
  const double d_exp[] = {-2.2, 2.2, -6.0, 18.6, -4.4, -18.6 };
  for (k = 0; k < n; k++) assert (abs (d[k] - d_exp[k]) < 1e-6 
    && "mnm_darrscale test failed.");

  mnm_iarrscale (i, n, 3);
  const int i_exp[] = { 3, 6, 9, 12, 15, -18 };
  for (k = 0; k < n; k++) 
    assert (i[k] == i_exp[k] && "mnm_iarrscale test failed.");

  mnm_larrscale (l, n, -1);
  const long l_exp[] = { -100, -200, -300, -400, -500, -600 };
  for (k = 0; k < n; k++) 
    assert (l[k] == l_exp[k] && "mnm_larrscale test failed.");

  puts ("All tests passed.\n");

  return 0;
}

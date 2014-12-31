#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "mnumerics.h"

int main ()
{
  const unsigned int n = 6;
  double d[] = {1.1, -1.1, 3.0, -9.3, 2.2, 9.3};
  bool b[] = {true, true, false, true, false, false};
  int i[] = {1, 2, 3, 4, 5, -6};

  puts ("Testing mnm_darrsum, mnm_iarrsum, mnm_barrsum ...");
  assert (mnm_darrsum(d, n) == 1.1-1.1+3.0-9.3+2.2+9.3 && 
    "mnm_darrsum test failed.");
  assert (mnm_barrsum(b, n) == 3 && "mnm_barrsum test failed.");
  assert (mnm_iarrsum(i, n) == 9);
  puts ("... tests passed.");

  puts ("All tests passed.");

  return 0;
}

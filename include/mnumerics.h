#ifndef __MNUMERICS_H__
#define __MNUMERICS_H__

#include <stdbool.h>
#include "vector.h"

double mnm_darrsum (const double*, const unsigned int);
int mnm_iarrsum (const int*, const unsigned int);
long mnm_larrsum (const long*, const unsigned int);
int mnm_barrsum (const bool*, const unsigned int);

#endif

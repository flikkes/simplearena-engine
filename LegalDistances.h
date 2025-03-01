#ifndef LEGALDISTANCES_H
#define LEGALDISTANCES_H
#include <math.h>
#include <cfloat>

#include "Direction.h"
struct LegalDistances {
    float xF = FLT_MAX;
    float xB = FLT_MAX;
    float yF = FLT_MAX;
    float yB = FLT_MAX;
    float zF = FLT_MAX;
    float zB = FLT_MAX;
};
#endif

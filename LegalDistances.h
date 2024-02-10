#ifndef LEGALDISTANCES_H
#define LEGALDISTANCES_H
#include <math.h>

#include "Direction.h"
struct LegalDistances {
    float xF = MAXFLOAT;
    float xB = MAXFLOAT;
    float yF = MAXFLOAT;
    float yB = MAXFLOAT;
    float zF = MAXFLOAT;
    float zB = MAXFLOAT;
};
#endif
#ifndef VALIDATION_H
#define VALIDATION_H

#include <gtk/gtk.h>

namespace Validation {

inline static bool isValidDimension(float f) {
  try {
    if (f > 0) {
      return true;
    } else {
      throw(f);
    }
  } catch (float ex) {
    g_print("Dimenstion value < 0: %f\n", ex);
    return false;
  }
  return false;
};

inline static bool isValidCoordinate(float f) {
  try {
    if (f > 0) {
      return true;
    } else {
      throw(f);
    }
  } catch (float ex) {
    g_print("Coordinate value < 0: %f\n", ex);
    return false;
  }
  return false;
};

inline static bool isValidMass(float f) {
  try {
    if (f > 0) {
      return true;
    } else {
      throw(f);
    }
  } catch (float ex) {
    g_print("Mass value < 0: %f\n", ex);
    return false;
  }
  return false;
};

}; // namespace Validation
#endif
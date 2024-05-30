#ifndef VALIDATION_H
#define VALIDATION_H

#include <iostream>

using namespace std;

namespace Validation {

inline static bool isValidDimension(float f) {
  try {
    if (f > 0) {
      return true;
    } else {
      throw(f);
    }
  } catch (float ex) {
    cout << "Dimenison value < 0: " << ex << endl;
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
    cout << "Coordinate value < 0: " << ex << endl;
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
    cout << "Mass value < 0: " << ex << endl;
    return false;
  }
  return false;
};

}; // namespace Validation
#endif
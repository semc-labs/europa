#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "Matrix.hpp"

namespace Fw {
  class Quaternion : public Vector<4> {
    Quaternion() {};
    Quaternion(F64 x, F64 y, F64 z, F64 w) {
      this->data[0][0] = x;
      this->data[1][0] = y;
      this->data[2][0] = z;
      this->data[3][0] = w;
    };
  }
} // Fw

#endif // QUATERNION_HPP

#include "Matrix.hpp"

#if FW_SERIALIZABLE_TO_STRING
#include <Fw/Types/String.hpp>
#endif

namespace Fw {
  template<U8 rows, U8 columns>
  Matrix<rows, columns> operator+(const Matrix<rows, columns>& lhs,
                                  const Matrix<rows, columns>& rhs) {
    Matrix<rows, columns> res;
    for (U8 i = 0; i < rows; i++) {
      for (U8 j = 0; j < columns; j++) {
        res.data[i][j] = lhs.data[i][j] + rhs.data[i][j];
      }
    }
    return res;
  }

  template<U8 rows, U8 columns>
  Matrix<rows, columns> operator-(const Matrix<rows, columns>& lhs,
                                  const Matrix<rows, columns>& rhs) {
    Matrix<rows, columns> res;
    for (U8 i = 0; i < rows; i++) {
      for (U8 j = 0; j < columns; j++) {
        res.data[i][j] = lhs.data[i][j] - rhs.data[i][j];
      }
    }
    return res;
  }

  template <U8 resrows, U8 rescolumns, U8 shared>
  Matrix<resrows, rescolumns> operator*(const Matrix<resrows, shared>& lhs,
                                        const Matrix<shared, rescolumns>& rhs){
    Matrix<resrows, rescolumns> res;
    for (U8 i = 0; i < resrows; i++) {
      for (U8 j = 0; j < rescolumns; j++) {
        F64 n = 0;
        for (U8 k = 0; k < shared; k++) {
          n += lhs.data[i][k] * rhs.data[k][j];
        }
        res.data[i][j] = n;
      }
    }
    return res;
  }

  template<U8 rows, U8 columns>
  Matrix<rows, columns> operator*(const Matrix<rows, columns>& lhs,
                                  F64 scale) {
    Matrix<rows, columns> res;
    for (U8 i = 0; i < rows; i++) {
      for (U8 j = 0; j < columns; j++) {
        res.data[i][j] = lhs.data[i][j] * scale;
      }
    }
    return res;
  }

  template<U8 rows, U8 columns>
  bool operator==(const Matrix<rows, columns>& lhs,
                  const Matrix<rows, columns>& rhs) {
    for (U8 i = 0; i < rows; i++) {
      for (U8 j = 0; j < columns; j++) {
        if (lhs.data[i][j] != rhs.data[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

#if FW_SERIALIZABLE_TO_STRING || BUILD_UT
  template <U8 rows, U8 columns>
  void Matrix<rows, columns>::toString(Fw::StringBase& text) const {
    static const char * formatString = "(rows = %u, columns = %u";
    char outputString[FW_SERIALIZABLE_TO_STRING_BUFFER_SIZE];

    U8 n = snprintf(outputString, FW_SERIALIZABLE_TO_STRING_BUFFER_SIZE, formatString, rows, columns);

    for (U8 i = 0; i < rows; i++) {
      n += snprintf(outputString+n, FW_SERIALIZABLE_TO_STRING_BUFFER_SIZE-n, "\n");
      for (U8 j = 0; j < columns; j++) {
        n += snprintf(outputString+n, FW_SERIALIZABLE_TO_STRING_BUFFER_SIZE-n, " %.2f ", this->data[i][j]);
      }
    }

    n += snprintf(outputString+n, FW_SERIALIZABLE_TO_STRING_BUFFER_SIZE-n, ")\n");

    // Force NULL termination
    outputString[FW_SERIALIZABLE_TO_STRING_BUFFER_SIZE-1] = 0;
    text = outputString;
  }
#endif

#ifdef BUILD_UT
  template <U8 rows, U8 columns>
  std::ostream& operator<<(std::ostream& os, const Matrix<rows, columns>& obj) {
      Fw::String str;
      obj.toString(str);
      os << str.toChar();
      return os;
  }
#endif
}

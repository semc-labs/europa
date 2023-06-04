#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <Fw/Types/Assert.hpp>
#include <Fw/Types/BasicTypes.hpp>
#include <Fw/Types/Serializable.hpp>

#if FW_SERIALIZABLE_TO_STRING
#include <Fw/Types/StringType.hpp>
#include <cstdio> // snprintf
#ifdef BUILD_UT
#include <iostream>
#include <Fw/Types/String.hpp>
#endif
#endif

namespace Fw {
  template <U8 rows, U8 columns>
  class Matrix {
    public:
      Matrix() {};
      Matrix(F64 data[rows][columns]) : data(data) {};

      void setData(F64 (&data)[rows][columns]) {
        for (U8 i = 0; i < rows; i++) {
          for (U8 j = 0; j < columns; j++) {
            this->data[i][j] = data[i][j];
          }
        }
      };

      const F64 *getData() { return data; };

      F64& operator() (U8 x, U8 y) {
        FW_ASSERT(x < rows);
        FW_ASSERT(y < columns);
        return data[x][y];
      };

      const F64& operator() (U8 x, U8 y) const {
        FW_ASSERT(x < rows);
        FW_ASSERT(y < columns);
        return data[x][y];
      };

      template<U8 addr, U8 addc>
      friend Matrix<addr, addc> operator+(const Matrix<addr, addc>& lhs,
                                          const Matrix<addr, addc>& rhs);

      template<U8 subr, U8 subc>
      friend Matrix<subr, subc> operator-(const Matrix<subr, subc>& lhs,
                                          const Matrix<subr, subc>& rhs);

      template<U8 resrows, U8 rescolumns, U8 shared>
      friend Matrix<resrows, rescolumns> operator*(const Matrix<resrows, shared>& lhs,
                                                   const Matrix<shared, rescolumns>& rhs);

      template<U8 scalr, U8 scalc>
      friend Matrix<scalr, scalc> operator*(const Matrix<scalr, scalc>& lhs,
                                            F64 scale);
      template<U8 eqlr, U8 eqlc>
      friend bool operator==(const Matrix<eqlr, eqlc>& lhs,
                             const Matrix<eqlr, eqlc>& rhs);

#if FW_SERIALIZABLE_TO_STRING || BUILD_UT
      void toString(Fw::StringBase& text) const;
#endif

#ifdef BUILD_UT
      template <U8 outr, U8 outc>
      friend std::ostream& operator<<(std::ostream& os, const Matrix<outr, outc>& obj);
#endif

    protected:
      F64 data[rows][columns];
  };

  template <U8 n>
  class Vector : public Matrix<n, 1> {
    F64 operator[](U8 idx) {
      FW_ASSERT(idx < n);
      return this->data[idx][0];
    }
  };
} /* Fw */

#endif

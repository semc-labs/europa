#include "Types/Matrix.cpp"
#include <gtest/gtest.h>

TEST(Matrix, Addition) {
  F64 a[3][3] = {{1, 2, 3},
                 {4, 5, 6},
                 {7, 8, 9}};

  Fw::Matrix<3, 3> one;
  one.setData(a);

  one = one + one;

  F64 b[3][3] = {{ 2,  4,  6},
                 { 8, 10, 12},
                 {14, 16, 18}};

  Fw::Matrix<3, 3> res;
  res.setData(b);

  ASSERT_EQ(one, res);
}

TEST(Matrix, Subtraction) {
  F64 a[3][3] = {{1, 2, 3},
                 {4, 5, 6},
                 {7, 8, 9}};

  Fw::Matrix<3, 3> one;
  one.setData(a);

  one = one - one;

  F64 b[3][3] = {{0, 0, 0},
                 {0, 0, 0},
                 {0, 0, 0}};

  Fw::Matrix<3, 3> res;
  res.setData(b);

  ASSERT_EQ(one, res);
}

TEST(Matrix, Multiplication) {
  F64 a[3][3] = {{1, 2, 3},
                 {4, 5, 6},
                 {7, 8, 9}};

  Fw::Matrix<3, 3> one;
  one.setData(a);

  one = one * one;

  F64 b[3][3] = {{ 30,  36,  42},
                 { 66,  81,  96},
                 {102, 126, 150}};

  Fw::Matrix<3, 3> res;
  res.setData(b);

  ASSERT_EQ(one, res);
}

TEST(Matrix, Scaling) {
  F64 a[3][3] = {{1, 2, 3},
                 {4, 5, 6},
                 {7, 8, 9}};

  Fw::Matrix<3, 3> one;
  one.setData(a);

  one = one * 3;

  F64 b[3][3] = {{ 3,  6,  9},
                 {12, 15, 18},
                 {21, 24, 27}};

  Fw::Matrix<3, 3> res;
  res.setData(b);

  ASSERT_EQ(one, res);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

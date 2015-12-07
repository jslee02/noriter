#include <iostream>

#include <gtest/gtest.h>

#include <Eigen/Core>
#include <Eigen/Dense>

#include "noriter/EigenHelpers.h"
#include "noriter/Stopwatch.h"

//==============================================================================
TEST(Template, Basic)
{
  Eigen::Isometry2d se2;
//  double rotation1 = se2.rotation();
  Eigen::Matrix2d rotation2 = se2.rotation();
//  Eigen::Quaterniond rotation3 = se2.rotation();

//  std::cout << nrt::is_eigen_matrix<Eigen::MatrixXd>::value << std::endl;
//  std::cout << nrt::is_eigen_matrix<Eigen::VectorXd>::value << std::endl;
//  std::cout << nrt::is_eigen_vector<Eigen::MatrixXd>::value << std::endl;
//  std::cout << nrt::is_eigen_vector<Eigen::VectorXd>::value << std::endl;
//  std::cout << nrt::is_eigen_vector<float>::value << std::endl;
//  Eigen::Matrix<double, 0, 1> m1;
//  Eigen::Matrix<double, 0, 1> m2;
//  Eigen::Matrix<double, 0, 1> m3;

//  m3 = m1;
//  m3 = m2 + m1;

//  m3[0] = 0.0;

//  int a = 10;
  Eigen::Matrix<double, 3, 3> m3;
//  m3 = m3.ldlt().solve(Eigen::Matrix3d::Identity());
  m3 = m3.inverse().eval();

//  Eigen::Matrix<double, 6, 6> m6;
//  m6 = m6.inverse();
//  m = m.ldlt().solve(Eigen::Matrix<double, 1, 1>::Identity());

  int a = 10;

}

struct empty_space {};

template <typename VectorType>
inline void inner(double& res, const VectorType& v1, const VectorType& v2)
{
  res = v1.dot(v2);
}

template <>
inline void inner<double>(double& res, const double& v1, const double& v2)
{
  res = v1 * v2;
}

template <>
inline void inner<empty_space>(double& res, const empty_space& v1, const empty_space& v2)
{
}

//==============================================================================
TEST(Template, Performance)
{
  nrt::Timer t;

  double double_1 = random();
  double double_2 = random();
  double double_3 = random();
  double double_4 = random();
  double double_5 = random();
  double double_6 = random();

  Eigen::Matrix<double, 1, 1> eigen1x1_1;
  Eigen::Matrix<double, 1, 1> eigen1x1_2;
  Eigen::Matrix<double, 1, 1> eigen1x1_3;
  Eigen::Matrix<double, 1, 1> eigen1x1_4;
  Eigen::Matrix<double, 1, 1> eigen1x1_5;
  Eigen::Matrix<double, 1, 1> eigen1x1_6;

  eigen1x1_1[0] = double_1;
  eigen1x1_2[0] = double_2;
  eigen1x1_3[0] = double_3;
  eigen1x1_4[0] = double_4;
  eigen1x1_5[0] = double_5;
  eigen1x1_6[0] = double_6;

  Eigen::Matrix<double, 0, 1> eigen0x1_1;
  Eigen::Matrix<double, 0, 1> eigen0x1_2;
  Eigen::Matrix<double, 0, 1> eigen0x1_3;
  Eigen::Matrix<double, 0, 1> eigen0x1_4;
  Eigen::Matrix<double, 0, 1> eigen0x1_5;
  Eigen::Matrix<double, 0, 1> eigen0x1_6;

  empty_space empty_1;
  empty_space empty_2;
  empty_space empty_6;

  double numTest = 1e+5;

//  //----------------------------------------------------------------------------

//  std::cout << "ADDITION" << std::endl;

//  t.start();
//  for (size_t i = 0; i < 1e+6; ++i)
//    double_6 = double_1 + double_2;
//  t.stop();
//  std::cout << "double: " << t.getLastElapsedTime() << std::endl;

//  t.start();
//  for (size_t i = 0; i < 1e+6; ++i)
//    eigen1x1_6[0] = eigen1x1_1[0] + eigen1x1_2[0];
//  t.stop();
//  std::cout << "eigen : " << t.getLastElapsedTime() << std::endl;

//  std::cout << "double: " << double_6 << std::endl;
//  std::cout << "eigen : " << eigen1x1_6 << std::endl;

//  std::cout << std::endl;

//  //----------------------------------------------------------------------------

//  std::cout << "INNER PRODUCT" << std::endl;

//  t.start();
//  for (size_t i = 0; i < 1e+6; ++i)
//    inner(double_6, double_1, double_2);
//  t.stop();
//  std::cout << "double: " << t.getLastElapsedTime() << std::endl;

//  t.start();
//  for (size_t i = 0; i < 1e+6; ++i)
//    inner(eigen1x1_6[0], eigen1x1_1, eigen1x1_2);
//  t.stop();
//  std::cout << "eigen : " << t.getLastElapsedTime() << std::endl;

//  std::cout << "double: " << double_6 << std::endl;
//  std::cout << "eigen : " << eigen1x1_6 << std::endl;

//  std::cout << std::endl;

//  //----------------------------------------------------------------------------

//  std::cout << "INNER PRODUCT" << std::endl;



//  t.start();
//  for (size_t i = 0; i < numTest; ++i)
//  {}
//  t.stop();
//  std::cout << "double: " << t.getLastElapsedTime() << std::endl;

//  t.start();
//  for (size_t i = 0; i < numTest; ++i)
//  {
//    inner(eigen1x1_6[0], eigen1x1_1, eigen1x1_2);
//  }
//  t.stop();
//  std::cout << "eigen : " << t.getLastElapsedTime() << std::endl;

//  t.start();
//  for (size_t i = 0; i < numTest; ++i)
//  {
//    inner(double_6, empty_1, empty_2);
//  }
//  t.stop();
//  std::cout << "empty : " << t.getLastElapsedTime() << std::endl;

////  std::cout << "double: " << double_6 << std::endl;
//  std::cout << "eigen : " << eigen0x1_6 << std::endl;

//  std::cout << std::endl;

  //----------------------------------------------------------------------------

  std::cout << "INVERSE" << std::endl;

  Eigen::Matrix<double, 1, 1> mat1x1_1 = Eigen::Matrix<double, 1, 1>::Identity();
  Eigen::Matrix<double, 1, 1> mat1x1_2 = Eigen::Matrix<double, 1, 1>::Identity();

  Eigen::Matrix2d mat2x2_1 = Eigen::Matrix2d::Identity();
  Eigen::Matrix2d mat2x2_2 = Eigen::Matrix2d::Identity();

  Eigen::Matrix3d mat3x3_1 = Eigen::Matrix3d::Identity();
  Eigen::Matrix3d mat3x3_2 = Eigen::Matrix3d::Identity();

  Eigen::Matrix<double, 6, 6> mat6x6_1 = Eigen::Matrix<double, 6, 6>::Identity();
  Eigen::Matrix<double, 6, 6> mat6x6_2 = Eigen::Matrix<double, 6, 6>::Identity();

  t.start();
  for (size_t i = 0; i < numTest; ++i)
  {
    mat1x1_2 = mat1x1_1.inverse();
  }
  t.stop();
  std::cout << "inverse1: " << t.getLastElapsedTime() << std::endl;

  t.start();
  for (size_t i = 0; i < numTest; ++i)
  {
    mat1x1_2 = mat1x1_1.ldlt().solve(Eigen::Matrix<double, 1, 1>::Identity());
  }
  t.stop();
  std::cout << "ldlt1   : " << t.getLastElapsedTime() << std::endl;

  t.start();
  for (size_t i = 0; i < numTest; ++i)
  {
    mat2x2_2 = mat2x2_1.inverse();
  }
  t.stop();
  std::cout << "inverse2: " << t.getLastElapsedTime() << std::endl;

  t.start();
  for (size_t i = 0; i < numTest; ++i)
  {
    mat2x2_2 = mat2x2_1.ldlt().solve(Eigen::Matrix2d::Identity());
  }
  t.stop();
  std::cout << "ldlt2   : " << t.getLastElapsedTime() << std::endl;

  t.start();
  for (size_t i = 0; i < numTest; ++i)
  {
    mat3x3_2 = mat3x3_1.inverse();
  }
  t.stop();
  std::cout << "inverse3: " << t.getLastElapsedTime() << std::endl;

  t.start();
  for (size_t i = 0; i < numTest; ++i)
  {
    mat3x3_2 = mat3x3_1.ldlt().solve(Eigen::Matrix3d::Identity());
  }
  t.stop();
  std::cout << "ldlt3   : " << t.getLastElapsedTime() << std::endl;

  t.start();
  for (size_t i = 0; i < numTest; ++i)
  {
    mat6x6_2 = mat6x6_1.inverse();
  }
  t.stop();
  std::cout << "inverse6: " << t.getLastElapsedTime() << std::endl;

  t.start();
  for (size_t i = 0; i < numTest; ++i)
  {
    mat6x6_2 = mat6x6_1.ldlt().solve(Eigen::Matrix<double, 6, 6>::Identity());
  }
  t.stop();
  std::cout << "ldlt6   : " << t.getLastElapsedTime() << std::endl;

  std::cout << std::endl;
}

//==============================================================================
int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

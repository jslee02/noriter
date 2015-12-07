#include <gtest/gtest.h>

#include <Eigen/Core>
#include <iostream>
#include <type_traits>
#include <cstdio>


// Helper class

//
template <typename T>
struct remap
{
  // Default: Output type is the same as input type.
  using type = T;
};

template <>
struct remap<char>
{
  using type = unsigned char;
};

template <>
struct remap<signed char>
{
  using type = unsigned char;
};

template <typename T>
class is_eigen_matrix
{
protected:
  // Note that these functions are never defined.
  template <typename Derived>
  static std::true_type is_eigen_matrix_test(const Eigen::MatrixBase<Derived>&);
  static std::false_type is_eigen_matrix_test(...);

public:
  using type = decltype(is_eigen_matrix_test(std::declval<T>()));
  enum { value = type::value };
};

template <typename T>
class is_eigen_vector
{
protected:
  template <typename Derived, typename Enable = void>
  struct size_checker : std::false_type {};

  template <typename Derived>
  struct size_checker<Derived,
      typename std::enable_if<Derived::ColsAtCompileTime == 1>::type>
      : std::true_type {};

public:
  using type = typename std::conditional<
      size_checker<T>::value & is_eigen_matrix<T>::value,
      std::true_type, std::false_type>::type;

  enum { value = type::value };
};


template <typename T, typename Enable = void>
struct Printer
{
  static void print(T x)
  {
    std::cout << "The type is ["
              << typeid(T).name()
              << "] and the value is ["
              << x
              << "].\n";
  }
};

// Using is_floating_point
template <typename T>
struct Printer<T, typename std::enable_if<std::is_floating_point<T>::value>::type>
{
  static void print(T x)
  {
    std::cout << "The type is one of floating point and the value is ["
              << x
              << "].\n";
  }
};

// Using is_floating_point
template <typename T>
struct Printer<T, typename std::enable_if<std::is_same<T, unsigned char>::value>::type>
{
  static void print(T x)
  {
    std::cout << "The type is one of floating point and the value is ["
              << x
              << "].\n";
  }
};

// Convenience function wrapper

template <typename T>
void print(T x)
{
  return Printer<typename remap<T>::type>::print(x);
}

//==============================================================================
TEST(Template, Basic)
{
  print(0.1f);
  print(0.2);
  print('c');
  print("c");
  print(0u);

  std::cout << is_eigen_matrix<Eigen::MatrixXd>::value << std::endl;
  std::cout << is_eigen_matrix<Eigen::VectorXd>::value << std::endl;
  std::cout << is_eigen_vector<Eigen::MatrixXd>::value << std::endl;
  std::cout << is_eigen_vector<Eigen::VectorXd>::value << std::endl;
  std::cout << is_eigen_vector<float>::value << std::endl;
}

//==============================================================================
int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

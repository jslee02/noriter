#ifndef NORITER_EIGENHELPERS_H
#define NORITER_EIGENHELPERS_H

#include <Eigen/Core>

namespace nrt {

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

} // namespace nrt

#endif  // NORITER_EIGENHELPERS_H


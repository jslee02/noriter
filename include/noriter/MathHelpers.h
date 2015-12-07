#ifndef NORITER_MATHHELPERS_H
#define NORITER_MATHHELPERS_H

#include "noriter/EigenHelpers.h"

namespace nrt {

// Primary template
template <typename T, typename Enable = void>
struct VectorInnerImpl
{
  static inline double inner(const T& v1, const T& v2)
  {
    return v1 * v2;
  }
};

// This specialization only exists when T is or inherits an Eigen::MatrixBase.
template <typename T>
struct VectorInnerImpl<T, typename std::enable_if<is_eigen_vector<T>::value>::type>
{
  static inline double inner(const T& v1, const T& v2)
  {
    return v1.dot(v2);
  }
};

template <typename T>
double inner(const T& v1, const T& v2)
{
  return VectorInnerImpl<T>::inner(v1, v2);
}

}  // namespace nrt

#endif  // NORITER_MATHHELPERS_H

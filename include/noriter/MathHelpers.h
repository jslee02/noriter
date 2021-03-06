//
// Copyright (c) 2015, Jeongseok Lee <jslee02@gmail.com>
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

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

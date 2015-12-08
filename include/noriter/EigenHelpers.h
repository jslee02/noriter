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


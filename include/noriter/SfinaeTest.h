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

#ifndef DART_COMMON_SFINAETEST_H_
#define DART_COMMON_SFINAETEST_H_

#include <type_traits>

#include "noriter/Macros.h"

namespace nrt {

//==============================================================================
// Generic SFINAE test if a class has a method where the return type and
// argment types are specified.
//
// [1] http://stackoverflow.com/questions/87372/check-if-a-class-has-a-member-function-of-a-given-signature
// [2] http://stackoverflow.com/questions/7557990/c-method-name-as-template-parameter
//==============================================================================

#define NORITER_HAS_METHOD(_class_name, _method_name, _return_type, _arg_types)\
  has_method<_class_name, _return_type(_arg_types)>::method_name<&_class_name::_method_name>::value

#define NORITER_IF_HAS_METHOD\
  if (has_method<_class_name, _return_type(_arg_types)>::method_name<&_class_name::_method_name>::value)

template <typename, typename T>
struct has_method
{
  static_assert(
      std::integral_constant<T, false>::value,
      "Second template parameter needs to be of function type.");
};

template <typename T, typename Ret, typename... Args>
struct has_method<T, Ret(Args...)>
{
  template <Ret (T::*Method)(Args...)>
  class method_name
  {
  private:
    template<typename C>
    static constexpr auto check(C*)
        -> typename std::is_same<
        Ret,
        decltype( (std::declval<C>().*Method)( std::declval<Args>()... ) )
        >::type;

    template<typename>
    static constexpr std::false_type check(...);

  public:
    using type = decltype( check<T>(nullptr) );
    static constexpr bool value = type::value;
  };
};

//==============================================================================
template <typename T>
class has_less_operator
{
protected:
  template <typename C>
  static auto check(C c1, C c2) -> decltype(c1 < c2, std::true_type());
  static auto check(...) -> decltype(std::false_type());

public:
  static constexpr bool value = decltype( check( std::declval<T>(), std::declval<T>() ) )::value;
};

}  // namespace nrt

#endif  // DART_COMMON_SFINAETEST_H_


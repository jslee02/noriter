#ifndef NORITER_ASSERTIONMACROS_H
#define NORITER_ASSERTIONMACROS_H

// Enforce use of template specialization. Note that this static_assert has to
// depend on T, otherwise it can be evaluated immediately by the compiler, which
// is always failure to compile.
//
// [Usage]
// template <typename T>
// T getValue()
// { NORITER_ENFORCE_TEMPLATE_FUNCTION_SPECIALIZED(getValue, T); }
//
#define NORITER_ENFORCE_TEMPLATE_FUNCTION_SPECIALIZED( name, type )            \
  static_assert(sizeof( type ) == -1,                                          \
                "This template function [" #name "] has to be specialized.");

#endif  // NORITER_ASSERTIONMACROS_H


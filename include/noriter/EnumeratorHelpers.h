#ifndef NORITER_ASSERTIONMACROS_H
#define NORITER_ASSERTIONMACROS_H

template <typename E>
constexpr typename std::underlying_type<E>::type to_underlying(E e)
{
  return static_cast<typename std::underlying_type<E>::type>(e);
}

#endif  // NORITER_ASSERTIONMACROS_H


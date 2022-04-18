#ifndef SZO_GOS_TYPE_TRAITS_HPP
#define SZO_GOS_TYPE_TRAITS_HPP

#include "cpp_features.hpp"

#include <type_traits>

namespace gos {
#ifdef GOS_LIB_REMOVE_CVREF
template <typename T> using remove_cvref_t = std::remove_cvref_t<T>;
#else
template <typename T> struct remove_cvref : std::remove_cv<T> {};
template <typename T> struct remove_cvref<T &> : std::remove_cv<T> {};
template <typename T> struct remove_cvref<T &&> : std::remove_cv<T> {};
template <typename T> using remove_cvref_t = typename remove_cvref<T>::type;
#endif
}

#endif // SZO_GOS_TYPE_TRAITS_HPP

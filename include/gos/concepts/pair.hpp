#ifndef SZO_GOS_PAIR_HPP
#define SZO_GOS_PAIR_HPP

#include "gos/config/concept.hpp"
#include "gos/config/cpp_features.hpp"
#include "gos/config/type_traits.hpp"

namespace gos {

#ifdef GOS_LIB_CONCEPTS
namespace detail {
template<typename T>
// GCC produces lvalue reference while clang non ref value
concept pair = requires(T t) {
    { t.first } -> std::convertible_to<typename T::first_type>;
    { t.second } -> std::convertible_to<typename T::second_type>;
};
} // namespace detail

template<typename T>
concept pair = detail::pair<gos::remove_cvref_t<T>>;

template<typename T>
concept is_pair_v = pair<T>;

#else
namespace detail {
template<typename T>
using pair_impl = std::void_t<typename T::first_type, typename T::second_type>;

template<typename T, typename = void>
struct pair : std::false_type {};

template<typename T>
struct pair<T, pair_impl<T>> : std::true_type {};
} // namespace detail

template<typename T, typename = void>
using pair = detail::pair<gos::remove_cvref_t<T>>;

template<typename T>
inline constexpr bool is_pair_v = pair<T>::value;

#endif // GOS_LIB_CONCEPTS
} // namespace gos

#endif // SZO_GOS_PAIR_HPP

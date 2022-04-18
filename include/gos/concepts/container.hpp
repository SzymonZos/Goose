#ifndef SZO_GOS_CONTAINER_HPP
#define SZO_GOS_CONTAINER_HPP

#include "gos/config/concept.hpp"
#include "gos/config/cpp_features.hpp"
#include "gos/config/type_traits.hpp"

#include <iterator>

namespace gos {

#ifdef GOS_LIB_CONCEPTS
namespace detail {
template<typename T>
concept container_impl =
    std::regular<T> && std::swappable<T> &&
    std::destructible<typename T::value_type> &&
    std::same_as<typename T::reference, typename T::value_type&> &&
    std::same_as<typename T::const_reference, const typename T::value_type&> &&
    std::forward_iterator<typename T::iterator> &&
    std::forward_iterator<typename T::const_iterator> &&
    std::signed_integral<typename T::difference_type> &&
    std::same_as<typename T::difference_type,
                 typename std::iterator_traits<
                     typename T::iterator>::difference_type> &&
    std::same_as<typename T::difference_type,
                 typename std::iterator_traits<
                     typename T::const_iterator>::difference_type> &&
    requires(T a, const T b) {
        { a.begin() } -> std::same_as<typename T::iterator>;
        { a.end() } -> std::same_as<typename T::iterator>;
        { a.cbegin() } -> std::same_as<typename T::const_iterator>;
        { a.cend() } -> std::same_as<typename T::const_iterator>;
        { a == b } -> std::convertible_to<bool>;
        { a != b } -> std::convertible_to<bool>;
        { a.size() } -> std::same_as<typename T::size_type>;
        { a.max_size() } -> std::same_as<typename T::size_type>;
        { a.empty() } -> std::convertible_to<bool>;
};

template<typename T>
concept container = container_impl<gos::remove_cvref_t<T>>;

template<typename T>
concept not_string = !std::same_as<gos::remove_cvref_t<T>, std::string>;
} // namespace detail

template<typename T>
concept container = detail::container<T> && detail::not_string<T>;

template<typename T>
concept is_container_v = container<T>;

#else
namespace detail {
template<typename T>
using container_impl = std::void_t<
    std::is_same<decltype(std::declval<T>().begin()), typename T::iterator>,
    std::is_same<decltype(std::declval<T>().end()), typename T::iterator>,
    std::is_same<decltype(std::declval<T>().cbegin()),
                 typename T::const_iterator>,
    std::is_same<decltype(std::declval<T>().cend()),
                 typename T::const_iterator>,
    std::is_same<decltype(std::declval<T>().size()), typename T::size_type>,
    std::is_same<decltype(std::declval<T>().max_size()),
                 typename T::size_type>,
    std::is_convertible<decltype(std::declval<T>().empty()), bool>,
    std::is_destructible<typename T::value_type>,
    std::is_same<typename T::reference, typename T::value_type&>,
    std::is_same<typename T::const_reference, const typename T::value_type&>,
    std::is_integral<typename T::difference_type>,
    std::is_signed<typename T::difference_type>,
    std::is_same<
        typename T::difference_type,
        typename std::iterator_traits<typename T::iterator>::difference_type>,
    std::is_same<typename T::difference_type,
                 typename std::iterator_traits<
                     typename T::const_iterator>::difference_type>>;

template<typename T, typename = void>
struct container : std::false_type {};

template<>
struct container<std::string> : std::false_type {};

template<typename T>
struct container<T, container_impl<T>> : std::true_type {};
} // namespace detail

template<typename T, typename = void>
using container = detail::container<gos::remove_cvref_t<T>>;

template<typename T>
inline constexpr bool is_container_v = container<T>::value;

#endif
} // namespace gos

#endif // SZO_GOS_CONTAINER_HPP

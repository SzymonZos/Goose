#ifndef SZO_GOS_GENERIC_OSTREAM_OPERATORS_HPP
#define SZO_GOS_GENERIC_OSTREAM_OPERATORS_HPP

#include "config/cpp_features.hpp"

#include <ostream>
#include <sstream>
#include <type_traits>

#ifdef GOS_LIB_CONCEPTS
#include <concepts>
#define GOS_CONCEPT(x) template<x T>
#else
#define GOS_CONCEPT(x) \
    template<typename T, typename = std::enable_if_t<x<T>::value>>
#endif
#define GOS_CONTAINER GOS_CONCEPT(gos::container)
#define GOS_PAIR GOS_CONCEPT(gos::pair)
#define GOS_COLLECTION GOS_CONCEPT(gos::collection)

namespace gos {

#ifdef GOS_LIB_REMOVE_CVREF
template <typename T>
using remove_cvref_t = std::remove_cvref_t<T>;
#else
template <typename T> struct remove_cvref : std::remove_cv<T> {};
template <typename T> struct remove_cvref<T&> : std::remove_cv<T> {};
template <typename T> struct remove_cvref<T&&> : std::remove_cv<T> {};
template <typename T> using remove_cvref_t = typename remove_cvref<T>::type;
#endif

#ifdef GOS_LIB_CONCEPTS
namespace detail {
template<typename T>
concept container_impl = std::regular<T> && std::swappable<T> &&
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

template<typename T>
// GCC produces lvalue reference while clang non ref value
concept pair = requires(T t) {
    { t.first } -> std::convertible_to<typename T::first_type>;
    { t.second } -> std::convertible_to<typename T::second_type>;
};
} // namespace detail

template<typename T>
concept container = detail::container<T> && detail::not_string<T>;

template<typename T>
concept is_container_v = container<T>;

template<typename T>
concept pair = detail::pair<gos::remove_cvref_t<T>>;

template<typename T>
concept is_pair_v = pair<T>;

template<typename T>
concept collection = container<T> || pair<T>;
} // namespace gos
#define GOS_COLLECTION_DEFINITION GOS_COLLECTION

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

template<typename T>
using pair_impl = std::void_t<typename T::first_type, typename T::second_type>;

template<typename T, typename = void>
struct pair : std::false_type {};

template<typename T>
struct pair<T, pair_impl<T>> : std::true_type {};
} // namespace detail

template<typename T, typename = void>
using container = detail::container<gos::remove_cvref_t<T>>;

template<typename T>
inline constexpr bool is_container_v = container<T>::value;

template<typename T, typename = void>
using pair = detail::pair<gos::remove_cvref_t<T>>;

template<typename T>
inline constexpr bool is_pair_v = pair<T>::value;

template<typename T, typename = void>
struct collection : std::disjunction<container<T>, pair<T>> {};
} // namespace gos
#define GOS_COLLECTION_DEFINITION template<typename T, typename>
#endif

GOS_COLLECTION
std::ostream& operator<<(std::ostream& stream, T&& collection);

namespace gos::detail {
GOS_CONTAINER
void proc_scalar_collection(std::ostream& stream, T&& collection) {
    stream << "[";
    for (auto it = collection.begin(); it != collection.end(); ++it) {
        stream << *it;
        if (std::next(it) == collection.end()) {
            stream << "]";
        } else {
            stream << ", ";
        }
    }
}

GOS_CONTAINER
void proc_complex_collection(std::ostream& stream, T&& collection) {
    stream << "{";
    for (auto it = collection.begin(); it != collection.end(); ++it) {
        stream << *it;
        if (std::next(it) != collection.end()) {
            stream << ",\n ";
        }
    }
    stream << "}";
}

GOS_CONTAINER
std::ostream& proc_container(std::ostream& stream, T&& container) {
    if (container.empty()) {
        stream << "[]";
        return stream;
    }
    using value_type = typename gos::remove_cvref_t<T>::value_type;
    if constexpr (std::is_scalar_v<value_type>) {
        proc_scalar_collection(stream, std::forward<T>(container));
    } else {
        proc_complex_collection(stream, std::forward<T>(container));
    }
    return stream;
}

GOS_PAIR
std::ostream& proc_pair(std::ostream& stream, T&& pair) {
    stream << "[" << pair.first << ", " << pair.second << "]";
    return stream;
}
} // namespace gos::detail

GOS_COLLECTION_DEFINITION
std::ostream& operator<<(std::ostream& stream, T&& collection) {
    using namespace gos::detail;
    if constexpr (gos::is_pair_v<T>) {
        return proc_pair(stream, std::forward<T>(collection));
    } else if constexpr (gos::is_container_v<T>) {
        return proc_container(stream, std::forward<T>(collection));
    }
    return stream;
}

namespace gos {
namespace detail {
template<typename T>
std::string to_string(T&& t) {
    std::stringstream ss;
    ss << std::forward<T>(t);
    return ss.str();
}
} // namespace detail

GOS_COLLECTION
std::string to_string(T&& collection) {
    return detail::to_string(std::forward<T>(collection));
}

inline std::string to_string(const std::string& str) {
    return detail::to_string(str);
}
} // namespace gos

#endif // SZO_GOS_GENERIC_OSTREAM_OPERATORS_HPP

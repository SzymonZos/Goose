#ifndef GENERIC_OSTREAM_OPERATORS_HPP
#define GENERIC_OSTREAM_OPERATORS_HPP

#include <concepts>
#include <ostream>
#include <tuple>
#include <type_traits>

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
concept container = container_impl<std::remove_cvref_t<T>>;

template<typename T>
concept not_string = !std::same_as<std::remove_cvref_t<T>, std::string>;
} // namespace detail

template<class T1, class T2>
std::ostream& operator<<(std::ostream& stream, const std::pair<T1, T2>& pair);

template<typename T>
requires detail::container<T> && detail::not_string<T> std::ostream&
operator<<(std::ostream& stream, T&& collection);

namespace detail {
template<container T>
void proc_scalar_collection(std::ostream& stream, T&& collection) {
    stream << "[";
    for (auto it = collection.begin(); it != collection.end(); ++it) {
        if (std::next(it) == collection.end()) {
            stream << *it << "]";
        } else {
            stream << *it << ", ";
        }
    }
}

template<container T>
void proc_complex_collection(std::ostream& stream, T&& collection) {
    stream << "{";
    for (auto it = collection.begin(); it != collection.end(); ++it) {
        if (std::next(it) == collection.end()) {
            stream << *it;
        } else {
            stream << *it << ",\n ";
        }
    }
    stream << "}";
}
} // namespace detail

template<typename T>
requires detail::container<T> && detail::not_string<T> std::ostream&
operator<<(std::ostream& stream, T&& collection) {
    if (collection.empty()) {
        stream << "[]";
        return stream;
    }
    using value_type = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::is_scalar_v<value_type>) {
        detail::proc_scalar_collection(stream, std::forward<T>(collection));
    } else {
        detail::proc_complex_collection(stream, std::forward<T>(collection));
    }
    return stream;
}

template<class T1, class T2>
std::ostream& operator<<(std::ostream& stream, const std::pair<T1, T2>& pair) {
    stream << "[" << pair.first << ", " << pair.second << "]";
    return stream;
}

#endif // GENERIC_OSTREAM_OPERATORS_HPP

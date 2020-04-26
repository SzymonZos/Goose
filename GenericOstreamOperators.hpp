#ifndef GENERIC_OSTREAM_OPERATORS_HPP
#define GENERIC_OSTREAM_OPERATORS_HPP

#include <array>
#include <ostream>
#include <tuple>
#include <type_traits>

template<template<typename...> class TT, typename... T>
static void ProcessScalarCollection(std::ostream& stream,
                                    const TT<T...>& collection) {
    stream << "[";
    for (auto it = collection.begin(); it != collection.end(); it++) {
        if (std::next(it) == collection.end()) {
            stream << *it << "]";
        } else {
            stream << *it << ", ";
        }
    }
}

template<template<typename...> class TT, typename... T>
static void ProcessComplexCollection(std::ostream& stream,
                                     const TT<T...>& collection) {
    stream << "{ ";
    for (auto it = collection.begin(); it != collection.end(); it++) {
        if (it != collection.begin()) {
            stream << "  ";
        }
        if (std::next(it) == collection.end()) {
            stream << *it;
        } else {
            stream << *it << ", \n";
        }
    }
    stream << " }";
}

template<typename T, std::size_t N>
static void ProcessScalarArray(std::ostream& stream,
                               const std::array<T, N>& array) {
    stream << "[";
    for (const auto& value : array) {
        if (&value == &array.back()) {
            stream << value << "]";
        } else {
            stream << value << ", ";
        }
    }
}

template<typename T, std::size_t N>
static void ProcessComplexArray(std::ostream& stream,
                                const std::array<T, N>& array) {
    stream << "{ ";
    for (const auto& value : array) {
        if (&value == &array.begin()) {
            stream << "  ";
        }
        if (&value == &array.back()) {
            stream << value;
        } else {
            stream << value << ", \n";
        }
    }
    stream << " }";
}

template<template<typename...> class TT,
         typename... T,
         typename = std::enable_if_t<!std::is_same_v<TT<T...>, std::string>>>
std::ostream& operator<<(std::ostream& stream, const TT<T...>& collection) {
    if (collection.empty()) {
        stream << "[]";
        return stream;
    }
    using FirstType = std::tuple_element_t<0, std::tuple<T...>>;
    if constexpr (std::is_scalar_v<FirstType>) {
        ProcessScalarCollection(stream, collection);
    } else {
        ProcessComplexCollection(stream, collection);
    }
    return stream;
}

template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& stream, const std::array<T, N>& array) {
    if (array.empty()) {
        stream << "[]";
        return stream;
    }
    if constexpr (std::is_scalar_v<T>) {
        ProcessScalarArray(stream, array);
    } else {
        ProcessComplexArray(stream, array);
    }
    return stream;
}

template<class T1, class T2>
std::ostream& operator<<(std::ostream& stream, const std::pair<T1, T2>& pair) {
    stream << "{ " << pair.first << ",\n" << pair.second << " }";
    return stream;
}

#endif // GENERIC_OSTREAM_OPERATORS_HPP

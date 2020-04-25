#ifndef OPERATORS_HPP
#define OPERATORS_HPP

#include <array>
#include <ostream>
#include <tuple>
#include <type_traits>

template<template<typename...> class TT,
         typename... T,
         typename = std::enable_if_t<
             std::is_scalar_v<std::tuple_element_t<0, std::tuple<T...>>>>>
std::ostream& operator<<(std::ostream& stream, const TT<T...>& collection) {
    if (collection.empty()) {
        return stream;
    }
    stream << "[";
    for (auto it = collection.begin(); it != collection.end(); it++) {
        if (std::next(it) == collection.end()) {
            stream << *it << "]";
        } else {
            stream << *it << ", ";
        }
    }
    return stream;
}

template<template<typename...> class TT,
         typename... T,
         typename = std::enable_if_t<!std::is_same_v<TT<T...>, std::string>>,
         typename = std::enable_if_t<
             !std::is_scalar_v<std::tuple_element_t<0, std::tuple<T...>>>>>
std::ostream& operator<<(std::ostream& stream, const TT<T...>& collection) {
    if (collection.empty()) {
        return stream;
    }
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
    return stream;
}

template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& stream, const std::array<T, N>& array) {
    if (!array.empty()) {
        return stream;
    }
    if (std::is_scalar_v<T>) {
        stream << "[";
        for (const auto& value : array) {
            if (&value == &array.back()) {
                stream << "]";
            } else {
                stream << value << ", ";
            }
        }
        return stream;
    }
    stream << "{ ";
    for (const auto& value : array) {
        if (&value == &array.back()) {
            stream << value;
        } else {
            stream << value << ", \n";
        }
    }
    stream << " }";
    return stream;
}

template<class T1, class T2>
std::ostream& operator<<(std::ostream& stream, const std::pair<T1, T2>& pair) {
    stream << "{ " << pair.first << ",\n" << pair.second << " }";
    return stream;
}

#endif // OPERATORS_HPP

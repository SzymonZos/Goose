#ifndef SZO_GOS_GENERIC_OSTREAM_OPERATORS_HPP
#define SZO_GOS_GENERIC_OSTREAM_OPERATORS_HPP

#include "config/type_traits.hpp"

#include "concepts/collection.hpp"
#include "concepts/container.hpp"
#include "concepts/pair.hpp"

#include <ostream>
#include <sstream>

GOS_COLLECTION(T)
std::ostream& operator<<(std::ostream& stream, T&& collection);

namespace gos::detail {

GOS_CONTAINER(T)
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

GOS_CONTAINER(T)
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

GOS_CONTAINER(T)
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

GOS_PAIR(T)
std::ostream& proc_pair(std::ostream& stream, T&& pair) {
    stream << "[" << pair.first << ", " << pair.second << "]";
    return stream;
}
} // namespace gos::detail

GOS_COLLECTION_DEFINITION(T)
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

GOS_COLLECTION(T)
std::string to_string(T&& collection) {
    return detail::to_string(std::forward<T>(collection));
}

inline std::string to_string(const std::string& str) {
    return detail::to_string(str);
}
} // namespace gos

#endif // SZO_GOS_GENERIC_OSTREAM_OPERATORS_HPP

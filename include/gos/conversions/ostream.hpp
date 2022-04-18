#ifndef SZO_GOS_OSTREAM_HPP
#define SZO_GOS_OSTREAM_HPP

#include "gos/config/type_traits.hpp"

#include "gos/concepts/collection.hpp"
#include "gos/concepts/container.hpp"
#include "gos/concepts/pair.hpp"

#include <ostream>

GOS_COLLECTION(T)
std::ostream& operator<<(std::ostream& stream, T&& collection);

namespace gos::detail {
GOS_CONTAINER(T)
void process_scalar_collection(std::ostream& stream, T&& collection) {
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
void process_complex_collection(std::ostream& stream, T&& collection) {
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
std::ostream& process_container(std::ostream& stream, T&& container) {
    if (container.empty()) {
        stream << "[]";
        return stream;
    }
    using value_type = typename gos::remove_cvref_t<T>::value_type;
    if constexpr (std::is_scalar_v<value_type>) {
        process_scalar_collection(stream, std::forward<T>(container));
    } else {
        process_complex_collection(stream, std::forward<T>(container));
    }
    return stream;
}

GOS_PAIR(T)
std::ostream& process_pair(std::ostream& stream, T&& pair) {
    stream << "[" << pair.first << ", " << pair.second << "]";
    return stream;
}
} // namespace gos::detail

GOS_COLLECTION_DEFINITION(T)
std::ostream& operator<<(std::ostream& stream, T&& collection) {
    using namespace gos::detail;
    if constexpr (gos::is_pair_v<T>) {
        return process_pair(stream, std::forward<T>(collection));
    } else if constexpr (gos::is_container_v<T>) {
        return process_container(stream, std::forward<T>(collection));
    }
    return stream;
}

#endif // SZO_GOS_OSTREAM_HPP

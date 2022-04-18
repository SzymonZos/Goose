#ifndef SZO_GOS_OSTREAM_HPP
#define SZO_GOS_OSTREAM_HPP

#include "gos/config/type_traits.hpp"

#include "gos/concepts/collection.hpp"
#include "gos/concepts/container.hpp"
#include "gos/concepts/pair.hpp"

#include <ostream>

GOS_COLLECTION(Collection)
std::ostream& operator<<(std::ostream& stream, Collection&& collection);

namespace gos::detail {
GOS_CONTAINER(Container)
void process_scalar_container(std::ostream& stream, Container&& container) {
    stream << "[";
    for (auto it = container.begin(); it != container.end(); ++it) {
        stream << *it;
        if (std::next(it) == container.end()) {
            stream << "]";
        } else {
            stream << ", ";
        }
    }
}

GOS_CONTAINER(Container)
void process_complex_container(std::ostream& stream, Container&& container) {
    stream << "{";
    for (auto it = container.begin(); it != container.end(); ++it) {
        stream << *it;
        if (std::next(it) != container.end()) {
            stream << ",\n ";
        }
    }
    stream << "}";
}

GOS_CONTAINER(Container)
std::ostream& process_container(std::ostream& stream, Container&& container) {
    if (container.empty()) {
        stream << "[]";
        return stream;
    }
    using value_type = typename gos::remove_cvref_t<Container>::value_type;
    if constexpr (std::is_scalar_v<value_type>) {
        process_scalar_container(stream, std::forward<Container>(container));
    } else {
        process_complex_container(stream, std::forward<Container>(container));
    }
    return stream;
}

GOS_PAIR(Pair)
std::ostream& process_pair(std::ostream& stream, Pair&& pair) {
    stream << "[" << pair.first << ", " << pair.second << "]";
    return stream;
}
} // namespace gos::detail

GOS_COLLECTION_DEFINITION(Collection)
std::ostream& operator<<(std::ostream& stream, Collection&& collection) {
    using namespace gos::detail;
    if constexpr (gos::is_pair_v<Collection>) {
        return process_pair(stream, std::forward<Collection>(collection));
    } else if constexpr (gos::is_container_v<Collection>) {
        return process_container(stream, std::forward<Collection>(collection));
    }
    return stream;
}

#endif // SZO_GOS_OSTREAM_HPP

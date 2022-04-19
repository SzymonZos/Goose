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
GOS_COLLECTION(Collection)
using ValueType = typename gos::remove_cvref_t<Collection>::value_type;

GOS_COLLECTION(Collection)
std::ostream&
process_collection(std::ostream& stream, Collection&& collection, std::size_t padding = 0);

GOS_CONTAINER(Container)
void process_scalar_container(std::ostream& stream, Container&& container) {
    stream << "[";
    for (auto it = container.begin(); it != container.end(); ++it) {
        stream << *it;
        if (std::next(it) != container.end()) {
            stream << ", ";
        }
    }
    stream << "]";
}

GOS_CONTAINER(Container)
void process_complex_container(std::ostream& stream, Container&& container, std::size_t padding) {
    stream << "{";
    padding++;
    for (auto it = container.begin(); it != container.end(); ++it) {
        process_collection(stream, std::forward<ValueType<Container>>(*it), padding);
        if (std::next(it) != container.end()) {
            stream << ",\n" << std::string(padding, ' ');
        }
    }
    stream << "}";
}

GOS_CONTAINER(Container)
std::ostream& process_container(std::ostream& stream, Container&& container, std::size_t padding) {
    using ContainerValueType = ValueType<Container>;
    if constexpr (std::is_scalar_v<ContainerValueType> || gos::is_pair_v<ContainerValueType>) {
        process_scalar_container(stream, std::forward<Container>(container));
    } else {
        process_complex_container(stream, std::forward<Container>(container), padding);
    }
    return stream;
}

GOS_PAIR(Pair)
std::ostream& process_pair(std::ostream& stream, Pair&& pair) {
    stream << "[" << pair.first << ", " << pair.second << "]";
    return stream;
}

GOS_COLLECTION_DEFINITION(Collection)
std::ostream&
process_collection(std::ostream& stream, Collection&& collection, std::size_t padding) {
    if constexpr (gos::is_pair_v<Collection>) {
        return process_pair(stream, std::forward<Collection>(collection));
    } else if constexpr (gos::is_container_v<Collection>) {
        return process_container(stream, std::forward<Collection>(collection), padding);
    }
    return stream;
}
} // namespace gos::detail

GOS_COLLECTION_DEFINITION(Collection)
std::ostream& operator<<(std::ostream& stream, Collection&& collection) {
    return gos::detail::process_collection(stream, std::forward<Collection>(collection));
}

#endif // SZO_GOS_OSTREAM_HPP

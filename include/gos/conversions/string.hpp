#ifndef SZO_GOS_STRING_HPP
#define SZO_GOS_STRING_HPP

#include "gos/concepts/collection.hpp"

#include "ostream.hpp"

#include <sstream>
#include <string>

namespace gos {
namespace detail {
template<typename T>
std::string to_string(T&& t) {
    std::stringstream ss;
    ss << std::forward<T>(t);
    return ss.str();
}
} // namespace detail

GOS_COLLECTION(Collection)
std::string to_string(Collection&& collection) {
    return detail::to_string(std::forward<Collection>(collection));
}

inline std::string to_string(const std::string& str) {
    return detail::to_string(str);
}
} // namespace gos

#endif // SZO_GOS_STRING_HPP

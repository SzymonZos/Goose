#ifndef SZO_GOS_COLLECTION_HPP
#define SZO_GOS_COLLECTION_HPP

#include "gos/config/cpp_features.hpp"
#include "gos/config/type_traits.hpp"

#include "container.hpp"
#include "pair.hpp"

namespace gos {

#ifdef GOS_LIB_CONCEPTS
template<typename T>
concept collection = container<T> || pair<T>;

#else
template<typename T, typename = void>
struct collection : std::disjunction<container<T>, pair<T> > {};

#endif // GOS_LIB_CONCEPTS
} // namespace gos

#endif // SZO_GOS_COLLECTION_HPP

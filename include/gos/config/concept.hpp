#ifndef SZO_GOS_CONCEPT_HPP
#define SZO_GOS_CONCEPT_HPP

#include "cpp_features.hpp"

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

#ifdef GOS_LIB_CONCEPTS
#define GOS_COLLECTION_DEFINITION GOS_COLLECTION
#else
#define GOS_COLLECTION_DEFINITION template<typename T, typename>
#endif

#endif // SZO_GOS_CONCEPT_HPP

#ifndef SZO_GOS_CONCEPT_HPP
#define SZO_GOS_CONCEPT_HPP

#include "cpp_features.hpp"

#ifdef GOS_LIB_CONCEPTS
#include <concepts>
#define GOS_CONCEPT(CONCEPT, T) template<CONCEPT T>
#else
#define GOS_CONCEPT(CONCEPT, T) \
    template<typename T, typename = std::enable_if_t<CONCEPT<T>::value>>
#endif

#define GOS_CONTAINER(T) GOS_CONCEPT(gos::container, T)
#define GOS_PAIR(T) GOS_CONCEPT(gos::pair, T)
#define GOS_COLLECTION(T) GOS_CONCEPT(gos::collection, T)

#ifdef GOS_LIB_CONCEPTS
#define GOS_COLLECTION_DEFINITION(T) GOS_COLLECTION(T)
#else
#define GOS_COLLECTION_DEFINITION(T) template<typename T, typename>
#endif

#endif // SZO_GOS_CONCEPT_HPP

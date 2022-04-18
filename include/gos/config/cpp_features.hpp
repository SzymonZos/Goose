#ifndef SZO_GOS_CPP_FEATURES_HPP
#define SZO_GOS_CPP_FEATURES_HPP

#if __has_include(<version>)
#include <version>
#else
#include <ciso646>
#endif

#ifdef __cpp_lib_remove_cvref
#define GOS_LIB_REMOVE_CVREF
#endif

#ifdef __cpp_lib_concepts
#define GOS_LIB_CONCEPTS
#endif

#endif // SZO_GOS_CPP_FEATURES_HPP

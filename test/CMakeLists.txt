add_executable(test-gos main.cpp tests.cpp)

if(GOS_USE_LIBCPP)
    target_compile_options(test-gos PRIVATE
        "$<$<STREQUAL:${CMAKE_CXX_COMPILER_ID},Clang>:-stdlib=libc++>"
    )
    set(LIBCPP_LINK_OPTIONS "-stdlib=libc++ -fuse-ld=lld -lc++abi")
    target_link_options(test-gos PRIVATE
        "$<$<STREQUAL:${CMAKE_CXX_COMPILER_ID},Clang>:${LIBCPP_LINK_OPTIONS}>"
    )
else()
    target_compile_options(test-gos PRIVATE
        "$<$<STREQUAL:${CMAKE_CXX_COMPILER_ID},Clang>:-stdlib=libstdc++>"
    )
    target_link_options(test-gos PRIVATE
        "$<$<STREQUAL:${CMAKE_CXX_COMPILER_ID},Clang>:-stdlib=libstdc++>"
    )
endif()

target_compile_options(test-gos PRIVATE
    -Wall
    -Wextra
    -Werror
    -Wshadow # Warn if variable overshadows parent context
    -Wnon-virtual-dtor # Warn if class with virtual func has no virtual dtor
    -Wcast-align # Warn for potential performance problem casts
    -Wunused # Warn on anything being unused
    -Wno-overloaded-virtual # Don't warn if overload a virtual function
    -Wpedantic # Warn if non-standard C++ is used
    -Wconversion # Warn on type conversions that may lose data
    -Wsign-conversion # Warn on sign conversions
    -Wdouble-promotion # Warn if float is implicit promoted to double
    -Wold-style-cast # Warn if c style cast is performed
)

target_include_directories(test-gos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(test-gos PRIVATE gos)

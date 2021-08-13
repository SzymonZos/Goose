set(TEST_SOURCES
    array.cpp
    pair.cpp
    string.cpp
    vector.cpp
    unordered_map.cpp
)
add_executable(test-gos main.cpp ${TEST_SOURCES})

if(GOS_USE_LIBCPP)
    target_compile_options(test-gos PRIVATE
        "$<$<CXX_COMPILER_ID:AppleClang,Clang>:-stdlib=libc++>"
    )
    set(LIBCPP_LINK_OPTIONS "-stdlib=libc++ -fuse-ld=lld -lc++abi")
    target_link_options(test-gos PRIVATE
        "$<$<CXX_COMPILER_ID:AppleClang,Clang>:${LIBCPP_LINK_OPTIONS}>"
    )
endif()

# As for now MSYS2 does not provide ASAN support apart from clang64 toolchain
# https://github.com/msys2/MINGW-packages/issues/3163
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
#TODO: Investigate why it does not work on github actions
#    target_compile_options(test-gos PRIVATE
#        "$<$<CONFIG:Debug>:-fsanitize=undefined,address>"
#    )
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

#include "gos/goose.hpp"

#include <array>

#include <catch.hpp>

namespace {
template<typename T>
using EmptyArr = std::array<T, 0>;

TEST_CASE("Empty array stringification", "[Empty]") {
    EmptyArr<int> arr{};
    REQUIRE(gos::to_string(arr) == "[]");
}

TEST_CASE("Empty 2D array stringification", "[Empty]") {
    EmptyArr<EmptyArr<float>> arr{};
    REQUIRE(gos::to_string(arr) == "{}");
}

TEST_CASE("Empty 4D array stringification", "[Empty]") {
    EmptyArr<EmptyArr<EmptyArr<EmptyArr<unsigned>>>> arr{};
    REQUIRE(gos::to_string(arr) == "{}");
}

TEST_CASE("Int array basic stringification", "[Scalar]") {
    std::array<int, 7> arr{1, 2, 3, -1, 0, 10};
    REQUIRE(gos::to_string(arr) == "[1, 2, 3, -1, 0, 10, 0]");
}

TEST_CASE("Float array basic stringification", "[Scalar]") {
    // It seems that only 6 digits of float are stored in the string stream
    std::array<float, 8> arr{1407654.807F,
                             2476523.4324F,
                             -4342358.4987F,
                             34325.4234F,
                             -23.5405F,
                             0.432454F,
                             -42.76923F,
                             0.7650234F};
    REQUIRE(gos::to_string(arr) == "[1.40765e+06, 2.47652e+06, -4.34236e+06, 34325.4,"
                                   " -23.5405, 0.432454, -42.7692, 0.765023]");
}

TEST_CASE("2D int array stringification", "[Complex]") {
    using Arr = std::array<int, 5>;
    std::array<Arr, 3> arr{{{1, 24234234, 3, -1, 0}, {10, 6000}, {777}}};
    REQUIRE(gos::to_string(arr) == "{[1, 24234234, 3, -1, 0],\n"
                                   " [10, 6000, 0, 0, 0],\n"
                                   " [777, 0, 0, 0, 0]}");
}

TEST_CASE("3D int array stringification", "[Complex]") {
    using Arr = std::array<int, 5>;
    // clang-format off
    std::array<std::array<Arr, 3>, 2> arr = {
        {{{{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}}},
         {{{16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}, {26, 27, 28, 29, 30}}}}
    };
    // clang-format on
    REQUIRE(gos::to_string(arr) == "{{[1, 2, 3, 4, 5],\n"
                                   "  [6, 7, 8, 9, 10],\n"
                                   "  [11, 12, 13, 14, 15]},\n"
                                   " {[16, 17, 18, 19, 20],\n"
                                   "  [21, 22, 23, 24, 25],\n"
                                   "  [26, 27, 28, 29, 30]}}");
}
} // namespace

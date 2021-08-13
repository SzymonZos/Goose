#include "gos/gos.hpp"

#include <array>

#include <catch.hpp>

namespace {
TEST_CASE("Empty array stringification", "[Empty]") {
    std::array<int, 0> arr{};
    REQUIRE(gos::to_string(arr) == "[]");
}

TEST_CASE("Array basic stringification", "[Scalar]") {
    std::array<int, 7> arr{1, 2, 3, -1, 0, 10};
    REQUIRE(gos::to_string(arr) == "[1, 2, 3, -1, 0, 10, 0]");
}
}

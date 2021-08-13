#include "gos/gos.hpp"

#include <vector>

#include <catch.hpp>

namespace {
TEST_CASE("Empty vector stringification", "[Empty]") {
    std::vector<int> vec{};
    REQUIRE(gos::to_string(vec) == "[]");
}

TEST_CASE("Vector basic stringification", "[Scalar]") {
    std::vector<int> vec{0, 10, 0, -1, 3, 2, 1};
    REQUIRE(gos::to_string(vec) == "[0, 10, 0, -1, 3, 2, 1]");
}

TEST_CASE("Empty vector of vectors stringification", "[Empty]") {
    using Vec2 = std::vector<std::vector<int>>;
    Vec2 vec2{};
    REQUIRE(gos::to_string(vec2) == "[]");
}
}

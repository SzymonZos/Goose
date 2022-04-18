#include "gos/gos.hpp"

#include <vector>

#include <catch.hpp>

namespace {
TEST_CASE("Empty vector stringification", "[Empty]") {
    std::vector<int> vec{};
    REQUIRE(gos::to_string(vec) == "[]");
}

TEST_CASE("Empty 2D vector stringification", "[Empty]") {
    std::vector<std::vector<int>> vec{};
    REQUIRE(gos::to_string(vec) == "[]");
}

TEST_CASE("Empty 4D vector stringification", "[Empty]") {
    std::vector<std::vector<std::vector<std::vector<int>>>> vec{};
    REQUIRE(gos::to_string(vec) == "[]");
}

TEST_CASE("Int vector stringification", "[Scalar]") {
    std::vector<int> vec{0, 10, 0, -1, 3, 2, 1};
    REQUIRE(gos::to_string(vec) == "[0, 10, 0, -1, 3, 2, 1]");
}

TEST_CASE("Double vector stringification", "[Scalar]") {
    std::vector<double> vec{0.3647438573,
                            10.5348534,
                            -53450.63565,
                            -1.54364367609,
                            343252355.767567,
                            2.654675478,
                            176575676.534};
    REQUIRE(gos::to_string(vec) == "[0.364744, 10.5349, -53450.6, -1.54364, "
                                   "3.43252e+08, 2.65468, 1.76576e+08]");
}

TEST_CASE("2D int vector stringification", "[Complex]") {
    using Vec2 = std::vector<std::vector<int>>;
    std::vector<int> vec{0, 10, 0, -1, 3, 2, 1};
    Vec2 vec2{vec, vec, vec, vec};
    REQUIRE(gos::to_string(vec2) == "{[0, 10, 0, -1, 3, 2, 1],\n"
                                    " [0, 10, 0, -1, 3, 2, 1],\n"
                                    " [0, 10, 0, -1, 3, 2, 1],\n"
                                    " [0, 10, 0, -1, 3, 2, 1]}");
}

TEST_CASE("3D int vector basic stringification", "[Complex]") {
    using Vec3 = std::vector<std::vector<std::vector<int>>>;
    Vec3 vec{{{2, -2159, 69504, 664}, {543, 654}, {9098, 543}}, {}, {{11, 23}, {777}}};
    REQUIRE(gos::to_string(vec) == "{{[2, -2159, 69504, 664],\n"
                                   "  [543, 654],\n"
                                   "  [9098, 543]},\n"
                                   " [],\n"
                                   " {[11, 23],\n"
                                   "  [777]}}");
}
} // namespace

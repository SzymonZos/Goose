#include "gos/gos.hpp"

#include <array>
#include <string>
#include <unordered_map>
#include <vector>

#include "catch.hpp"

namespace {
TEST_CASE("Empty array stringification", "[Empty]") {
    std::array<int, 0> arr{};
    REQUIRE(gos::to_string(arr) == "[]");
}

TEST_CASE("Array basic stringification", "[Scalar]") {
    std::array<int, 7> arr{1, 2, 3, -1, 0, 10};
    REQUIRE(gos::to_string(arr) == "[1, 2, 3, -1, 0, 10, 0]");
}

TEST_CASE("Empty vector stringification", "[Empty]") {
    std::vector<int> vec{};
    REQUIRE(gos::to_string(vec) == "[]");
}

TEST_CASE("Vector basic stringification", "[Scalar]") {
    std::vector<int> vec{0, 10, 0, -1, 3, 2, 1};
    REQUIRE(gos::to_string(vec) == "[0, 10, 0, -1, 3, 2, 1]");
}

TEST_CASE("Is empty string still empty", "[Empty]") {
    std::string str{};
    REQUIRE(gos::to_string(str).empty());
}

TEST_CASE("Is basic string still working", "[Scalar]") {
    std::string str{"something"};
    REQUIRE(gos::to_string(str) == "something");
}

TEST_CASE("Empty pair of ints stringification", "[Empty]") {
    std::pair<int, int> pair;
    REQUIRE(gos::to_string(pair) == "[0, 0]");
}

TEST_CASE("Empty pair of vectors stringification", "[Empty]") {
    using Vec = std::vector<int>;
    std::pair<Vec, Vec> pair;
    REQUIRE(gos::to_string(pair) == "[[], []]");
}

TEST_CASE("Pair of vectors stringification", "[Scalar]") {
    using Vec = std::vector<int>;
    Vec vec{0, 10, 0, -1, 3, 2, 1};
    std::pair<Vec, Vec> pair(vec, vec);
    REQUIRE(gos::to_string(pair) ==
            "[[0, 10, 0, -1, 3, 2, 1], [0, 10, 0, -1, 3, 2, 1]]");
}

TEST_CASE("Empty unordered map stringification", "[Empty]") {
    using HashMap = std::unordered_map<std::string, int>;
    HashMap map{};
    REQUIRE(gos::to_string(map) == "[]");
}

TEST_CASE("Unordered map of string and int stringification", "[Complex]") {
    using HashMap = std::unordered_map<std::string, int>;
    HashMap map{{"xD", 1}, {"smth", 2}, {":(((", 3}};
    REQUIRE(gos::to_string(map) == "{[:(((, 3],\n"
                                   " [smth, 2],\n"
                                   " [xD, 1]}");
}

TEST_CASE("Empty vector of vectors stringification", "[Empty]") {
    using Vec2 = std::vector<std::vector<int>>;
    Vec2 vec2{};
    REQUIRE(gos::to_string(vec2) == "[]");
}

TEST_CASE("Vector of vectors of int stringification", "[Complex]") {
    using Vec2 = std::vector<std::vector<int>>;
    std::vector<int> vec{0, 10, 0, -1, 3, 2, 1};
    Vec2 vec2{vec, vec, vec, vec};
    REQUIRE(gos::to_string(vec2) == "{[0, 10, 0, -1, 3, 2, 1],\n"
                                    " [0, 10, 0, -1, 3, 2, 1],\n"
                                    " [0, 10, 0, -1, 3, 2, 1],\n"
                                    " [0, 10, 0, -1, 3, 2, 1]}");
}
} // namespace

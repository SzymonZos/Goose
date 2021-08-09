#include "gos/gos.hpp"

#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "catch.hpp"

namespace {

template<typename T>
std::string to_string(T&& container) {
    std::stringstream ss;
    ss << container;
    return ss.str();
}

TEST_CASE("Array basic stringification", "[Scalar]") {
    std::array<int, 7> arr{1, 2, 3, -1, 0, 10};
    REQUIRE(to_string(arr) == "[1, 2, 3, -1, 0, 10, 0]");
}

TEST_CASE("Vector basic stringification", "[Scalar]") {
    std::vector<int> vec{0, 10, 0, -1, 3, 2, 1};
    REQUIRE(to_string(vec) == "[0, 10, 0, -1, 3, 2, 1]");
}

TEST_CASE("Is string still working", "[Scalar]") {
    std::string str{"something"};
    REQUIRE(to_string(str) == "something");
}

TEST_CASE("Pair of vectors stringification", "[Scalar]") {
    using Vec = std::vector<int>;
    Vec vec{0, 10, 0, -1, 3, 2, 1};
    std::pair<Vec, Vec> pair(vec, vec);
    REQUIRE(to_string(pair) ==
            "[[0, 10, 0, -1, 3, 2, 1], [0, 10, 0, -1, 3, 2, 1]]");
}

TEST_CASE("Unordered map of string and int stringification", "[Complex]") {
    using HashMap = std::unordered_map<std::string, int>;
    HashMap map{{"xD", 1}, {"smth", 2}, {":(((", 3}};
    REQUIRE(to_string(map) == "{[:(((, 3],\n"
                              " [smth, 2],\n"
                              " [xD, 1]}");
}

TEST_CASE("Vector of vectors of int stringification", "[Complex]") {
    using Vec2 = std::vector<std::vector<int>>;
    std::vector<int> vec{0, 10, 0, -1, 3, 2, 1};
    Vec2 vec2{vec, vec, vec, vec};
    REQUIRE(to_string(vec2) == "{[0, 10, 0, -1, 3, 2, 1],\n"
                               " [0, 10, 0, -1, 3, 2, 1],\n"
                               " [0, 10, 0, -1, 3, 2, 1],\n"
                               " [0, 10, 0, -1, 3, 2, 1]}");
}
} // namespace

#include "gos/gos.hpp"

#include <unordered_map>
#include <string>
#include <vector>

#include <catch.hpp>

namespace {
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



TEST_CASE("Vector of vectors of int stringification", "[Complex]") {
    using Vec2 = std::vector<std::vector<int>>;
    std::vector<int> vec{0, 10, 0, -1, 3, 2, 1};
    Vec2 vec2{vec, vec, vec, vec};
    REQUIRE(gos::to_string(vec2) == "{[0, 10, 0, -1, 3, 2, 1],\n"
                                    " [0, 10, 0, -1, 3, 2, 1],\n"
                                    " [0, 10, 0, -1, 3, 2, 1],\n"
                                    " [0, 10, 0, -1, 3, 2, 1]}");
}
}

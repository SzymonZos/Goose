#include "gos/gos.hpp"

#include <utility>
#include <vector>

#include "catch.hpp"

namespace {
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
} // namespace
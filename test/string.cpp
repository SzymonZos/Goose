#include "gos/goose.hpp"

#include <string>

#include <catch.hpp>

namespace {
TEST_CASE("Is empty string still empty", "[Empty]") {
    std::string str{};
    REQUIRE(gos::to_string(str).empty());
}

TEST_CASE("Is basic string still working", "[Scalar]") {
    std::string str{"something"};
    REQUIRE(gos::to_string(str) == "something");
}
} // namespace

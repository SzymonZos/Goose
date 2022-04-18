#include "gos/gos.hpp"

#include <string>
#include <unordered_map>

#include <catch.hpp>

namespace {
TEST_CASE("Empty unordered map stringification", "[Empty]") {
    using HashMap = std::unordered_map<std::string, int>;
    HashMap map{};
    REQUIRE(gos::to_string(map) == "[]");
}

TEST_CASE("Unordered map of string and int stringification", "[Complex]") {
    using HashMap = std::unordered_map<std::string, int>;
    using Catch::Matchers::Contains;
    using Catch::Matchers::EndsWith;
    using Catch::Matchers::StartsWith;

    HashMap map{{"xD", 1}, {"smth", 2}, {":(((", 3}};
    REQUIRE_THAT(gos::to_string(map),
                 StartsWith("{[") && Contains("[xD, 1]") && Contains("[smth, 2]") &&
                     Contains("[:(((, 3]") && EndsWith("]}") && Contains(",\n"));
}
} // namespace

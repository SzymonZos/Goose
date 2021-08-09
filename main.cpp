#include "GenericOstreamOperators.hpp"
#include <array>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
    std::array<int, 7> arr{1, 2, 3, -1, 0, 10};
    std::vector<int> vec(arr.rbegin(), arr.rend());
    std::string str{"something"};
    std::pair<std::vector<int>, std::vector<int>> pair(vec, vec);
    std::unordered_map<std::string, int> map{{"xD", 1},
                                             {"smth", 2},
                                             {":(((", 3}};
    std::vector<std::vector<int>> vec_vec{vec, vec, vec, vec};
    std::cout << arr << '\n' << vec << '\n' << str << '\n' << pair << '\n';
    std::cout << map << '\n' << vec_vec;
    return 0;
}

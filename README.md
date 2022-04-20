# Goose

![Linux and Mac builds](https://github.com/SzymonZos/Goose/actions/workflows/cmake-builds-mac-linux.yml/badge.svg)

Goose is a small utility library which supports inserting STL collection-like
types to the output streams. It also provides stringification of such
collections.

## Supported platforms

Supported C++ standard versions are 17 and 20. Linux and Mac are tested on the
CI. Support for Windows is not guaranteed.

## Usage

1. Goose can be used as single header library from the release version.
2. Another way of using Goose is to add this repo as a submodule. Currently,
   only CMake is supported as a build system.

## Examples

### Using overloaded `operator<<` for STL collections

One-dimensional vector:

```c++
std::vector<int> vec{1, 2, 3, 4};
std::cout << vec << std::endl;
```

Output:

```text
[1, 2, 3, 4]
```

Two-dimensional vector (I'm not saying you should use this example in
production :D):

```c++
using Vec2 = std::vector<std::vector<int>>;
Vec2 vec2{{1, 2, 3, 4}, {-1, -2, -3, -4}, {42, -68}};
std::cout << vec2 << std::endl;
```

Output:

```text
{[1, 2, 3, 4],
 [-1, -2, -3, -4],
 [42, -68]}
```

### Using `gos::to_string` for STL collections

```cpp
using HashMap = std::unordered_map<std::string, int>;
HashMap map{{"some", 42}, {"random", 600}, {"words", 68}};
auto stringified_map = gos::to_string(map);
std::printf("Stringified map: %s\n", stringified_map.c_str());
```

Possible output:

```text
Stringified map: [[words, 68], [random, 600], [some, 42]]
```

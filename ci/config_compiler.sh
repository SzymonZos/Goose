#!/usr/bin/env bash
set -Eeuo pipefail

case "$1" in
  *gcc*)
    sudo apt install gcc-10 g++-10
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 10
    echo "CC=/usr/bin/gcc" >> "$GITHUB_ENV"
    sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10 10
    echo "CXX=/usr/bin/g++" >> "$GITHUB_ENV"
    ;;
  *clang*)
    sudo apt install llvm-12-dev clang-12 lld-12 libc++-12-dev libc++abi-12-dev
    sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-12 10
    echo "CC=/usr/bin/clang" >> "$GITHUB_ENV"
    sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-12 10
    echo "CXX=/usr/bin/clang++" >> "$GITHUB_ENV"
    ;;
esac

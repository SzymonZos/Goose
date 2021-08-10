#!/usr/bin/env bash
set -Eeuo pipefail

case "$1" in
  *gcc*)
    echo "CC=$(which gcc-10)" >> "$GITHUB_ENV"
    echo "CXX=$(which g++-10)" >> "$GITHUB_ENV"
    ;;
  *clang*)
    CC="$(which clang-12)" || CC="$(brew --prefix llvm)/bin/clang"
    CXX="$(which clang++-12)" || CXX="$(brew --prefix llvm)/bin/clang++"
    echo "CC=$CC" >> "$GITHUB_ENV"
    echo "CXX=$CXX" >> "$GITHUB_ENV"
    ;;
esac

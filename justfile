set shell := ["pwsh.exe", "-Command"]

CC_FLAGS := "-I./options -L./options -loptions"

build:
  cd ./build && cmake ".." && cmake --build .

test: build
  gcc tests/test.c {{CC_FLAGS}} -o options_tests
  ./options_tests

run_examples:
  gcc examples/stringIndexing.c {{CC_FLAGS}} -o build/stringIndexing
  gcc examples/solutionExists.c {{CC_FLAGS}} -o build/solutionExists
  gcc examples/isInList.c {{CC_FLAGS}} -o build/isInList
  gcc examples/fileIO.c {{CC_FLAGS}} -o build/fileIO
  ./build/stringIndexing
  ./build/solutionExists
  ./build/isInList
  ./build/fileIO README.md

build_debug:
  clang examples/fileIO.c {{CC_FLAGS}} -g -Wall -o build/fileIO

set shell := ["cmd.exe", "/c"]

build_object:
  gcc -c options/options.c -o options/options.o
static_build: build_object
  ar rcs options/options.lib options/options.o

build_test: static_build
  gcc tests/test.c -I./options -L./options -loptions -o options_tests

test: build_test
  options_tests

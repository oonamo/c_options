set shell := ["pwsh.exe", "-Command"]

build:
  cd ./build && cmake ".." && cmake --build .

test: build
  gcc tests/test.c -I./options -L./options -loptions -o options_tests
  ./options_tests

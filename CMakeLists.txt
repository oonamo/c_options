cmake_minimum_required(VERSION 3.10)
project(Options C)

set(OPTIONS_VERSION 0.1)

add_library(options STATIC options/options.c)

target_include_directories(options PUBLIC options)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

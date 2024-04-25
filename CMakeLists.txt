cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)

project(
  rasterization
  LANGUAGES CXX C
  DESCRIPTION "rasterization by cpp"
  VERSION 0.1.0
)

aux_source_directory(src SOURCE_FILES)
file(GLOB_RECURSE HEADER_FILES "src/*.h(pp?)")

add_executable(rasterization ${SOURCE_FILES} ${HEADER_FILES})
cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
  rasterization
  LANGUAGES CXX C
  DESCRIPTION "rasterization by cpp"
  VERSION 0.1.0
)

add_subdirectory(core)
add_subdirectory(src)

add_executable(rasterization main.cpp)
target_link_libraries(rasterization PUBLIC renderer)


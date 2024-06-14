set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE MATH_SOURCE_FILES "*.cpp")


add_library(core ${MATH_SOURCE_FILES})
target_include_directories(core INTERFACE .)
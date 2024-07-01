
file(GLOB_RECURSE SOURCE_FILES "./*.cpp")

add_library(renderer ${SOURCE_FILES})

target_link_libraries(renderer PUBLIC core)
target_include_directories(renderer PUBLIC .)
target_compile_definitions(renderer PRIVATE USE_CPU_RENDERER=1)
target_compile_definitions(renderer PRIVATE USE_WINDOWS_WINDOW=1)
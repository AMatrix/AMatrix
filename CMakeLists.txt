cmake_minimum_required (VERSION 3.3)
project(AMatrix)

set(AMATRIX_VERSION_MAJOR 0)
set(AMATRIX_VERSION_MINOR 1)

include_directories("${PROJECT_SOURCE_DIR}/include")
enable_testing()

add_subdirectory(test)
add_subdirectory(benchmarks)
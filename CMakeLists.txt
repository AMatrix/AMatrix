cmake_minimum_required (VERSION 3.2.2)
project(AMatrix)

set(AMATRIX_VERSION_MAJOR 0)
set(AMATRIX_VERSION_MINOR 1)

# Allowed build types
SET( CMAKE_CONFIGURATION_TYPES Release RelWithDebInfo Debug )

# If build mode is not defined, assume Release
if(NOT CMAKE_BUILD_TYPE)
  message("Undefined CMAKE_BUILD_TYPE, building in 'Release' mode.")
  set(CMAKE_BUILD_TYPE Release)
else(NOT CMAKE_BUILD_TYPE)
  list(FIND CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} FOUND_MODE)
  if(FOUND_MODE EQUAL -1)
    message("Unknown CMAKE_BUILD_TYPE '${CMAKE_BUILD_TYPE}', using 'Release'.")
    set(CMAKE_BUILD_TYPE Release)
  endif(FOUND_MODE EQUAL -1)
endif(NOT CMAKE_BUILD_TYPE)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -funroll-loops -std=c++11")

include_directories("${PROJECT_SOURCE_DIR}/include")
enable_testing()

add_subdirectory(test)
add_subdirectory(benchmarks)
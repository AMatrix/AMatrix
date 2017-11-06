include_directories("${PROJECT_SOURCE_DIR}/include")

if( EIGEN3_INCLUDE_DIR )
    message("EIGEN3_INCLUDE_DIR : ${EIGEN3_INCLUDE_DIR}")
    add_definitions(-DAMATRIX_COMPARE_WITH_EIGEN)
    add_definitions(-DNDEBUG)
    include_directories ( "${EIGEN3_INCLUDE_DIR}" )
else()
    message( "Please point the environment variable EIGEN3_INCLUDE_DIR to the include directory of your Eigen3 installation.")
endif()


add_executable(run_benchmark_matrix ${PROJECT_SOURCE_DIR}/benchmarks/benchmark_matrix.cpp)

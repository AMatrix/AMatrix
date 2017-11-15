include_directories("${PROJECT_SOURCE_DIR}/include")

find_package(Boost)

if( Boost_FOUND )
    message("BOOST_INCLUDE_DIRS : ${Boost_INCLUDE_DIRS}")
    add_definitions(-DAMATRIX_COMPARE_WITH_UBLAS)
    add_definitions(-DNDEBUG)
    include_directories ( "${Boost_INCLUDE_DIRS}" )
else()
    message( "Boost not found. In order to make comparison with ublas please define one of these macros:
        BOOST_ROOT        
        BOOST_INCLUDEDIR")
endif()


if( EIGEN3_INCLUDE_DIR )
    message("EIGEN3_INCLUDE_DIR : ${EIGEN3_INCLUDE_DIR}")
    add_definitions(-DAMATRIX_COMPARE_WITH_EIGEN)
    add_definitions(-DNDEBUG)
    include_directories ( "${EIGEN3_INCLUDE_DIR}" )
else()
    message( "Eigen not found. In order to make comparison with eigen please point the environment variable EIGEN3_INCLUDE_DIR to the include directory of your Eigen3 installation.")
endif()

add_executable(run_benchmark_matrix ${PROJECT_SOURCE_DIR}/benchmarks/benchmark_matrix.cpp)

install(TARGETS run_benchmark_matrix DESTINATION "${PROJECT_SOURCE_DIR}/build" )

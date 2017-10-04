include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(run_test_matrix_access ${PROJECT_SOURCE_DIR}/test/test_matrix_access.cpp)
add_test(MatrixAcessTest run_test_matrix_access COMMAND run_test_matrix_access)

add_executable(run_test_matrix_assign  ${PROJECT_SOURCE_DIR}/test/test_matrix_assign.cpp)
add_test(MatrixAssignTest run_test_matrix_assign COMMAND run_test_matrix_assign)

add_executable(run_test_matrix_plus  ${PROJECT_SOURCE_DIR}/test/test_matrix_plus.cpp)
add_test(MatrixPlusTest run_test_matrix_plus COMMAND run_test_matrix_plus)

add_executable(run_test_matrix_minus  ${PROJECT_SOURCE_DIR}/test/test_matrix_minus.cpp)
add_test(MatrixMinusTest run_test_matrix_minus COMMAND run_test_matrix_minus)
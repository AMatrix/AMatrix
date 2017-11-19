include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(run_test_matrix_access ${PROJECT_SOURCE_DIR}/test/test_matrix_access.cpp)
add_test(MatrixAcessTest run_test_matrix_access COMMAND run_test_matrix_access)

add_executable(run_test_matrix_assign  ${PROJECT_SOURCE_DIR}/test/test_matrix_assign.cpp)
add_test(MatrixAssignTest run_test_matrix_assign COMMAND run_test_matrix_assign)

add_executable(run_test_matrix_plus  ${PROJECT_SOURCE_DIR}/test/test_matrix_plus.cpp)
add_test(MatrixPlusTest run_test_matrix_plus COMMAND run_test_matrix_plus)

add_executable(run_test_matrix_minus  ${PROJECT_SOURCE_DIR}/test/test_matrix_minus.cpp)
add_test(MatrixMinusTest run_test_matrix_minus COMMAND run_test_matrix_minus)

add_executable(run_test_matrix_product  ${PROJECT_SOURCE_DIR}/test/test_matrix_product.cpp)
add_test(MatrixProductTest run_test_matrix_product COMMAND run_test_matrix_product)

add_executable(run_test_matrix_transpose  ${PROJECT_SOURCE_DIR}/test/test_matrix_transpose.cpp)
add_test(MatrixTransposetTest run_test_matrix_transpose COMMAND run_test_matrix_transpose)

add_executable(run_test_dynamic_matrix_access ${PROJECT_SOURCE_DIR}/test/test_dynamic_matrix_access.cpp)
add_test(DynamicMatrixAcessTest run_test_dynamic_matrix_access COMMAND run_test_dynamic_matrix_access)

add_executable(run_test_dynamic_matrix_assign ${PROJECT_SOURCE_DIR}/test/test_dynamic_matrix_assign.cpp)
add_test(DynamicMatrixAssignTest run_test_dynamic_matrix_assign COMMAND run_test_dynamic_matrix_assign)

add_executable(run_test_dynamic_matrix_minus ${PROJECT_SOURCE_DIR}/test/test_dynamic_matrix_minus.cpp)
add_test(DynamicMatrixMinusTest run_test_dynamic_matrix_minus COMMAND run_test_dynamic_matrix_minus)

add_executable(run_test_dynamic_matrix_plus ${PROJECT_SOURCE_DIR}/test/test_dynamic_matrix_plus.cpp)
add_test(DynamicMatrixPlusTest run_test_dynamic_matrix_plus COMMAND run_test_dynamic_matrix_plus)

add_executable(run_test_dynamic_matrix_product ${PROJECT_SOURCE_DIR}/test/test_dynamic_matrix_product.cpp)
add_test(DynamicMatrixProductTest run_test_dynamic_matrix_product COMMAND run_test_dynamic_matrix_product)

add_executable(run_test_dynamic_matrix_transpose ${PROJECT_SOURCE_DIR}/test/test_dynamic_matrix_transpose.cpp)
add_test(DynamicMatrixTransposeTest run_test_dynamic_matrix_transpose COMMAND run_test_dynamic_matrix_transpose)

install(
  TARGETS 
    run_test_matrix_access  run_test_matrix_assign  run_test_matrix_plus
    run_test_matrix_minus   run_test_matrix_product run_test_matrix_transpose
    run_test_dynamic_matrix_access run_test_dynamic_matrix_assign run_test_dynamic_matrix_minus
    run_test_dynamic_matrix_plus
  DESTINATION  
    "${PROJECT_SOURCE_DIR}/bin" 
  )
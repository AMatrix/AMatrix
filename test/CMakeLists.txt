include_directories("${PROJECT_SOURCE_DIR}/include")

function(add_amatrix_test TEST_SOURCE_FILE)
    get_filename_component(TEST_FILENAME ${TEST_SOURCE_FILE} NAME)
    string(REGEX REPLACE ".cpp" "" TEST_NAME ${TEST_FILENAME})
    message(STATUS  "adding ${TEST_NAME} ")
    add_executable(${TEST_NAME} ${TEST_SOURCE_FILE})
    add_test(${TEST_NAME} ${TEST_NAME})
    install(TARGETS ${TEST_NAME} DESTINATION "${PROJECT_SOURCE_DIR}/bin")
endfunction()

file(GLOB test_files "${PROJECT_SOURCE_DIR}/test/*.cpp")

foreach(test_file ${test_files})
  add_amatrix_test(${test_file})
endforeach(test_files)
